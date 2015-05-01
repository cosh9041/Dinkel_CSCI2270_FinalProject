//Jack Dinkel
//CSCI 2270 - Hoenigman
//Final Project

//HashTable header file

#ifndef HASHTABLE_H
#define HASHTABLE_H

struct Movie{
    std::string title;
    int year;
    double ranking;
    Movie *next; //for the linked list

    //for the BST
    Movie *alphaLeft;
    Movie *alphaRight;
    Movie *numLeft;
    Movie *numRight;

    Movie(){};

    Movie(std::string in_title, int in_year)
    {
        title = in_title;
        year = in_year;

        //set values to NULL
        next = NULL;
        alphaRight = NULL;
        alphaLeft = NULL;
        numRight = NULL;
        numLeft = NULL;
    }
};

class HashTable
{
    public:
        HashTable(int size); //ctor
        ~HashTable(); //dtor
        void insertMovie(Movie *newMovie); //insert movie into the table
        Movie* findMovie(std::string in_title); //search the table for a movie
        void deleteMovie(std::string in_title); //delete a movie from the table
        void printInventory(); //print the contents of the table
        int hashFunction(std::string in_title); //calculate hash value for a string
        bool ham(std::string in_title, std::string compare_title); //determines hamming distance between two strings
        Movie* buildMovieArray(); //converts table into an array
        void movieMatch(std::string in_title); //searches array for match using hamming distance
        void Tree_InsertNUM(Movie *newNode, Movie *root); //Inserts a Movie into the tree
        void Tree_InsertSTRING(Movie *newNode, Movie *root); //Inserts a Movie into the tree
        void buildBSTString(Movie *root); //Build a tree
        void buildBSTNum(Movie *root); //Build a tree
        void PrintThatTreeString(Movie *root); //Print the tree
        void PrintThatTreeNum(Movie *root); //Print the tree

        Movie *root; //root of the tree
    protected:
    private:
        int table_size; //size of the hashTable
        int movies_in_table = 0; //number of movies in the hashTable
        Movie *hashTable; //hashTable
};

#endif // HASHTABLE_H
