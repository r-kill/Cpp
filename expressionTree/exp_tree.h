// Author: Rowan Kill
// Due: 4/26/2018
// Purpose: This class implements an expression tree that can
//    be used to evaluate and print a fully parenthesized
//    expression. The expressions are read individually from an
//    input stream that's provided by the client, the operators
//    and operands of the expression are stored in individual
//    nodes within the tree. These nodes are connected with
//    pointers. The expression can also be evaluated with a
//    postorder traversal that applies the operator to the operands
//    and returns that value.
// Design: The class is designed to have a set of public functions
//    that call private recursive functions that do most of the work
//    that would be expected of the public functions. The tree is
//    pointer-based, so there must be a default constructor and
//    destructor. The constructor initializes an empty list and the
//    destructor calls a private recursive function to destroy the
//    nodes in the tree. The trees must be empty before they're built
//    recursively based on the character read from a stream. If an
//    operand is read, an operand node is created, which has NULL
//    subtrees. If an operator is read, then an operator node is
//    created, which has two operand children. Operator nodes can
//    contain another operator node in a subtree, which represents
//    a nested expression such as "(8+2)" in the expression
//    ((8+2) - 4). This is done recursively and allows the expressions
//    to be evaluated starting with the innermost expression. The
//    nodes are destroyed recursively with a postorder traversal that
//    deletes nodes in the left, then right subtrees, then deleted the
//    root node of the subtrees. This repeats until the tree is empty.
//    The tree can then be printed be using the recursive preorder,
//    inorder, or postorder methods. The corresponding functions print
//    the expression tree in prefix, infix, or postfix notation. When
//    an operand is encountered by any of the functions, its output
//    to the terminal. If an operator is encountered, it's left and
//    right subtrees are traversed and the operator is printed in the
//    appropriate order. For infix notation, the parentheses must also
//    be printed in the appropriate order. The value of the expression
//    is calculated by using a postorder traversal to recursively find
//    the value of all operator trees (an operator with two operand
//    children) starting from the bottom leftmost tree. The result of
//    each operator tree is found by recursively evaluating the left
//    and right subtrees, then applying the operator in the root of
//    the subtrees to the operands now in the subtrees and returning
//    that value.

#include <fstream>
#include <iostream>
using namespace std;

class ExpTree
{
public:
	// constructor
	// postcondition: Initializes an empty expression tree.
	ExpTree() { root = NULL; }

	// destructor - calls private recursive destroy() to delete nodes
	// precondition: An expression tree exists that can be destroyed.
	// postcondition: The expression tree object and its nodes are
	//    recursively deleted with the private destroy() function.
	~ExpTree() { destroy(root); }

	// build the tree
	void build(istream& in_s);

	// printing the tree in prefix notation
	// precondition: This function has no special requirements.
	// postcondition: The expression within the tree, if any,
	//    is printed in prefix notation using a recursive
	//    function that implements a preorder traversal.
	void prefix() { r_prefix(root); }

	// printing the tree in infix notation
	// precondition: This function has no special requirements.
	// postcondition: The expression within the tree, if any,
	//    is printed in infix notation using a recursive
	//    function that implements a inorder traversal.
	void infix() { r_infix(root); }

	// printing the tree in postfix notation
	// precondition: This function has no special requirements.
	// postcondition: The expression within the tree, if any,
	//    is printed in postfix notation using a recursive
	//    function that implements a postorder traversal.
	void postfix() { r_postfix(root); }

	// calculate and return the value of the tree
	// precondition: This function has no special requirements.
	// postcondition: This function calls a private recursive
	//    function that traverses the tree and calculates the
	//    value of the expression.
	int value() { return r_value(root); }

private:
	struct Node
	{
		int operand;	// holds the operand
		char optr;	// holds the operator
		Node *left;	// points to the left subtree
		Node *right;	// points to the right subtree
	};
	Node *root;		// points to the root of the tree

	// destroy nodes in the tree recursively
	void destroy(Node *p);

	// build the tree recursively
	Node* r_build(istream& in_s);

	// print the tree in prefix notation recursively
	void r_prefix(Node *r);

	// print the tree in infix notation recursively
	void r_infix(Node *r);

