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
				cout << "Movie found in position: " << i << endl;
                cout << "\tTitle: " << traverse->next->title << endl;
                cout << "\tYear: " << traverse->next->year << endl;
                cout << "\tRanking: " << traverse->next->ranking << endl;
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

bool HashTable::ham(string in_title, string compare_title){
	string in_title_inverse = "";
	string compare_title_inverse = "";
	float ham = 0;
	float score1;
	float score2;

	for (int i = in_title.length()-1; i >= 0; i--){
        in_title_inverse += in_title[i];
    }
    for (int i = compare_title.length()-1; i >= 0; i--){
        compare_title_inverse += compare_title[i];
    }


    for (int i = 0; i < in_title.length(); i++){
        if (in_title[i] != compare_title[i]){
            ham++;
        }
    }

    score1 = (in_title.length() - ham) / in_title.length();

    cout << score1 << endl;


    ham = 0;


    for (int i = 0; i < in_title_inverse.length(); i++){
        if (in_title_inverse[i] != compare_title_inverse[i]){
            ham++;
        }
    }

    score2 = (in_title_inverse.length() - ham) / in_title_inverse.length();

    cout << score2 << endl;
    if (score1 < score2){
    	score1 = score2;
    }
    if (score2 >= .5){
    	return true;
    }
    else{
    	return false;
    }
}