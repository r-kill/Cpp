// Author: Rowan Kill
// Due: 3/29/2018
// Purpose: The purpose of this program is to use sequential
//    queues to simulate having many queue/server pairs. For
//    example, the checkout at a grocery store has many checkout
//    lines with cashiers, in this program the checkout lines
//    are represented by queues and the cashiers are represented
//    by servers. This simulation simulates that exact scenario
//    using parameters that are input by the user. The user can
//    control the number of queue/server pairs, the probability
//    that a new customer will arrive and enqueue themselves in
//    the shortest line, the maximum amount of time that each
//    server can spend serving one customer, the duration of the
//    simulation in clock ticks that are simulated by the program,
//    and finally the seed value that's used to determine how
//    long any given transaction takes for a customer/server pair.
//    This information is used to determine the total number of
//    customers served, the average time the customers spent
//    waiting in a queue, the longest time any customer had to
//    wait, and the number of customers that remain in queues when
//    the simulation has completed.
// Design: This program is designed to use the input parameters to
//    create an array of queues and an array of transaction times
//    that holds the time remaining for each cashier working with
//    a customer. For each clock tick, a random value determines if
//    a customer arrived. If a customer arrived, it needs to be
//    enqueued in the shortest queue which is the queue with the
//    least number of items and the shortest transaction time remaining.
//    The shortest queue is found with the shortest() function.
//    Regardless of if a customer arrived, the transaction times for
//    each server must be decremented. If the transaction time for
//    a given server is 0, then that server has finished serving the
//    current customer and a new customer is served by that server.
//    The new customer is added to the total number of customers and
//    the amount of time they spent in a queue is added to a sum so
//    the average wait time can be calculated for all served customers.
//    Then a random transaction time is set for the new customer, this
//    value will be between 1 and the max transaction time that was
//    input by the user. Before moving on to the next clock tick,
//    a snapshot of the current tick, servers, and queues is printed
//    to the terminal which shows the current transaction time for
//    the servers along with the list of items in each queue for each
//    server. When the simulation is complete, the program outputs
//    the number of customers served to the terminal, along with the
//    average wait time for customers, the longest wait time of any
//    customer, and the number of customers that are still in a
//    queue. Then, the user is asked to input another set of simulation
//    parameters, which also allows the user to terminate the program
//    if they don't want to run another simulation. If the user exits,
//    then the program deletes the arrays of items and terminates to
//    prevent any memory leaks. If a new set of simulation parameters
//    is input, the arrays are still deleted, but the variables used
//    to track the progress of the simulation are reset so they can
//    be used again. Input is gathered from the user with the input()
//    function which receives the simulation parameters as arguments
//    that are passed by reference so the user can input values in that
//    function and those values will be returned to the invoking
//    function so the values can be used outside of input(). This
//    function handles getting the user input and validating the
//    values so the simulation uses proper parameters. This function
//    returns a sentinel value if the user inputs the sentinel value
//    to terminate the program, this allows the program to terminate
//    correctly when the user chooses to exit.

#include "queue.h"
#include <random>
#include <iostream>
using namespace std;

// function prototypes
int shortest(Queue queues[], int transTimes[], int size);
int input(int& numLines, int& arriveProb, int& max_transTime,
	int& duration, int& seed);

