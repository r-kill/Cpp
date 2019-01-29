// Author: Rowan Kill
// Due: 3/21/2018
// Purpose: The purpose of this program is to read prefix
//    expressions from a file and print the expression and
//    its result to the terminal after calculating the result.
//    The file should be local to the program and contain at
//    least one expression. The expressions in the file should
//    be in proper prefix notation, but some error handling is
//    done. The expression is calculated using a stack.
// Design: This program is designed to read prefix expressions
//    from a file, push them onto a stack, solve the expression,
//    and finally output the results to the terminal. First, the
//    user is asked to input the name of the file, then the file
//    is opened and the characters are read individually from the
//    file. Space characters are ignored, but all other characters
//    are pushed onto the stack with an associated Boolean value
//    that represents whether the value is an operator or an
//    operand. The characters are also output to the terminal, so
//    the expression will eventually be printed in full. When the
//    stack contains at least three values, then there's a chance
//    for a pattern of values to form such that one operator is
//    under two operands and all three are at the top of the stack.
//    As long as this pattern exists on the stack, there is a
//    prefix expression that can be evaluated so those three
//    items are popped off the stack and passed to a function
//    that applies the operator to the operands and returns the
//    result. That result is converted into its ASCII decimal
//    representation because the push() stack operation expects
//    the operand values that are passed to it to be in ASCII
//    representation, so it subtracts '0' from those values
//    before pushing them onto the stack. This means that the
//    apply() function is working with numeric values instead of
//    ASCII values, so it will return a numeric value instead
//    of its ASCII representation. This numeric value is
//    converted to its ASCII representation by adding '0' to it
//    before passing it to push(), which then subtracts '0' from it.
//    When the expression is fully evaluated, only the result
//    will exist on the stack and it needs to be printed. If the
//    file contains more than one expression, then the result is
//    printed when the newline character is read from the file
//    and there's only one value on the stack. After that, the
//    next expression is read until the end of the file is
//    reached. When the end of the file is reached and all
//    expressions have been solved, the last result is printed to
//    the terminal or the user is informed that no result could
//    be determined and the stack in emptied. Finally, the user
//    is asked if they want to input another file or exit the program.

#include <iostream>
#include "stack.h"
#include <fstream>
#include <string>

// function prototypes
void openFile(ifstream &file, string &fileName);
int apply(char optr, int op1, int op2);

int main()
{
	// variables
	ifstream file;		// contains the file stream
	string fileName;	// holds the file name input by user
	char ch;		// holds data from the file
	Stack stk;		// Stack object
	int out;		// holds output value

	// user information
	cout << "Prefix notation: +22 = 4"
	     << "\n    Prefix expressions are evaluated and the result is printed."
	     << "\n    Expressions are read from a file that's local to the program."
	     << "\n    The expressions should use proper syntax."
	     << "\n    The file should be named 'fileName.dat'."
	     << "\n    The file should contain at least one expression."
	     << "\n Input '-1' at any point to exit the program." << endl;

	// get file name from the user
	cout << "\nEnter the file name: ";
	cin >> fileName;

	// ensure the user didn't exit
	while (fileName != "-1")
	{
		// open the file that the user specified
		openFile(file, fileName);

		// check for sentinel value after openFile() returns
		if (fileName == "-1")
			return 0;

		// output
		cout << "\nExpression: ";

		// read chars from file until the end of the file
		// check for sentinel value, user can exit when EOF is reached
		file.get(ch);
		while (!file.eof() && fileName != "-1")
		{
			// ensure char is not a space
			if (ch > ' ')
			{
				// push char onto stack
				stk.push(ch, isdigit(ch));

				// print expression, one char at a time
				cout << ch << ' ';
			} // end nested if

			// check for pattern if at least 3 items on stack
			while (stk.size() >= 3 && stk.check())
				// apply operator to operands and push result
				// add '0' so it can be subtracted in push() without
				//    errors
				// result of apply will be an operand, so pass true to
				//    push
				stk.push(apply(stk.pop(), stk.pop(), stk.pop()) + '0', true);

			// read next char from file
			file.get(ch);

			// check for end of one expression in a file
			//    that may contain many expressions
			if (ch == '\n')
			{
				// read another char, effectively skips newline
                		file.get(ch);

				// test for end of file after newline
				if(!file.eof())
				{
					// print result
					cout << "\nResult: " << stk.pop() << endl;

					// get ready for next expression
					cout << "\nExpression: ";
				} // end nested if
			} // end nested if
		} // end nested while

		// print result for final expression in file
		if (stk.size() == 1)
			cout << "\nResult: " << stk.pop() << endl;
		else
		{
			// tell user that no expression was found
			cout << "\nResult: No expression found!" << endl;

			// clear all items off stack
			while (!stk.empty())
				stk.pop();
		} // end nested if else

		// ask user to continue or exit
		cout << "\nEnter the name of a new file or -1 to exit: ";
		cin >> fileName;

		// close file
		file.close();
	} // end while

    return 0;
}

// open file so it can be read, check arguments for errors as well
// precondition: This function receives an ifstream variable so it
//    can manipulate files, passed by reference so there are no access
//    conflicts. The second parameter is a string provided by the user
//    that represents the file name of the file to open, this is also
//    passed by reference because the user has the opportunity to input
//    another file name in case the first was erroneous.
// postcondition: This function doesn't return any values, it only
//    ensures the file names input by the user can be opened, then it
//    opens them.
void openFile(ifstream &file, string &fileName)
{
	// counter to determine when to ask user to input a new filename
	int count = 0;

	// attempt to read file, get proper input values until a file
	//    is opened or the user exits the program
	do
	{
		file.clear();

		// ask user for a new file name if the first iteration failed
		if (count > 0)
		{
			cout << "Error in the most recent file name provided." << endl;
			cout << "\nEnter the name of a file: ";
			cin >> fileName;
		} // end nested if

		// make sure file name has a .dat file extension
		// test for exit here if user exits after entering improper file name
		while (fileName != "-1" & fileName.find(".dat") == -1)
		{
			// error info
			cout << "There was an error with the file:"
			     << "\n    Use this format: file.dat"
			     << "\n    Make sure file shares a directory with the program."
			     << endl;

			// get another file name to try opening
			cout << "\nEnter the name of the file: ";
			cin >> fileName;
		} // end nested while

		// check for sentinel value (exit)
		if (fileName == "-1")
			return;

		// open file
		file.open(fileName);

		// increment counter
		++count;
	} while (file.fail() && fileName != "-1");
}

// apply operator to operands
// precondition: This function expects an operator and two operands
//    as arguments. The operator is a character and the operands are
//    both integer values. The operator is passed as an ASCII decimal
//    value in this program. The integers should be single digit
//    numbers.
// postcondition: This function returns the result of applying the
//    operator to the operands.
int apply(char optr, int op1, int op2)
{
	// determine which operator was used
	// return result of operator applied to operands
	if (optr == '+')
		return op1 + op2;
	else if (optr == '-')
		return op1 - op2;
	else if (optr == '*')
		return op1 * op2;
	else if (optr == '/')
		return op1 / op2;
}
