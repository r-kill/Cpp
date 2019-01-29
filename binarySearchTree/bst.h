// Author: Rowan Kill
// Due: 4/18/2018
// Purpose: This class implements a pointer-based binary search
//    tree that represents an ordered list. The tree can be
//    manipulated in the same manner as the list would be
//    manipulated and contains a number of functions to
//    recursively operate on the tree.
// Design: The class is designed to be used by a client in the
//    same way that an ordered list ADT would be used by a client.
//    The constructor creates an empty list, the nodes are
//    destroyed recursively with a private function. The tree is
//    printed recursively by traversing the tree inorder and
//    printing the nodes as they're visited. Present() iteratively
//    searches the tree for a given item number and returns true
//    if that item is in the tree, otherwise it returns false.
//    There are functions for finding the total value of all items
//    in the tree, for counting the number of items in the tree,
//    and for determining if the tree is empty or not. Finding
//    the total of the items in the tree and the number of items
//    in the tree is done recursively. Nodes can be inserted
//    and removed from a tree recursively as well. Removing nodes
//    required a total of three functions, one to call the
//    private recursive search function, which then calls the
//    private recursive remove_node() function when the specified
//    node is found in the tree. The tree can be operated on more
//    quickly than a typical list ADT. A tree works well for this
//    implementation of an ordered list because the tree can be
//    searched and sorted more quickly than searching an actual list.

#include <iostream>
#include <cstring>
using namespace std;

class BST
{
public:
	typedef int Item;

	// constructor
	// postcondition: Initializes an empty BST.
	BST() { root = NULL; }

	// destructor - calls private recursive destroy() to delete nodes
	// precondition: A BST object exists that must be deleted.
	// postcondition: The BST object and it's nodes are recursively
	//    deleted with the private destroy() function.
	~BST() { destroy(root); }

	// print_tree - calls the recursive print() to print nodes
	// precondition: The argument is an integer values that corresponds
	//    to an item number in the tree. If an integer is provided, then
	//    only items with that item value are printed, otherwise the
	//    entire tree is printed.
	// postcondition: If the tree is not empty, then the tree or a given
	//    item number in the tree is printed. If multiple items have the
	//    same ID, all are printed and they're first sorted by item number,
	//    then by price so that the duplicates are also sorted. The items
	//    are printed recursively by the private print_tree() function.
	void print(Item id=-1) { print_tree(root, id); }

	// present - search a tree to determine if an item is present
	bool present(Item target);

	// insert - call private recursive help_insert()
	// precondition: This function receives all of the values that will
	//    be used to create the new node that's inserted, then passes
	//    them to the recursive function that actually inserts the values.
	//    The size of the name attribute is also provided so it can be
	//    correctly stored in the character array. Three integer values
	//    are received to give the new node an item number and a quantity
	//    as well as specifying the number of characters in the name array,
	//    a double value represents the price, and a character array holds
	//    the name of the item.
	// postcondition: This function calls the  private recursive
	//    help_insert() function and passes it all of the argument
	//    provided to this function. The recursive function inserts
	//    the new item recursively.
	void insert(Item id, char name[], int nameSize, Item quantity, double price)
		{ help_insert(root, id, name, nameSize, quantity, price); }

	// remove - call private recursive help_remove()
	void remove(Item target);

	// total - sum the value of the items in the BST
	// precondition: This function doesn't have special requirements.
	// postcondition: The function calls the recursive r_total()
	//    that calculates the total value of all items in the tree.
	double total() { return r_total(root); }

	// length - calls private recursive function
	// precondition: This function doesn't have special requirements.
	// postcondition: The function calls the private find_length()
	//    function that recursively counts the number of nodes in the
	//    tree.
	int length() { return find_length(root); }

	// is tree empty?
	// precondition: This function doesn't have special requirements.
	// postcondition: The function returns true if the tree is empty,
	//    otherwise it returns false.
	bool empty() { return root == NULL; }

private:
	struct Node
	{
		int id;			// contains the item ID
		char name[10];		// item name (10 chars max)
		int quant;		// quantity of an item
		double price;		// price of item
		Node *left;		// contains pointer to the left subtree
		Node *right;		// contains pointer to the right subtree
	};
	Node *root;			// root of the tree