int main()
{
	// user info
	cout << "Simulation parameter rules:" << endl
	     << "    There must be at least one queue/server pair." << endl
	     << "    The probability of arrival must be an integer between"
	     << "\n      1 and 100." << endl
	     << "    The maximum transaction time must be a positive integer"
	     << "\n      value." << endl
	     << "    The duration of the simulation must be at least one tick."
	     << endl
	     << "    Enter -1 for any value (excluding the seed value) to exit"
	     << "\n      the program." << endl;

	// variables
	int time,		// simulates time
	    count = 0,		// number of people in line
	    remaining = 0,	// holds number of customers remaining at end
	    entryTime,		// time when a customer joins a line
	    wait_sum = 0,	// total time waited by a customer in line
	    longest = 0,	// holds longest wait time of all customers served
	    seed,		// seed the random value
	    numLines,		// number of queues/servers (1 queue needs 1 server)
	    arriveProb,		// probability that a customer arrives
	    max_transTime,	// maximum transaction time
	    duration = 1;	// duration of simulation in clock ticks

	// get the users input for simulation parameters
	// if the input function returns -1, it means the user input
	//    the sentinel value, so the program should terminate
	// otherwise, the arguments are passed by reference so they
	//    maintain the values input to the function
	if (input(numLines, arriveProb, max_transTime, duration, seed) == -1)
		return 0;

	// check for user exit
	while (numLines != -1 && arriveProb != -1 &&
		max_transTime != -1 && duration != -1)
	{
		// apply seed to rand()
		srand(seed);

		// create array of queues with numLines input value
		Queue *queues = new Queue[numLines];

		// create array of transaction times
		int *transTimes = new int[numLines];

		// initialize all transaction times to 0
		// initialize the array of queues
		for (int i = 0; i < numLines; ++i)
		{
			transTimes[i] = 0;
			queues[i] = Queue();
		} // end for

		// show format of snapshots for user
		cout << "\nClock  transact  arrival" << endl;
		cout << " time   times     times" << endl;

		// simulation loop - each iteration is one "clock tick"
		for (time = 0; time < duration; ++time)
		{
			// check if a customer arrived (arriveProb% of the time)
			if (rand() % 100 < arriveProb)
				// enqueue the time the customer arrived in shortest queue
				queues[shortest(queues, transTimes, numLines)].enqueue(time);

			// decrement transaction times for each queue one time
			//    per clock tick, otherwise the server is free and
			//    can serve a new customer
			// add new customer to total customers sum and calculate
			//    how long the new customer waited in line
			// generate a random transaction time for this new customer
			for (int i = 0; i < numLines; ++i)
			{
				// check if any servers are free this tick, otherwise
				//    decrement transactionTime until one is free
				if (transTimes[i] == 0)
				{
					// ensure the queue isn't empty,
					//    serve a new customer
					if (!queues[i].empty())
					{
						// add the wait time for this new
						//    customer to sum
						entryTime = queues[i].dequeue();
						wait_sum += (time - entryTime);
						++count;	// count this new customer

						// check for longest wait time
						if (time - entryTime > longest)
							longest = time - entryTime;

						// get a random transaction time for this
						//    new customer, this value is confined
						//    within a user-specified range
						transTimes[i] = (rand() % max_transTime)+1;
					} // end nested if
				}
				else
					// decrement transaction times to finish
					//    the current transaction
					--transTimes[i];
			} // end nested for

			// output snapshot
			for (int j = 0; j < numLines; ++j)
			{
				// output the current time in the first row of output
				if (j == 0)
				{
					cout.width(10);
					cout << left << time + 1 << right
					     << transTimes[j] << "  ";
					cout << queues[j] << endl;
				}
				else
				{
					// exclude the time (tick number) in other rows
					cout.width(11);
					cout << right << transTimes[j] << "  "
					     << queues[j] << endl;
				} // end nested if else
			} // end nested for
			cout << endl;	// whitespace between snapshots
		} // end nested for

		// report number of customers served and average wait time
		// ensure count > 0 to prevent division by zero
		if(count > 0)
			cout << count << " customers waited an average of "
			     << wait_sum / count << " ticks." << endl;

		// report longest wait time
		// this can be printed if no customers were served
		cout << "The longest wait time was " << longest
		     << " ticks." << endl;

		// calculate number of customers in like
		for (int i = 0; i < numLines; ++i)
			remaining += queues[i].length();

		// report number of customers still in line
		// this can be printed if no customers were served
		cout << remaining << " customers remain in line." << endl;

		// get user input for next simulation
		// if the input function returns -1, it means the user input
		//    the sentinel value, so the program should terminate
		// otherwise, the arguments are passed by reference so they
		//    maintain the values input to the function
		if (input(numLines, arriveProb, max_transTime, duration, seed) == -1)
		{
			// delete queues array and transTimes array
			delete[] queues;
			delete[] transTimes;

			// terminate the program
			return 0;
		} // end nested if

		// delete queues array and transTimes array
		delete[] queues;
		delete[] transTimes;

		// reset variables
		wait_sum = count = remaining = longest = 0;
	} // end while

    return 0;
}

