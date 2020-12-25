/*
* -------------------------------------------------------------------------------
*    sequence3.cpp
*    
*    -Ahmad Adil, 2020
* -------------------------------------------------------------------------------
*/


#include <cstdlib>
#include <cassert>
#include "node1.h"
#include "sequence3.h"

using namespace std;
namespace main_savitch_5
{

//========================================================================================
//  BEGIN Constructors

    // Default constructor
    /*Run time analysis: O(1) - constant time*/
    sequence::sequence()
    {
        m_total_nodes = 0;    // 0 nodes in the sequece
        m_head = m_tail = m_current_node = m_precurrent_node = NULL;     // All nodes point to NULL;
    }


    // COPY constructor
    /* Run time analysis: O(N) - linear time, copies nodes one at a time.*/
    sequence::sequence(const sequence& source)
    {
        list_copy(source.m_head, m_head, m_tail);
        list_copy(source.m_current_node, m_current_node,m_precurrent_node);
        m_total_nodes = source.size();
    }

    // Destructor
    /* Run time analysis: O(n):O(1) - constant time*/
    sequence::~sequence()
    {
        list_clear(m_head);
        m_precurrent_node = m_current_node = NULL;
        m_total_nodes = 0;
    }

 // End of Constructors
//========================================================================================


//========================================================================================
// CONSTANT member functions:


/*    is_item() indicates there is an item within the current node
 *    Postcondition: A true return value indicates that there is a valid
 *    "current" item that may be retrieved by activating the current
 *    member function (listed below). A false return value indicates that
 *    there is no valid current item.
 *    Run time analysis: O(1)  - constant time*/
bool sequence::is_item() const
{
    return m_current_node != NULL;
}


/*   size returns how many cells within the array have been taken
 *   Postcondition: The return value is the number of items on the sequence.
 *   Run time analysis: O(1)  - constant time*/
sequence::size_type sequence::size() const
{
    return m_total_nodes;
}

/* current returns the value that is in the cell of array.
 * Precondition: is_item( ) returns true.
 * Postcondition: The item returned is the current item on the sequence.
 * Run time analysis: O(1)  - constant time*/
sequence::value_type sequence::current( ) const
{
    return m_current_node -> data(); 
}

// end of CONSTANT member functions
//========================================================================================


//========================================================================================
//  BEGIN MODIFICATION MEMBER FUNCTIONS



    /* start creates the first node and points the previous node to NULL
     * Postcondition: The first item on the sequence becomes the current item
     * (but if the sequence is empty, then there is no current item)
     * Run time analysis: O(1)  - constant time*/
    void sequence::start()
    {
        m_precurrent_node = NULL;
        m_current_node = m_head;
    }


    /*  Advance checks if is_item() is true then moves the current up one or makes the 
     *  makes the node taken the current item.
     *  Precondition: is_item returns true.
     * Postcondition: If the current item was already the last item on the
     * sequence, then there is no longer any current item. Otherwise, the new
     * current item is the item immediately after the original current item.
     * Run time analysis: O(1)  - constant time*/
    void sequence::advance()
    {
        assert(is_item());
        m_precurrent_node = m_current_node;
        m_current_node = m_current_node -> link();
    }



    /* Inserts a new entry to the beginning of the node and makes that the current item. If not then
     * the entry there becomes the current item.
     *  Postcondition: A new copy of entry has been inserted in the sequence before
     * the current item. If there was no current item, then the new entry has 
     * been inserted at the front of the sequence. In either case, the newly
     * inserted item is now the current item of the sequence.
     * Run time analysis: O(1)  - constant time*/
    void sequence::insert(const value_type& entry)
    {
        if(m_total_nodes == 0)
        {
            m_precurrent_node = NULL;
            list_head_insert(m_head,entry);
            m_current_node = m_head;
            m_tail = m_head;
        }

        else if(is_item() == false || m_current_node == m_head)
        {
            list_head_insert(m_head,entry);
            m_precurrent_node = NULL;
            m_current_node = m_head;
        }

        else
        {
            list_insert(m_precurrent_node, entry);
            m_current_node = m_precurrent_node -> link();
        }
        ++m_total_nodes;
    }


    /* attch adds an entry after the current item. If current item doesn't exits then 
     * attach is placed at end of list.
     *  Postcondition: A new copy of entry has been inserted in the sequence after
     * the current item. If there was no current item, then the new entry has 
     * been attached to the end of the sequence. In either case, the newly
     * inserted item is now the current item of the sequence.
     * Run time analysis: O(1)  - constant time*/
    void sequence::attach(const value_type& entry)
    {
        if(m_total_nodes == 0)
        {
            m_precurrent_node = m_head;
            list_head_insert(m_head,entry);
            m_current_node = m_head;
            m_tail = m_head;
        }

        else if(is_item() == 0 || m_current_node == m_tail)
        {
            m_precurrent_node = m_tail;
            list_insert(m_tail,entry);
            m_tail = m_tail->link();
            m_current_node = m_tail;
        }

        else
        {
            m_precurrent_node = m_current_node;
            list_insert(m_current_node,entry);
            m_current_node = m_current_node -> link();
        }

        ++m_total_nodes;
        
    }


    /* remove_current removes the current node that is selected. Then the item after becomes the new
     * current node
     * Precondition: is_item returns true.
     * Postcondition: The current item has been removed from the sequence, and the
     * item after this (if there is one) is now the new current item.
     * Run time analysis: O(1)  - constant time*/
    void sequence::remove_current()
    {
        assert(is_item());

        if(m_total_nodes == 1)
        {
            list_head_remove(m_head);
            m_precurrent_node = m_current_node = m_tail = NULL;
        }

        else if(m_current_node == m_head)
        {
            m_precurrent_node = NULL;
            list_head_remove(m_head);
            m_current_node = m_head;
        }

        else if(m_current_node == m_tail)
        {
            m_tail = m_precurrent_node;
            list_remove(m_tail);
            m_current_node = NULL;
        }

        else
        {
            m_current_node = m_current_node -> link();
            list_remove(m_precurrent_node);
        }

        --m_total_nodes;
        
    }


    /* operator= correctly makes a dynamic list for both the copy and original
     *  Postcondition: The sequence that activated this function has the same items 
     * and capacity as source
     * Run time analysis: O(N) - linear time*/
    void sequence::operator=(const sequence& source)
    {
        if(this ==  &source)
        {
            return;
        }

        list_clear(m_head);
        list_copy(source.m_head, m_head, m_tail);
        m_total_nodes = source.m_total_nodes;

        start();
        for(node* i = source.m_head; i != NULL && i != source.m_current_node; i = i -> link())
        {
            advance();
        }
    }
}
//  END MODIFICATION MEMBER FUNCTIONS
//========================================================================================