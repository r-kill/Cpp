// Author: Rowan Kill
// Due: 1/23/2018
// CSCI 301 - Section 2
// Purpose: This program asks the user to input a positive integer
//   value that's greater than 1 and will calculate the prime factors
//   of that value. Once the prime factors are calculated, they are
//   output to the console in ascending order.
// Design: First, some user information is output so the user knows
//   what to input. The program then gets that input from the user
//   and ensures that the value is factorable and is not the sentinel
//   value. The program will keep asking the user for proper input
//   values if one isn't entered originally. The input value is then
//   passed to the factor() function that calculates the prime factors
//   of that value. The first step is to determine the smallest prime
//   factor of the original input value, this is handled by the
//   smallestFactor() function that's called within the factor() function
//   and given the value of the argument that was passed to factor().
//   The smallest prime factor is the first value that divides into the
//   argument value without a remainder. The prime factor will be anywhere
//   from 2 to the argument value, inclusive. The smallest prime factor of
//   the argument passed to the factor() function is returned to factor()
//   when it's found by smallestFactor(), and that value is stored in a
//   variable that's local to the factor() function. The smallest prime
//   factor of the argument is then compared to the value of the argument,
//   if they're the same then the factor is output to the console and the
//   factor() function returns to the caller. If the factor value is not
//   equivalent to the argument value, then the smallest factor is output
//   to the console before factor() is called recursively and the argument
//   passed to factor() is the value of the argument passed to the current
//   factor() instance divided by the smallest factor. When the recursion
//   is finished, the user is asked if they want to input another positive
//   integer to factor or if they want to exit the program. This process
//   repeats until the user inputs the sentinel value -1.
// NOTE: I left the code to print the prime factors in descending order,
//   but commented it out. This simply shows that I did it.

#include <iostream>
using namespace std;

// function prototypes
int smallestFactor(int num);
int factor(int num);

int main()
{
	// variable
	int userInput;    // holds the positive integer that's input by the user

	// user info
	cout << "This program will determine the prime factors of a positive"
	     << "\n   integer and print those factors in ascending order."
	     << "\n   Factorable integers must be greater than or equal to 2."
	     << "\n   The user can input the value -1 to exit the program."
	     << endl;

	// get user input
	cout << "\nEnter a positive integer: ";
	cin >> userInput;

	// loop allows user to continue entering values or exit the program
	while (userInput != -1)
	{
		// make sure the user input a value that can be factored,
		// unless it's the sentinel value
		while (userInput < 2)
		{
			// get user input
			cout << "\nEnter a positive integer that can be factored: ";
			cin >> userInput;

			// check for sentinel value
			if (userInput == -1)
				return 0;
		} // end nested while

		// prepare console for output
		cout << "\tThe prime factors of " << userInput << " are: ";

		// call function to find prime factors
		factor(userInput);

		// ask for new input or the sentinel value
		cout << "\n\nEnter another positive integer or -1 to exit: ";
		cin >> userInput;
	} // end while

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

// function that finds the prime factors of a positive integer
// precondition: this function expects a positive integer value that's
//   greater than 1.
// postcondition: this function mostly outputs the prime factors to the
//   the terminal. The return value is the recursive call, it calls the
//   function and the value passed to the new factor() instance is the
//   argument value from the current factor() instance divided by the
//   smallest prime factor of that argument value. This allows the function
//   to find the next smallest prime factor of the users input.
int factor(int num)
{
	// holds the smallest prime factor of the argument value
	int small = smallestFactor(num);

	// base case
	if (small == num)
		// if num is a prime number, its smallest prime factor is itself
		// so print num
		cout << num << " ";
	else
	{
		// printing the prime factors of the current argument value
		// in ascending order is done by printing the current
		// smallest prime factor and then recursively calling this
		// function to print the remaining prime factors
		cout << small << " ";

		// recursive call
		return factor(num / small);

		//// DESCENDING ORDER: Uncomment this block and comment out the previous
		////	code in this else clause
		//// recursive call
		//factor(num / small);

		//// print the prime factors of the current argument value
		//// in descending order
		//cout << small << " ";
		//return 0;
	} // end if else
}