// get user input for simulation parameters
// precondition: This function receives the simulation parameters
//    that the user will input as argument values that are passed
//    by reference because this is where the user inputs those values.
//    This function assumes that the user has read the rules regarding
//    the parameter values printed at the beginning of execution, but
//    has some error checking to prevent improper input values.
// postcondition: The user inputs proper values into the simulation
//    parameter variables, these are passed by reference so the function
//    can return all input values to the invoking function. If the
//    user inputs -1 for any value except the seed, then the function
//    returns -1 which tells the invoking function to terminate the
//    program. The seed value is excluded because it's acceptable to
//    seed rand() with -1.
int input(int& numLines, int& arriveProb, int& max_transTime, int& duration, int& seed)
{
	// get input parameters
	cout << "\nInput the simulation parameters:" << endl;

	// get user input for number of queues
	cout << "    Number of queue/server pairs: ";
	cin >> numLines;

	// check input value after each input so the user
	//    doesn't need to enter all of the simulation
	//    parameters before the program exits
	// ensure the user didn't exit and that there's at
	//    least 1 queue/server pair
	if (numLines == -1)
		return -1;
	else if(numLines < 1)
		while (numLines < 1)
		{
			// get user input for number of queues
			cout << "    Number of queue/server pairs: ";
			cin >> numLines;
		} // end nested while

	// get input for probability of a customer arriving
	cout << "    Arrival probability (80 = 80%): ";
	cin >> arriveProb;

	// ensure user did not exit and that probability falls
	//    between 1 and 100 (inclusive)
	if (arriveProb == -1)
		return -1;
	else if (arriveProb > 100 || arriveProb < 1)
		while (arriveProb > 100 || arriveProb < 1)
		{
			// get input for probability of a customer arriving
			cout << "    Arrival probability (80 = 80%): ";
			cin >> arriveProb;
		} // end nested while

	// max time in a transaction
	cout << "    Max transaction time: ";
	cin >> max_transTime;

	// ensure user didn't exit and that the maximum
	//    transaction time is a positive integer
	if (max_transTime == -1)
		return -1;
	else if(max_transTime < 1)
		while (max_transTime < 1)
		{
			// max time in a transaction
			cout << "    Max transaction time: ";
			cin >> max_transTime;
		} // end nested while

	// get input for the duration of the whole simulation
	cout << "    Duration of simulation: ";
	cin >> duration;

	// ensure user didn't exit and that the simulation is
	//    at least 1 tick long
	if (duration == -1)
		return -1;
	else if (duration < 1)
		while (duration < 1)
		{
			// get input for the duration of the whole simulation
			cout << "    Duration of simulation: ";
			cin >> duration;

			// check input
			if (duration == -1)
				return -1;
		} // end nested while

	// get the seed for rand()
	cout << "    Seed for random value generation: ";
	cin >> seed;
}

// find the shortest queue in an array of queues,
//    then return the index of that queue
// precondition: This function receives the array of queues,
//    the array of transaction times, and an integer that
//    represents the number of server/queue pairs as argument
//    values. These arrays should be initialized, but don't
//    need to contain any particular values. The integer should
//    be a positive value that's greater than one.
// postcondition: This function returns the index of the
//    shortest queue in the array of queues. The shortest
//    queue is a queue that has the smallest length() value,
//    if two queues have the same length() value and are
//    both the shortest queues in the array, then the queue
//    that has the shortest transaction time remaining is
//    considered the smallest queue.
int shortest(Queue queues[], int transTimes[], int size)
{
	// index of smallest queue, assume queues[0] is smallest
	//    to begin
	int small = 0;

	for (int i = 0; i < size; ++i)
	{
		// check if one queue is shorter than another
		if (queues[i].length() < queues[small].length())
			small = i;
		else if (queues[i].length() == queues[small].length() &&
			  transTimes[i] < transTimes[small])
			// if there are two "shortest" queues with the same length,
			//    choose the one with a teller that will be open sooner
			// note that what two shortest queues have the same length
			//    AND have the same transaction time, then the new
			//    customer should choose the first shortest queue
			small = i;
	} // end for

	// return index of smallest queue
	return small;
}
