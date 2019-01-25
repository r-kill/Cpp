// Author: Rowan Kill
// Due: 2/15/2018
// Purpose: This class implements a linked list that can be manipulated with a
//    number of member functions.
// Design: The class overloads specific operators and the copy constructor in
//    order to implement a data type that feels natural to use, such as printing
//    and assignment. The copy constructor paired with the overloaded assignment
//    operator allow lists to be assigned to new lists. The destructor must delete
//    the nodes in a list, which aren't members of the class so they need to be
//    explicitly deleted. The make_empty() function is a copy of the destructor
//    that can be called explicitly in order to force a list to be empty. The
//    insert() function allows values to be inserted into a list, the list should
//    not already contain that value and no duplicate values can be inserted. The
//    insertion process involves keeping track of two nodes so the value can be
//    inserted in correct ascending order. The remove() function is passed a value
//    that should be removed from a list if it exists in that list. The empty()
//    function returns true or false depending on whether the list is empty or not.
//    Length() returns the length of the list by traversing the nodes in the invoking
//    list and incrementing a counter for each node that's traversed. The present()
//    function returns true or false if the argument value is found to exist in
//    the invoking list or not. The kth() function receives an integer value that
//    represents the node number in the invoking list that will be returned.
//    This function returns the value of the kth node in a list. The "<<" operator
//    overload function is used to print the nodes in a list and returns an
//    output stream. Nodes are declared as a struct that contains data and a
//    pointer to the next node in the list. There's also a pointer in this class
//    that points to the first node within a list. The get_node() function is
//    used to create a single node and supply it with data and a pointer to the
//    next node in the list, then the function returns the address of that node.

using namespace std;

class List
{
public:
	// specify a new Item data type that can be used throughout the program
	typedef int Item;

	// constructors and destructors
	// inline function below
	List() { first = NULL; }	// default constructor initializes an empty list
	List(const List& source);	// copy constructor copies oldList to newList
	~List();			// destructor

	// member functions that modify the list object
	void make_empty();
	void insert(Item value);
	void remove(Item target);
	void operator=(List source);

	// constant member functions
	bool empty();			// returns true if the list is empty
	int length();			// returns the length of a list - number of nodes
	bool present(Item target);	// determines if target’s present in a list object
	Item kth(int k);		// return the kth item in a list

	// friend function writes the list to the console - overloads << operator
	friend ostream& operator<<(ostream& out_s, List list);

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
};

// copy constructor - copies contents of one list to another
// C++ automatic copy constructor and assignment operator only copy data
//    members of one class object to another. We define our own because
//    nodes aren't data members of the list class, only the pointer to the
//    first node in a list object is a data member. This means that the
//    nodes themselves need to be copied from the original list, which is
//    what we add to the copy constructor
// precondition: This function receives a list as a constant argument
//    that's passed by reference so the values of the argument list can be
//    accessed properly. The values in the argument list are used to create
//    a new list. The values in the list are expected to be integers.
// postcondition: The constructor doesn't return anything, but it initializes
//    a new list with values obtained from another list.
List::List(const List &source)
{
	Node *p;	// traveling pointer
	Node *last;	// pointer to last node in the list

	// copy source list to new list
	if (source.first == NULL)
		// if the source list is empty, make new list empty
		first = NULL;
	else
	{
		// set first node in new list to data in first
		//    node of source list
		first = get_node(source.first->data, NULL);

		// advance pointer down list
		p = source.first->next;

		// update last so it points to the current
		//    last node in the new list
		last = first;

		// copy nodes from source until the last node in the
		//    source list is encountered
		while (p != NULL)
		{
			// append new node to the new list
			last->next = get_node(p->data, NULL);

			// advance pointer to current last node
			last = last->next;

			// advance traveling pointer to next node
			p = p->next;
		} // end nested while
	} // end if else
}

// destructor
// precondition: This function doesn't use any parameters.
// postcondition: The list of the object that invoked this function
//    will be made empty by deleting all of the nodes in the list.
List::~List()
{
	Node *temp;	// holds node to be deleted

	// delete nodes from first to last
	while (first != NULL)
	{
		// point temp to first node to be deleted (first node in list)
		temp = first;

		// advance first to next node in list
		first = first->next;

		// delete node pointed to by temp
		delete temp;
	} // end while
}

// makes the list an empty list - same code as destructor
// precondition: This function doesn't use any parameters, it does the
//    same job as ~List() but can be called explicitly.
// postcondition: The invoking list object will be made empty by
//    deleting all of the nodes in the list from head to tail.
void List::make_empty()
{
	Node *temp;	// holds node to be deleted

	// delete nodes from first to last
	while (first != NULL)
	{
		// point temp to first node to be deleted (first node in list)
		temp = first;

		// advance first to next node in list
		first = first->next;

		// delete node pointed to by temp
		delete temp;
	} // end while
}

