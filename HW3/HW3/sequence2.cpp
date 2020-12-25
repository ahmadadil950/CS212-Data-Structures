/*
* -------------------------------------------------------------------------------
*    sequence2.cpp
*    
*    -Ahmad Adil, 2020
* -------------------------------------------------------------------------------
*/

#include <iostream>
#include "sequence2.h"
#include <assert.h>
#include <algorithm>

using std::copy;
using namespace main_savitch_4;


const sequence::size_type sequence::DEFAULT_CAPACITY;

//========================================================================================
//  BEGIN Constructors

/* Default Constructor
 * initial capacity shows how many items to allocate for dynamic array*/
sequence::sequence(size_type initial_capacity)
{
    m_data = new value_type[initial_capacity];
    m_capacity = initial_capacity;
    m_cellTaken = 0;                    // No cell has been taken when default constructor is called
}

/* The copy constructor
 * The amount of memoryallocated for sourcedetermines how much 
 * memory to allocate forthe new dynamic array.*/
sequence::sequence(const sequence& source)
{
    m_data = new value_type [source.m_capacity];
    m_capacity = source.m_capacity;
    m_cellTaken = source.m_cellTaken;
    copy(source.m_data, source.m_data + m_cellTaken, m_data);
    m_currentInd = source.m_currentInd;

}

// Deconstructor
sequence::~sequence( )
{
    delete[] m_data;
}

// End of Constructors
//========================================================================================



//========================================================================================
// CONSTANT member functions:

/* is_item() indicates there is an item within the current cell
 * Postcondition: A true return value indicates that there is a valid
 * "current" item that may be retrieved by activating the current
 * member function (listed below). A false return value indicates that
 * here is no valid current item.*/
    bool sequence::is_item() const
    {
        return (m_currentInd < m_cellTaken);
    }

/* current returns the value that is in the cell of array.
 * Precondition: is_item( ) returns true.
 * Postcondition: The item returned is the current item in the sequence.*/
    sequence::value_type sequence::current() const
    {
        assert(is_item());
        return m_data[m_currentInd];
    }

/* size returns how many cells within the array have been taken
 * Postcondition: The return value is the number of items in the sequence.*/
    sequence::size_type sequence::size() const
    {
        return m_cellTaken;
    }

// end of CONSTANT member functions
//========================================================================================



//========================================================================================
//  BEGIN MODIFICATION MEMBER FUNCTIONS

/* Checks to see if the first item in array becomes the current item
 * Postcondition: The first item on the sequence becomes the current item
 * (but if the sequence is empty, then there is no current item).*/
void sequence::start()
{
    if(size() > 0)
    {
        m_currentInd = 0;
    }
}


/* Advance checks if is_item() is true then moves the current up one or makes the 
 * makes the cell taken the current item
 * Precondition: is_item returns true.
 * Postcondition: If the current item was already the last item in the
 * sequence, then there is no longer any current item. Otherwise, the new
 * current item is the item immediately after the original current item.*/
void sequence::advance()
{
    if(is_item())
    {
        ++m_currentInd;
    }
    else
    {
        m_currentInd = m_cellTaken;
    }
    
}

/* Inserts a new entry to the beginning of the array and makes that the current item. If not then
 * the entry there becomes the current item
 * Precondition: size( ) < CAPACITY.
 * Postcondition: A new copy of entry has been inserted in the sequence
 * before the current item. If there was no current item, then the new entry 
 * has been inserted at the front of the sequence. In either case, the newly
 * inserted item is now the current item of the sequence.*/
void sequence::insert(const value_type& entry)
{
    if(m_capacity <= size())
    {
        resize(size() + 1);
    }
    if(!is_item())
    {
            m_currentInd = 0;
    }
    for(sequence::size_type x = m_cellTaken; x > m_currentInd; --x)
        {
            m_data[x] = m_data[x-1];
        }
        m_data[m_currentInd] = entry;
        ++m_cellTaken;
}


/* attch adds an entry after the current item. If current item doesn't exits then
 * attach is placed at end of array.
 * Postcondition: A new copy of entry has been inserted in the sequence after
 * the current item. If there was no current item, then the new entry has 
 * been attached to the end of the sequence. In either case, the newly
 * inserted item is now the current item of the sequence.*/
void sequence::attach(const value_type& entry)
{
    if(m_capacity <= size())
    {
        resize(size() + 1);
    }
    if(!is_item())
        {
            m_currentInd = m_cellTaken;
        }
        else
        {
            m_currentInd++;
            for(sequence::size_type x = m_cellTaken; x > m_currentInd; --x)
            {
                m_data[x] = m_data[x-1];
            }
        }
        m_data[m_currentInd] = entry;
        ++m_cellTaken;
}

/* remove_current removes the current item that is selected. Then the item after becomes the new
 * current item
 * Precondition: is_item returns true.
 * Postcondition: The current item has been removed from the sequence, and the
 * item after this (if there is one) is now the new current item.*/
void sequence::remove_current()
{
    assert(is_item());
        if(is_item())
        {
            for(sequence::size_type x = m_currentInd; x < m_cellTaken; x++)
            {
                m_data[x]= m_data[x+1];
            }
        }
        --m_cellTaken;
}


/* resizes dynamically changes the capacity of the array using the 
 * using the copy constructor and assigning the values from the defualt array
 * Postcondition: The sequence's current capacity is changed to the 
 * new_capacity (but not less that the number of items already on the
 * sequence). The insert/attach functions will work efficiently (without
 * allocating new memory) until this new capacity is reached.*/
void sequence::resize(size_type new_capacity)
{
    sequence::value_type *m_data_new;
    if(m_capacity == new_capacity)
    {
        return;
    }
    else if(new_capacity < m_cellTaken)
    {
        new_capacity = m_cellTaken;
    }
    m_data_new = new value_type[new_capacity];
    copy(m_data, m_data+m_cellTaken, m_data_new);
    delete [] m_data;
    m_data = m_data_new;
    m_capacity = new_capacity;
    
}

/* operator= correctly makes a dynamic array for both the copy and original
 * Postcondition: The bag that activated this function has the same items 
 * and capacity as source*/
void sequence::operator=(const sequence& source)
{
    sequence::value_type *m_data_new;
    if(this == &source)
    {
        return;
    }
    else
    {
        m_capacity = source.m_capacity;
        m_data_new = new sequence::value_type[source.m_capacity];
        delete[] m_data;
        m_data = m_data_new;
    }
    m_cellTaken = source.size();
    copy(source.m_data, source.m_data+size(), m_data);
    m_currentInd = source.m_currentInd;
}

//  END MODIFICATION MEMBER FUNCTIONS
//========================================================================================
