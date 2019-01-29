// Author: Rowan Kill
// Due: 4/10/2018
// Purpose: This program implements and compares the execution times of
//     three different sorting algorithms. The sorting algorithms are
//     compared by the number of executions of each algorithms
//     characteristic operation.
// Design: The user determines how many values to sort, the values are
//     randomly generated using a seed that's also provided by the user.
//     The user can choose to print the resulting arrays to show the
//     sorted and unsorted values. The program creates three arrays that
//     each contain the same random values, initially they're unsorted.
//     If the user wants to print the unsorted values, then a fourth
//     array is created to hold those values in that order, this is so
//     the values can be printed after the sorting has been complete
//     for easier comparison. The random values are bounded using
//     modulus 1000 for readability, but were tested with and without
//     that boundary. After the arrays have been created, the three to
//     be sorted are passed to their respective sorting functions along
//     with the counter to count the number of characteristic operation
//     executions. When they complete the sorting, the arrays are
//     output to the terminal if the user specified such. The arrays
//     then need to be deleted and the user is asked if they would like
//     to continue sorting values. The user can exit the program by
//     entering any value less than 1 for the number of values to sort.

#include <iostream>
using namespace std;

// function prototypes
void print(int a[], int size);
void insertSort(int a[], int size, int& opCount);
void merge(int a[], int low, int mid, int high, int& opCount);
void merge_sort(int a[], int low, int high, int& opCount);
void quickSort(int a[], int low, int high, int& opCount);
void partition(int a[], int low, int high, int pivot, int& i, int &j, int& opCount);

int main()
{
	// variables
	int size,		// holds size of arrays
	    seed,		// holds the seed for rand()
	    num,		// holds return value of rand()
	    count = 0;		// counts the characteristic operations for sorts
	char verbose;		// print unsorted and sorted values if == 'y'

	// declare and initialize arrays - dynamic size
	int *aInsert = NULL,
	    *aMerge = NULL,
	    *aQuick = NULL,
	    *aUnsorted = NULL;

	// user info
	cout << "Compare Insertion Sort, Merge Sort, and Quick Sort."
	     << endl;
	cout << "The number of values to sort must be between 1 and 5000."
	     << endl;
	cout << "To exit the program, enter 0 for the number of values"
	     << " to sort." << endl;

	// get user input for size
	cout << "\nEnter the number of values to sort: ";
	cin >> size;

	// ensure user didn't exit the program
	while (size > 0)
	{
		// verify size is between 1 and 5000
		if (size <= 5000)
		{
			// create arrays with given size
			aInsert = new int[size];
			aMerge = new int[size];
			aQuick = new int[size];
		}
		else
		{
			while(size > 5000 || size <= 0)
			{
				// error message
				cout << "The number of values to sort must be between"
				     << " 1 and 5000." << endl;

				// get new input for size
				cout << "Enter the number of values to sort (1 - 5000): ";
				cin >> size;
			} // end nested while

			// create arrays with given size
			aInsert = new int[size];
			aMerge = new int[size];
			aQuick = new int[size];
		} // end nested if else

		// continue getting input - seed
		cout << "Enter the seed value for generating random numbers: ";
		cin >> seed;

		// get user input for printing unsorted and sorted values
		cout << "Print the values? ";
		cin >> verbose;

		// if user wants to print unsorted and sorted values,
		//    create the array of unsorted values with the
		//    size specified by the user (it will be filled
		//    and printed after sorting completes)
		if (verbose == 'y')
			aUnsorted = new int[size];

		// verify verbose == 'y' or 'n'
		while (verbose != 'y' && verbose != 'n')
		{
			// error message and get new input value
			cout << "Input must be the character 'y' or the character 'n'."
			     << "\nPrint the values? ";
			cin >> verbose;
		} // end nested while

		// seed rand()
		srand(seed);

		// generate values to put in arrays
		for (int i = 0; i < size; ++i)
		{
			num = rand() % 1000;
			aInsert[i] = aMerge[i] = aQuick[i] = num;

			// fill unsorted array with values if necessary
			if (verbose == 'y')
				aUnsorted[i] = num;
		} // end nested for

		// call sorting algorithms and print number of
		//    executions of characteristic operation
		insertSort(aInsert, size, count);
		cout << "\nInsertion Sort count = " << count << endl;
		count = 0;
		merge_sort(aMerge, 0, size - 1, count);
		cout << "Merge Sort count = " << count << endl;
		count = 0;
		quickSort(aQuick, 0, size - 1, count);
		cout << "Quick Sort count = " << count << endl;
		count = 0;

		// print unsorted and sorted values
		if (verbose == 'y')
		{
			// whitespace
			cout << endl << "Unsorted: ";
			print(aUnsorted, size);
			cout << "Insert: ";
			print(aInsert, size);
			cout << "Merged: ";
			print(aMerge, size);
			cout << "Quick: ";
			print(aQuick, size);
		} // end nested if

		// delete dynamic arrays
		delete[] aInsert;
		delete[] aMerge;
		delete[] aQuick;

		// delete unsorted if it exists
		if (verbose == 'y')
			delete[] aUnsorted;

		// get user input for size
		cout << "======================================="
		     << "==============================" << endl;
		cout << "\nEnter the number of values to sort: ";
		cin >> size;
	} // end while

    return 0;
}

