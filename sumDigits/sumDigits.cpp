// Author: Rowan Kill
// Due: 1/23/2018
// CSCI 301 - Section 2
// Purpose: This program asks the user to input a positive integer value and
//   outputs the sum of the digits that are in that input value.
// Design: This program first outputs some information to the user so they know
//   what the program does, then asks them to input the first number. That number
//   is passed to the digits() function as an argument as long as it's not equal
//   to -1 (sentinel value), this function generates the sum of the digits in the
//   argument value recursively. Once the function returns the sum, it is output
//   to the user and the user is asked to input a new number or -1 to exit the
//   program. The digits() function expects positive integer values and returns the
//   total of the digits in that integer by first verifying that the integer has
//   more than one digit. If it does not, that one-digit value is returned to the
//   previous caller. If more than one digit is found, then the function calls itself
//   but divides the input value by 10 to remove a digit from the right side (for
//   example, 123 / 10 = 12 with integer division). When the function receives an
//   argument value that only has one digit, it's returned to the caller and that
//   caller then adds the returned value to the sum variable. After that addition,
//   the caller adds the rightmost digit of the argument value to the sum and returns
//   the new sum to the last caller. This process repeats until the last caller was
//   main(), which then receives the total sum of the digits.

#include <iostream>
#include <string>
using namespace std;

// function prototype
int digits(int n);

int main()
{
	// variables
	int inputNum,		// holds the digits that will be added together
	    total;		// holds sum of digits

	// user info
	cout << "Enter a positive integer, this program will output the"
	     << "\n  sum of the digits in that integer." << endl;

	// get input
	cout << "\nEnter the integer: ";
	cin >> inputNum;

	// loop allows user to continue entering numbers or exit
	while (inputNum != -1)
	{
		// call recursive function
		total = digits(inputNum);

		// output results of the function
		cout << "The total of the digits in \"" << inputNum << "\" is: " << total;

		// ask user if they want to continue
		cout << "\n\nEnter a new integer (or -1 to exit): ";
		cin >> inputNum;
	} // end while

    return 0;
}

// recursively generate a sum of the digits of the positive int argument
// precondition: the argument values should be positive integers containing at
//   least one digit.
// postcondition: main can expect the total of the digits to be returned, but the
//   recursive calls should expect a smaller value to be returned. The recursive
//   callers will add a new value to the one that was returned, then return that
//   new value.
int digits(int n)
{
	// create sum variable
	int sum = 0;

	// base case when n is between 0 and 9 inclusive, only 1 digit for 0 - 9
	if (n < 10)
		return n;
	else
	{
		sum += digits(n / 10);	// remove leftmost digit and call function
		return (sum += n % 10);	// add last digit to sum
	} // end if else
}
