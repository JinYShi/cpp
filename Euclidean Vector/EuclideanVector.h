#pragma once
#ifndef EUCLIDEANVECTOR_EUCLIDEANVECTOR_H
#define EUCLIDEANVECTOR_EUCLIDEANVECTOR_H

#include <cassert>
#include <iterator>
#include <initializer_list>
#include <list>
#include <cmath> 
#include <iostream>
#include <vector>
#include <cmath>  
/* reference:
https://stackoverflow.com/questions/580622/dynamic-array-copy-constructor-destructor-overloaded-assignment-operator
http://www.geeksforgeeks.org/copy-constructor-in-cpp/
*/

namespace evec{
    class EuclideanVector {
    public:
        //default constructor
        EuclideanVector();
        //constructor take dimensions but no magnitude
        EuclideanVector(const unsigned numD);
        //constructor take the demension and magnitude
        EuclideanVector(const unsigned numD, const double mag);        
        //constructor for iterator
        template <typename Ite> EuclideanVector(const Ite& start, const Ite& end ,typename Ite::iterator_category *p=0
        ) {
            normalFormCalculated = 0;
            numDimension = static_cast<unsigned>(std::distance(start,end));
            magnitude = new double[numDimension];
            int count = 0;
            auto begin = start;
            while(begin != end) {
                magnitude[count] = *begin;
                begin++;
                count++;
            }              
        }
        //construcor for initializer_list
        EuclideanVector(std::initializer_list<double> li);       
        //copy constructor
        EuclideanVector(const EuclideanVector &obj);
        //move constructor
        EuclideanVector(EuclideanVector &&obj);
        //copy assignment operator
        EuclideanVector& operator=(const EuclideanVector &obj);
        //move assignemnt operator
        EuclideanVector& operator=(EuclideanVector &&obj);
        //Destructor
        ~EuclideanVector();
        //dimension getter
        const unsigned int getNumDimensions()const;
        //index getter
        const double get (int n) const;
        //Normal getter
        const double getEuclideanNorm() const;
        //create the unit vector
        EuclideanVector createUnitVector() const;
        //two overload set function
        double& operator[] (int i);
        double operator[] (int i) const; 
        //operator
        EuclideanVector& operator+=(const EuclideanVector &obj);
        EuclideanVector& operator-=(const EuclideanVector &obj);
        EuclideanVector& operator*=(const double d);
        EuclideanVector& operator/=(const double d);      
        //friend function
        friend std::ostream& operator<<(std::ostream &os, const EuclideanVector &obj);
        friend bool operator==(const EuclideanVector &obj1, const EuclideanVector &obj2);
        friend EuclideanVector& operator+(const EuclideanVector &obj1, const EuclideanVector &obj2);
        friend EuclideanVector& operator-(const EuclideanVector &obj1, const EuclideanVector &obj2);
        friend double operator*(const EuclideanVector &obj1, const EuclideanVector &obj2); 
        friend EuclideanVector& operator*(const EuclideanVector &obj1, const double numD);
        friend EuclideanVector& operator*(const EuclideanVector &obj1, const int numI);
        friend EuclideanVector& operator*(const double numD, const EuclideanVector &obj1);
        friend EuclideanVector& operator*(const int numI, const EuclideanVector &obj1);
        friend EuclideanVector& operator/(const EuclideanVector &obj1, const double numD);
        friend EuclideanVector& operator/(const EuclideanVector &obj1, const int numI);
        // Type conversion
        operator std::vector<double>() const;
        operator std::list<double>() const; 
    private:
        double *magnitude;
        unsigned int numDimension; 
        mutable double normalFormCalculated;
    };
#endif
    std::ostream& operator<<(std::ostream &os, const EuclideanVector &obj);
    bool operator==(const EuclideanVector &obj1, const EuclideanVector &obj2);
    bool operator!=(const EuclideanVector &obj1, const EuclideanVector &obj2);
    EuclideanVector& operator+(const EuclideanVector &obj1, const EuclideanVector &obj2);
    EuclideanVector& operator-(const EuclideanVector &obj1, const EuclideanVector &obj2);
    double operator*(const EuclideanVector &obj1, const EuclideanVector &obj2);

    EuclideanVector& operator*(const EuclideanVector &obj1, const double numD);
    EuclideanVector& operator*(const EuclideanVector &obj1, const int numI);
    EuclideanVector& operator*(const double numD, const EuclideanVector &obj1);
    EuclideanVector& operator*(const int numI, const EuclideanVector &obj1);
    EuclideanVector& operator/(const EuclideanVector &obj1, const double numD);
    EuclideanVector& operator/(const EuclideanVector &obj1, const int numI);
    
}
