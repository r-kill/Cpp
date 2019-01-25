// Author: Rowan Kill
// Due: 1/23/2018
// CSCI 301 - Section 2
// Purpose: This program asks the user to input two numbers that
//   represent a range of values to be added together, then output
//   that sum to the console.
// Design: The program first prints some user information, then asks
//   the user to input the lowest and highest values in the range of
//   values that will be added together. After the user inputs those
//   values, the program verifies that the user didn't enter the
//   sentinel value and that the low value is lower than the high
//   value. The sentinel value causes the program to exit. If the low
//   value is larger than the high value, the program will ask the
//   user to input new high and low values until low < high, while
//   also checking for the sentinel value. The function is then
//   called that sums the values in the range from low to high,
//   inclusive. When that function returns control to the main function,
//   the results are output to the console and the user is asked to
//   input a new range of values or exit the program. The range()
//   function is the function used to calculate the sum of all of the
//   values in a given range recursively. The range is determined
//   by the values passed to the function as arguments. The function
//   initialized a local variable that stores the values in the range
//   from low to high in separate instances of the range() function.
//   The base case for this function occurs when the low argument is
//   equivalent to the high argument because the range is only one number,
//   so the sum of that range is just the value itself. If the base
//   case is false, then the current value for the low argument is stored
//   in the sum variable and the function is called recursively with
//   low+1 and high as arguments. Storing the low value in the sum
//   variable allows the function instances to keep track of the values
//   that are being added together, the values are stored in instances
//   from low to high. Then the sum values are added together in
//   descending order when the highest value in the range is returned
//   to the previous function instance. The return statements are
//   addition expressions, so the returned value is added to the low
//   value of the current working instance and that sum is returned to
//   the next previous instance. This process of return values being
//   added to the low value of the current working instance will
//   calculate the total of the range and return that value to the caller.

#include <iostream>
using namespace std;

// function prototype
int range(int low, int high);

int main()
{
	// variables
	int low,	// holds the lowest value in the range
	    high,	// holds the highest value in the range
	    total;	// holds the total of the values in the range

	// user info
	cout << "This program will calculate the sum of the numbers in a"
	     << "\n   range that is chosen by the user. The user only needs"
	     << "\n   to input the lowest and highest values in the range,"
	     << "\n   those values should be integers and the range is inclusive."
	     << "\n   However, the value 0 can be input for either boundary to"
	     << "\n   exit the program. The sentinel value to exit the program"
	     << "\n   is 0 because the range is inclusive, so using the range"
	     << "\n   0 to 4 will produce the same result as using the range"
	     << "\n   1 to 4. This is also true for ranges that include negative"
	     << "\n   numbers, so there's no need to explicitly specify the use"
	     << "\n   of the number 0. This means that the user doesn't need to"
	     << "\n   input the number 0 for any value to get a specific result,"
	     << "\n   making 0 the best candidate for the sentinel value to exit."
	     << endl;

	// get input data
	cout << "\nEnter the lower and upper bounds of the range.";
	cout << "\nLow: ";
	cin >> low;
	cout << "High: ";
	cin >> high;

	// loop to allow user to enter multiple input values
	// verifies that the user did not enter the sentinel value as initial input
	while (low != 0 && high != 0)
	{
		// verify that low is less than high
		// ask for new values as long as low > high
		while (low > high)
		{
			cout << "\nThe lower bound of the array must be a smaller integer"
			     << endl << "   than the higher bound. \nEnter new values such"
			     << " that low is less than high.";
			cout << "\nLow: ";
			cin >> low;
			cout << "High: ";
			cin >> high;

			// check for sentinel value
			if (low == 0 || high == 0)
				return 0;
		} // end nested while

		// call function
		total = range(low, high);

		// output results
		cout << "The total of the values from " << low << " to "
		     << high << " is: " << total << endl;

		// ask user if they want to continue with a new range or exit
		cout << "\nEnter a new range or 0 for either value to exit." << endl;
		cout << "Low: ";
		cin >> low;
		cout << "High: ";
		cin >> high;
	} // end while

    return 0;
}

// totals the values in the range that's bound by the argument values
// precondition: This function expects two positive integer values.
//   Low should have a smaller value than high and neither value should
//   equal zero.
// postcondition: The return value will either be the total sum of the
//   values from low to high, inclusive, or the total sum of only some of
//   the values in the range starting at low. The second return value is
//   only used by the previous instance of the range() function to calculate
//   the sum of all of the integers in the range.
int range(int low, int high)
{
	// holds the lowest value in the current range or the sum of some
	// (or all) values in the range
	int sum = 0;

	// base case
	if (low == high)
		// if the bounds of the range are the same value,
		// then no addition occurs
		return low;
	else
	{
		// assign sum to lowest value in range
		// this works because the recursion is going to go from lowest
		// value up to the highest value, then it returns the highest value
		// to the sum for highest-1 so it becomes highest-1 += highest,
		// which is then returned to the next lowest value in the range and
		// so on until the total is calculated
		// basically storing what values are in the range from low to high
		// in individual instances of the function, then adding those
		// values from high to low
		sum = low;

		// smaller solution
		return(sum += range(low + 1, high));
	} // end if else
}
