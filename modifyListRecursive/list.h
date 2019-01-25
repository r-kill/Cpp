// Author: Rowan Kill
// Due: 2/27/2018
// Purpose: This class implements a linked list that can be manipulated with a
//    number of member functions. The member functions should use recursion
//    whenever possible.
// Design: The class overloads specific operators and the copy constructor in
//    order to implement a data type that feels natural to use, such as printing
//    out a lists nodes. The overloaded copy constructor receives a source list
//    to copy values from and passes that to a recursive function that traverses
//    the list and creates a new list. The destructor must delete the nodes in a
//    list, which aren't members of the class so they need to be explicitly
//    deleted. The make_empty() function is a copy of the destructor that can be
//    called explicitly in order to force a list to be empty. This function is
//    public and calls the private recursive function that actually deletes the
//    nodes. The insert() function receives a value from the user and passes that
//    value when it calls the recursive insert function which inserts values into
//    a list, the list should not already contain that value and no duplicate
//    values can be inserted. The insertion process involves keeping track of two
//    nodes so the value can be inserted in correct ascending order. The remove()
//    function receives a value, calls the recursive remove function and passes it
//    that value which will be removed from a list if it exists. The empty() function
//    returns true or false depending on whether the list is empty or not. Length()
//    calls the recursive length function and passes it a pointer to the first node
//    in the list, it then returns the length of the list by traversing the nodes in
//    the invoking list and incrementing a "counter" for each node that's traversed
//    by returning 1 for each recursive iteration. The present() function receives
//    that should be searched for in the list and then passes that Item when it
//    calls the recursive present function that returns true or false if the
//    argument value is found to exist in an Item the invoking list or not by
//    recursively searching the list. The kth() function receives an integer value
//    that represents the node number in the invoking list that will be returned.
//    It passes that value to the recursive kth function that actually traverses
//    the list and returns the value of the kth node. The "<<" operator overload
//    function is used to print the nodes in a list and returns an output stream.
//    The function receives an output stream and a list to print, which it passes
//    to the recursive write function when it's called. The recursive function
//    must be static for this case. Nodes are declared as a struct that contains
//    data and a pointer to the next node in the list. There's also a pointer in
//    this class that points to the first node within a list. The get_node() function
//    is used to create a single node and supply it with data and a pointer to the
//    next node in the list, then the function returns the address of that node.
//    All of the recursive functions are private and require a pointer to a node
//    in the list so it can be traversed.

using namespace std;

class List
{
public:
	// specify a new Item data type that can be used throughout the program
	typedef int Item;

	// constructor and destructor
	List() { first = NULL; }	// default constructor initializes an empty list
	~List();			// destructor

	// calls recursive copy constructor
	List(const List& source) { r_copier(source, source.first, first); }

	// returns true if the list is empty, false otherwise
	bool empty();

	// postcondition: This function calls the recursive function that
	//    empties the list and provides it with a pointer to the first
	//    node in the list.
	void make_empty() { r_make_empty(first); }

	// precondition: This function receives an Item value from the user
	//    and passes it, along with a pointer to the first node in the
	//    list, to the recursive function that inserts the value into the
	//    list.
	// postcondition: There is no output, but the recursive function
	//    inserts the value into the list in ascending order.
	void insert(Item value) { r_insert(first, value); }

	// precondition: This function receives a target value from the user,
	//    this is the value that the user wants to remove from the list.
	// postcondition: The function has no output, it calls the recursive
	//    remove function and passes it a pointer to the first node in the
	//    list and the value to be removed from the list.
	void remove(Item target) { r_remove(first, target); }

	// postcondition: This function calls the recursive length function
	//    and passes it a pointer to the first node in the list, that
	//    function determines the length of the list and returns that
	//    integer value.
	int length() { return r_length(first); }

	// precondition: This function receives an integer value from the user.
	//    That value should be at most as large as the length of the list.
	//    The function assumes the list has values in it.
	// postcondition: This function has no output, it calls the recursive
	//    kth function and passes it a pointer to the first node in the
	//    list along with the integer value provided by the user.
	Item kth(int k) { return r_kth(first, k); }

	// precondition: This function receives a target value to search for in a list.
	// postcondition: The target value is passed to the recursive present
	//    function along with a pointer to the first node in the list. That
	//    function returns true if the target is found in the list, but
	//    this function has no output.
	bool present(Item target) { return r_present(first, target); }

