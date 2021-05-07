//Name: andrew Thompson
//date due: 5/6/2021
//description: file containing all functuions for the animal game program

#pragma once
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "bintreenode.h"
#include "input.h"



//Preconditions: Option 3 called from menu
//Postconditions: displays info about the animal game
void instructions();
//Preconditions: a pointer referencing a location in a binary tree
//Postconditions: asks a quesion in that node of the binary tree, and moves the pointer accordingly
void askAndMove(Binary_Tree_Node<string>*& currPtr);
//Preconditions: a pointer of type string belonging to te binarytreenode class and a file
//Postconditions: creates the binary taxonomy tree from the contents of the file, and returns a pointer to that trees root
Binary_Tree_Node<string>* beginTree(Binary_Tree_Node<string>*& currPtr, ifstream& file);
//Preconditions: a pointer which points to the location in which a new question will be inserted
//Postconditions: creates a question and adds an animal out of user input
void learnNewAnimal(Binary_Tree_Node<string>*& currPtr);
//Preconditions: play game was chose in the menu, a pointer pointing to nullptr or an empty node
//Postconditions: runs the game, asking the user to find the animal the user is thinking of, until if finds the answer or learns a new animal
void runGame(Binary_Tree_Node<string>* currPtr);
//Preconditions: a file and a rootpnr
//Postconditions: creates the binary taxonomy tree by calling begin tree and passes it to runGame
void playGame(Binary_Tree_Node<string>*& rootPtr, ifstream& file);
//Preconditions: a taxonmy tree root pointer and a outfile
//Postconditions: saves the taxonomy tree to the file.
void save(Binary_Tree_Node<string>*& rootPtr, ofstream& outfile);
Binary_Tree_Node<string>* beginTree(Binary_Tree_Node<string>*& currPtr, ifstream& file)
{

	string input;
	getline(file, input);
	char delim = input[0];


	input = input.substr(1, input.length() - 2);


	currPtr = new Binary_Tree_Node<string>(input);
	if (delim != '(')
	{
		beginTree(currPtr->left(), file);
		beginTree(currPtr->right(), file);
	}
	else
	{
		currPtr->left() = nullptr;
		currPtr->right() = nullptr;
	}

	return currPtr;

}
void askAndMove(Binary_Tree_Node<string>*& currPtr)
{
	cout << currPtr->data();
	if (inquire("Answer "))
		currPtr = currPtr->left();
	else
		currPtr = currPtr->right();

}
void learnNewAnimal(Binary_Tree_Node<string>*& leafPtr)
{
	string guess;
	string correct;
	string newQuestion;

	guess = leafPtr->data();
	cout << "Alright, I give. What was your animal?\n";
	getline(cin, correct);
	cout << "Enter a new yes or no question that will distinguish a " << correct << " from a " << guess << ".\n";
	getline(cin, newQuestion);

	leafPtr->setData(newQuestion);
	cout << "As a " << correct << ", " << newQuestion << '\n';
	if (inquire("Answer "))
	{
		leafPtr->setLeft(new Binary_Tree_Node<string>(correct));
		leafPtr->setRight(new Binary_Tree_Node<string>(guess));
	}
	else
	{
		leafPtr->setRight(new Binary_Tree_Node<string>(correct));
		leafPtr->setLeft(new Binary_Tree_Node<string>(guess));

	}
}

void runGame(Binary_Tree_Node<string>* currPtr)
{
	cout << "Think of an animal, then press the return key";
	eatLine();
	while (!currPtr->isLeaf())
		askAndMove(currPtr);

	cout << "My guess is " + currPtr->data() << ".\n";
	if (!inquire("Am I correct? "))
		learnNewAnimal(currPtr);
	else
		cout << "\nAh, I knew it was that from the start!\n";




}
void instructions()
{

	cout << "\tThis is a learning version of twenty questions : one that not only plays the game, but learns new\n";
	cout << "\tobjects when it loses.\n";

}
void playGame(Binary_Tree_Node<string>*& rootPtr, ifstream& file)
{
	if (rootPtr->left() != nullptr)
		deleteTree<string>(rootPtr);
	rootPtr = new Binary_Tree_Node<string>();
	rootPtr = beginTree(rootPtr, file);
	//do
	runGame(rootPtr);
	//while (inquire("want to play again?"));
	//cout << "Thanks for teaching me more about animals!\n";
	return;
}
void save(Binary_Tree_Node<string>*& rootPtr, ofstream& outfile)
{
	if (rootPtr != nullptr)
	{
		if (!rootPtr->isLeaf())
			outfile << '[' + rootPtr->data() + ']' << '\n';
		else
			outfile << '(' + rootPtr->data() + ')' << '\n';
		save(rootPtr->left(), outfile);
		save(rootPtr->right(), outfile);
	}

}