	// print the tree in postfix notation recursively
	void r_postfix(Node *r);

	// calculate the value of the expression tree recursively
	int r_value(Node *r);
};

// build the tree
// precondition: This function receives an input file stream that
//    is passed to the private recursive function. The class is
//    designed for this stream to be a file to be read.
// postcondition: This function destroys the invoking tree to ensure
//    no values from previous expressions exist in the tree. Then the
//    private recursive function is called and passed the file stream.
void ExpTree::build(istream& in_s)
{
	destroy(root);		// ensure list is empty before building
	root = r_build(in_s);	// recursively build the tree
}

// destroy the tree
// precondition: This function receives a pointer to a node
//    in the tree as an argument, the tree can be empty.
// postcondition: This function recursively visits and deletes
//    each node in the subtrees of the argument node, then
//    deleted the node passed to the function. If the tree is
//    empty, then nothing needs to be deleted.
void ExpTree::destroy(Node *p)
{
	// make sure list isn't already empty
	if (p != NULL)
	{
		// destroy nodes with postorder traversal
		destroy(p->left);
		destroy(p->right);
		delete p;
	} // end if
}

// recursively builds the tree and returns a pointer to the root node
// precondition: The invoking tree should be empty before this function
//    is called because it reads expressions from a file and stores them
//    in the invoking tree. The input stream should be open and available
//    for extraction, ideally this would be a file. The expressions, if
//    any, should be fully parenthesized.
// postcondition: This function recursively creates nodes containing the
//    operators and operands. Operator nodes contain the operator character
//    and have two operands as children, but they can be nested within each
//    other. This means that an operator node can have another operator node
//    in a subtree, but the bottom-most nested operator nodes must have two
//    operand children and must evaluate to an operand value. The operand
//    nodes contain the value of the operand and their left and right
//    subtrees are NULL. This is how the expression tree is created for each
//    expression. This function can only create one tree at a time, so
//    expressions are built from a file one-by-one. The client is responsible
//    for ensuring the entire file was read.
ExpTree::Node* ExpTree::r_build(istream& in_s)
{
	char ch;	// store characters read from the stream
	Node *temp;	// used to build nodes
	in_s >> ch;	// read a char from the input stream

	// if the character read is an operand then create a leaf for it
	if (isdigit(ch))
	{
		// create new node
		temp = new Node;
		temp->operand = ch - '0';	// convert value out of ASCII

		// subtrees of operands are always NULL, only operators
		//    have subtrees which contain two operands
		temp->left = NULL;
		temp->right = NULL;
	}
	else // if the character read is a left parenthesis
	{
		// create new node for the operator in the expression
		//    following the '('
		temp = new Node;

		// recursively read the left operand and store it in
		//    the left subtree of the new node
		temp->left = r_build(in_s);

		// read the operator and put it in the node just created
		in_s >> temp->optr;

		// recursively read the right operand and store it in the
		//    right subtree of the new node
		temp->right = r_build(in_s);

		in_s >> ch;	// read the right parenthesis ')'
	} // end nested if else

	// return the root of the tree
	return temp;
}

// recursively prints the expression in prefix notation
// precondition: This function doesn't have special requirements.
//    The tree shouldn't be empty, but if it's empty then there's
//    simply no output created by this function. The function receives
//    a pointer to the root of the invoking expression tree.
// postcondition: If the tree isn't empty, recursively traverse the
//    tree with a preorder traversal. Print the operator character
//    for each operator tree, then print the values of operators left
//    and right subtrees recursively. Print the values of the operands
//    in the operand nodes.
void ExpTree::r_prefix(Node *r)
{
	// ensure tree isn't empty
	if (r != NULL)
	{
		// see if pointer is an operand node or an operator node
		if (r->left == NULL)
			// if the node has an operand, print it
			cout << r->operand << ' ';
		else
		{
			// if the node has an operator, print the operator
			cout << r->optr << ' ';

			// recursively print the left and right subtrees
			//    of the operator
			r_prefix(r->left);
			r_prefix(r->right);
		} // end nested if else
	} // end outer if
}

