// Author: Rowan Kill
// CSCI 301 - Section 2
// Due: 1/16/2018
// Purpose: This class defines a fraction of the format "0/1" and can perform
//   basic arithmetic on two fraction objects and an operator such as +, -, *, /.
//   The fractions should only contain positive integers and one of the four
//   operator characters. The user inputs the fractions and operator to use.
//   One module outputs the fraction object to the terminal. The numerator
//   and denominator for a fraction are assigned to the object with a dedicated
//   module. The operator is applied to the fraction objects with the apply module
//   that determines which operator was used and calculates the results accordingly.
//   Fractions that need to be adjusted to find a common denominator are sent to
//   a module that finds the LCM of the two denominators and scales the values for
//   the operands appropriately. Then the results and scaled values are assigned
//   to the proper variables and used in the apply module to calculate the final
//   results.
// Design: This class is used by the program to create and manipulate fraction
//   objects. The fraction objects are initialized with the constructor to "0/1"
//   by first assigning the integer values to the numerator and denominator
//   variables, then using the assign module to assign those values to the fraction
//   object. The assign module simply assigns its argument values to the numerator
//   and denominator data members. The output module is also relatively simple, it
//   prints the numerator and denominator to the terminal with a '/' between them.
//   The apply module does most of the computation, it determines which operation
//   to do on the fraction operands and calculates the results accordingly. For
//   multiplication, the numerators are multiplied together and the denominators
//   are multiplied together. Division of fractions can be accomplished by
//   multiplying one of the fractions by the reciprocal of the other fraction,
//   so when the division operator is encountered the module cross-multiplies the
//   numerators with the denominators. Addition and subtraction are accomplished by
//   first determining if the denominators are the same, if they are then the
//   addition and subtraction only need to be done to the numerators because the
//   denominator doesn't change in the result. If the denominators for the two
//   operand fractions are different, the lcm module is called to find the least
//   common multiple of the two denominators, then the result numerator is
//   calculated based on the changes made by the lcm module. The lcm module assigns
//   the denominator values to local variables and determines which is the larger
//   value and which is smaller, assigning each to a different variable. A loop
//   first checks if the larger denominator is a multiple of the smaller one as
//   well as a multiple of itself, if it's not then the variable is incremented
//   and the next value is checked. Once a common multiple is encountered, it's
//   assigned to the denominator of the result and the loop is broken out of. After
//   that the fractions need to be scaled so the calculations are accurate, this
//   is done by dividing the result denominator by the original denominators and
//   assigning that value to a "scale" data member. The scale must be adjusted
//   for each operand fraction before the numerator and denominator are both
//   multiplied by the scale value. The module scales the smaller fraction, and
//   depending on whether that fraction appears on the left or the right side of
//   the operator determines how the fractions are scaled. The lcm module doesn't
//   return anything, it just changes data member values so that the apply module
//   can properly calculate the results of the addition or subtraction.

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;

class fraction
{
// private member data
private:
	int numerator,			// variable to hold the numerator of the object
	    denominator,		// variable to hold the denominator of the object
	    scale,			// variable to hold the scaling factor for fractions
	    scaledNumLeft,		// variable to hold scaled numerator for left operand
	    scaledNumRight;		// variable to hold scaled numerator for right operand

	// module finds the least common multiple of the two operand denominators
	void lcm(fraction f);

// public member modules
public:
	int resultNum,			// variable to hold the numerator of the RESULT
	    resultDenom;		// variable to hold the denominator of the RESULT
	fraction();				// constructor
	void output();			// outputs the results to the console

	// applies the input operator to the two input fractions
	void apply(fraction f, char op);

	// assigns input values two variables that represent 1 of the 2 fractions
	void assign(int numerator, int denominator);
};

// constructor initializes a default fraction to 0/1
// Postcondition: The module assigns the values 0 and 1 to the numerator
//   and denominator, respectively, and assigns those values to the fraction
//   object that's created
fraction::fraction()
{
	// initialize a fraction to 0/1
	numerator = 0;
	denominator = 1;

	// assign those values to the fraction object
	assign(numerator, denominator);
}

