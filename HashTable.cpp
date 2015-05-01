//Jack Dinkel
//CSCI 2270 - Hoenigman
//Final Project

//HashTable class file

#include <iostream>
#include "HashTable.h" //include the header file

using namespace std;

HashTable::HashTable(int size){
	/*
    Function prototype:
    HashTable::HashTable(size);

    Function Description:
    Constructor for the HashTable Class
    Initializes the hash table as an array of Movies of an inputed size
    Sets each Movie in the hashtable to null

    Example:
    HashTable h(10);

    Pre-condition:
    None

    Post-condition:
    A HashTable of type Movie is created.
    Each Movie is set to null
    */

	hashTable = new Movie[size]; //initialize hashtable as an array
	table_size = size; //set size of table

	for (int i = 0; i < table_size; i++){ //set every value in the hashtable to NULL
		hashTable[i].next = NULL;
	}
}

HashTable::~HashTable(){ //dtor
}

void HashTable::insertMovie(Movie *newMovie){
	/*
    Function prototype:
    void HashTable::insertMovie(Movie*);

    Function Description:
    Inserts a movie into the hashtable
    Calls hashFunction() to determine where to store it
    Uses a linked list to manage collisions
    Sorts in the linked list alphabetically

    Example:
    Movie *newMovie = new Movie;
    //set newMovie characteristics (title, year, ranking, etc...)
	h.insertMovie(newMovie);

    Pre-condition:
    A hashTable of type Movie has been initialized
    There can be any number of movies in it

    Post-condition:
    The hashTable will contain newMovie
    */

	int index = hashFunction(newMovie->title); //finds the index by using the hashFunction
	bool added = false; //determines whether to add to the end of a linked list

	//add to beginning of linked list
	if (hashTable[index].next == NULL){
		hashTable[index].next = newMovie;
	}
	//add to the middle of linked list
	else{
		Movie *traverse = new Movie; //Movie node used to move through the linked list

		traverse = &hashTable[index]; //start at the begining of the list

		while (traverse->next != NULL){
			if (newMovie->title < traverse->next->title){ //if it has reached the spot to insert
				newMovie->next = traverse->next;
				traverse->next = newMovie;
				added = true; //do not enter if statement below
				break;
			}
			traverse = traverse->next;
		}

		//add to the end of linked list
		if (!added){
			newMovie->next = NULL;
			traverse->next = newMovie;
		}
	}
	movies_in_table++;
}

