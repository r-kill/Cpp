// Author: Rowan Kill - cs301152
// CSCI 301 - Section 02
// Due: 1/30/2018
// Purpose: This program recursively finds exits to a maze. The maze
//    is drawn with ASCII characters and stored in a file with a
//    particular format that allows this program to access and read
//    the map properly. The program finds open "corridors" in the maze
//    and follows that path until it reaches the end of the maze or
//    until it reaches a dead end, where the steps are removed until
//    a new path can be tried.
// Design: Four functions make up this program. In main(), the user
//    is asked to input the name of the file that contains the maze
//    and other relevant data. The users input is checked to ensure
//    it isn't a sentinel value that would allow the user to exit
//    the program, then the input is checked to ensure it contains
//    the proper file extension, if the extension isn't correct the
//    user is asked to enter an appropriate file name until one is
//    input. Then, the program tries to open the file and will ask
//    the user to enter a new file name until the user enters a file
//    that can be opened. Once the input file is properly verified and
//    opened, the first line of the file is read so the number of rows
//    and columns in the maze can be determined and converted to
//    integer values. These values are then checked to ensure the maze
//    is of the proper size, if the maze is too big the program will
//    ask the user to input a new file, which goes through the some
//    checks as other input values. If the file is acceptable, the
//    number of rows and columns are used to create a 2D array that's
//    passed to other functions. The first function reads the maze
//    data in the file and stores each character from the file into
//    the 2D array, it doesn't return any values because the array
//    is passed by reference and the other argument values are only
//    used to terminate the loops. Then main() calls the search()
//    function and passes it the 2D array that contains the maze and
//    the number of rows and columns in the maze along with a row
//    and column value that represents the current location in the
//    maze or 2D array. The function loops through the 2D array and
//    checks if the current row is the last row in the array, if
//    that's the case it means that the function has found a path to
//    the exit so the maze can be printed with the path highlighted
//    and the function can return. The print function is passed the
//    2D array and the dimensions of the array so it can loop through
//    it and output the values to the console. If the search functions
//    location is not in the last row, the function checks all adjacent
//    locations in the maze. Those directions are the elements to the left
//    and right of the current location and the same index as the current
//    location in the rows above and below the current location. The
//    directions are checked in this order: up, down, left, right. If a
//    direction is found to contain a space character, then the function
//    recursively calls a new instance of itself and passes it the 2D array
//    along with the index of the new location to move to. This process
//    continues until one instance reaches a dead end, where no spaces are
//    adjacent to the current location, or the exit of the maze in the
//    bottom row. When either of those cases occur, the previous instances
//    remove the path that was created in order to clear dead ends and
//    find alternate paths to the exit. Since the directions are checked
//    in sequence, multiple paths can be created from one location if there
//    are multiple adjacent space characters. For example, if a location has
//    two spaces adjacent to it, one above and one to the right, the function
//    will recursively follow the upper path until the exit or a dead end is
//    reached. Then, the function reverses those steps and follows the right
//    path when it gets back to that location. When a path is found through
//    the maze, it's printed and the function returns control to main()
//    where the user is asked to input a new file to evaluate and the previous
//    file and some variables are reset for use with a new maze. The user can
//    exit at any point by entering the value -1 as input.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// function prototypes
void readFile(ifstream &mazeFile, int rows, int cols, char** maze);
void printMazeArray(char** maze, int rows, int cols);
void search(char** maze, int xRows, int xCols, int row, int col);

