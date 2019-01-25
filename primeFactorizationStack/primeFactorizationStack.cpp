// Author: Rowan Kill
// Due: 3/13/2018
// Purpose: This program uses a custom Stack class to create a Stack object
//    that stores the prime factors of a positive integer that's input by
//    the user. When all of the prime factors are found and stored in the
//    stack, they're output to the terminal.
// Design: The program is designed to get the users input, which is a
//    positive integer, and find the smallest factor of that value, which
//    will be prime. That factor is pushed onto the stack, then the
//    original input value is divided by the factor. The smallest factor
//    of the quotient is then found, pushed onto the stack, and the process
//    repeats until the quotient is 1. At that point, the program will
//    print the prime factorization of the input value if there wasn't
//    an overflow. After that the user is asked to input a new integer
//    or -1 to exit the program. The smallest factor of a number is the
//    first value that divides evenly into that number, this was found
//    with modulus.

#include <string>
#include <iostream>
#include "stack.h"	// custom Stack class
using namespace std;

// function prototypes
int smallestFactor(int num);
void print(Stack& s);

int main()
{
	// variables
	Stack s;
	string input;
	int item,
	    small;

	// user info
	cout << "Enter a positive integer and the program will output the prime"
	     <<  "\n    factorization of that integer. Enter -1 to exit the program."
	     << endl;

	// get user input
	cout << "\nEnter a positive integer (-1 to exit): ";
	cin >> input;

	// ensure user didn't exit
	while (input != "-1")
	{
		// convert string to int
		item = stoi(input);

		// get smallest factor of original input value
		// push the smallest factor onto the stack
		// divide original input value by the smallest factor
		// then find the smallest factor of the quotient and repeat
		while (item > 1 && s.overflow == false)
		{
			// get smallest factor of item
			small = smallestFactor(item);

			// push factor onto stack
			s.push(small);

			// divide item by factor
			item /= small;
		} // end nested while

		// ensure there was no overflow attempt
		if (s.overflow == false)
		{
			// print stack or 1 if 1 was input
			cout << "Prime Factors: ";
			if (input == "1")
				// only factor of 1 is 1
				cout << input << " = 1" << endl;
			else if (input == "0")
				// only factor of 0 is 0
				cout << input << " = 0" << endl;
			else
			{
				// output prime factorization of input value
				cout << input << " = ";
				print(s);
			} // end nested if else
		} // end nested if

		// get new input
		cout << "\nEnter a positive integer (-1 to exit): ";
		cin >> input;

		// reset overflow flag for stack
		s.overflow = false;
	} // end outer while

    return 0;
}

// function that finds the smallest factor greater than 1 (which will be prime)
// precondition: the argument should be a positive integer value
//   that's greater than 1 because 0 and 1 aren't factorable.
// postcondition: the value returned by this function will be the
//   smallest nontrivial prime factor of the argument provided. This
//   value will be a positive integer that's greater than 1.
int smallestFactor(int num)
{
	// find the smallest factor of the argument iteratively
	// iterator starts at 2 because 1 is a trivial factor
	for (int i = 2; i <= num; ++i)
		if (num % i == 0)
			return i;
}

// print the values in the stack with an 'x' between them to
//    show multiplication
// precondition: assume the stack argument contains integer values, but
//    this is checked. If the stack has overflowed, don't print the stack
//    values because the output will be incorrect.
// postcondition: the Items in the stack will be output to the terminal,
//    the final stack Item will be followed by a newline character instead
//    of the string " x "
void print(Stack& s)
{
	// counter
	int top = s.size();

	// print stack Items until the bottom of the stack is reached,
	//    but don't print stack if its overflow flag is set to true.
	while (top != 0 && s.overflow == false)
	{
		// print top Item in stack
		s.size() > 1 ? cout << s.pop() << " x " : cout << s.pop() << "\n";

		// adjust top of stack (can do this in conditional statmnt with top--)
		--top;
	} // end while
}