// overloading assignment operator (=) to handle lists
//    related to copy constructor
// precondition: This function receives a list as an argument,
//    it will be used to copy values from one list into a new
//    list that was initialized by the copy constructor. The
//    list should contain integer values.
// postcondition: This function, along with the copy constructor,
//    initializes a new list and copies values from the source
//    list to this new list.
void List::operator=(List source)
{
	Node *p;	// traveling pointer
	Node *last;	// points to last node in list

	// check for self-assignment, make sure source addr != invoker addr
	//    invoker is list3 in the expression: list3 = list1;
	//    list3 = invoking/implicit parameter that's not in the prototype
	//    list1 = explicit parameter that IS in the function prototype
	//    &source returns the address of the source object
	//    "this" keyword refers to the address of the invoking object
	if (&source != this)
	{
		// empty the list so it can accept new
		//    values from explicit param
		make_empty();

		// make sure source list isn't empty
		if (source.first != NULL)
		{
			// set first node in new list to data in
			//    first node of source list
			first = get_node(source.first->data, NULL);

			// advance pointer down list
			p = source.first->next;

			// update last so it points to the current
			//    last node in the new list
			last = first;

			// copy nodes from source until the last node in the
			//    source list is encountered
			while (p != NULL)
			{
				// append new node to the new list
				last->next = get_node(p->data, NULL);

				// advance pointer to current last node
				last = last->next;

				// advance traveling pointer to next node
				p = p->next;
			} // end nested while
		} // end nested if
	} // end if
}

// determine if an item is in the list
// precondition: This function receives an integer value to
//    search for in the invoking list.
// postcondition: The function returns true if the argument
//    value is in the list and false if it's not in the list.
bool List::present(Item target)
{
	// traveling pointer initialized to the first node in the list
	Node *p = first;

	// move p down list until target value or end of the list are found
	//    condition is short-circuit so the order matters
	while (p != NULL && p->data != target)
		p = p->next;

	// return false or true when p points to the last node or the target
	return (p != NULL);
}

// return the kth item in the list
// precondition: Assumes that the list is not empty and
//    that the argument is 0 < k < list.length(). The argument
//    value should be an integer.
// postcondition: This function returns the data value from
//    the kth node in the invoking list.
List::Item List::kth(int k)
{
	// traveling pointer pointing to first node in list
	Node *p = first;

	// advance pointer down list k-1 times
	for (int i = 0; i < k; ++i)
		p = p->next;

	// return data at node that p points to after loop
	return p->data;
}

// insert a value into a list
// precondition: This function receives a value to insert into
//    a list in ascending order. No duplicate values are added
//    to the list. The target value should be an integer.
// postcondition: This function doesn't return anything, it
//    inserts the argument value into the list in the appropriate
//    order.
void List::insert(Item value)
{
	Node *prev;	// points to the node BEFORE the inserted node

	// return if value is already in list
	if (present(value))
		return;

	// if list is empty or the inserted item is inserted as the first
	//    node in the list
	if (first == NULL || value < first->data)
		// set first node to value of new node with inserted value and
		//    point new node to where first used to point
		first = get_node(value, first);
	else
	{
		prev = first;	// start looking for insertion point from first node

		// look ahead at next node in list to determine if prev can advance
		// verify that the next node isn't the end of the list and
		//    that the data value in the next node is less than the
		//    value to be inserted (insert int before nodes with larger
		//    data values and after nodes with smaller data values)
		while (prev->next != NULL && prev->next->data < value)
			prev = prev->next;

		// insert value after smaller node and make it point to the
		//    node that the smaller node used to point to
		prev->next = get_node(value, prev->next);
	} // end if else
}

// remove an item from the list
// precondition: The argument value is the value to remove from a list,
//    if the value isn't present in the list the this function just returns.
//    The target value should be an integer.
// postcondition: The function doesn't return anything, but the invoking
//    list won't contain the argument value anymore, if it was in the list
//    to begin with.
void List::remove(Item target)
{
	Node *prev = first;	// start looking for target at first node
	Node *temp;			// points to node to be deleted

	// check if target value is in list, return if not present
	if (!present(target))
		return;

	// check if target to remove is first node
	// handles lists with only 1 element that happens
	//    to be the target, makes the list an empty list
	if (first->data == target)
	{
		// advance first down list because original
		//    first node is being removed
		first = first->next;

		// delete target node (first node in this case)
		delete prev;
	}
	else
	{
		// advance prev until target value is found by
		//    looking ahead at next node
		while (prev->next->data != target)
			prev = prev->next;

		// once target is found, assign temp to that node
		temp = prev->next;

		// advance prev so it points to the node AFTER
		//    the target node
		prev->next = temp->next;
		delete temp;
	} // end if else
}

// overload the << operator to write the list to the console
// precondition: The parameters for this function represent the operands
//    in an expression such as "cout << a" where cout is an output stream
//    (out_s) and a is the item to be sent to the output stream. In this
//    case, that item is a list so they can be printed.
// postcondition: The list is printed to the console by sending the data
//    items in each node to the output stream argument along with a space
//    character. When all of the nodes in the list are sent, the output
//    stream is returned. This allows the use of successive << operators
//    (cout << a << b << c),
ostream& operator<<(ostream& out_s, List list)
{
	// this function is NOT a member function of List class so the
	//    scope of the Node type needs to be explicitly defined with
	//    the scope operator (::)
	List::Node *p;	// traveling pointer

	// point p at the first node in the list argument
	p = list.first;

	// output list until the last node is encountered
	while (p != NULL)
	{
		// send "nodeData, " (notice the comma and space in
		//    that string, if value is last value in list then
		//    comma is not printed) to any output stream,
		//    meaning this works with console, files, etc.
		p->next != NULL ? out_s << p->data << ", " : out_s << p->data << ' ';

		// advance pointer down list to print the data value
		//    in the next node
		p = p->next;
	} // end while

	// return the data from the list as an output stream
	return out_s;
}

// return the length of the list
// postcondition: This function returns the number of nodes
//    that exist in the invoking list.
int List::length()
{
	// traveling pointer initialized to first pointer in list
	Node *p = first;

	// counts the nodes in the list
	int count = 0;

	// count the nodes
	while (p != NULL)
	{
		++count;
		p = p->next;
	} // end while

	// return number of nodes
	return count;
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