	// destroy a node recursively
	void destroy(Node *p);

	// print the tree recursively
	void print_tree(Node *p, Item id=-1);

	// insert a node into the tree recursively
	void help_insert(Node *&t, Item id, char name[], int nameSize, Item quantity, double price);

	// search for a node to remove using recursion
	// when a node is found to be removed, call recursive remove_node()
	void help_remove(Node *&t, Item target);

	// remove a node from the tree recursively
	void remove_node(Node *&t);

	// calculate the total value of all nodes
	double r_total(Node *p);

	// recursively find the length of the list represented by the tree
	int find_length(Node *p);
};

// present
// precondition: This function receives an integer value that
//    represents an item number for an item in the tree.
// postcondition: The function returns true if the provided
//    argument value exists in the tree, otherwise it returns
//    false.
bool BST::present(Item target)
{
	Node *p = root;	// traveling pointer

	// iteratively find the target value in the tree
	while (true)
	{
		if (p == NULL)
			// return false if tree is empty
			return false;
		else if (target < p->id)
			// search for target ID in left subtree
			p = p->left;
		else if (target == p->id)
			// return true if target ID is found
			return true;
		else // if(target > p->id
			// search for target ID in right subtree
			p = p->right;
	} // end while
}

// remove public function
// precondition: The argument represents the item number of
//    the item to be removed. It should be an integer.
// postcondition: If the tree isn't empty, this function calls
//    the private recursive help_remove() function which
//    searches the tree for the item to be removed.
void BST::remove(Item target)
{
	// ensure tree isn't empty before trying to remove anything
	if(!empty())
		help_remove(root, target);
}

// destroy
// precondition: This function receives a pointer to a node
//    in the tree as an argument, the tree can be empty.
// postcondition: This function recursively visits and deletes
//    each node in the subtrees of the argument node, then
//    deleted the node passed to the function. If the tree is
//    empty, then nothing needs to be deleted.
void BST::destroy(Node *p)
{
	// make sure list isn't already empty
	if (p != NULL)
	{
		// destroy nodes with postorder traversal
		destroy(p->left);
		destroy(p->right);
		delete p;
	} // end if
}

// print
// precondition: This function receives a pointer to a node
//    which is used to tell the function where to start printing.
//    An integer value is also received, this value can be a
//    default value or it can represent an item number that's
//    specified by the user.
// postcondition: This function prints the entire tree or a subset
//    of items that have a specified item number. Either way,
//    the items are printed in a table created with the iomanip
//    library. The nodes are traversed inorder. This function
//    replaces the report() function, it prints the item info of
//    the item specified by the argument value, if the items
//    doesn't exist in the list then an error message is presented
//    to the user. Instead of being a boolean function that returns
//    true/false if the item is/isn't present, the function will
//    or will not print the item info of the specified item to
//    represent true/false. If multiple items in the tree have the
//    same item number, then all of those items are printed. All
//    printing is done using recursion.
void BST::print_tree(Node *p, Item id)
{
	// ensure tree is not empty before printing
	// prints entire tree or just one node if item ID is specified
	if (p != NULL && id == -1)
	{
		// print nodes with inorder traversal
		print_tree(p->left);	// print left subtree

		// set up cout format with iomanip, then print current node
		cout << fixed << showpoint << setprecision(2);
		cout << " " << setw(4) << setfill('0') << p->id
		     << " " << setfill(' ') << setw(10) << p->name
		     << " " << setw(5) << p->quant
		     << setw(10) << p->price << endl;
		print_tree(p->right);	// print right subtree
	}
	else if (p != NULL && id != -1)
	{
		// check if specified item ID is present before printing
		if (present(id))
		{
			// move to the node with the specified item ID
			while (p->id != id)
				// search left and right subtrees as needed
				if (id < p->id)
					p = p->left;
				else // id > p->id
					p = p->right;

			// check both subtrees for duplicate item IDs,
			//    print all duplicates
			if (p->id == id && p->left != NULL)
				if(p->left->id == id)
					// check left subtree and print those duplicates
					print_tree(p->left, id);

			// set up cout format with iomanip, then print
			cout << fixed << showpoint << setprecision(2);
			cout << " " << setw(4) << setfill('0') << p->id
			     << " " << setfill(' ') << setw(10) << p->name
			     << " " << setw(5) << p->quant
			     << setw(10) << p->price << endl;

			if (p->id == id && p->right != NULL)
				if(p->right->id == id)
					// check right subtree and print those duplicates
					print_tree(p->right, id);
		}
		else
			// tell user that requested item was not found in tree
			cout << "  Item not found" << endl;
	} // end if else if
}

