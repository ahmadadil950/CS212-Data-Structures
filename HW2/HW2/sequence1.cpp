#include <iostream>
#include "sequence1.h"
#include <assert.h>

namespace main_savitch_3
{
    //sequence::CAPACITY is the maximum number of items that a sequence can hold.
    const sequence::size_type sequence::CAPACITY; 


    // default constructor
    sequence::sequence()
    {
        m_currentInd = 0;   // Arrays start at zero -> default constructor makes it start at zero
        m_cellTaken = 0;    // No cell has been taken when default constructor is called
    }


// CONSTANT member functions:

    /*is_item() indicates there is an item within the current cell  */
    /*Postcondition: A true return value indicates that there is a valid
   "current" item that may be retrieved by activating the current
    member function (listed below). A false return value indicates that
     there is no valid current item.*/
    bool sequence::is_item() const
    {
        return (m_currentInd < m_cellTaken);
    }

    /*current returns the value that is in the cell of array.*/
    /*Precondition: is_item( ) returns true.
     Postcondition: The item returned is the current item in the sequence.*/
    sequence::value_type sequence::current() const
    {
        assert(is_item());
        return m_data[m_currentInd];
    }

    /*size returns how many cells within the array have been taken*/
    /*Postcondition: The return value is the number of items in the sequence.*/
    sequence::size_type sequence::size() const
    {
        return m_cellTaken;
    }

// end of CONSTANT member functions


    /*Checks to see if the first item in array becomes the current item*/
    /*Postcondition: The first item on the sequence becomes the current item
    (but if the sequence is empty, then there is no current item).*/
    void sequence::start()
    {
        if(size() > 0)
        {
            m_currentInd = 0;
        }
    }

    /*Advance checks if is_item() is true then moves the current up one or makes the 
    makes the cell taken the current item*/
    /*Precondition: is_item returns true.
     Postcondition: If the current item was already the last item in the
     sequence, then there is no longer any current item. Otherwise, the new
     current item is the item immediately after the original current item.*/
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
    
    /*Inserts a new entry to the beginning of the array and makes that the current item. If not then
    the entry there becomes the current item*/
    /*Precondition: size( ) < CAPACITY.
     Postcondition: A new copy of entry has been inserted in the sequence
     before the current item. If there was no current item, then the new entry 
     has been inserted at the front of the sequence. In either case, the newly
     inserted item is now the current item of the sequence.*/
    void sequence::insert(const value_type& entry)
    {
        assert(size()<CAPACITY);
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

    /*attch adds an entry after the current item. If current item doesn't exits then
    attach is placed at end of array.*/
    /*Postcondition: A new copy of entry has been inserted in the sequence after
     the current item. If there was no current item, then the new entry has 
     been attached to the end of the sequence. In either case, the newly
     inserted item is now the current item of the sequence.*/
    void sequence::attach(const value_type& entry)
    {
        assert(size() < CAPACITY);
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


    /*remove_current removes the current item that is selected. Then the item after becomes the new
    current item*/
    /*Precondition: is_item returns true.
     Postcondition: The current item has been removed from the sequence, and the
     item after this (if there is one) is now the new current item.*/
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
}