// print an array passed as argument
// precondition: This function assumes that the array argument contains values
//     and that the size argument is the actual size of the array argument. The
//     array should be an array of integer values and the size should be an
//     integer.
// postcondition: The array is printed to the terminal, a newline character is
//     printed after 10 values are printed for readability. The array i
//     unchanged.
void print(int a[], int size)
{
	// iterate through each array element
	for (int i = 0; i < size; ++i)
	{
		// print each element
		cout << a[i] << ' ';

		// newline after every 10 values printed
		if (i > 0 && i % 10 == 0)
			cout << endl << "\t";
	} // end for

	// print whitespace for next output statement
	cout << endl;
}

// insertion sort
// precondition: This function receives an array of integers, the integer
//     representation of the size of the array, and a reference to a
//     counter that's used to count the number of executions of the
//     characteristic operation. The array should contain values to sort
//     and the size of the array should be a positive integer.
// postcondition: This function returns the sorted array and the counter.
//     The array is altered when the sorting occurs, sorting is done when
//     an element in the array has a higher value than the element that
//     immediately precedes it in the array. This ends up placing the
//     smaller values at the front of the array.
void insertSort(int a[], int size, int& opCount)
{
	int index,	// used to access elements in a[]
	    temp;	// holds original value in element swap

	// iterate through array
	for (int i = 1; i < size; ++i)
	{
		index = i;

		// compare consecutive elements in array
		while (index > 0 && a[index] < a[index - 1])
		{
			// exchange indices, swap the values so that the lower
			//    of the two comes before the larger in the array
			temp = a[index];
			a[index] = a[index - 1];
			a[index - 1] = temp;

			// increment characteristic operation counter
			++opCount;

			// decrement index
			--index;
		} // end nested while
	} // end outer for
}

// merge sort
// precondition: This function receives an array of unsorted integer values,
//     the low and high arguments represent the positive integer indices of
//     the first and last elements in the array. The function also receives a
//     counter to count the number of executions of a characteristic operation,
//     this value is passed by reference so it can be returned along with the
//     sorted array.
// postcondition: This function splits the array into smaller segments
//     recursively until those segments are sorted, then merges those segments
//     together so they create a larger sorted segment. This process repeats
//     until the entire array is sorted.
void merge_sort(int a[], int low, int high, int& opCount)
{
	int mid;

	// ensure array is not empty
	if (low < high)
	{
		mid = (low + high) / 2;    // middle of array

		// recursively split array into smaller halves
		// keep halving left half of array
		merge_sort(a, low, mid, opCount);

		// keep halving right half of array
		merge_sort(a, mid + 1, high, opCount);

		// merge the halves of arrays
		merge(a, low, mid, high, opCount);
	} // end if
}

