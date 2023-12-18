#ifndef BST_YEAR_H
#define BST_YEAR_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "SalesHashTable.h"
#include <algorithm>
using namespace std;       

// the yearSales represent the the node in The bst_year
struct yearSales
{
    int year;
    SaleHashTable sales[12]; // array of hashtables of sales // each hash table represents the sales for a specific month
    yearSales(int yr)
    {
        if (false)
        {

            throw underflow_error("aya3");
        }
        else
        {
            year = yr;
        }
    }
    
    yearSales(int &&yr)
    {
        if (year < 1990 || year > 2022)
        {
            throw underflow_error("");
        }
        else
        {
            year = move(yr);
        }
    }
    
    yearSales(int yr, SaleHashTable sl[])
    {
        if (year < 1990 || year > 2022)
        {
            throw underflow_error("");
        }
        else
        {
            year = yr;
        }
        for (int i = 0; i < 12; i++)
        {
            sales[i] = sl[i];
        }
    }; // we need first to create an array of sales that contain hash table of arrays
    yearSales(int &&yr, SaleHashTable sl[])
    {
        if (year < 1990 || year > 2022)
        {
            throw underflow_error("aya2");
        }
        else
        {
            year = move(yr);
        }
        for (int i = 0; i < 12; i++)
        {
            sales[i] = sl[i];
        }
    }
    bool operator<(const yearSales &other) const
    {
        return year < other.year;
    }
};


class bst_Year
{
  public:
    
    
    // farmer struct
    struct Farmer
    {
        // Farmer's ID, Farmer's area, Farmer's SSN,
        // Farmer's Full Name,Farmer's gender,
        // Farmer's age,Number Of People Who Help them
        long farmer_Id;
        int farmer_area;
        long farmer_SSN;
        string farmer_fullName;
        string farmer_gender; // Male or Female
        int farmer_age;
        int nb_helpers;

        // constructor function
        Farmer(long i = 0, int area = 0, long SSN = 0, string name = "", string gender = "",
               int age = 0, int helpers = 0)
            : farmer_Id{i}, farmer_area{area}, farmer_SSN{SSN}, farmer_fullName{name},
              farmer_gender{gender}, farmer_age{age}, nb_helpers{helpers} {};
    };

    //constructor 
    bst_Year( ) : root{ nullptr },count(0)
    {
        init("cities.csv");  // filling the cities, areas, wilayas vectors
        read_farmers("farmer.csv"); // filling the vector of farmers
    }

    /**
     * Copy constructor
     */
    bst_Year( const bst_Year & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
        wilayas =rhs.wilayas;
        cities =rhs.cities;
        farmers =rhs.farmers;
        areas =rhs.areas;
    }

    /**
     * Move constructor
     */
    bst_Year( bst_Year && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
        wilayas = move(rhs.wilayas);
        cities = move(rhs.cities);
        areas = move(rhs.areas);
        farmers = move(rhs.farmers);
    }
    
    /**
     * Destructor for the tree
     */
    ~bst_Year( )
    {
        makeEmpty( );
        cout << "destroyed success"<<endl;
    }

