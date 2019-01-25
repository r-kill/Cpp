// Author: Rowan Kill
// Due: 2/7/2018
// Purpose: This program asks the user to input two files that contain
//    integer values. The values are stored in lists which are merged
//    into one list such that the values are in ascending order. The
//    lists are printed to the console.
// Design: The program asks the user to input file names, which are
//    checked as they're input to ensure the user entered a proper file
//    name that can be opened. The function that opens the files is where
//    the error checking is done, the file should contain a ".dat"
//    extension and should be local to the program file. Once the files
//    are opened successfully, they can be read and the lists can be created,
//    then they're merged together and all of the lists are output to the
//    terminal. The user can merge two lists at a time, this can be repeated
//    until the user inputs a sentinel value.

#include <string>
#include <iostream>
#include <fstream>
#include "list.h" // local list class, not <list>
using namespace std;

// function prototypes
void openFile(ifstream &file, string &fileName);

int main()
{
	// variables
	string file1,		// holds user input name for file 1
	       file2;		// holds user input name for file 2
	ifstream inFile1,	// file stream for file specified by user
	         inFile2;	// file stream for file specified by user
	List list1,		// holds contents of file1
	     list2,		// holds contents of file2
	     list3;		// holds list1 merged with list2
	int content = -1;	// holds content of a file

	// user info
	cout << "Enter two files that contain integer values, these values"
	     << "\n  will be stored in two linked lists that will be merged"
	     << "\n  into one list such that the values are in ascending order."
	     << "\n  The files should be in the same directory as the program"
	     << "\n  and should be in this format: file.dat" << endl;

	// get file names from user
	cout << "\nEnter the name of the first file: ";
	cin >> file1;

	while (file1 != "-1" && file2 != "-1")
	{
		// read first file input by user
		openFile(inFile1, file1);

		// user can change bad input values in openFile()
		// check for sentinel value
		if (file1 == "-1")
			return 0;

		// get user input for file2
		cout << "Enter the name of the next file: ";
		cin >> file2;

		// read second file
		openFile(inFile2, file2);

		// user can change bad input values in openFile()
		// check for sentinel value
		if (file2 == "-1")
			return 0;

		// insert file contents to list1 and list2
		while (inFile1.is_open() || inFile2.is_open())
		{
			// read all data from the files to the lists
			if (!inFile1.eof())
			{
				// ensure file1 is open before inserting value to list1
				inFile1 >> content;
				if(content != -1)
					list1.insert(content);
			}
			else if (!inFile2.eof())
			{
				// ensure file2 is open before inserting value to list2
				inFile2 >> content;
				if(content != -1)
					list2.insert(content);
			}
			else
				// break while loop when both files have been read
				break;

			// clear content variable after each loop iteration
			content = -1;
		} // end while

		// merge list1 and list2 into list3
		list3.merge(list1, list2);

		// output list1 values
		cout << "\nlist1 has " << list1.length() << " values:\n\t" << list1;
		cout << "\nlist2 has " << list2.length() << " values:\n\t" << list2;
		cout << "\nlist3 has " << list3.length() << " values:\n\t" << list3;

		// ask user to continue or exit
		cout << "\n\nEnter the name of a new file or -1 to exit: ";
		cin >> file1;

		// close file to open new one
		inFile1.close();
		inFile2.close();

		// empty List objects
		list1.make_empty();
		list2.make_empty();
		list3.make_empty();
	} // end outer while

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
			cout << "\nError in the most recent file name provided.";
			cout << "\nEnter the name of a file: ";
			cin >> fileName;
		} // end nested if

		// make sure file name has a .dat file extension
		// test for exit here if user exits after entering improper file name
		while (fileName != "-1" & fileName.find(".dat") == -1)
		{
			// error info
			cout << "\nThere was an error with the file:"
			     << "\n    Use this format: file.dat"
			     << "\n    Make sure the file shares a directory with the program."
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