// merge two sorted array segments for merge sort
// precondition: The arguments are an array of unsorted integer values,
//    three positive integer values that represent indices in the array,
//    and an integer counter to count the number of characteristic
//    operation executions.
// postcondition: The function copies the array argument into a local
//     array and then searches the array with two index values, which
//     allows the array to be sorted from the first element to the middle
//     and from the element after the middle to the end of the array at
//     the same time. This is effectively searching both "segments" of
//     the array created by merge_sort(), but we're searching one array
//     with two indices at the same time. If one segment is smaller than
//     the other, then the smaller segment will be fully traversed before
//     the larger one. In that case, the larger segment is sorted so all
//     of its values will be larger than those in the smaller segment,
//     meaning we can just append the remainder of the larger segment to
//     the end of the sorted array. Sorting occurs when traversing the two
//     segments, the value at the given index in the first segment is
//     compared to the value at the given index of the second segment, the
//     smaller of the two is put into the sorted array and the index for
//     that segment is incremented to check the next value in that segment.
//     The index for the other segment is not incremented to avoid skipping
//     any values from either segment.
void merge(int a[], int low, int mid, int high, int& opCount)
{
	// note that local[] must be declared in this way for Linux/Unix
	//     (which we're expected to use for these programs),
	//     declaring this array like the arrays in main()
	//     (int *p = new int[size];) causes the program to leak
	//     memory and overflow the stack on Linux/Unix. For
	//     Windows, this array must be declared like those
	//     declared in main() (shown previously in this comment)
	//     because the argument "high" cannot be used as a constant
	//     on Windows. This is not the case for Linux/Unix.
	int local[high];	// local array, copy of a[]
	int i1 = low,		// used to index left half
	    i2 = mid + 1,	// used to index right half
	    index = low;	// used to index merged list

	// copy elements in a[] to local[]
	for (int i = low; i <= high; ++i)
	{
		local[i] = a[i];

		// increment characteristic operation counter
		++opCount;
	} // end for

	// merge the two array segments into a[]
	while (i1 <= mid && i2 <= high)
	{
		// sort the values from both segments by comparing
		//    values in each array at the same index the
		//    smaller value from both segments is placed at
		//    the beginning of the sorted array the index
		//    variable for the segment that contains the
		//    smaller value is incremented, the index variable
		//    for the other segment is not incremented to
		//    avoid skipping values in either segment
		if (local[i1] < local[i2])
		{
			a[index] = local[i1];

			// increment i1
			++i1;

			// increment characteristic operation counter
			++opCount;
		}
		else
		{
			a[index] = local[i2];

			// increment i2
			++i2;

			// increment characteristic operation counter
			++opCount;
		} // end nested if else

		// increment index
		++index;
	} // end while

	// if one segment has more elements than the other, and all
	//    values have been checked from the smaller segment, then
	//    append all remaining elements from larger segment into
	//    sorted array because they should be in order
	// basically, if one array is traversed before the other,
	//    then finish traversing the other and append everything
	//    to the end of the sorted array
	while (i1 <= mid)
	{
		a[index] = local[i1];

		// increment index variables (index, i1)
		++index;
		++i1;

		// increment characteristic operation counter
		++opCount;
	} // end while
	while (i2 <= high)
	{
		a[index] = local[i2];

		// increment index variables (index, i2)
		++index;
		++i2;

		// increment characteristic operation counter
		++opCount;
	} // end while
}

// quick sort
// precondition: This function receives an array of unsorted integer
//     values, two positive integer values that represent the first
//     and last index in the array, and another integer value that is
//     used to count the number of executions of the characteristic
//     operation. This counter is passed by reference so it can be
//     returned with the sorted array.
// postcondition: The function recursively sorts an array by partitioning
//     it into three segments based on a pivot value in the array. The
//     segments are then sorted individually using recursion. The function
//     returns the sorted array and the number of executions of the
//     characteristic operation.
void quickSort(int a[], int low, int high, int& opCount)
{
	int pivot,		// where to split array
	    lastS1,		// index of the last value of S1
	    firstS3;		// index of the first value of S3

	// ensure array isn't empty
	if (low < high)
	{
		// set pivot to the lowest value in the array argument a[]
		pivot = a[low];

		// partition the array, sort it into S1, S2, and S3
		partition(a, low, high, pivot, lastS1, firstS3, opCount);

		// recursively sort the S1 and S3
		quickSort(a, low, lastS1, opCount);
		quickSort(a, firstS3, high, opCount);
	} // end if
}

