//Jack Dinkel
//CSCI 2270 - Hoenigman
//Final Project

//Driver file

//Builds a hashtable to store movie information using user input
//Uses class: HashTable
//Takes no command line input

#include <iostream>
#include "HashTable.h" //include the HashTable class

using namespace std;

void displayMenu();
string askInput();

int main(){
    /*
    main function:
    This function handles a main menu with user input to select options.
    It then calls other functions based on the user input.
    When the function ends, the program terminates
    */

	HashTable h(10); //initialize the table

	bool quit = false; //when true, will end the while loop below
	int input; //user input variable
    int movieCounter = 0; //counter to track number of movies in hashTable

	while(quit != true){ //to run until the user says quit
        displayMenu();
        cin >> input;

        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');

        switch (input){ //this switch handles the main input from the menu
            case 1: //insert movie
            {
            	Movie *newMovie = new Movie; //movie to create
                //input variables
            	string title;
            	string tempYr;
            	string tempRank;
            	int year;
                double ranking;

            	//ask user for input
            	cout << "Enter title: ";
            	title = askInput();
            	cout << "Enter year: ";
            	cin >> tempYr;
            	year = stoi(tempYr);
            	
                cout << "Enter your ranking (0-10): ";
                cin >> tempRank;
                ranking = stod(tempRank);
                while (ranking > 10.0 || ranking < 0.0){ //if ranking invalid
                    cout << "Invalid ranking! Please enter an integer between 1 and 10: ";
                    cin >> tempRank; //try again
					ranking = stod(tempRank);
                }

            	//build the new Movie object
            	newMovie->title = title;
            	newMovie->year = year;
                newMovie->ranking = ranking;
                newMovie->next = NULL;
                newMovie->alphaLeft = NULL;
                newMovie->alphaRight = NULL;
                newMovie->numLeft = NULL;
                newMovie->numRight = NULL;

                //if it is the first movie added, set as root
                if (movieCounter == 0){
                    h.root = newMovie;
                    movieCounter++; //increase movieCounter so the if is not entered again
                }

            	h.insertMovie(newMovie); //insert the movie into the hashtable

                break;
            }

            case 2: //delete movie
            {
            	string title; //input variable

            	//ask user for input
            	cout << "Enter title: " << endl;
            	title = askInput();

            	h.deleteMovie(title); //delete the movie from the hashtable

                break;
            }

            case 3: //find movie
            {
            	Movie *movieToFind = new Movie;
            	string title; //input variable

            	//ask user for input
            	cout << "Enter title: " << endl;
            	title = askInput();

            	movieToFind = h.findMovie(title); //search the hashtable for the movie

            	if (movieToFind == NULL){ //if NULL is returned, try to match movie
                    h.movieMatch(title);
            	}
            	else{ //print statements
            		cout << "Movie found in position: " << h.hashFunction(title) << endl;
                    cout << "\tTitle: " << movieToFind->title << endl;
                    cout << "\tYear: " << movieToFind->year << endl;
                    cout << "\tRanking: " << movieToFind->ranking << endl;
            	}

                break;
            }

            case 4: //Print table contents
            	h.printInventory(); //print the hashtable
                break;

            case 5: //Print in alphebetical order
            {
                h.buildBSTString(h.root); //build a BST to order movies in alphabetical order
                h.PrintThatTreeString(h.root); //print the BST

                //clear BST
                h.root->alphaLeft = NULL;
                h.root->alphaRight = NULL;
                break;
            }

            case 6: //Print in rank order
                h.buildBSTNum(h.root); //build a BST to order movies in rank order
                h.PrintThatTreeNum(h.root); //print the BST

                //clear BST
                h.root->numLeft = NULL;
                h.root->numRight = NULL;
                break;

            case 7: //Quit
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

void displayMenu(){
    /*
    Function prototype:
    void displayMenu();

    Function Description:
    This method diplays the main menu for the program and then ends

    Example:
    displayMenu();

    Pre-condition:
    None

    Post-condition:
    The menu has been printed
    */

    cout << "======Main Menu======" << endl;
    cout << "1. Insert movie" << endl;
    cout << "2. Delete movie" << endl;
    cout << "3. Find movie" << endl;
    cout << "4. Print table contents" << endl;
    cout << "5. Print in alphebetical order" << endl;
    cout << "6. Print in rank order" << endl;
    cout << "7. Quit" << endl;
    return;
}

string askInput(){
    /*
    Function prototype:
    string askInput();

    Function Description:
    This method asks the user for input
    Spaces are not excluded, so the input string can contain a space

    Example:
    String input;
    input = askInput();

    Pre-condition:
    A string variable to store the return value of the function needs to be initialized

    Post-condition:
    the inputed string will be returned
    */

	char input[100];
	string inputString;
	cin >> inputString;
	cin.getline(input,100);
	inputString += string(input);

	return inputString;
}