	// friend function writes the list to the console - overloads << operator
	// precondition: This function receives the output stream and the list
	//    object that should be printed to the output stream.
	// postcondition: Those arguments are passed to the recursive r_write
	//    function that sends each node in the list to the output stream.
	//    This function returns the output stream.
	friend ostream& operator<<(ostream& out_s, List list)
	{
		// call private recursive function and return the output stream
		r_write(out_s, list.first);
		return out_s;
	}

private:
	// data for each item node in the list
	struct Node
	{
		Item data;	// the data that's stored in a node
		Node *next;	// pointer to the next node in the list
	};

	// pointer to the first node in the list
	Node *first;

	// private member function - initializes new node, returns its address
	Node *get_node(Item data, Node *link);

	// recursive member functions
	int r_length(Node *p);		         // returns the length of the list
	void r_insert(Node *&p, Item value);	 // inserts value in ascending order
	void r_remove(Node *&p, Item target);    // removed target value from list
	bool r_present(Node *p, Item target);    // returns true if target value is in list
	Item r_kth(Node *p, int k);		 // returns data in the kth node in list
	void r_make_empty(Node *&p);		 // reinitializes a list to be empty

	// recursive copy constructor, assign values from oldList to newList
	void r_copier(const List& source, const Node *p, Node *last);

	// recursively write data in the nodes of a list to an output stream
	// this must be static in order to be called by the friend function
	//    for operator<< (insertion operator)
	static void r_write(ostream& out_s, Node *p);
};

// C++ automatic copy constructor and assignment operator only copy data
//    members of one class object to another. We define our own because
//    nodes aren't data members of the list class, only the pointer to the
//    first node in a list object is a data member. This means that the
//    nodes themselves need to be copied from the original list, which is
//    what we add to the copy constructor helper
// precondition: This function receives a list as a constant argument
//    that's passed by reference so the values of the argument list can be
//    accessed properly. The values in the argument list are used to create
//    a new list. The values in the list are expected to be of type Item.
//    The list is traversed using the other arguments, which are both traveling
//    pointers. The p pointer traverses the source list and the last pointer
//    traverses the invoking list. The last pointer points to the node
//    immediately before the node that p points at in their respective lists.
//    Both pointers are expected to point to the first node in their
//    respective lists.
// postcondition: The constructor doesn't return anything, but it initializes
//    a new list with values obtained from another list recursively.
void List::r_copier(const List& source, const Node *p, Node *last)
{
	// check if source is empty
	if (source.first == NULL)
		first = NULL;

	// ensure end of list hasn't been reached
	if (p != NULL)
	{
		// create the first node
		if (p->data == source.first->data)
		{
			// set first node to source.first->data
			first = get_node(p->data, NULL);

			// advance traveling pointer
			p = source.first->next;

			// second traveling pointer starts at the first node
			//    and is one node behind p
			last = first;

			// recursive call
			r_copier(source, p, last);
		}
		else
		{
			// append new node to the new list
			last->next = get_node(p->data, NULL);

			// advance pointer to current last node
			last = last->next;

			// advance traveling pointer to next node
			p = p->next;

			// recursive call
			r_copier(source, p, last);
		} // end nested if else
	} // end if
}

// destructor
// precondition: This function doesn't use any parameters.
// postcondition: The list of the object that invoked this function
//    will be made empty by deleting all of the nodes in the list.
List::~List()
{
	// recursively delete the nodes in the list
	// list is traversed from head to tail and back
	if(first != NULL)
		// delete the next node in the list until the last node is
		//    reached
		delete r_make_empty(first);
}

// makes the list an empty list
// precondition: This function receives a pointer to the first
//    node in the list as an argument. The pointer should be
//    passed by reference.
// postcondition: The invoking list object will be made empty by
//    deleting all of the nodes in the list from head to tail.
void List::r_make_empty(Node *&p)
{
	Node *temp;	// holds node to be deleted

	// delete nodes from first to last
	if(p != NULL)
	{
		// point temp to first node to be deleted (first node in list)
		temp = p;

		// advance p
		p = p->next;

		// delete node pointed to by temp
		delete temp;

		// advance down list
		r_make_empty(p);
	} // end if
}

// determine if an item is in the list
// precondition: This function receives an Item value to
//    search for in the invoking list. A pointer to a node in
//    the list is required so the function has a place to
//    start the search.
// postcondition: The function returns true if the Item argument
//    value is in the list and false if it's not in the list.
bool List::r_present(Node *p, Item target)
{
	// return false if the end of the list is reached before target is found
	if (p == NULL)
		return false;
	else if (p->data == target)
		// return true if target is found
		return true;
	else
		// if target isn't found before the end of the list, then
		//    look at the next node in the list recursively
		return r_present(p->next, target);
}