// applies the input operator to the two fractions
// precondition: f is an object of the fraction class and op contains +, -, *, or /
// postcondition: the operator is applied to the operand fractions that were input
//   at the terminal. The operands are scaled as needed and the results are
//   prepared for use.
void fraction::apply(fraction f, char op)
{
	// if operator is *, multiply numerators and denominators
	if (op == '*')
	{
		// multiply numerators from both fractions
		resultNum = numerator * f.numerator;

		// multiply denominators from both fractions
		resultDenom = denominator * f.denominator;
	}
	// else if operator is '/', cross multiply the fractions
	else if (op == '/')
	{
		// multiply the numerator of the left operand by the denominator of the right
		resultNum = numerator * f.denominator;

		// multiply the denominator of the left operand by the numerator of the right
		resultDenom = denominator * f.numerator;
	}
	else if (op == '+' || op == '-')
	{
		// compare denominators
		if (denominator != f.denominator)
		{
			// find a common denominator if denominators are different
			lcm(f);

			// apply operator to fractions
			// add/subtract the scaled numerators from the operands
			if (op == '+')
				resultNum = scaledNumLeft + scaledNumRight;
			else
				resultNum = scaledNumLeft - scaledNumRight;
		}
		else
		{
			// add or subtract the fractions when denominators are equivalent
			if (op == '+')
				// add numerators if operator is +
				resultNum = f.numerator + numerator;
			else
				// subtract numerators if operator is -
				resultNum = numerator - f.numerator;

			// set denominator value for result
			resultDenom = denominator;
		} // end nested if else
	} // end nested if else if
}

// assigns the numerator and denominator inputs to the fraction object
// precondition: the parameters should be positive integers.
// postcondition: the module assigns the argument values to the numerator
//   and denominator of the fraction object.
void fraction::assign(int n, int d)
{
	numerator = n;
	denominator = d;
}

// output module prints the fraction objects numerator and denominator
// postcondition: the numerator and denominator are output to the console
//   with a '/' between them.
void fraction::output()
{
	// output numerator and denominator of fraction object with a '/' between them
	cout << to_string(numerator) + "/" + to_string(denominator);
}

// find the LCM of two integers, which will be the least common denominator
// scales the smaller fraction to give it a common denominator with the larger fraction
// scaled fraction is operated on in the apply module
// precondition: f is an object of the fraction class that should have a
//   denominator value that's not equal to the denominator value of the
//   local fraction object. The denominator values should be positive integers.
// postcondition: this module finds the least common denominator of the two
//   operand fractions and then scales their values in order to prepare to
//   calculate the result.
void fraction::lcm(fraction f)
{
	// variables for this module
	int a = denominator,			// denominator of local fraction object
	    b = f.denominator,			// denominator of other fraction object
	    max = (a > b) ? a : b,		// get max value of the two denominators
	    notMax = (max == a) ? b : a;	// initialize to the denominator not used by max

	// the loop condition should always evaluate to true because this module is only
	// called when the denominators are not equal
	// the loop increments the larger denominators value until it's a common multiple
	while (a != b)
	{
		// find the common multiple that's nearest to the two integers
		if (max % a == 0 && max % b == 0)
		{
			// once the LCM is found, assign it to the result denominator
			resultDenom = max;

			// break out of loop once LCM is found
			break;
		}
		else
			// increment max to find the closest common multiple of a and b
			++max;
	} // end while

	// set scale for fractions
	scale = (max / notMax);

	// apply scale to operand fractions' numerators
	if (notMax == b)
	{
		// if notMax == b then a is the larger fractions denominator (a is left operand)
		// in this case, the scale will be initialized for the right operand (smaller)
		// scale right operand
		scaledNumRight = f.numerator * scale;

		// adjust scale for left operand
		scale = resultDenom / denominator;

		// scale left operand
		scaledNumLeft = numerator * scale;
	}
	else
	{
		// if notMax == a then b is the larger fractions denominator (b is right
		// operand) scale will be adjusted for the left operand because it's the
		// smaller fraction scale left operand
		scaledNumLeft = numerator * scale;

		// adjust scale for right operand
		scale = resultDenom / b;

		// scale right operand
		scaledNumRight = f.numerator * scale;
	} // end if else
}