Movie* HashTable::findMovie(string in_title){
	/*
    Function prototype:
    Movie* HashTable::findMovie(string);

    Function Description:
    Searches for a movie in the HashTable
    Calculates the index of in_title and searches the linked list stored in that slot in the table
    Returns the found movie. If no movie is found, returns a NULL movie

    Example:
    Movie *myMovie = new Movie;
    string title;
    //set the value of title
	myMovie = h.findMovie(title);

    Pre-condition:
    The hashTable must exist
    There can be any number of movies in it

    Post-condition:
    myMovie will now contain either the found movie or NULL
    */

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

void HashTable::deleteMovie(string in_title){
	/*
    Function prototype:
    void HashTable::deleteMovie(string);

    Function Description:
    Removes a movie from the hashTable
    Prints "not found" if the movie doesn't exist

    Example:
    string title;
    //set the value of title
	h.deleteMovie(title);

    Pre-condition:
    The hashTable must exist
    There can be any number of movies in it

    Post-condition:
    The movie with the corresponding title will no longer be in the hashTable or "not found" will be printed
    */

	int index = hashFunction(in_title); //find location of Movie inside the hashtable
	Movie *traverse = new Movie; //Movie node used to move through the linked list

	traverse = &hashTable[index]; //start at the beginning of the list

	while (traverse->next != NULL){
		if (traverse->next->title == in_title){ //if the titles match
			traverse->next = traverse->next->next; //overwrite the old node
			return; //end the function
		}
		traverse = traverse->next;
	}

	cout << "not found" << endl; //if the node is never found
	return;
}

void HashTable::printInventory(){
	/*
    Function prototype:
    void HashTable::printInventory();

    Function Description:
    Loops through the hashTable and prints movie information for each Movie in the hashTable
    Prints "empty" if the hashTable is empty

    Example:
    h.printInventory();

    Pre-condition:
    The hashTable must exist
    There can be any number of movies in it

    Post-condition:
    All movies inside the hashTable will be printed to the scren
    */

	int count = 0; //used to keep track of whether anything is ever printed
	Movie *traverse = new Movie; //Movie node used to move through the linked list

	for (int i = 0; i < table_size; i++){ //for every linked list in the table
		traverse = &hashTable[i]; //start at the beginning of the list

		while (traverse->next != NULL){
			if (traverse->next->title.size() > 0){ //if the title exists
				//print statements
				cout << "Movie found:" << endl;
                cout << "\tTitle: " << traverse->next->title << endl;
                cout << "\tYear: " << traverse->next->year << endl;
                cout << "\tRanking: " << traverse->next->ranking << endl;
				count++; //keeps track of whether the if statement has been entered
			}
			traverse = traverse->next;
		}
	}

	if (count == 0){ //if the table is empty
		cout << "empty" << endl;
	}
}

int HashTable::hashFunction(string in_title){
	/*
    Function prototype:
    int HashTable::hashFunction(string);

    Function Description:
    This hash function adds up the ASCII values for each character in the 
    string in_title and mods by the size of the hashtable.
    It then returns that value.

    Example:
    int hash;
    hash = h.hashFunction("My Title");

    Pre-condition:
    None

    Post-condition:
    The hashValue of the in_title will be returned
    */

	int hash = 0;

	for (int i = 0; i < in_title.length(); i++){ //for each character in the string
		hash += in_title[i]; //add up the ASCII values for each character
	}
	hash %= table_size; //mod by the table size

	return hash;
}

bool HashTable::ham(string in_title, string compare_title){
	/*
    Function prototype:
    bool HashTable::ham(string, string);

    Function Description:
    This function calculates the hamming distance between two strings and returns whether
    that distance is greater than .5.
    It takes two strings and compares them twice, starting at the beginning and the end.
    The more similarity the strings have, the higher the hamming distance will be.
    The higher of the two numbers is then compared to .5.
    If the number is greater than .5, the function returns true, otherwise, false.

    Example:
    if (h.ham("my_title_1, my_title_2")){
		cout << "The two titles are close" << endl;
    }

    Pre-condition:
    None

    Post-condition:
    The function will return a boolean value
    */

    float ham = 0; //counter used to calculate hamming distance
	float score1; //forward comparison score
	float score2; //backward comparison score
	string in_title_inverse = ""; //used to build inverse of in_title
	string compare_title_inverse = ""; //used to build inverse of compare_title

	//build inverses
	for (int i = in_title.length()-1; i >= 0; i--){
        in_title_inverse += in_title[i];
    }
    for (int i = compare_title.length()-1; i >= 0; i--){
        compare_title_inverse += compare_title[i];
    }

    //count letters that are the same
    for (int i = 0; i < in_title.length(); i++){
        if (in_title[i] != compare_title[i]){
            ham++;
        }
    }

    score1 = (in_title.length() - ham) / in_title.length(); //calculate hamming distance

    ham = 0; //reset for backwards comparison

    //count letters that are the same
    for (int i = 0; i < in_title_inverse.length(); i++){
        if (in_title_inverse[i] != compare_title_inverse[i]){
            ham++;
        }
    }

    score2 = (in_title_inverse.length() - ham) / in_title_inverse.length(); //calculate hamming distance

    //compare the two scores
    if (score1 < score2){
    	score1 = score2;
    }
    //return true if greater than .5
    if (score1 >= .5){
    	return true;
    }
    else{
    	return false;
    }
}

Movie* HashTable::buildMovieArray(){
	/*
    Function prototype:
    Movie* HashTable::buildMovieArray();

    Function Description:
    This function loops through the hashTable and stores each movie in a simple array.
    This allows each movie to be looped through very easily.

    Example:
    Movie *movieArray = new Movie[movies_in_table];
    movieArray = buildMovieArray();

    Pre-condition:
    The hashTable exists and contains any number of movies.
    The program knows the number of movies in the hashTable, which must be the size of the arrray

    Post-condition:
    Returns a pointer to the beginning of the new array that contains each movie in the hashTable.
    The hashTable is untouched.
    */

	Movie *movieArray = new Movie[movies_in_table];
	Movie *traverse = new Movie; //Movie node used to move through the linked list
	int x = 0;

	for (int i = 0; i < table_size; i++){ //for every linked list in the table
		traverse = &hashTable[i]; //start at the beginning of the list

		while (traverse->next != NULL){
			if (traverse->next->title.size() > 0){ //if the title exists
				movieArray[x] = *traverse->next;
				x++;
			}
			traverse = traverse->next;
		}
	}
	return movieArray;
}

void HashTable::movieMatch(string in_title){
	/*
    Function prototype:
    void HashTable::movieMatch(string);

    Function Description:
    This function calls buildMovieArray() to build an array out of the hashTable.
    It then loops through the array and uses ham() to calculate the hamming distance
    between in_title and the title of the movie in the array.
    If the hamming distance is close, the function then prints the movie information.
    If not, it prints "No close matches found."

    Example:
    h.movieMatch(my_title);

    Pre-condition:
    The hashTable exists and contains any number of movies.
    The program knows the number of movies in the hashTable

    Post-condition:
    Prints movie information if a match is found
    */

	Movie *movieArray = new Movie[movies_in_table];
	int count = 0;

	cout << "No match found. Searching for close matches..." << endl;
	
	movieArray = buildMovieArray(); //convert hashtable into an array that can be searched through

	for (int i = 0; i < movies_in_table; i++){
		if (ham(in_title, movieArray[i].title)){ //if the hamming distance is large enough
			//print statements
			cout << "Close match found:" << endl;
			cout << "\tTitle: " << movieArray[i].title << endl;
            cout << "\tYear: " << movieArray[i].year << endl;
            cout << "\tRanking: " << movieArray[i].ranking << endl;
			count++;
		}
	}
	if (count == 0){
		cout << "No close matches found." << endl;
	}
}

void HashTable::Tree_InsertNUM(Movie *newNode, Movie *root){
	/*
    Function prototype:
    void HashTable::Tree_InsertNUM(Movie*, Movie*);

    Function Description:
    This function inserts the Movie newNode into a binary search tree for ranking

    Example:
    Movie *movie_to_insert = new Movie;
    Movie *root = new Movie;
    //set values for movie_to_insert and root
    h.Tree_InsertNUM(movie_to_insert, root);

    Pre-condition:
    The BST can contain any number of Movies

    Post-condition:
    The BST now contains movie_to_insert, sorted with the greatest ranking to the left
    */

    Movie *traverse = new Movie; //Movie node used for moving through the tree
    Movie *parent = new Movie; //Movie node used to keep track of the parent of newNode

    traverse = root; //set traverse to start at root

    //navigate through tree to correct location
    while(traverse != NULL){ //make sure not at bottom of tree
        parent = traverse;

        if (newNode->ranking > traverse->ranking){ //left brance
            traverse = traverse->numLeft;
        }
        else{ //right brance
            traverse = traverse->numRight;
        }
    }   

    //insert newNode
    if (newNode->ranking > parent->ranking){
        parent->numLeft = newNode;   
    }
    else{
        parent->numRight = newNode;
    }
}

void HashTable::Tree_InsertSTRING(Movie *newNode, Movie *root){
	/*
    Function prototype:
    void HashTable::Tree_InsertSTRING(Movie*, Movie*);

    Function Description:
    This function inserts the Movie newNode into an alphabetized binary search tree

    Example:
    Movie *movie_to_insert = new Movie;
    Movie *root = new Movie;
    //set values for movie_to_insert and root
    h.Tree_InsertSTRING(movie_to_insert, root);

    Pre-condition:
    The BST can contain any number of Movies

    Post-condition:
    The BST now contains movie_to_insert, sorted with the alphabetically greatest to the left
    */

    Movie *traverse = new Movie; //Movie node used for moving through the tree
    Movie *parent = new Movie; //Movie node used to keep track of the parent of newNode

    traverse = root; //set traverse to start at root

    //navigate through tree to correct location
    while(traverse != NULL){ //make sure not at bottom of tree
        parent = traverse;

        if (newNode->title < traverse->title){ //left branch
            traverse = traverse->alphaLeft;
        }
        else{ //right branch
            traverse = traverse->alphaRight;
        }
    }

    //insert newNode
    if (newNode->title < parent->title){
        parent->alphaLeft = newNode;   
    }
    else{
        parent->alphaRight = newNode;
    }
}

void HashTable::buildBSTString(Movie *root){
	/*
    Function prototype:
    void HashTable::buildBSTString(Movie*);

    Function Description:
    This function loops through the hashTable and calls Tree_InsertSTRING() to build a tree out of it.

    Example:
    Movie *root = new Movie;
    //set values for root
    h.buildBSTString(root);

    Pre-condition:
    The hashTable must exist and can contain any number of movies

    Post-condition:
    A BST has been created that contains each movie in the hashTable and is orderd alphabetically
    */

    Movie *traverse = new Movie; //Movie node used to move through the linked list
    for (int i = 0; i < 10; i++){ //for every linked list in the table
        traverse = &HashTable::hashTable[i]; //start at the beginning of the list
        while (traverse->next != NULL){
            if (traverse->next->title.size() > 0 && traverse->next->title != root->title){ //if the title exists
                Tree_InsertSTRING(traverse->next, root);
            }
            traverse = traverse->next;
        }
    }
}

void HashTable::buildBSTNum(Movie *root){
	/*
    Function prototype:
    void HashTable::buildBSTNum(Movie*);

    Function Description:
    This function loops through the hashTable and calls Tree_InsertNUM() to build a tree out of it.

    Example:
    Movie *root = new Movie;
    //set values for root
    h.buildBSTNum(root);

    Pre-condition:
    The hashTable must exist and can contain any number of movies

    Post-condition:
    A BST has been created that contains each movie in the hashTable and is orderd by rank
    */

    Movie *traverse = new Movie; //Movie node used to move through the linked list
    for (int i = 0; i < 10; i++){ //for every linked list in the table
        traverse = &HashTable::hashTable[i]; //start at the beginning of the list
        while (traverse->next != NULL){
            if (traverse->next->title.size() > 0 && traverse->next->title != root->title){ //if the title exists
                Tree_InsertNUM(traverse->next, root);
            }
            traverse = traverse->next;
        }
    }
}

void HashTable::PrintThatTreeString(Movie *root){
	/*
    Function prototype:
    void HashTable::PrintThatTreeString(Movie*);

    Function Description:
    This function recursively loops through the BST and prints movie information for each Movie.

    Example:
    Movie *root = new Movie;
    //set values for root
    h.buildBSTString(root);
    h.PrintThatTreeString(root);

    Pre-condition:
    The BST must exist and contain any number of movies.
    buildBSTString() needs to have been called to ensure the BST exists properly.

    Post-condition:
    The contents of the BST have been printed
    */

	if (root->alphaLeft != NULL)
	{
		PrintThatTreeString(root->alphaLeft); //move left
	}
	//print statements
	cout << "Movie found: " << endl;
    cout << "\tTitle: " << root->title << endl;
    cout << "\tYear: " << root->year << endl;
    cout << "\tRanking: " << root->ranking << endl;
  	if (root->alphaRight != NULL)
  	{
    	PrintThatTreeString(root->alphaRight); //move right
  	}
}

void HashTable::PrintThatTreeNum(Movie *root){
	/*
    Function prototype:
    void HashTable::PrintThatTreeNum(Movie*);

    Function Description:
    This function recursively loops through the BST and prints movie information for each Movie.

    Example:
    Movie *root = new Movie;
    //set values for root
    h.buildBSTNum(root);
    h.PrintThatTreeNum(root);

    Pre-condition:
    The BST must exist and contain any number of movies.
    buildBSTNum() needs to have been called to ensure the BST exists properly.

    Post-condition:
    The contents of the BST have been printed
    */

	if (root->numLeft != NULL)
	{
		PrintThatTreeNum(root->numLeft); //move left
	}
	//print statements
	cout << "Movie found: " << endl;
    cout << "\tTitle: " << root->title << endl;
    cout << "\tYear: " << root->year << endl;
    cout << "\tRanking: " << root->ranking << endl;
  	if (root->numRight != NULL)
  	{
    	PrintThatTreeNum(root->numRight); //move right
  	}
}