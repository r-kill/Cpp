// Author: Rowan Kill
// CSCI 301 - Section 2
// Due: 1/16/2018
// Purpose: This program asks the user to input two fractions and an
//   operator that will be applied to them. The operator will be one of
//   these four characters: +, -, *, /. The fractions will be input in
//   the format "0/1" and the numerators and denominators will be
//   positive integer values. With both fractions input along with an
//   operator, three fraction objects are created and the numerators and
//   denominators are assigned to the proper objects. The operator is then
//   applied to the operands and the results are pulled from one of the
//   operands and assigned to the third fraction object. The entire
//   expression, including results, is output to the terminal. Finally, the
//   user is asked to input another expression to calculate. This process
//   repeats until the user inputs an expression containing at least one
//   fraction that tries division by zero.
// Design: The program is designed to read expressions from the user and
//   assign the values to their corresponding object members. Much of the
//   work is handled by the fraction class, but the objects are initialized
//   and assigned values in this program. The operator is applied to the
//   fraction objects and the results are assigned to another object and output.

#include "stdafx.h"
#include <iostream>
#include <string>
#include "fraction.h"
using namespace std;

int main()
{
	// variables that contain user input
	int leftNumerator, leftDenominator,
	    rightNumerator, rightDenominator;
	char op,	// contains the operator
	     x;		// contains the forward slash from the input fractions

	// user information
	cout << "Enter an expression with two fractions and a basic operator," << endl
	     << "  this program will solve the expression and output the result." << endl
	     << "\nThe expression should be in the format:" << endl << "\t1/2 + 3/4" << endl
	     << "The basic operators that will be used are: \n\t+ - * /\n" << endl
	     << "To stop entering more expressions, enter an expression that contains"
	     << endl << "  at least one fraction that divides by zero, such as:" << endl
	     << "\t0/0 + 0/0\n\n";

	// ask user to input two fractions and an operator
	cout << "Expression: ";
	cin >> leftNumerator >> x >> leftDenominator >> op >> rightNumerator
	    >> x >> rightDenominator;

	// verify that neither of the denominators are 0 (indicates user quitting)
	while (leftDenominator != 0 && rightDenominator != 0)
	{
		// create the fraction objects
		fraction f1 = fraction();
		fraction f2 = fraction();
		fraction result = fraction();

		// assign values to the fraction objects
		f1.assign(leftNumerator, leftDenominator);
		f2.assign(rightNumerator, rightDenominator);

		// apply input operator to the fractions
		// this also outputs the results
		f1.apply(f2, op);

		// assign the results from assign to the result object
		result.assign(f1.resultNum, f1.resultDenom);

		// output
		cout << "\n\t";
		f1.output();
		cout << " " << op << " ";
		f2.output();
		cout << " = ";
		result.output();

		// get the next expression from the user
		// ask user to input two fractions and an operator
		cout << "\n\nNew expression: ";
		cin >> leftNumerator >> x >> leftDenominator >> op >> rightNumerator
		    >> x >> rightDenominator;
	} // end while
	return 0;
}
