// Author: Rowan Kill
// Due: 2/15/2018
// Purpose: This program is designed to allow the user to directly
//    manipulate an empty list by filling it with values, removing
//    values, emptying the list and many other commands. The user
//    creates a list from an empty list, the program loops so that
//    the user is forced to enter the proper command in order to exit
//    this program.
// Design: This program consists of four functions that allow the user
//    to manipulate the list. It relies on a custom list class and it's
//    various member functions. The menu() function simple prints the
//    commands that the user enters in order to manipulate the list and
//    use the program. The extract() function strips an integer value out
//    of a string and returns that integer as an integer, so it extracts
//    the integer value and converts it from a string to an integer. The
//    convert() function converts a character array to a string, the
//    character array contains the original input from the user and is used
//    to verify which command was input and if that command also contains
//    a value that needs to be extracted. The main() function does the
//    majority of the work in this program, it gets the users input,
//    manipulates those values and determines which command was input. If the
//    command contains a value, the value is extracted and assigned to a
//    variable so it can be used in the list. The appropriate member function
//    of the custom list class is called based on the command input, if the
//    command isn't recognized the user is asked to input a new command.
//    When the member function associated with the command is finished
//    executing, the user is asked to input another command until the
//    character 'q' is input, which tells the program to terminate.

#include <string>
#include <iostream>
#include "list.h" // local list class, not <list>
using namespace std;

// function prototypes
void menu();
int extract(string input);
string convert(char *cmd, int size);

int main()
{
	// variables
	char cmd[80];	// holds full command input by user
	string input;	// holds user input as a string
	List list;	// holds contents of users list
	int value;	// holds values provided in some commands

	// user info
	cout << "This program allows the user to input commands that directly"
	     << "\n    manipulate a list, so the user can have complete control"
	     << "\n    of the values that are contained in that list. The list"
	     << "\n    is initially empty." << endl;
	menu();

	// get file names from user
	cout << "\n--> ";
	cin.getline(cmd, sizeof(cmd));

	// ensure user didn't quit
	while (cmd[0] != 'q')
	{
		// convert input from char array to string
		input = convert(cmd, sizeof(cmd));

		// extract value if there is one to extract
		// check for a space in the command to determine
		//    if a value is present
		if (cmd[1] == ' ')
			value = extract(input);

		// determine what to do based on user input
		if (cmd[0] == 'e')
			list.make_empty();
		else if (cmd[0] == 'i')
			// insert extracted value into the list
			list.insert(value);
		else if (cmd[0] == 'r')
			// remove extracted value from list
			list.remove(value);
		else if (cmd[0] == 'm')
			// report if list is empty or not
			if (list.empty())
				cout << "The list is empty." << endl;
			else
				cout << "The list is NOT empty." << endl;
		else if (cmd[0] == 'l')
			// output list length
			cout << "The list has " << list.length() << " values." << endl;
		else if (cmd[0] == 'p')
			// report if the value is in the list or not
			if (list.present(value))
				cout << "The value " << value << " is in the list." 
                                     << endl;
			else
				cout << "The value " << value << " is NOT in the list." 
                                     << endl;
		else if (cmd[0] == 'k')
			// report the kth value in the list
			if (list.length() != 0 && list.length() >= value && value != 0)
				// numbering of list elements starts at 0, but user will
				//    assume it starts at 1. Account for this by sending
				//    value - 1 as the argument to kth() member function.
				// ensure the list isn't empty before getting a value
				// ensure the desired index exists in the list
				cout << "The value at index " << value
				     << " in the list is " << list.kth(value - 1) << endl;
			else if (list.empty())
				// inform the user that the list is empty
				cout << "The list is empty." << endl;
			else
				// inform user if list doesn't contain the desired index
				cout << "The list doesn't contain " << value << " values." 
                                     << endl;
		else if (cmd[0] == 'w')
			// write the list delineated by < >
			cout << "< " << list << ">" << endl;
		else if (cmd[0] == 'h')
			// print the menu
			menu();
		else if (cmd[0] == 'q')
			// exit the program
			break;
		else
			// tell the user that the command was not in the list
			cout << "That command was not recognized, see the menu." << endl;

		// ask user to continue or exit
		cout << "\n--> ";
		cin.getline(cmd, sizeof(cmd));
	} // end outer while

	return 0;
}

// print the menu
// postcondition: This function will print the list of commands the user
//    can input, providing explanations of how to use them and what they do.
void menu()
{
	cout << "\n  e     -- Re-initialize the list to be empty."
	     << "\n  i v   -- Insert the integer value v into the list."
	     << "\n  r v   -- Remove the integer value v from the list."
	     << "\n  m     -- Check if the list is empty."
	     << "\n  l     -- Report the length of the list."
	     << "\n  p v   -- Check if the integer value v is present in the list."
	     << "\n  k kth -- Report the kth value in the list."
	     << "\n  w     -- Write out the contents of the list."
	     << "\n  h     -- Display this menu."
	     << "\n  q     -- Quit." << endl;
}

// extract an int value from a string that contains other characters
// precondition: This function receives a string argument that also contains
//    a number within the string. The number should be a positive integer and
//    the string should be in the format "k #" with the command flag, a space
//    character and the integer value.
// postcondition: The integer value is found in the string argument by
//    avoiding any letters and spaces in the string. When the integer is
//    discovered, it's appended to another string that will be converted to an
//    integer when it's returned. The function will return the integer value
//    that's found in the string argument, it will be returned as an integer.
int extract(string in)
{
	// variable that contains all of the digits in a command value
	string returnValue = "";

	for (int i = 0; i < in.length(); ++i)
		// ignore all menu flags and space characters
		if (in[i] != ' ' && in[i] != 'i' && in[i] != 'r' &&
		    in[i] != 'p' && in[i] != 'k' && in[i] != 'm' &&
		    in[i] != 'l' && in[i] != 'w' && in[i] != 'h' &&
		    in[i] != 'e')
			returnValue += in[i];

	// convert string to int and return
	return std::stoi(returnValue);
}

// convert a character array to a string and return the string value
// precondition: This function receives a pointer to a character array as
//    an argument, along with the size of that character as an integer.
// postcondition: The size argument is used to iterate through the character
//    array, where each character value is appended to a string variable.
//    When the array contains '\0' then there are no more characters in the
//    array and the loop breaks. The sting value is returned to the caller,
//    it will contain the command that the user input as a string.
string convert(char *cmd, int size)
{
	// initialize a string to be returned
	string input = "";

	// convert input to string
	for (int i = 0; i < size; ++i)
	{
		// append chars to string
		input += cmd[i];

		// break after getting all useful values from cmd
		if (cmd[i] == '\0')
			break;
	} // end for

	return input;
}
