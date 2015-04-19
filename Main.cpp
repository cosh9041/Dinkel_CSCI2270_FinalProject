//Jack Dinkel
//CSCI 2270 - Hoenigman
//Assignment9

//Driver file

//Builds a hashtable to store movie information using user input
//Uses class: HashTable
//Takes no command line input

#include <iostream>
#include "HashTable.h"

using namespace std;

void displayMenu();
string askInput();

int main(){
	HashTable h(10); //initialize the table

	bool quit = false;
	int input;

	while(quit != true){ //to run until the user says quit
        displayMenu();
        cin >> input;

        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');

        switch (input){
            case 1: //insert movie
            {
            	Movie *newMovie = new Movie;
            	string title;
            	int year;

            	//ask user for input
            	cout << "Enter title:" << endl;
            	title = askInput();
            	cout << "Enter year:" << endl;
            	cin >> year;

            	//build the new Movie object
            	newMovie->title = title;
            	newMovie->year = year;

            	h.insertMovie(newMovie); //insert the movie into the hashtable

                break;
            }

            case 2: //delete movie
            {
            	Movie *movieToFind = new Movie;
            	string title;

            	//ask user for input
            	cout << "Enter title:" << endl;
            	title = askInput();

            	h.deleteMovie(title); //delete the movie from the hashtable

                break;
            }

            case 3: //find movie
            {
            	Movie *movieToFind = new Movie;
            	string title;

            	//ask user for input
            	cout << "Enter title:" << endl;
            	title = askInput();

            	movieToFind = h.findMovie(title); //search the hashtable for the movie

            	if (movieToFind == NULL){ //if NULL is returned, print "not found"
            		cout << "not found" << endl;
            	}
            	else{ //print statement
            		cout << h.hashFunction(title) << ":" << movieToFind->title << ":" << movieToFind->year << endl;
            	}

                break;
            }

            case 4: //Print table contents
            	h.printInventory(); //print the hashtable
                break;

            case 5: //Quit
                cout << "Goodbye!" << endl;
                quit = true; //end program
                break;

            default: // invalid input
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore(10000,'\n');
                break;
        }
    }
    return 0;
}

void displayMenu(){ //displays the Main Menu for the program
    cout << "======Main Menu======" << endl;
    cout << "1. Insert movie" << endl;
    cout << "2. Delete movie" << endl;
    cout << "3. Find movie" << endl;
    cout << "4. Print table contents" << endl;
    cout << "5. Quit" << endl;
    return;
}

string askInput(){ //waits for user for input, returns a string (works with spaces)
	char input[100];
	string inputString;
	cin >> inputString;
	cin.getline(input,100);
	inputString += string(input);

	return inputString;
}