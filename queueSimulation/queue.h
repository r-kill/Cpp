// Author: Rowan Kill
// Due: 3/29/2018
// Purpose: This class implements a sequential queue data type.
//    This structure reads the items in the queue in first in,
//    first out order, meaning that the first item that's enqueued
//    will be the first item that's dequeued. Enqueued items are
//    appended to the end of the queue. To prevent the indices of
//    items from going out of bounds, the queue is implemented as
//    a circular queue. Member functions exist to determine the
//    length of the queue, if the queue is empty, and to print the
//    queue with the "<<" operator.
// Design: The queue is designed to use an array of pre-defined
//    size to maintain integer values as they're enqueued and
//    dequeued. The default queue size is 20 elements. The constructor
//    initialized an empty queue by assigning 0 to the front of
//    the queue which represents the index of the first item in
//    the queue, assigning the rear of the queue to be the index
//    immediately behind the front of the queue, and assigning
//    0 to the variable that represents the number of items in the
//    queue. Items can be enqueued as long as the queue isn't full
//    and dequeued as long as the queue is not empty. Enqueuing
//    simply takes the argument value of the enqueue() function
//    and places it at the rear of the queue, which is the first
//    index in the data array that does not contain a value. This
//    index is found with the next() function, which returns the
//    index after the index provided as an argument, keeping in
//    mind that the queue is circular. Dequeuing an item involves
//    getting the data from the first item in the queue, adjusting
//    where the front of the queue is in the data array, and finally
//    returning the value from the original front of the queue. The
//    length() function returns the variable that tracks the number
//    of elements in the array. The empty() function returns true
//    if that same variable is 0, otherwise it returns false. The
//    overloaded "<<" operator prints each item in a queue by
//    sending each item to an output stream and returning that stream.
//    The items in the queue are dequeued, send to the stream,
//    and enqueued so that the queue appears unchanged after printing.

#include <fstream>
using namespace std;

class Queue
{
public:
	typedef int Item;

	// the maximum number of elements in a queue
	static const int CAPACITY = 20;

	// constructor
	// precondition: The default constructor is called when
	//    an object of the Queue class is created.
	// postcondition: An empty queue is initialized by this
	//    function.
	Queue() { front = 0; rear = CAPACITY - 1; count = 0; }

	// enqueue
	void enqueue(Item entry);

	// dequeue
	Item dequeue();

	// length
	// precondition: The invoking queue should be initialized.
	// postcondition: This function returns the value of the
	//    counter used to count the number of items in the
	//    queue.
	int length() { return count; }

	// is empty?
	// precondition: This function doesn't accept argument
	//    values, it only expects the invoking object to be
	//    initialized.
	// postcondition: The return value will be true if the
	//    invoking queue is empty, otherwise it will return
	//    false.
	bool empty() { return count == 0; }

	// friend function - output
	friend ostream& operator<<(ostream& out_s, Queue q);
private:
	// queue array
	Item data[CAPACITY];
	int front,	// index of the first value in queue
	    rear,	// index of the last value in queue
	    count;	// number of elements in queue

	// return next index in queue
	// precondition: This function receives a positive
	//    integer value that represents an index in the
	//    queue.
	// postcondition: The index that immediately following
	//    the argument is returned, when the end of the
	//    queue is reached the next index will be the front
	//    of the queue.
	int next(int i) { return (i + 1) % CAPACITY; }
};

// enqueue
// precondition: This function is passed an Item value
//    that will be placed at the end of the queue. The
//    queue shouldn't be full.
// postcondition: The new item is appended to the rear
//    of the queue and the counter for the number of
//    Items in the queue in incremented. Nothing is
//    returned if the queue is already full.
void Queue::enqueue(Item entry)
{
	// ensure queue is not full
	if (count < CAPACITY)
	{
		rear = next(rear);	// get index in queue for new item
		data[rear] = entry;	// set new item to the next index
		++count;		// track size of queue
	} // end if
}

// dequeue
// precondition: This function doesn't require any
//    argument values.
// postcondition: If the queue isn't empty, this
//    function will return the value of the Item
//    at the front of the queue. If the queue is
//    empty, the function terminates.
Queue::Item Queue::dequeue()
{
	Item it;	// holds the item from the queue

	// ensure queue is not empty
	if (count > 0)
	{
		it = data[front];	// get data from first item in queue
		front = next(front);	// advance front to next index in queue
		--count;		// track size of queue

		// return data from original front of queue
		return it;
	} // end if
}

// overloaded << operator
// precondition: This function receives an output stream and a
//    queue object as arguments. The output stream is passed by
//    reference so that the queue can be printed.
// postcondition: Each Item in the queue is sent to the output
//    stream argument, which is then returned. The Items in the
//    queue are dequeued before being sent to the output stream,
//    then enqueued again so that they appear in the queue in the
//    same order. This leaves the queue seemingly unchanged because
//    this function has dequeued and enqueued everything.
ostream& operator<<(ostream& out_s, Queue q)
{
	Queue::Item it;		// holds the queue items
	int n = q.length();	// get size of queue

	// print items in queue, then put them back
	//    in the queue in the same order by
	//    dequeuing and then enqueuing the items
	for (int i = 0; i < n; ++i)
	{
		it = q.dequeue();	// get first item in queue
		out_s << it << ' ';	// print first item in queue
		q.enqueue(it);		// enqueue previous first item
	} // end for

	return out_s;	// return output stream
}