// return the kth item in the list
// precondition: Assumes that the list is not empty and
//    that the integer argument is 0 < k < list.length().
//    The argument values should be a pointer to a node in
//    a list and an integer. The node pointer gives the
//    function a place to start the search, this is expected
//    to be the first node in the list.
// postcondition: This function returns the data value from
//    the kth node in the invoking list.
List::Item List::r_kth(Node *p, int k)
{
	// ensure the current node isn't NULL
	// ensure k isn't equal to 0, when print the data in the node when k == 0
	//    because that's the kth node in the list
	if (p != NULL && k != 0)
		return r_kth(p->next, --k);
	else
		return p->data;
}

// insert a value into a list
// precondition: This function receives an Item value to insert
//    into a list in ascending order. No duplicate values are added
//    to the list. The target value should be an Item. The function
//    also receives a pointer to a node in the list that's used to
//    recursively search the list for the proper insertion point for
//    the target value. The pointer should be passed by reference.
// postcondition: This function doesn't return anything, it
//    inserts the target value into the list in the appropriate
//    order.
void List::r_insert(Node *&p, Item value)
{
	// return if value is already in list
	if (present(value))
		return;

	// ensure the current node isn't NULL and that the insert value
	//    is less than the value is the current node
	if (p == NULL || value < p->data)
		// create node with the value to be inserted
		p = get_node(value, p);
	else
		// search for the proper insertion point in the list recursively
		r_insert(p->next, value);
}

// remove an item from the list
// precondition: The Item argument value is the value to remove from a list,
//    if the value isn't present in the list the this function just returns.
//    The target value should be an Item type. The Node argument is used to
//    recursively search the list for the target value. The pointer should
//    be passed by reference.
// postcondition: The function doesn't return anything, but the invoking
//    list won't contain the target value anymore, if it was in the list
//    to begin with.
void List::r_remove(Node *&p, Item target)
{
	// traveling pointer that will point to the node that's deleted
	Node *temp;

	// check if target value is in list, return if not present
	if (!present(target))
		return;

	// if target is found
	if (p->data == target)
	{
		// point temp to target
		temp = p;

		// advance pointer that searches for the target
		p = p->next;

		// delete the target node
		delete temp;
	}
	else
		// check the next node recursively
		r_remove(p->next, target);
}

// private write function
// precondition: This function receives the output stream and a
//    pointer to a node in a list. The list is searched recursively
//    and the values in each node are sent to the output stream.
//    The output stream should be passed by address.
// postcondition: This function sends data to an output stream so
//    it prints to the console.
void List::r_write(ostream& out_s, Node *p)
{
	// don't do anything if the pointer is null
	if (p != NULL)
	{
		// print the data value in the node with a comma unless the node
		//    is the last node in the list - prevents trailing comma (1, 2,)
		p->next != NULL ? out_s << p->data << ", " : out_s << p->data << ' ';

		// recursively advance to the next node in the list
		r_write(out_s, p->next);
	} // end if
}

// return the length of the list
// precondition: This function receives a pointer to a node in the list as
//    an argument, this should point to the first node in the list. The
//    pointer is used to traverse the list.
// postcondition: This function returns the number of nodes
//    that exist in the invoking list.
int List::r_length(Node *p)
{
	// return the length of the list
	if (p == NULL)
		// return 0 if the list is empty
		// or if end of list reached
		return 0;
	else
		// recursive call
		return 1 + r_length(p->next);
}

// check if the list is empty
// postcondition: This function returns true if the list is empty and
//    false if it's not. Emptiness is determined by checking the value
//    of the pointer to the first node in the list.
bool List::empty()
{
	// if first == NULL, then the list is empty so true is returned
	return (first == NULL);
}

// initialize a new node and return its address
// precondition: This function creates a single node in a list, the
//    argument values determine the new nodes data value and where the
//    new node should point.
// postcondition: This function returns the address of the new node
//    that was created.
List::Node *List::get_node(Item value, Node *link)
{
	Node *temp;		// points to a node that will be added to a list
	temp = new Node;	// create a new node
	temp->data = value;	// store value argument in data field of new node
	temp->next = link;	// determines where new node should point, can be NULL
	return temp;		// return the new node
}
