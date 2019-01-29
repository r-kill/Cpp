// Author: Rowan Kill
// Due: 4/18/2018
// Purpose: This program is designed to allow the user to create an
//    inventory of items that contains each items number, name,
//    quantity, and price. The user starts with an empty list and can
//    insert new items that they create with input values or the items
//    can be read from a file. Items can be removed or inserted as
//    needed without altering the file contents.
// Design: The inventory is an ordered list that's represented by a
//    binary search tree. The user is presented with some information
//    and a list of commands they can use, each time a command is
//    entered its value is compared to those shown in the list. If the
//    input value matches a command in the list, then that command is
//    executed and the user is asked to input another command, at which
//    point they can input another command or input 'q' to terminate
//    the program. If the input value doesn't match one of the commands
//    shown in the menu, an error message is output to the user and
//    the user is asked to input another value. The user can see the
//    number of items in the inventory and they can check if it's empty.
//    The total value of all items in a given list can be calculated.
//    The menu() function prints the list of commands and a short
//    explanation about how to use them, this is called when 'h' is input.
//    Duplicates are allowed and occur when two items have the same
//    item number. If the items have the same item number and price,
//    their quantities can be combined and only one item needs to be
//    used in the final list to represent the duplicates. If the items
//    have the same item number but different prices, then they're
//    first sorted by item number (with the rest of the inventory)
//    and then the duplicates are sorted by their price, this way the
//    duplicates appear in similar places in the list and the
//    duplicates are obvious. This is the only case where items are
//    sorted by a property other than their item number. The user can
//    choose to print the entire inventory in a table. The user can
//    also choose to print a single value from the inventory, if it's
//    not found then an error message is output and the user is asked
//    to input another command. If there are multiple items that have
//    the same item number, then all of those items are printed. The
//    list can contain data from one or more files.
// Improvements:
//    Save function that writes inventory to a file.
//    If I input 5 custom items before doing anything,
//        then remove them all, then read "in.dat" specifically
//        (doesn't occur with t.dat), the names of the first
//        five items in "in.dat" aren't read correctly.
//        -Note: This problem was patched by resetting t->name
//            when creating a new node in help_insert()
//   Printing duplicate values doesn't always work, reading
//        in.dat before reading t.dat causes this feature to
//        fail because it's not searching the whole tree. This
//        is just one failure case, there are probably others.

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include "BST.h"
using namespace std;

// function prototypes
void menu();
void openFile(ifstream &file, string &fileName);