// help_insert
// precondition: This function receives a pointer that's passed
//    by reference so it can modify every node in the tree and
//    those modifications will maintain outside of the function.
//    Otherwise, the arguments represent the node attributes.
//    The integer values represent the item number, the number
//    of characters in the items name, and the quantity of that
//    item. The character array holds the name of the item. The
//    double value is the price of the item.
// postcondition: This function recursively finds the correct
//    spot in the tree to insert the node, then creates the node
//    and puts it in the tree. The new nodes are given the values
//    provided by the arguments. The left and right subtrees are
//    searched recursively to find the proper position for the new
//    node. This function also handles inserting duplicate values,
//    if the item to be inserted has the same item number and
//    price as the item currently being looked at in the search,
//    then the quantity of the new item is added to the quantity
//    of the existing item so no new items are created if they're
//    the same item. If two items have the same item number but
//    different prices, then the new item will be placed in the
//    existing items left or right subtree, recursively, such
//    that the duplicates are sorted by price among themselves,
//    after being sorted by item number among all items in the tree.
void BST::help_insert(Node *&t, Item id, char name[], int nameSize, Item quantity, double price)
{
	// if tree is empty, create root node with inserted value
	if (t == NULL)
	{
		t = new Node;
		t->id = id;
		t->quant = quantity;
		t->price = price;
		t->left = NULL;
		t->right = NULL;

		// reset t->name to prevent overlap - problem
		for(int i = 0; i < 10; ++i)
			t->name[i] = '\0';

		// secure function so windows compiler isn't upset about security
		// windows wanted strncpy_s(), doesn't work for g++
		strncpy(t->name, name, nameSize);
		//// ANOTHER METHOD - can replace strncpy_s() when uncommented
		//for (int i = 0; i < 10; ++i)
		//	// ensure name is the proper size and the
		//	//    name array is fully initialized
		//	if (i < nameSize)
		//		t->name[i] = name[i];
		//	else
		//		// initialize empty part of name array with ' '
		//		t->name[i] = ' ';
	}
	else if (id < t->id)
		// find a place in the left subtree to insert node
		help_insert(t->left, id, name, nameSize, quantity, price);
	else if (id == t->id && price == t->price)
		// if the item already exists in the list with the same
		//    price and ID, just increase the quant of that item
		t->quant += quantity;
	else if(id == t->id && price < t->price)
		// if the item already exists but at a higher price, put
		//    the new duplicate item in the left subtree to sort
		//    by price
		// don't need to worry about when price > t->price because
		//    that's caught by the else clause
		help_insert(t->left, id, name, nameSize, quantity, price);
	else // entry > t->id
		// find a place in the right subtree to insert node
		help_insert(t->right, id, name, nameSize, quantity, price);
}

// help_remove
// precondition: This function receives a pointer that's passed by
//    reference so it can pass that argument to another function
//    that actually deletes nodes in the tree. This function also
//    receives an integer value that represents the item number of
//    the node to be removed.
// postcondition: This function recursively searches the tree for
//    the node with the item number provided in the arguments, if
//    that node is found the remove_node() function is called to
//    remove it and adjust the tree.
void BST::help_remove(Node *&t, Item target)
{
	// ensuring the tree isn't empty and handles removing
	//    IDs that aren't in the tree
	if (t != NULL)
	{
		// search tree to find target,
		// then call remove_node() to delete it
		if (t->id == target)
			// if target found in current node, delete it
			remove_node(t);
		else if (target < t->id)
			// if target will be in left subtree, search there
			help_remove(t->left, target);
		else // target >  t->id
			help_remove(t->right, target);
	} // end if
}

