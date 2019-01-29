// Author: Rowan Kill
// Due: 3/21/2018
// Purpose: This class implements a stack data structure that
//    can be used by a client, the stack contains integer values.
// Design: Using a linked list allows the stack to hold a dynamic
//    number of values. Values are pushed onto the stack and
//    popped off the stack as needed. Underflow is considered by
//    this implementation and there's no need for this class to
//    consider overflow because it's a linked list. When an item
//    is pushed onto the stack, a new node is created and put on
//    top of any previous nodes in the stack. Popping an item off
//    the stack deletes the top node on the stack and returns the
//    value that was contained in that node, the top of the stack
//    is adjusted to accommodate these changes. The nodes on the
//    stack should contain integer values that represent an
//    operator or a single-digit integer operand. The stack can be
//    checked for a pattern that's used to perform operations on
//    the stack values, that pattern is one operator under two
//    operands and all three values are at the top of the stack,
//    with one of the operands being the top item on the stack.

using namespace std;

// pointer-based stack
class Stack
{
public:
	typedef int Item;

	// constructor
	// precondition: The function doesn't accept arguments.
	// postcondition: Initializes an empty stack object with no Nodes.
	Stack() { top = NULL; depth = 0; }

	~Stack();				// destructor
	void push(Item entry, bool is_value);	// push
	Item pop();				// pop

	// size
	// precondition: This function expects the Stack object
	//    to be initialized.
	// postcondition: Returns the length of the list, an
	//    empty list will return 0.
	int size() { return depth; }

	// is empty?
	// precondition: This function doesn't accept arguments.
	// postcondition: Returns true if the list is empty,
	//    false otherwise.
	bool empty() { return top == NULL; }

	// check for pattern of first three values on top of the stack
	// pattern will look like this in stack:
	// | 3 |
	// | 2 |
	// | - |
	// ##### BOTTOM OF STACK
	// result will be 2 - 3 = -1 (in that order)
	bool check();
private:
	// Node type
	struct Node
	{
		Node *next;		// pointer to next Node in Stack
		Item data;		// data in Node
		bool is_value;		// true if data in Node is an operator
	};

	Node *top;	// pointer to top of stack
	int depth;	// number of items in stack
};

// destructor
// precondition: This function expects the Stack object to be
//    initialized.
// postcondition: The Nodes in the Stack object will be deleted
//    and the Stack will be empty.
Stack::~Stack()
{
	// delete all Items on the stack
	while (depth != 0)
	{
		Node *temp = top;	// traveling pointer points to top of stack
		top = top->next;	// advance pointer to the new top of the stack
		delete temp;		// delete top Item
		--depth;		// adjust counter of the number of items on stack
	} // end while
}

// push
// precondition: This function expects an integer value for the entry
//    argument and a Boolean value for the is_value argument. Entry will
//    be put on top of the Stack, is_value determines if the entry value
//    is an operator or an operand. All entry values are ASCII decimal
//    representations of either an operator or operand, operands are
//    converted to their numeric values before going onto the Stack.
//    Operators are not changed when they're pushed onto the Stack.
//    Operands should be single digit numbers.
// postcondition: Entry is pushed on top of the Stack by creating a new
//    Node with entry as data and pointing it to was used to be the top
//    of the Stack, then making this new Node the new top of the Stack.
//    The number of values in the Stack is tracked with a counter.
void Stack::push(Item entry, bool is_value)
{
	Node *temp;		// points to a node that will be added to a list
	temp = new Node;	// create a new node
	temp->next = top;	// determines where new node should point

	// determines if entry is an operator or operand
	temp->is_value = is_value;

	// store entry in data field of new node
	// convert integers from ASCII value to numeric
	// value or just push ASCII value of operators
	temp->data = is_value ? entry - '0' : entry;

	top = temp;	// assign top to new node
	++depth;	// increment depth
}

// pop
// precondition: This function assumes that the Stack object is not empty.
// postcondition: The top Node on Stack is deleted and the value it
//    contained is returned. The top of the Stack is adjusted as well.
Stack::Item Stack::pop()
{
	if (depth > 0)
	{
		Node *temp;			// traveling pointer
		Item popped = top->data;	// holds Item that's on top of stack
		temp = top;			// temp points to top of stack
		top = top->next;		// advance pointer to new top item on stack
		delete temp;			// delete top Item
		--depth;			// track the number of items on the stack
		return popped;
	} // end if
}

// check
// precondition: The Stack object should have at least three Nodes,
//    otherwise the pattern cannot exist in the Stack. The Nodes
//    should contain integer values along with the appropriate Boolean
//    value. The Boolean value is used to check for the pattern.
// postcondition: Returns true of false depending on the top three
//    values in the Stack, if two operands are found to exist on top
//    of an operator then the pattern exists and true is returned.
bool Stack::check()
{
	// ensure stack is not empty
	if (!empty())
	{
		// return false (meaning pattern is not present) if
		//    top Item is not a digit or
		//    next Item is not a digit or
		//    third Item IS a digit
		if (!top->is_value || !top->next->is_value ||
			top->next->next->is_value)
			return false;
		else
			return true;
	} // end outer if
}