int main()
{
	// variables
	ifstream inputFile;			// file stream for file specified by user
	string mazeName,			// holds name of maze input by user
	       fileExtension = ".dat",		// used to test file extension of input
	       firstLine,			// holds first line of maze file - size of maze
	       rowStr,				// holds number of rows from firstLine
	       colStr;				// holds number of columns from firstLine
	bool continueFlag = false;		// flag for error checking
	int rows,				// holds number of rows in maze as an int
	    cols;				// holds number of columns in maze as an int

	// user information
	cout << "This program will solve a maze that's read from a file."
	     << "\n    The file containing the maze should follow a specific format"
	     << "\n    in order for this program to understand it. Enter the file"
	     << "\n    name as \"maze.dat\" and make sure the file is in the same"
	     << "\n    directory as the program executable. You can also enter \"-1\""
	     << "\n    to exit the program at any point where the program accepts input."
	     << endl;
	
	// get file name of maze from user
	cout << "\nEnter the name of the maze file: ";
	cin >> mazeName;

	// make sure user didn't exit the program
	while (mazeName != "-1")
	{
		// make sure file name has a .dat file extension
		// test for exit here if user exits after entering improper file name
		while (mazeName.find(fileExtension) == -1)
		{
			cout << "\nThe file name must be input in this format: maze.dat"
			     << endl;
			cout << "Enter the name of the maze file: ";
			cin >> mazeName;

			// check for sentinel value (exit)
			if (mazeName == "-1")
				return 0;
		} // end nested while

		// read file data from local directory
		// file opened in main() so it can be checked for availability
		// and if it can't be opened the user will be able to enter a
		// new file name that will also be error checked
		inputFile.open(mazeName);

		// make sure file is open
		while (!inputFile)
		{
			// get a new file name
			cout << "\nUnable to open file " + mazeName << endl;
			cout << "The file name you entered may not exist or"
			     << "\n   may not be in the same directory as this program.";
			cout << "\nEnter a new maze file: ";
			cin >> mazeName;

			// set flag for outer while loop to continue
			continueFlag = true;

			// break out of this loop to check new input with previous loops
			break;
		} // end nested if

		// continue outer while loop so new filename is checked for errors
		if (continueFlag)
		{
			// reset flag and continue outer while loop
			continueFlag = false;
			continue;
		} // end nested if

		/* -- Create 2D array and pass it to functions as needed -- */
		// read first line of maze file to get array dimensions
		getline(inputFile, firstLine);

		// split first line into maze dimensions for maze
		for (int i = 0; i < firstLine.length(); ++i)
		{
			// split maze dimensions by the space in "20 60"
			// so that the left dimension (rowStr) = 20 and
			// the right dimension (colStr) = 60
			if (firstLine[i] != ' ')
				rowStr += firstLine[i];
			else if (firstLine[i] == ' ')
			{
				// assign the remaining rightmost characters to colStr
				// variable if a space is encountered in firstLine
				while (i < firstLine.length())
				{
					// increment i so that colStr isn't assigned 
					// any unexpected characters in the first element
					++i;

					// make sure firstLine[i] isn't NULL
					// grabs only integer values from first line
					// and avoids the space and \n characters
					if (firstLine[i] != NULL)
						colStr += firstLine[i];
				} // end nested while
				break;
			} // end nested if else
		} // end nested for

		// assign array dimension values to int variables
		// add 1 to cols to prevent off-by-one error
		//	cols will only hold 19 out of 20 characters in a row
		rows = stoi(rowStr);
		cols = stoi(colStr) + 1;

		// ensure that maze dimensions are acceptable (22 by 76 is max)
		if (rows > 22 || cols > 76)
		{
			cout << "This maze file is too big for this program."
			     << "\n   Please enter a different file that's at"
			     << "\n   most 22 rows by 76 columns." << endl;

			// ask user if they want to solve a different maze
			cout << "\nEnter a different maze file or -1 to exit: ";
			cin >> mazeName;

			// close current file and reset variables before trying new file
			inputFile.close();
			rowStr = "";
			colStr = "";
			continue;
		} // end nested if

		// create 2D array with dynamic size found in maze file
		char** maze;
		maze = new char* [rows];
		for (int i = 0; i < rows; ++i)
			maze[i] = new char[cols];

		// read file and assign maze data to an array
		readFile(inputFile, rows, cols, maze);

		// search maze starting at position maze[0][0]
		search(maze, rows, cols, 0, 0);

		// ask user if they want to solve a new maze
		cout << "\nEnter another file or -1 to exit: ";
		cin >> mazeName;

		// delete maze before making a new one
		delete[] maze;

		// close file
		inputFile.close();

		// reset string variables
		rowStr = "";
		colStr = "";
	} // end while

	return 0;
}

