//Jack Dinkel
//CSCI 2270 - Hoenigman
//Final Project

//HashTable class file

#include <iostream>
#include "HashTable.h"

using namespace std;

HashTable::HashTable(int size){ //ctor
	hashTable = new Movie[size]; //initialize hashtable as an array
	table_size = size; //set size of table

	for (int i = 0; i < table_size; i++){ //set every value in the hashtable to NULL
		hashTable[i].next = NULL;
	}
}

HashTable::~HashTable(){ //dtor
}

void HashTable::insertMovie(Movie *newMovie){ //inserts a movie into the hashtable
	int index = hashFunction(newMovie->title);
	bool added = false;

	if (hashTable[index].next == NULL){ //add to beginning of linked list
		hashTable[index].next = newMovie;
	}
	else{
		Movie *traverse = new Movie; //Movie node used to move through the linked list

		traverse = &hashTable[index]; //start at the begining of the list

		while (traverse->next != NULL){
			if (newMovie->title < traverse->next->title){ //if it has reached the spot to insert
				newMovie->next = traverse->next;
				traverse->next = newMovie;
				added = true;
				break;
			}
			traverse = traverse->next;
		}

		if (!added){ //add to the end of linked list
			newMovie->next = NULL;
			traverse->next = newMovie;
		}
	}
}

Movie* HashTable::findMovie(string in_title){ //searches for a movie inside the hashtable
	int index = hashFunction(in_title); //find location of Movie inside the hashtable
	Movie *traverse = new Movie; //Movie node used to move through the linked list

	traverse = &hashTable[index]; //start at the beginning of the list

	while (traverse->next != NULL){
		if (traverse->next->title == in_title){ //if the titles match
			return traverse->next;
		}
		traverse = traverse->next;
	}

	traverse = NULL;
	return traverse; //return NULL
}

void HashTable::deleteMovie(string in_title){ //remove a movie from the hashtable
	int index = hashFunction(in_title); //find location of Movie inside the hashtable
	Movie *traverse = new Movie; //Movie node used to move through the linked list

	traverse = &hashTable[index]; //start at the beginning of the list

	while (traverse->next != NULL){
		if (traverse->next->title == in_title){ //if the titles match
			traverse->next = traverse->next->next; //overwrite the old node
			return;
		}
		traverse = traverse->next;
	}

	cout << "not found" << endl; //if the node is never found
	return;
}

void HashTable::printInventory(){ //prints the contents of the hashtable
	int count = 0; //used to keep track of whether anything is ever printed
	Movie *traverse = new Movie; //Movie node used to move through the linked list

	for (int i = 0; i < table_size; i++){ //for every linked list in the table
		traverse = &hashTable[i]; //start at the beginning of the list

		while (traverse->next != NULL){
			if (traverse->next->title.size() > 0){ //if the title exists
				cout << traverse->next->title << ":" << traverse->next->year << endl; //print
				count++;
			}
			traverse = traverse->next;
		}
	}

	if (count == 0){ //if nothing was ever printed (the table is empty)
		cout << "empty" << endl;
	}
}

int HashTable::hashFunction(string in_title){ //hash function, adds up ASCII values and mods by hashtable size
	int hash = 0;

	for (int i = 0; i < in_title.length(); i++){ //for each character in the string
		hash += in_title[i]; //add up the ASCII values for each character
	}
	hash %= table_size; //mod by the table size

	return hash;
}