// remove_node
// precondition: This function receives a pointer that's passed by
//    reference so it's able to delete the root node and change
//    the tree to maintain order after removing a node.
// postcondition: This function removes a node from the tree and
//    fixes the tree to maintain order and shape after deleting a
//    node. If the node to delete has one child, then the node is
//    deleted and the parent of the deleted node will point to the
//    child of the deleted node, so the tree is re-routed around
//    the deleted node to its child. If the node to be deleted has
//    two children, then the function assigns a pointer to the node
//    to be deleted and finds the leftmost node in the right
//    subtree of the node to be deleted. The node to be deleted is
//    then overwritten by the leftmost node in the right subtree of
//    the node to be deleted. After the node is overwritten, any
//    subtrees of that node are traversed and adjusted to match the
//    new value in the parent node. This last step is done recursively.
void BST::remove_node(Node *&t)
{
	Node *ptr, *back;

	// determine how node should be deleted
	if (t->left == NULL && t->right == NULL)
	{
		// if target is found in a LEAF
		delete t;
		t = NULL;
	}
	else if (t->left == NULL)
	{
		// if target is found in a node with one child on the right
		ptr = t;
		t = t->right;
		delete ptr;
	}
	else if (t->right == NULL)
	{
		// if target is found in a node with one child on the left
		ptr = t;
		t = t->left;
		delete ptr;
	}
	else // target has two children, neither subtree is empty
	{
		// search the tree, go right one node and then as far left
		//    as possible to find the value immediately after the
		//    target value in the list
		back = t;
		ptr = t->right;	// one step right

		// go left as far as possible
		while (ptr->left != NULL)
		{
			// advance pointers that track position in tree
			back = ptr;
			ptr = ptr->left;
		} // end while

		// overwrite target value
		t->id = ptr->id;
		t->quant = ptr->quant;
		t->price = ptr->price;

		// copy ptr->name to t->name
		// can be done iteratively, see help_insert()
		// secure function so windows compiler isn't upset about security
		strncpy(t->name, ptr->name, sizeof(ptr->name));

		// ptr->id will now appear in tree twice, so we need to
		//    remove it, considering when the right subtree does
		//    and doesn't have left children to match the search
		if (back == t)
			// if the right child has no left child
			remove_node(back->right);
		else
			// right child does have a left child
			remove_node(back->left);
	} // end outer if else if
}

// total
// precondition: This function receives a pointer to a node in
//    the tree, this determines the starting node of the function.
//    If the argument isn't the root node, then the function
//    finds the total value of all items in the tree that are
//    below that specified node.
// postcondition: This function recursively traverses the tree
//    using a postorder traversal. Visiting each node involves
//    returning the product of the items quantity multiplied by
//    its price, this value is returned to the previous function
//    instance and is added to a running sum. When the final
//    instance finished execution, the total sum is returned.
//    If the tree is empty, then the total value of the items
//    in the tree is zero and that value's returned.
double BST::r_total(Node *p)
{
	// holds the sum on the (quant * price) for each item
	double sum = 0;

	// check for an empty tree
	if (p == NULL)
		return 0;
	else
	{
		// recursively get the sum of the values - postorder traversal
		sum += r_total(p->left);
		sum += r_total(p->right);
		return sum += p->price * p->quant;
	} // end if else
}

// find_length
// precondition: This function received a pointer to a node in the
//    tree, this is used to tell the function where to start counting
//    the number of items in the tree. This item should usually be
//    the root node, but if it's not then the length of the tree
//    will be the length of the tree under the specified node
//    only, this value will exclude any parent nodes of the specified
//    node.
// postcondition: This function recursively traverses the tree with
//    an inorder traversal. If the tree is empty, the function
//    returns zero because there are zero nodes in the tree. Otherwise
//    nodes in the left subtree are counted, then the root node
//    (determined by the argument) is counted, then the nodes in
//    the right subtree are counted.
int BST::find_length(Node *p)
{
	// get the lengths of the left and right subtrees, sum them
	// add one to that sum to count the root node
	if (p == NULL)
		// return 0 if tree is empty
		return 0;
	else
		// recursively find length with inorder traversal
		return find_length(p->left) + 1 + find_length(p->right);
} 
