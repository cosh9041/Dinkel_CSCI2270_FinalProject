//Jack Dinkel
//CSCI 2270 - Hoenigman
//Final Project

//HashTable header file

#ifndef HASHTABLE_H
#define HASHTABLE_H

struct Movie{
    std::string title;
    int year;
    Movie *next;

    Movie(){};

    Movie(std::string in_title, int in_year)
    {
        title = in_title;
        year = in_year;
    }
};

class HashTable
{
    public:
        HashTable(int size);
        ~HashTable();
        void insertMovie(Movie *newMovie);
        Movie* findMovie(std::string in_title);
        void deleteMovie(std::string in_title);
        void printInventory();
        int hashFunction(std::string in_title);
    protected:
    private:
        int table_size;
        Movie *hashTable;
};

#endif // HASHTABLE_H