// partition an array into segments (S1, S2, S3) for quick sort
// precondition: This function receives an array of unsorted integer values,
//     two positive integers that represent the first and last indices in
//     the array, another positive integer value that represents the index of
//     the value chosen from the array to be the pivot. The next two arguments
//     passed to this function are uninitialized and passed by reference, their
//     values are calculated in this function and returned to quick_sort()
//     where they're used to determine the indices of the segments created in
//     this function so they can be sorted. The last argument is an integer
//     that's passed by reference, this is used to count the number of executions
//     of the characteristic operation.
// postcondition: The function creates three segments, the first one contains the
//     values that are lower than the value of the pivot, the second segment
//     contains the values that are equivalent to the pivot, and the last segment
//     contains the values greater than the pivot. While sorting, there's a fourth
//     segment that contains the values that have not been sorted yet. In order
//     to index the array properly, the segments begin at indices that are not
//     part of the array so the array is initially one large segment of unsorted
//     values. As they're sorted the indices for the segments move around the array.
//     When a value is less than the pivot, the first segment is expanded to
//     accommodate this value, then the last value in that segment is swapped
//     with the first value in the segment of unsorted values before that segment
//     is shrunk by one value. When a value that's equivalent to the pivot is
//     encountered, the segment of unsorted values is shrunk and no values need
//     to be swapped. When a value is greater than the pivot, the third segment
//     is expanded, then the first value from the unsorted segment is swapped
//     with the first value of the third segment. In this case we don't change
//     the unsorted segment size because we still need to sort the value that
//     was swapped from the third segment.
void partition(int a[], int low, int high, int pivot, int& i, int &j, int& opCount)
{
	int lastS1 = low - 1,		// index of the last element in S1
	    firstU = low,		// index of the first unknown value in array
	    firstS3 = high + 1,		// index of the fist element in S3
	    temp;			// holds a value that's being swapped

	// sort unknowns into S1, S2, or S3
	// structure of array for quick sort:
	// |---------|----|----------|-------------|
	// |   S1    | S2 | Unknowns |       S3    |
	// |---------|----|----------|-------------|
	// therefore, when firstU == firstS3, all of
	//    the unknown values have been sorted
	while (firstU < firstS3)
	{
		// if the first unknown value is less than the pivot,
		//    then put it into S1
		if (a[firstU] < pivot)
		{
			// expand S1 so it can accommodate the value from firstU
			++lastS1;

			// swap lastS1 with firstU
			temp = a[lastS1];
			a[lastS1] = a[firstU];
			a[firstU] = temp;

			// increment firstU to shrink partition for unknown values
			// this ensures S1 is the correct size after adding another
			//    value to it
			++firstU;
		}
		else if (a[firstU] == pivot)
			// if element at firstU == pivot, then add it to S2
			// to do that, just move firstU one index to the right
			//    so that the value that's equivalent to the pivot
			//    is just absorbed by S2
			++firstU;
		else
		{
			// if a[firstU] > pivot, add it to S3
			--firstS3;	// expand boundary of S3

			// swap firstU with firstS3, expanding S3 put the last element
			//    in unknown at the front of S3, so swapping the last element
			//    of unknown (now the first element in S3) with the first
			//    element of unknown puts the first element in unknown at the
			//    front of S3, which is where we want it
			temp = a[firstU];
			a[firstU] = a[firstS3];
			a[firstS3] = temp;
		} // end nested if else

		// increment characteristic operation counter
		++opCount;
	} // end while

	// assign lastS1 and firstS3 to i and j so they're both
	//    returned to merge_sort()
	i = lastS1;
	j = firstS3;
}