int main()
{
	// variables
	string input,		// holds user input as a string
	    fileName,		// holds file name to read
		name,		// holds name of item to insert
		data;		// holds individual lines read from file
	BST inv;		// holds contents of users list
	int id,			// holds item ID
	 quant;			// holds quantity of item to insert
	double price;		// holds price of item to insert
	char aName[10];		// holds name of an item as a character array
	ifstream file;		// file stream for reading files with item info

	// user info
	cout << "This program allows the user to create and manipulate"
	     << "\n    an inventory of items that each have an item number"
	     << "\n    (which is used to identify the items), a name, a"
	     << "\n    quantity that represents how many items are in the"
	     << "\n    inventory, and a price." << endl;
	cout << "Duplicates are allowed. Items are sorted in ascending order"
	     << "\n    by their item number, if two items have the same item"
	     << "\n    number and the same price, then they can be considered"
	     << "\n    the same item and the quantities of each are added"
	     << "\n    together, no new items need to be created in this case."
	     << "\n    When two items have the same item number and different"
	     << "\n    prices, they are considered separate items and are"
	     << "\n    sorted by item number, then price, both in ascending"
	     << "\n    order. In this case, items with identical item number"
	     << "\n    but differing prices will have unique list entries."
	     << "\n    To remove duplicate items, follow the same procedure as"
	     << "\n    removing a single item, but in this case the duplicate"
	     << "\n    with the lowest price is removed first. There is no way"
	     << "\n    to selectively remove duplicate items." << endl;
	menu();

	// get file names from user
	cout << "\n--> ";
	cin >> input;

	// ensure user didn't quit
	while (input != "q")
	{
		// determine what to do based on user input
		if (input == "f")
		{
			// read inventory from file - get file name from user
			cout << "Enter inventory file name: ";
			cin >> fileName;

			// try opening the file
			openFile(file, fileName);

			// read file if user didn't quit before entering
			//    a proper file name
			if (fileName != "q")
			{
				// read file and store each word from each line
				//    in the file into a variable
				// this will detect the end of the file
				while (file >> id >> name >> quant >> price)
				{
					// convert name string to character array
					//    for class
					for (int i = 0; i < 10; ++i)
						// ensure input name isn't larger than
						//    max size of item name
						if (i < name.size())
							aName[i] = name[i];
						else
							// also make sure name array of
							//    class is fully initialized
							aName[i] = ' ';

					// insert extracted value into the list
					inv.insert(id, aName, name.size(), quant, price);
				} // end nested while
			} // end nested if
		}
		else if (input == "i")
		{
			// get some item info from the user before inserting
			cout << "Enter the item description:" << endl;
			cout << "  Number: ";
			cin >> id;
			cout << "  Name: ";
			cin >> name;
			cout << "  Quantity: ";
			cin >> quant;
			cout << "  Price: ";
			cin >> price;

			// convert name string to character array for class
			for (int i = 0; i < name.size(); ++i)
				// ensure input name isn't larger than max size
				//    of item name
				if (i < 10)
					aName[i] = name[i];
				else
					break;

			// insert extracted value into the list
			inv.insert(id, aName,name.size(), quant, price);
		}
		else if (input == "r")
		{
			// get the item ID of item to remove
			cout << "Item number to remove: ";
			cin >> id;

			// remove extracted value from list
			inv.remove(id);
		}
		else if (input == "e")
			// report if list is empty or not
			if (inv.empty())
				cout << "The list is empty." << endl;
			else
				cout << "The list is NOT empty." << endl;
		else if (input == "a")
		{
			// get item ID from user
			cout << "Item number to report: ";
			cin >> id;

			// check if inventory is empty before printing the header
			if (!inv.empty())
			{
				// print the header only if the tree isn't empty
				cout << endl;	// whitespace
				cout << fixed << showpoint << setprecision(2);
				cout << setw(5) << setfill(' ') << "Number "
				     << setw(10) << "Name "
				     << setw(5) << "Quantity"
				     << setw(7) << "Price" << endl;
				cout << "--------------------------------" << endl;
			} // end nested if

			// print the item with that ID
			inv.print(id);
		}
		else if (input == "v")
			// output total price of all items in inventory
			cout << "The inventory's total value is: $"
			     << inv.total() << endl;
		else if (input == "p")
		{
			// check if inventory is empty before printing the header
			if (!inv.empty())
			{
				// print the header only if the tree isn't empty
				cout << fixed << showpoint << setprecision(2);
				cout << setw(5) << setfill(' ') << "Number "
				     << setw(10) << "Name "
				     << setw(5) << "Quantity"
				     << setw(7) << "Price" << endl;
				cout << "--------------------------------" << endl;
			} // end  nested if

			// print the list as a table
			inv.print();
		}
		else if (input == "l")
			// print the length of the list
			cout << "Number of unique items: "
			     << inv.length() << endl;
		else if (input == "h")
			// print the menu
			menu();
		else if (input == "q")
			// exit the program
			break;
		else
			// tell the user that the command was not in the list
			cout << "That command was not recognized, see the menu."
			     << endl;

		// ask user to continue or exit
		cout << "\n--> ";
		cin >> input;
	} // end outer while

	// close any open file
	file.close();

	return 0;
}

// print the menu
// postcondition: This function will print the list of commands the user
//    can input, providing explanations of how to use them and what they do.
void menu()
{
	cout << "\n  f   -- Read an inventory from a file."
	     << "\n  i   -- Insert an integer into the inventory."
	     << "\n  r   -- Remove an integer from the inventory."
	     << "\n  e   -- Check if the inventory is empty."
	     << "\n  a   -- Report an item's information."
	     << "\n  v   -- Report the inventory's total value."
	     << "\n  p   -- Print the inventory to the terminal."
	     << "\n  l   -- Report the number of items in the inventory."
	     << "\n  h   -- Display this menu."
	     << "\n  q   -- Quit." << endl;
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
		while (fileName != "q" & fileName.find(".dat") == -1)
		{
			// error info
			cout << "There was an error with the file:"
			     << "\n    Use this format: file.dat"
			     << "\n    Make sure the file shares a directory"
			     << "with the program." << endl;

			// get another file name to try opening
			cout << "\nEnter the name of the file: ";
			cin >> fileName;
		} // end nested while

		// check for sentinel value (exit)
		if (fileName == "q")
			return;

		// open file
		file.open(fileName);

		// increment counter
		++count;
	} while (file.fail() && fileName != "q");
}
