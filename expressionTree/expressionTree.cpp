// Author: Rowan Kill
// Due: 4/26/2018
// Purpose: This program reads fully parenthesized expressions
//    from a file and prints them in prefix, fully parenthesized
//    infix, and postfix notation. Then the program evaluates
//    the expression and prints the result. Whitespace is ignored
//    when reading the expressions, they only need to be fully
//    parenthesized. The expressions should each occupy only one
//    line of the file.
// Design: This program first prints one user information, then
//    gets the name of the file to read. The program tries to open
//    the file and will keep asking the user for an acceptable
//    file name until one is provided or until the user exits the
//    program. When a file is finally opened, the expressions are
//    read and the output is generated for each expression in the
//    file. When the file has been read, the user is asked to enter
//    another file name to read more expressions. The user can also
//    exit the program at this point.

#include <string>
#include <iostream>
#include <fstream>
#include "exp_tree.h"
using namespace std;

// function prototypes
void openFile(ifstream &file, string &fileName);

int main()
{
	// variables
	string fileName;	// contains the name of the file to open
	ExpTree tree;		// contains the expressions read from the file in a tree
	ifstream file;		// file stream for reading expressions from files

	// user info
	cout << "This program reads expressions from a file and stores them"
	     << "\n    in a tree. Then, the expressions are printed using prefix,"
	     << "\n    infix, and postfix notation. Finally, the values of the"
	     << "\n    expressions are printed. The expressions in the file should"
	     << "\n    be fully parenthesized." << endl;
	cout << "To exit the program, the user can enter '-1' for any input."
	     << endl;

	// get file name from user
	cout << "\nEnter file name: ";
	cin >> fileName;

	// ensure the user didn't exit
	while (fileName != "-1")
	{
		// try opening the file
		openFile(file, fileName);

		// build trees from file if user didn't quit before
		//    entering a proper file name
		if (fileName != "-1")
		{
			char ch;	// variable used to find the end of the file

			// ensure the entire file is read
			while (file.peek() > -1)
			{
				// we have to peek() at the character after the
				//    newline character at the end of the last
				//    line of the file to determine if we've
				//    reached the end of the file.
				// this if statement and the "ch" variable are
				//    not required for Windows because lines are
				//    ended differently.
				if(file.peek() == 10)
				{
					// if a newline is found, read it and peek at
					//    the next character in the line
					file.get(ch);
					if(file.peek() < ' ')
						// if the next character in the line is
						//    anything other than the start
						//    of another expression, then
						//    assume the end of the file has
						//    been reached and get a new filename
						break;
				} // end nested if

				// build the tree
				tree.build(file);

				// print the tree in prefix, infix, and postfix notations
				cout << "\nPrefix: ";
				tree.prefix();
				cout << endl;	// whitespace
				cout << "Infix: ";
				tree.infix();
				cout << endl;	// whitespace
				cout << "Postfix: ";
				tree.postfix();
				cout << endl;	// whitespace

				// print the value of the tree
				cout << "Value = " << tree.value() << endl;
			} // end nested while

			// get new file name from user
			cout << "\nEnter another file name: ";
			cin >> fileName;
		} // end nested if
	} // end while

	// close any open file
	file.close();

    return 0;
}

// open file so it can be read, check arguments for errors as well
// precondition: This function receives an ifstream variable so it
//    can manipulate files, passed by reference so there are no access
//    conflicts. The second parameter is a string provided by the user
//    that represents the file name of the file to open, this is also
//    passed by reference because the user has the opportunity to input
//    another file name within this function if the first was erroneous.
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
		file.close();	// close any open file before opening a new one

		// ask user for a new file name if the first iteration failed
		if (count > 0)
		{
			cout << "Error in the most recent file name provided."
			     << endl;
			cout << "\nEnter the name of a file: ";
			cin >> fileName;
		} // end nested if

		// make sure file name has a .dat file extension
		// ensure user didn't exit after entering improper file name
		while (fileName != "-1" & fileName.find(".dat") == -1)
		{
			// error info
			cout << "There was an error with the file:"
			     << "\n    Use this format: file.dat"
			     << "\n    Make sure the file shares a directory"
			     << " with the program." << endl;

			// get another file name to try opening
			cout << "\nEnter the name of the file: ";
			cin >> fileName;
		} // end nested while

		// check for sentinel value (exit)
		if (fileName == "-1")
			return;

		// open file - convert file name string to char* for Linux
		file.open(fileName.c_str());

		// increment counter
		++count;
	} while (file.fail() && fileName != "-1");
}
