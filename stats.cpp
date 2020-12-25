#include <iostream>
#include <assert.h>
#include "stats.h"

using namespace std;
namespace main_savitch_2C

{
/*This is the default constructor that we create*/
/*
Postcondition: The object has been initialized, and is ready to accept
a sequence of numbers. Various statistics will be calculated about the sequence.*/
statistician::statistician()
{
    reset();
}

/*This is the reset function that sequence all of the private members = 0*/
/*Postcondition: The statistician has been cleared, as if no numbers had yet been given to it.*/
void statistician::reset()
{
    count = 0;
    total = 0;
    tinyest = 0;
    largest = 0;
}

/*This is the mean function that takes in a set of numbers and calculates the mean*/
/*
Precondition: length( ) > 0
Postcondition: The return value is the arithmetic mean (i.e., the 
average of all the numbers in the statistician's sequence).*/
double statistician::mean() const
{
    assert(length() > 0);
    return total / count;
}

// This function takes in a set of numbers and calculates the total
/*Postcondition: The return value is the sum of all the numbers in the statistician's sequence.*/
double statistician::sum() const {
  return total;
}

// This function calculates the minimum number from a set
/*
Precondition: length( ) > 0 
Postcondition: The return value is the tinyest number in the statistician's sequence.*/
double statistician::minimum() const {
  assert(length() > 0);
  return tinyest;
}

// This function calculates the max number from a set
/*
Precondition: length( ) > 0
Postcondition: The return value is the largest number in the statistician's sequence.*/
double statistician::maximum() const {
  assert(length() > 0);
  return largest;
}

//This function gives numbers to statistician one at a time
/*The number r has been given to the statistician as the next number in its sequence of numbers.*/
void statistician::next(double r)
{
    count++;
    total += r;
    if(length() == 1)
    {
        tinyest = r;
        largest = r;
    }
    else
    {
        if(r > maximum())
        {
            largest = r;
        }
        else if( r < minimum())
        {
            tinyest = r;
        }
    }
}

// This member returns the length of the sequence of numbers
/*
Postcondition: The return value is the length of the sequence that has 
been given to the statistician (i.e., the number of times that the 
next(r) function has been activated).*/
int statistician::length() const
{
    return count;
}

// this operator tests whether two statisiticans are equal
/*
Postcondition: The return value is true if s1 and s2 have the zero
length. Also, if the length is greater than zero, then s1 and s2 must
have the same length, the same  mean, the same minimum, 
the same maximum, and the same sum.*/
bool operator ==(const statistician& s1, const statistician& s2)
{
    if (s2.length() == 0 && s1.length() == 0)
    {
        return true;
    }
    else if
    (s2.length() == s1.length()    &&
    s2.sum() == s1.sum()           && 
    s2.minimum() == s1.minimum()   &&
    s2.maximum() == s1.maximum()   &&
    s2.mean() == s1.mean())
    {
    return true;
    }

    else
    {
        return false;
    }
    

}

// This operator adds two statisticans together
/*Postcondition: The statistician that is returned contains all the numbers of the sequences of s1 and s2.*/
statistician operator +(const statistician& s1, const statistician& s2)
{
    statistician s3;
    if(s1.length() == 0 && s2.length() == 0)
    {
        return s3;
    }

    else if(s1.length() == 0)
    {
        return s2;
    }

    else if(s2.length() == 0)
    {
        return s1;
    }

    else
    {
        s3.count = s1.length() + s2.length();
        s3.total = s1.sum() + s2.sum();
        
        if(s1.minimum() >= s2.minimum())
        {
            s3.tinyest = s2.tinyest;
        }
        else
        {
            s3.tinyest = s1.tinyest;
        }

        if(s1.maximum() >= s2.maximum())
        {
            s3.largest = s1.largest;
        }
        else
        {
            s3.largest = s2.largest;
        }
    }
    return s3;
}

// This operator multiplies a statistician by a scale(number)
/*
Postcondition: The statistician that is returned contains the same 
numbers that s does, but each number has been multiplied by the scale number.*/
statistician operator *(double scale, const statistician& s)
    {
        statistician u;
        if(s.length() == 0)
        {
            return s;
        }
        u.total = scale * s.sum();
        u.count = s.length();

        if(scale >= 0)
        {
            u.tinyest = scale * s.tinyest;
            u.largest = scale * s.largest;
        }
        else
        {
            u.tinyest = scale * s.largest;
            u.largest = scale * s.tinyest;
        }
        return u;
    }

}
