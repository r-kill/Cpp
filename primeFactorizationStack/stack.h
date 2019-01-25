// Author: Rowan Kill
// Due: 3/13/2018
// Purpose: This class implements a stack data structure that can
//    be used by a client.
// Design: The stack is designed to hold 100 integer values, they
//    are pushed onto the stack and can be popped off the stack.
//    Overflow and underflow are considered in these cases. Pushing
//    an Item onto the stack appends it to the data array, popping
//    an Item off the stack returns the value of the Item on top
//    of the stack and decrements the used variable. Decrementing
//    used when popping is done so the top index can be overwritten
//    as needed, the values aren't actually deleted from the stack.
//    After an Item is pushed onto the stack, the used variable is
//    incremented so the next Item to be pushed will be pushed on
//    top of the previously pushed Item.

using namespace std;

class Stack
{
public:
	typedef int Item;
	static const int CAPACITY = 100; // size of stack

	// constructor
	// postcondition: initialize an empty stack
	Stack() { used = 0; }

	// modification member functions
	void push(Item entry);	// push an Item onto the stack
	Item pop();		// pop an Item off the stack and return it

	// returns the size of the stack
	// precondition: assume the stack has been initialized
	// postcondition: return the index of the top Item in the stack
	int size() { return used; }

	// returns true if the stack is empty
	// precondition: assume the stack has been initialized
	// postcondition: return true if the list is empty or
	//    false if it's not empty
	bool empty() { return used == 0; }

	// overflow flag
	bool overflow = false;	// true if there was an attempted overflow

private:
	Item data[CAPACITY];	// this is the stack (sequential)
	int used;		// counts number of stack elements that've been used
};

// push an Item onto the stack
// precondition: Assuming the list isn't full, entry should be a positive
//    integer that will be pushed on top of the stack.
// postcondition: The integer is pushed onto the stack and used is incremented.
void Stack::push(Item entry)
{
	if (overflow == false)
		// check for overflow before pushing
		if (used < CAPACITY)
			// push the Item onto the stack and increment used
			data[used++] = entry;
		else
		{
			// set flag and output error message
			overflow = true;
			cout << "Stack overflow." << endl;
		} // end nested if else
}

// pop the top Item off the stack and return its value
// precondition: assume that the list has values, but underflow is considered.
// postcondition: return the top Item in the stack and decrement used.
Stack::Item Stack::pop()
{
	// check for underflow
	if (used - 1 >= 0)
		return data[--used];
}
