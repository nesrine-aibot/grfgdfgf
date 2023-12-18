#include "winnertree.h"

// the big five :

// default constructor
winnertree::winnertree() : data(), root(nullptr)
{
    root = nullptr;
}

// Copy constructor
winnertree::winnertree(const winnertree &other) : data(other.data), root(copyTree(other.root)) {}

// Move constructor
winnertree::winnertree(winnertree &&other) noexcept : data(std::move(other.data)), root(other.root)
{
    other.root = nullptr;
}

winnertree &winnertree::operator=(const winnertree &other) // Copy assignment operator
{
    if (this != &other)
    {
        data = other.data;
        root = copyTree(other.root);
    }
    return *this;
}

winnertree& winnertree::operator=(winnertree &&other) noexcept
{ // Move assignment operator
    // using the swap method that we learned in the TP sessions
    data = std::move(other.data);
    root = std::move(other.root);
    return *this;
}

// the destructor
winnertree::~winnertree()
{
    destroyTree(root);
    cout << "destroyed success winn"<<endl;
}

// the purpose of this function is to store and check the winner of each category in each month of a given year
void winnertree::update_winner(const Sales &farmer)
{
    update_winner(farmer, root);
}
// the helper function of the update winner funcion :
void winnertree::update_winner(const Sales &farmer, winner_node *&temp)
{
    if (temp == nullptr)
    {
        /*
       Since we reached a point where the root becomes empty, so we didn't find any farmer
       corresponding to this year, then this farmer is the first and the only one (for this moment),
       so he is the winner of his the categories
       */

        winner_node *newnode = new winner_node();
        //   newnode.month_winner = vector<winnerCategory> (12);
        newnode->year = farmer.year;
        // This farmer is the winner in all the categories
        newnode->month_winner[farmer.month - 1].formula_veg_winner = calculateformula(farmer, 0);
        newnode->month_winner[farmer.month - 1].id_of_veg_winner = farmer.farmer_id;

        newnode->month_winner[farmer.month - 1].id_of_fruits_winner = farmer.farmer_id;
        newnode->month_winner[farmer.month - 1].formula_fruits_winner = calculateformula(farmer, 1);
        newnode->month_winner[farmer.month - 1].id_of_cereals_winner = farmer.farmer_id;
        newnode->month_winner[farmer.month - 1].formula_cereals_winner = calculateformula(farmer, 2);

        newnode->month_winner[farmer.month - 1].id_of_olives_winner = farmer.farmer_id;
        newnode->month_winner[farmer.month - 1].formula_olives_winner = calculateformula(farmer, 3);

        newnode->month_winner[farmer.month - 1].id_of_dates_winner = farmer.farmer_id;
        newnode->month_winner[farmer.month - 1].formula_dates_winner = calculateformula(farmer, 4);

        temp = newnode; // Insert this node with the new year

        return;

        // we traversed all the list and we didn't found the corresponding year so
    }
    int currentYear = farmer.year;

    if (currentYear > temp->year)
    {
        update_winner(farmer, temp->right);
    }
    else if (currentYear < temp->year)
    {
        update_winner(farmer, temp->left);
    }
    else
    {
        // year found
        int month = farmer.month - 1;

        double formula = calculateformula(farmer, 4);
        if (formula > data.month_winner[month].formula_veg_winner)
        {
            temp->month_winner[month].formula_veg_winner = formula;
            temp->month_winner[month].id_of_veg_winner = farmer.farmer_id;
        }

        formula = calculateformula(farmer, 2);
        if (formula > data.month_winner[month].formula_fruits_winner)
        {
            temp->month_winner[month].formula_fruits_winner = formula;
            temp->month_winner[month].id_of_fruits_winner = farmer.farmer_id;
        }

        formula = calculateformula(farmer, 0);
        if (formula > data.month_winner[month].formula_cereals_winner)
        {
            temp->month_winner[month].formula_cereals_winner = formula;
            temp->month_winner[month].id_of_cereals_winner = farmer.farmer_id;
        }

        formula = calculateformula(farmer, 1);
        if (formula > data.month_winner[month].formula_dates_winner)
        {
            temp->month_winner[month].formula_dates_winner = formula;
            temp->month_winner[month].id_of_dates_winner = farmer.farmer_id;
        }

        formula = calculateformula(farmer, 3);
        if (formula > data.month_winner[month].formula_olives_winner)
        {
            temp->month_winner[month].formula_olives_winner = formula;
            temp->month_winner[month].id_of_olives_winner = farmer.farmer_id;
        }

        return;
    }
}

