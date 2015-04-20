//Jack Dinkel
//CSCI 2270 - Hoenigman
//Final Project

//Driver file

//Builds a hashtable to store movie information using user input
//Uses class: HashTable
//Takes no command line input

#include <iostream>
#include <regex>
#include "HashTable.h"

using namespace std;

void displayMenu();
string askInput();
int regexTest();
void similarity();

int main(){
	HashTable h(10); //initialize the table
    cout << h.ham("this is a test", "thisis a test") << endl;
    cout << h.ham("another test", "another") << endl;

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
                int ranking;

            	//ask user for input
            	cout << "Enter title: ";
            	title = askInput();
            	cout << "Enter year: ";
            	cin >> year;
                cout << "Enter your ranking (1-10): ";
                cin >> ranking;
                while (ranking > 100 || ranking < 1){ //if ranking invalid
                    cout << "Invalid ranking! Please enter an integer between 1 and 10: ";
                    cin >> ranking;
                }

            	//build the new Movie object
            	newMovie->title = title;
            	newMovie->year = year;
                newMovie->ranking = ranking;

            	h.insertMovie(newMovie); //insert the movie into the hashtable

                break;
            }

            case 2: //delete movie
            {
            	Movie *movieToFind = new Movie;
            	string title;

            	//ask user for input
            	cout << "Enter title: " << endl;
            	title = askInput();

            	h.deleteMovie(title); //delete the movie from the hashtable

                break;
            }

            case 3: //find movie
            {
            	Movie *movieToFind = new Movie;
            	string title;

            	//ask user for input
            	cout << "Enter title: " << endl;
            	title = askInput();

            	movieToFind = h.findMovie(title); //search the hashtable for the movie

            	if (movieToFind == NULL){ //if NULL is returned, print "not found"
            		cout << "not found" << endl;
            	}
            	else{ //print statement
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
                cout << "print in alphebetical order" << endl;
                break;

            case 6: //Print in rank order
                cout << "print in rank order" << endl;
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

void displayMenu(){ //displays the Main Menu for the program
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

string askInput(){ //waits for user for input, returns a string (works with spaces)
	char input[100];
	string inputString;
	cin >> inputString;
	cin.getline(input,100);
	inputString += string(input);

	return inputString;
}

int regexTest(){
    std::string subject("Name: John Doe");
    std::string result;
    cout << "test" << endl;
    try {
        std::regex re("Name: (.*)");
        std::smatch match;
        if (std::regex_search(subject, match, re) && match.size() > 1) {
            result = match.str(1);
        }
        else {
            result = std::string("");
        } 
        cout << result << endl;
    }
    catch (std::regex_error& e) {
        cout << "error" << endl;
          // Syntax error in the regular expression
    }

  return 0;
}

void similarity(){
    string s1 = "This is a test";
    string s2 = "This is a test";
    string s1inv = "";
    string s2inv = "";

    float maxLen;
    float ham = 0;
    float score1;
    float score2;


    for (int i = s1.length()-1; i >= 0; i--){
        s1inv += s1[i];
    }
    for (int i = s2.length()-1; i >= 0; i--){
        s2inv += s2[i];
    }


    for (int i = 0; i < s1.length(); i++){
        if (s1[i] != s2[i]){
            ham++;
        }
    }

    score1 = (s1.length() - ham) / s1.length();

    cout << score1 << endl;


    ham = 0;


    for (int i = 0; i < s1inv.length(); i++){
        if (s1inv[i] != s2inv[i]){
            ham++;
        }
    }

    score2 = (s1inv.length() - ham) / s1inv.length();

    cout << score2 << endl;

}