// function that assigns maze values to 2D array
// precondition: The inputs for this function should be the file containing
//    the maze, the number of rows and columns, and the maze array. The file
//    is passed by reference so that this function can access it. The number
//    of rows and columns are expected to be positive integer values. The maze
//    argument is expected to be a 2D character array that contains '+' and
//    ' ' (space) characters.
// postcondition: This function doesn't return any values, but it reads data
//    from the file as individual characters and puts them into the 2D array.
//    The 2D array is passed by reference by default, so any changes made to
//    it in this function will reflect in other functions. The row and column
//    numbers are only used to determine how many times the loops should iterate.
void readFile(ifstream &mazeFile, int rows, int cols, char** maze)
{
	// local variables
	char data;

	// fill array with data from file - one char at a time
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
		{
			// read characters from file that main() opened
			// main() gets the dimensions of the maze and passes them to
			// functions as rows and cols
			mazeFile.get(data);

			// assign characters read from file to elements of 2D maze array
			maze[i][j] = data;

			// prevent misreading data from file:
			// last column of last row in maze will be given
			// an additional unwanted '+' if the last character
			// in the file is not '\n'
			if (i == (rows - 1) && j == (cols - 1) && maze[i][j] != '\n')
				// force last character in array to '\n' if the last
				// character in the file is not '\n'
				maze[i][j] = '\n';
		} // end nested for
}

// prints the 2D array that represents the maze to the console
// precondition: The inputs of this function are expected to be a 2D character
//    array containing characters and two positive integer values. The integers
//    are used to determine the size of the 2D array and iterate through it
//    accordingly.
// postcondition: The maze is output to the console. No changes are made to the
//    argument values.
void printMazeArray(char** maze, int rows, int cols)
{
	// whitespace
	cout << endl;

	// print maze
	for (int i = 0; i < rows; ++i)
		for (int j = 0; j < cols; ++j)
			cout << maze[i][j];
}

// search through the 2D array to find a path through the maze
// predondition: Four positive integer values and a 2D character array
//    containing characters are expected as arguments. The integers
//    represent the number of rows and columns in the maze as well as
//    the starting coordinate for the search.
// postcondition: This function loops through the 2D array from the starting
//    point indicated by the argument values and searches for ' ' (space)
//    characters that are adjacent to each other based on the size determined
//    by the xRow and xCol argument values. The goal is to reach the space
//    character in the last row of the 2D array (array[row][column]) and
//    print the path that the program found to reach that location from the
//    starting location. Each step in the path in done by recursively calling
//    this function and providing it with a new location that was found by
//    the current instance of this function. When a dead-end is found, the
//    steps are reversed until a new path can be tried. 
void search(char** maze, int xRows, int xCols, int row, int col)
{
	// loop through 2D array
	for (int i = row; i < xRows; ++i)
	{
		for (int j = col; j < xCols; ++j)
		{
			// base case 1 - if in the bottom row, print maze and return
			if (i == xRows - 1)
			{
				// if in last row and the current column is a space, print array
				printMazeArray(maze, xRows, xCols);

				// return
				return;
			} // end nested if
			
			// if current location in maze is a space or @, try to move
			// checks for new moves from the current @
			if (maze[i][j] == ' ' || maze[i][j] == '@')
			{
				// print an @ - this is for the entry space
				maze[i][j] = '@';

				// check if space ABOVE is available (UP)
				if (i != 0 && maze[i - 1][j] == ' ')
				{
					// mark the step if direction is available
					maze[i - 1][j] = '@';

					// recursive call to continue path ABOVE current location
					search(maze, xRows, xCols, (i - 1), j);

					// undo step
					maze[i - 1][j] = ' ';
				} // end nested if 

				// check if space BELOW is available (DOWN)
				if (maze[i + 1][j] == ' ')
				{
					// mark the step if direction is available
					maze[i + 1][j] = '@';

					// recursive call to continue path BELOW current location
					search(maze, xRows, xCols, i + 1, j);

					// undo step
					maze[i + 1][j] = ' ';
				} // end nested if

				// check if space LEFT is available (LEFT)
				if (j != 0 && maze[i][j - 1] == ' ')
				{
					// mark the step if direction is available
					maze[i][j - 1] = '@';

					// recursive call to continue path to the LEFT
					// of the current location
					search(maze, xRows, xCols, i, j - 1);

					// undo step
					maze[i][j - 1] = ' ';
				} // end nested if

				// check if space RIGHT in available (RIGHT)
				if (maze[i][j + 1] == ' ')
				{
					// mark the step if direction is available
					maze[i][j + 1] = '@';

					// recursive call to continue path to the RIGHT
					// of the current location
					search(maze, xRows, xCols, i, j + 1);

					// undo step
					maze[i][j + 1] = ' ';
				} // end nested if

				// base case 2 - after testing all directions,
				// if none of the other if statements are invoked, return
				// because the current location is a dead end
				// this also undoes everything
				return;
			} // end nested if
		} // end nested for
	} // end outer for
}
