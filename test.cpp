#include <list>
#include <exception>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "bst_Year.h"
#include "winnertree.h"
using namespace std;

// the file sles.csv contains 2000 sales 
// the sales file contains 400000
int main()
{
  bst_Year bst;
  winnertree winner;
  string Path = "sales.csv";
  ifstream file(Path);
  string line;
  int counter =0;
  // reading from the file and store the line in a string
  
 while (getline(file, line)) {
           stringstream ss(line);
           string token;
           string tokens[26];
           int count =0;
          
           while (getline(ss, token, ',')) { 
               tokens[count] = token;
               count ++;
            }
           
           //we create a categories array to store the categories information
           category categories[5];
           int count_0 = 0; // to check if the categories are all null
           int pos = 0; 
           
           for (int i=0 ; i<5 ; i++) { // filling the categories 
              categories[i].category_name = tokens[pos+1];
              categories[i].average_price = stod (tokens[pos+2]);
              categories[i].nb_kg_sold = stod (tokens[pos+3]);
              categories[i].severity_penalty = stoi (tokens[pos+4]);
              pos += 4;
              if(categories[i].average_price == 0 && categories[i].nb_kg_sold == 0 && categories[i].severity_penalty == 0){
               count_0 ++;
              }
            
            }
            if(count_0 == 5){ // if a line doesn't contain any sale (all the sales for each category = 0 ) then skip
                  counter ++ ;
                  continue;}
            else{
              
              long id = stol(tokens[0]);
              int month = stoi(tokens[22]);
              int year = stoi(tokens[23]);
              double electricity = stod(tokens[24]) ;
              double water = stod(tokens[25]) ;
              Sales obj(id, categories,month,year,electricity,water );
              counter ++;
              cout<< counter << endl;
              winner.update_winner(obj);
              bst.insert(obj);
           }
           
   }
    
    bst.reportSales(2012,39080);
    winner.find_winner_by_year_month(2010,3);
    bst.getCount();
    cout << endl;
    cout<< counter << endl;
  
  
  return 0;
  
}