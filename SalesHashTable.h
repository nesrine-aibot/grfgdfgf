#ifndef SALESHASHTABLE_H
#define SALESHASHTABLE_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iomanip>
#include <functional>
//#include <mpfr.h>
using namespace std;


int nextPrime(int n);

// this structure is for the 5 categries (vegetable , fruits , olives , cereals , dates) 
struct category
{
    string category_name;
    double average_price;
    double nb_kg_sold;
    int severity_penalty;
     // category constructor
    category(string name = " ", double average_pr = 0, double nb_kg = 0, int penalty = 0 ) : category_name{name},
    average_price{average_pr}, nb_kg_sold{nb_kg}, severity_penalty{penalty} {}

    friend ostream &operator<<(ostream &os, const category &sale)
    {
        // Your implementation here
        os <<  "  Category          :" << sale.category_name << "\n"
           <<  "  the average price : " << setprecision(2) << fixed << sale.average_price << "\n"
           <<  "  number of kg      : " << setprecision(2) << fixed << sale.nb_kg_sold << "\n"
           <<  "  severity_penalty  : " << sale.severity_penalty <<"\n";

        return os;
    }

    bool operator==(const category &rhs) const
    {
        return (category_name == rhs.category_name &&
                average_price == rhs.average_price &&
                nb_kg_sold == rhs.nb_kg_sold &&
                severity_penalty == rhs.severity_penalty);
    }

    bool operator!=(const category &rhs) const
    {
        return !(*this == rhs);
    }

    category &operator=(const category &other)
    {
        if (this != &other)
        {
            category_name = other.category_name;
            average_price = other.average_price;
            nb_kg_sold = other.nb_kg_sold;
            severity_penalty = other.severity_penalty;
        }
        return *this; 
    }
};


// this structure represents an item of the hash tables that stores the sales, where the key is the ID of the farmer
struct Sales
{
    long farmer_id;
    category *set;
    int month;
    int year;
    double water ;
    double electricity ;

    // sales constructor
    Sales(long id = 0, category *name = nullptr, int m = 0, int y = 0 ,  double w = 0 , double el = 0)
        : farmer_id{id}, month{m}, year{y}, water{w} , electricity{el}
     {
        set = new category[5];

        if (name != nullptr)
        {
            for (int i = 0; i < 5; i++)
            {
                set[i] = name[i];
            }
        }
    }

    // sales destructor 
    ~Sales()
    {
        delete[] set;
    }

    // copy constructor
    Sales(const Sales &other)
        : farmer_id{other.farmer_id}, month{other.month}, year{other.year} , water{other.water} , electricity{other.electricity}
    {
        set = new category[5];
        for (int i = 0; i < 5; i++)
        {
            set[i] = other.set[i];
        }
    }

    //copy assignment
    Sales &operator=(const Sales &other)
    {
        if (this != &other)
        {
            delete[] set;
            farmer_id = other.farmer_id;
            month = other.month;
            year = other.year;
            water = other.water;
            electricity = other.electricity;
            set = new category[5];
            for (int i = 0; i < 5; i++)
            {
                set[i] = other.set[i];
            }
        }
        return *this;
    }

    friend ostream &operator<<(ostream &os, const Sales &sale)
    {
        os <<"Farmer ID  :" << sale.farmer_id <<"\n";
        os <<"Categories : " << "\n";

        for (int i = 0; i < 5; i++)
        {
            os << sale.set[i] << "\n";
        }
        os <<"month       : " << sale.month << "\n" ;
        os <<"year        : " << sale.year << "\n" ;
        os <<"water       : " << setprecision(2) << fixed << sale.water << "\n" ;
        os <<"electricity : " << setprecision(2) << fixed << sale.electricity<<"\n";
       
        return os;
    }

    bool operator==(const Sales &rhs) const
    {
        if (!((farmer_id == rhs.farmer_id) && (month == rhs.month) && (year == rhs.year) && (water == rhs.water) && (electricity == rhs.electricity)))
            return false;

        for (int i = 0; i < 5; i++)
        {
            if (set[i] != rhs.set[i])
                return false;
        }
        return true;
    }

    bool operator!=(const Sales &other)
    {
        return !(*this == other);
    }
};



class SaleHashTable
{
public:
    SaleHashTable(int size = 101) ; // constructor of SaleHashTable class . 
    
    bool contains(const Sales &x); // check if the sale is in the table or no using the Sale object. the running time is O(1).
    
    bool contains(const long x); //  takes the ID_farmer as parameter and checks if it exists in the hash table . the running time is O(1).

    void makeEmpty(); // make the table of the sales empty. the running time is O(n)

    bool insert(const Sales &x);  // insert the sales using the Id farmer. the running time is O(1).

    bool remove(const Sales &x);  // to remove the sale element. the running time is O(1).

    Sales getSales(long key) ;// it returns the element inside the object in the array cell. the running time is O(1).
   
    int findPos(long key) ; // we made findPos to find the position of the sale inside the table. the running time is O(1).


    enum EntryType
    {
        ACTIVE,
        EMPTY,
        DELETED
    };

private:
    struct HashEntry
    {
        Sales element;
        EntryType info;

        HashEntry(const Sales &e = Sales{}, EntryType i = EMPTY)
            : element{e}, info{i} {}

        HashEntry(Sales &&e, EntryType i = EMPTY)
            : element{std::move(e)}, info{i} {}
    };

    vector<HashEntry> array;
    int currentSize;

    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    size_t myhash(long key) const
    {
        static hash<long> hf;
        return hf(key) % array.size();
    }

    size_t hash2(long key) const
    {
        return 101 - (key % 100);
    }

    void rehash()
    {
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize(nextPrime(2 * oldArray.size()));
        for (auto &entry : array)
            entry.info = EMPTY;

        // Copy table over
        currentSize = 0;
        for (auto &entry : oldArray)
            if (entry.info == ACTIVE)
                insert(move(entry.element));
    }
};

#endif