// find the winner in a given year and in a given month

winnerCategory winnertree::find_winner_by_year_month(int y, int m)
{
    if (y < 1990 || y > 2022)
    {
        throw underflow_error("");
    }
    if (m > 12 || m < 1)
    {
        throw underflow_error("");
    }

    winner_node *temp = root;

    while (temp != nullptr)
    {
        if (y > temp->year)
            temp = temp->right;
        else if (y < temp->year)
            temp = temp->left;
        else
        {
            if ((temp->month_winner[m - 1]).isvalid())
            {

                cout << "the winners of " << m << " / " << y << " are : -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"
                     << endl;
                cout << temp->month_winner[m - 1];
                return temp->month_winner[m - 1];
            }
            else
            {
                cout << "there is not yet winners in " << m << " / " << y << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
                return winnerCategory();
            }
        }
    }

    cout << "year not found -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------";
    return winnerCategory();
}

// find the winner in a given year
vector<winnerCategory> winnertree::find_winner_by_year(int y)
{
    // if (y < 1962 || y > 2024)
    //     throw underflow_error("");
    vector<winnerCategory> result(12);
    cout << " the winners in all the monthes in the year  " << y << "are : ***************************************************************************" << endl;
    for (int i = 1; i <= 12; i++)
    {
        result.push_back(find_winner_by_year_month(y, i));
    }
    return result;
}

// find the winner in a given month
vector<winnerCategory> winnertree::find_winner_by_month(int m)
{
    winner_node *temp = root;
    vector<winnerCategory> result(10);

    if (m < 1 || m > 12)
    {
        throw std::invalid_argument("Invalid month value provided.");
    }
    cout << "the winners in all the years corresponding to the month " << m << "  are : *****************************************************************************************************************************************************************************************************************" << endl;
    find_winner_by_month(m, result, temp);
    return result;
}

// function to calculate the formula needed to compare the farmers
double winnertree::calculateformula(Sales farmer, int category)
{
    return farmer.set[category].nb_kg_sold * farmer.set[category].average_price * (1 - farmer.set[category].severity_penalty / 100) - (farmer.electricity + farmer.water) / 5;
}

// return true if the tree is empty
bool winnertree::isEmpty() const
{
    return root == nullptr;
}

// find the winner in a given month and in a given year  (helper function )
void winnertree::find_winner_by_month(int m, vector<winnerCategory> &result, winner_node *root)
{

    if (root == nullptr)
        return;
    // inorder traversal of the tree :
    find_winner_by_month(m, result, root->left);

    // process the root :
    cout << root->month_winner[m];
    result.push_back(root->month_winner[m]);

    find_winner_by_month(m, result, root->right);
}

winner_node *winnertree::copyTree(winner_node *node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    winner_node *newNode = new winner_node(*node);
    newNode->left = copyTree(node->left);
    newNode->right = copyTree(node->right);
    return newNode;
}

void winnertree::destroyTree(winner_node *node)
{
    if (node == nullptr)
    {
        return;
    }
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

winner_node *winnertree::insert(const winner_node &element, winner_node *&t)
{

    if (t == nullptr)
    {
        t = new winner_node();
        t->year = element.year;

        t->month_winner = element.month_winner;
        t->left = nullptr;
        t->right = nullptr;
    }
    else if (element.year < t->year)
    {
        insert(element, t->left);
    }
    else if (element.year > t->year)
    {
        insert(element, t->right);
    }

    return t;
}

void winnertree::insert(const winner_node &element)
{
    insert(element, root);
}