    /**
     * Copy assignment
     */
    bst_Year & operator=( const bst_Year & rhs )
    {
        bst_Year copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    bst_Year & operator=( bst_Year && rhs )
    {
        std::swap( root, rhs.root );
        bst_Year copy = std::move(rhs);
        wilayas = rhs.wilayas;
        areas = rhs.areas;
        cities = rhs.cities;
        farmers = rhs.farmers;       
        return *this;
    }
    
    
    bool contains( const yearSales & x ) const
    {
        return contains( x, root );
    }

    bool isEmpty( ) const
    {
        return root == nullptr;
    }

   

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const yearSales & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( yearSales && x )
    {
        insert( std::move( x ), root );
    }
    void insert(const Sales &sl)
    {
        BinaryNode *temp = root;
        // we need first to check if the year exist or no
        while (temp != nullptr)
        {
            if (sl.year < temp->element.year)
                temp = temp->left;
            else if (sl.year > temp->element.year)
                temp = temp->right;
            else
            {
                // the year exist then we just need to insert the sales to the its hashtable
                temp->element.sales[sl.month-1].insert(sl);
                count ++;
                return;
            }
        }
        // if the year doesn't exist then we need to create a yearSales object and then insert the sale then we need to insert
        // the yearSales object (hold) into our bst_Year
        yearSales hold(sl.year);
        hold.sales[sl.month-1].insert(sl);
        insert(hold);
        count ++;
        return;
    };
    // we add it just for verification purposes
    void getCount() const
    {
        cout << count;
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const yearSales & x )
    {
        remove( x, root );
    }

    // Getting the sales of a specific farmer in a specific year and a specific month
    void reportSales(int year, int month, long id) const
    {
        BinaryNode *temp = root;
        while (temp != nullptr) // we need first to find the node of the specified year
        {
            if (year < temp->element.year)
            {
                
                temp = temp->left;
            }
            else if (year > temp->element.year)
            {
              
                temp = temp->right;
            }
            else
            {       // after finding the year now we check if the farmer exist in this hash table
                   if(temp->element.sales[month-1].contains(id)){
                    // we print the sales of the farmer then
                    Sales tempSale = temp->element.sales[month-1 ].getSales(id);
                    cout << "The farmer  " << farmers[id-1].farmer_fullName<< " "<<id << " has sold " << tempSale << endl;
                    temp = nullptr;
                    
                    
                    }
                else{
                    cout << "the farmer "<<farmers[id-1].farmer_fullName<<" didn't work in " << month <<endl;
                    temp = nullptr;
                }

            }
        }
    }

    // Getting the sales of a specific farmer in a specific year 
    void reportSales(int year, long id) const
    {
        
        BinaryNode *temp = root;
        while (temp != nullptr)
        {
            if (year < temp->element.year)
                temp = temp->left;

            else if (year > temp->element.year)
                temp = temp->right;
                
            else if(year == temp->element.year)
            {
                cout << "---------------------------------------------------------------------------"<<endl;
                for (int i = 1; i < 13; i++)
                {
                    cout << i <<endl;
                    reportSales(year, i, id);
                }
                cout << "---------------------------------------------------------------------------"<<endl;
                return;
                
            }
        }
    }
    
    //getting the penalties of a specific farmer in a specific year and month
    void reportPenalties(int year, int month, long id) const
    {
        BinaryNode *temp = root;
        while (temp != nullptr)
        {
            if (year < temp->element.year)
                temp = temp->left;
            else if (year < temp->element.year)
                temp = temp->right;
            else
            {
                cout << "---------------------------------"<<endl;
                Sales tempSale = temp->element.sales[month - 1].getSales(id);
                cout << "The farmer " << farmers[id].farmer_fullName << " has penalties on the categories  " << endl;
                for (int i = 0; i < 5; i++)
                {
                    cout << tempSale.set[i].category_name << ": " << tempSale.set[i].severity_penalty << endl;
                }
                cout << " in the month " << month << " and year " << year << endl;
                cout << "---------------------------------"<<endl;
                temp = nullptr;
                return;
            }
        }
    }

    //getting the penalties of a specific farmer in a specific year
    void reportPenalties(int year, long id) const
    {
        BinaryNode *temp = root;
        while (temp != nullptr)
        {
            if (year < temp->element.year)
                temp = temp->left;
            else if (year < temp->element.year)
                temp = temp->right;
            else
            {
                for (int i = 0; i < 12; i++)
                {
                    reportPenalties(year, i, id);
                }
            }
        }
    }
    
    //getting the sales of the farmers of a specific area in a specific year
    void reportArea(int year,int areaID)const
    {
        for (const auto &idFarmer : areas[areaID])
        {
           for (int i=1 ; i<13 ; i++){
            reportSales(year,i,idFarmer);
           }
        }
    }
    //getting the sales of the farmers of a specific city in a specific year

    void reportCity(int year,int cityId) const
    {
        for (const auto &areaID : cities[cityId])
        {
            reportArea(year,areaID);
        }
    }

    //getting the sales of the farmers of a specific wilaya in a specific year
    void reportWilaya(int year,int wilayaId) const
    {
        for (auto &element : wilayas[wilayaId])
        {
            reportCity(year,element);
        }
    }
    
    
    private:
    struct BinaryNode
    {
        yearSales element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const yearSales & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( yearSales && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };
    int count;
    BinaryNode *root;
    int nb_farmers;
    // wilayas stores a linked list of the cities corresponding to the current position in the vector
    // we will assume that the array starts at position 0 to keep consistent with the different wilayas and cities codes
    vector<list<int>> wilayas = vector<list<int>>(59);
    // cities stores a linkedist of areas codes corresponding to city position
    vector<list<int>> cities = vector<list<int>>(4829);
    // areas stores a linked list of Farmers ' Ids belonging to the area position
    vector<list<long>> areas = vector<list<long>>(1542);

    // definition of the Farmer struct as a an entry of the Farmers vector

    // Declare the farmers vector that contains a collection of farmers
    vector<Farmer> farmers;
    void fill_farmers(const Farmer &obj)
    {
        farmers.push_back(obj);
    }

    // Defining a function fill_areas to fill the areas vector with the appropriate farmers
    //  ' IDs
    void fill_areas(const bst_Year::Farmer &obj)
    {
        int area = obj.farmer_area;
        areas[area].push_back(obj.farmer_Id);
    }
    void init(string file_path)
    {
        ifstream file;
        file.open(file_path);
        if (!file)
        {
            cerr << "Error opening the file." << endl;
            return;
        }

        // creating a string which holds a single row in the file
        string line;

        // before reaching the eof indicator
        while (getline(file, line))
        {
            // creating a string stream to simplify strings operations
            stringstream S(line);
            string wilaya;
            string city;
            string area;

            // Assume each line has two columns separated by a comma
            // retrieve the wilaya
            getline(S, wilaya, ',');
            // retrieve the city
            getline(S, city, ',');
            wilayas[stoi(wilaya)].push_back(stoi(city));
            // retrieve the area
            getline(S, area, ',');
            cities[stoi(city)].push_back(stoi(area));
        }

        file.close();
    }
    void read_farmers(string path)
    {
        ifstream file;
        file.open(path);
        if (!file)
            cerr << "File located in " << path << "couldn't be opened!" << endl;
        string line;
        getline(file, line);
        while (getline(file, line))
        {
            stringstream S(line);
            string id_farmer;   // to be converted
            string area_farmer; // to be converted
            string SSN_farmer;  // to be converted
            string fullName_farmer;
            string gender_farmer;
            string age_farmer;        // to be converted
            string nb_helpers_farmer; // to be converted

            getline(S, id_farmer, ',');
            getline(S, area_farmer, ',');
            getline(S, SSN_farmer, ',');
            getline(S, fullName_farmer, ',');
            getline(S, gender_farmer, ',');
            getline(S, age_farmer, ',');
            getline(S, nb_helpers_farmer, ',');

            // build an instance of Farmer
            Farmer temp(stoll(id_farmer), stoi(area_farmer), stoll(SSN_farmer),
                        fullName_farmer, gender_farmer, stoi(age_farmer), stoi(nb_helpers_farmer));

            // push the instance of Farmer created to the vector containing all the farmers
            fill_farmers(temp);
            // pass the instance of Farmer created to the function that matches each farmer
            // with their corresponding area
            fill_areas(temp);
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const yearSales & x, BinaryNode * & t )
    {
        if( t == nullptr ){
            t = new BinaryNode{ x, nullptr, nullptr };
            }
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
            ;  // Duplicate; do nothing
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( yearSales && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
            ;  // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const yearSales & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


  
    bool contains( const yearSales & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

 

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};

#endif
