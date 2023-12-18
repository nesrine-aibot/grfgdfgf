#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <iomanip>
#include "SalesHashTable.h"
using namespace std;

struct winnerCategory
{

    int id_of_veg_winner;
    double formula_veg_winner;
    int id_of_fruits_winner;
    double formula_fruits_winner;
    int id_of_cereals_winner;
    double formula_cereals_winner;
    int id_of_olives_winner;
    double formula_olives_winner;
    int id_of_dates_winner;
    double formula_dates_winner;

    // the default constructor initializes everything to 0
    winnerCategory()
        : id_of_veg_winner(0),
          formula_veg_winner(0),
          id_of_fruits_winner(0),
          formula_fruits_winner(0),
          id_of_cereals_winner(0),
          formula_cereals_winner(0),
          id_of_olives_winner(0),
          formula_olives_winner(0),
          id_of_dates_winner(0),
          formula_dates_winner(0) {}

    // overloaded operator<< for winnerCategory
    friend std::ostream &operator<<(std::ostream &os, const winnerCategory &winner)
    {
        if (winner.formula_veg_winner > 0)
        {
            os << "\t"
               << "\t"
               << "in the vegetables category :" << endl;
            os << "\t"
               << "\t"
               << "\t"
               << "ID of Veg Winner: " << winner.id_of_veg_winner << "\n"
               << "\t"
               << "\t"
               << "\t"
               << "Formula Veg Winner: " << winner.formula_veg_winner << "\n";
        }

        if (winner.formula_fruits_winner > 0)
        {
            os << "\t"
               << "\t"
               << "in the fruits category :" << endl;
            os << "\t"
               << "\t"
               << "\t"
               << "ID of Fruits Winner: " << winner.id_of_fruits_winner << "\n"
               << "\t"
               << "\t"
               << "\t"
               << "Formula Fruits Winner: " << winner.formula_fruits_winner << "\n";
        }
        if (winner.formula_cereals_winner > 0)
        {
            os << "\t"
               << "\t"
               << "in the cereals category :" << endl;
            os << "\t"
               << "\t"
               << "\t"
               << "ID of Cereals Winner: " << winner.id_of_cereals_winner << "\n"
               << "\t"
               << "\t"
               << "\t"
               << "Formula Cereals Winner: " << winner.formula_cereals_winner << "\n";
        }
        if (winner.formula_olives_winner > 0)
        {
            os << "\t"
               << "\t"
               << "in the olives category :" << endl;
            os << "\t"
               << "\t"
               << "\t"
               << "ID of Olives Winner: " << winner.id_of_olives_winner << "\n"
               << "\t"
               << "\t"
               << "\t"
               << "Formula Olives Winner: " << winner.formula_olives_winner << "\n";
        }
        if (winner.formula_dates_winner > 0)
        {
            os << "\t"
               << "\t"
               << "in the olives category :" << endl;
            os << "\t"
               << "\t"
               << "\t"
               << "ID of Dates Winner: " << winner.id_of_dates_winner << "\n"
               << "\t"
               << "\t"
               << "\t"
               << "Formula Dates Winner: " << winner.formula_dates_winner << "\n";
        }
        return os;
    }

    bool isvalid()
    {
        if (id_of_cereals_winner == 0 && id_of_dates_winner == 0 && id_of_fruits_winner == 0 && id_of_olives_winner == 0 && id_of_veg_winner == 0)
            return false;

        return true;
    }
};

struct winner_node
{
    int year;
    std::vector<winnerCategory> month_winner = vector<winnerCategory>(12);
    winner_node *left;
    winner_node *right;

    // the default constructor initializes year to 0 and creates a vector with 12 elements (representing months)
    winner_node() : year(0)
    {
        left = nullptr;
        right = nullptr;
    }

    // overloaded operator<< for winner_node
    friend std::ostream &operator<<(std::ostream &os, const winner_node &node)
    {
        os << "Year: " << node.year << endl;

        for (int i = 0; i < node.month_winner.size(); i++)
        {
            os << "the winner in the month : " << i + 1 << "are :" << endl;
            os << node.month_winner[i];
        }

        return os;
    }

    // Overloaded operator=
    winner_node &operator=(const winner_node &other)
    {
        if (this != &other) // self-assignment check
        {
            year = other.year;
            month_winner = other.month_winner;
            left = other.left;
            right = other.right;
        }
        return *this;
    }
};

class winnertree 

{

public:
    // Constructor
    winnertree() ;
    

    // Copy constructor
 winnertree(const winnertree &other);

    // Move constructor
    winnertree(winnertree &&other) noexcept ;
   

    // Copy assignment operator
    winnertree &operator=(const winnertree &other);
    

    // Move assignment operator
    winnertree &operator=(winnertree &&other) noexcept ;
    
    // Destructor
    ~winnertree();
   
void update_winner(const Sales &farmer);   // the purpose of this function is to store and check the winner of each category in each month of a given year


// fucntions to search for the winner depending on the year , month , or both :

winnerCategory find_winner_by_year_month(int y, int m); // find the winner in a given year and in a given month 
 

vector<winnerCategory> find_winner_by_year(int y);// find the winner in a given year  
    

vector<winnerCategory> find_winner_by_month(int m);// find the winner in a given month 
    

    

private:
winner_node data;
winner_node *root;

    

 void update_winner(const Sales &farmer, winner_node *&temp); // helper function 
   

void printTree(winner_node *t, ostream &out) const; // helper function 
   

double calculateformula(Sales farmer, int category);  // function to calculate the formula needed to compare the farmers
    

bool isEmpty() const;  // return true if the tree is empty
    

void find_winner_by_month(int m, vector<winnerCategory> &result, winner_node *root); // find the winner in a given month and in a given year 
   
    
winner_node *copyTree(winner_node *node) const; // Function to copy a subtree

  
void destroyTree(winner_node *node);   // Function to destroy a subtree


winner_node *insert(const winner_node &element, winner_node *&t);  // insert a new node , wich is a helper function that we will call just inside the update_winner 
    

void insert(const winner_node &element); // insert a node 
   
};
