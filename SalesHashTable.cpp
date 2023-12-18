#include <iostream>
#include "SalesHashTable.h"

using namespace std;

bool isPrime(int n)
{
    if (n == 2 || n == 3)
        return true;

    if (n == 1 || n % 2 == 0)
        return false;

    for (int i = 3; i * i <= n; i += 2)
        if (n % i == 0)
            return false;

    return true;
}

int nextPrime(int n)
{
    if (n % 2 == 0)
        ++n;

    for (; !isPrime(n); n += 2)
        ;

    return n;
}

SaleHashTable ::SaleHashTable(int size) : array(nextPrime(size))
{
    makeEmpty();
}

bool SaleHashTable ::contains(const Sales &x)
{
    return isActive(findPos(x.farmer_id));
}

bool  SaleHashTable :: contains(const long x)
{
     return isActive(findPos(x));
}

void SaleHashTable ::makeEmpty()
{
    currentSize = 0;
    for (auto &entry : array)
        entry.info = EMPTY;
}

bool SaleHashTable ::insert(const Sales &x)
{
    // Insert x as active
    int currentPos = findPos(x.farmer_id);
    if (isActive(currentPos))
        return false;
    if (array[currentPos].info != DELETED)
        ++currentSize;

    array[currentPos].element = x;
    array[currentPos].info = ACTIVE;

    // Rehash; see Section 5.5
    if (currentSize > array.size() / 2)
        rehash();

    return true;
}

bool SaleHashTable ::remove(const Sales &x)
{
    int currentPos = findPos(x.farmer_id);
    if (!isActive(currentPos))
        return false;

    array[currentPos].info = DELETED;
    return true;
}

Sales SaleHashTable ::getSales(long key) // it returns the element inside the object in the array cell
{
    int currentPos = findPos(key);
    if (currentPos < array.size())
        return array[currentPos].element;
}

int SaleHashTable ::findPos(long key) // we made findPos a public function so we can use it later
{

    int offset = hash2(key);

    int currentPos = myhash(key);

    while (array[currentPos].info != EMPTY && array[currentPos].element.farmer_id != key)
    {
        currentPos += offset; // Compute ith probe
        // offset += 2;
        if (currentPos >= array.size())
            currentPos -= array.size();
    }
    return currentPos;
}