// recursively prints the expression in infix notation
// precondition: This function doesn't have special requirements.
//    The tree shouldn't be empty, but if it's empty then there's
//    simply no output created by this function. The function receives
//    a pointer to the root of the invoking expression tree.
// postcondition: If the tree isn't empty, recursively traverse the
//    tree with an inorder traversal. Recursively print the value of
//    the operator nodes left subtree, then print the operator, and
//    finally print the value of the operator nodes right subtree
//    recursively. Before traversing the left subtree, print an
//    opening parenthesis '(', then print a closing parenthesis ')'
//    after the recursive traversal of the right subtree. This
//    function prints a fully parenthesized infix expression from
//    the invoking expression tree.
void ExpTree::r_infix(Node *r)
{
	// ensure tree isn't empty
	if (r != NULL)
	{
		// see if pointer points to an operand node or
		//    an operator node
		if (r->left == NULL)
			// if the node has an operand, print it
			cout << r->operand << ' ';
		else
		{
			// print the left parenthesis '('
			cout << "( ";

			// recursively print the operands in the left
			//    subtree of the operator
			r_infix(r->left);

			// print the operator
			cout << r->optr << ' ';

			// recursively print the operands in the right
			//    subtree of the operator
			r_infix(r->right);

			// print the left parenthesis ')'
			cout << ") ";
		} // end nested if else
	} // end outer if
}

// recursively prints the expression in postfix notation
// precondition: This function doesn't have special requirements.
//    The tree shouldn't be empty, but if it's empty then there's
//    simply no output created by this function. The function receives
//    a pointer to the root of the invoking expression tree.
// postcondition: If the tree isn't empty, recursively traverse the
//    tree with a postorder traversal. Print the values of operator nodes
//    left and right subtrees recursively, then print the values of the
//    operands in the resulting operand nodes. Finally print the operator
//    nodes whose subtrees were just traversed. This function prints the
//    expression from the invoking expression tree in postfix notation.
void ExpTree::r_postfix(Node *r)
{
	// ensure tree isn't empty
	if (r != NULL)
	{
		// see if pointer is an operand node or an operator node
		if (r->left == NULL)
			// if the node has an operand, print it
			// operands have NULL subtrees, checking for either
			//    one works fine
			cout << r->operand << ' ';
		else
		{
			// recursively print the left and right subtrees of the
			//    operator
			r_postfix(r->left);
			r_postfix(r->right);

			// if the node has an operator, print the operator
			cout << r->optr << ' ';
		} // end nested if else
	} // end outer if
}

// recursively calculate the value of the expression tree
// precondition: This function doesn't have special requirements.
//    The tree shouldn't be empty, but if it's empty then the
//    function just returns zero because that's the result of the
//    expression. The function receives a pointer to the root of
//    the invoking expression tree.
// postcondition: Using a recursive postorder traversal, this
//    function calculates the result of the expression held in
//    the invoking tree. If the tree has values, the root operator
//    nodes left and right subtrees are traversed and their values
//    are calculated. Then the operator is applied to the resulting
//    operands, and that value is returned. During the traversal,
//    the values in operand nodes are just returned, while the
//    operator nodes first have their left and right subtrees
//    traversed and evaluated. Then the operator is applied to the
//    two operands in the subtrees. This relies on the nodes of the
//    tree having the attributes specified in the r_build() function,
//    but since the tree needs to be build before this function can
//    provide any useful output, the function can assume that the
//    nodes will have those attributes.
int ExpTree::r_value(Node *r)
{
	int l_val,	// hold the value of the left subtree
		r_val;	// hold the value of the right subtree

	// determine what to print
	if (r == NULL)
		// return 0 if the tree is empty
		return 0;
	else if (r->left == NULL)
		// if there's only 1 operand, return it - base case
		// 1 operand means that is the value of the expression
		return r->operand;
	else
	{
		// in this case the pointer points to an operator
		// solve the expression by recursively solving any
		//    expressions in the left and right subtrees
		l_val = r_value(r->left);
		r_val = r_value(r->right);

		// apply the operator in the current node to the operands
		//    in the left and right subtrees
		if (r->optr == '+')
			return l_val + r_val;
		else if (r->optr == '-')
			return l_val - r_val;
		else if (r->optr == '*')
			return l_val * r_val;
		else if (r->optr == '/')
			return l_val / r_val;
	} // end if else if
}
