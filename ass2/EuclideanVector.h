//
// Created by Haonan on 8/24/16.
//

#ifndef EUCLIDEANVECTOR_H
#define EUCLIDEANVECTOR_H


#include <vector>
#include <list>
#include <iostream>
namespace evec
{
    class EuclideanVector
    {

    public:
        EuclideanVector();
        EuclideanVector(const unsigned int dimension); //first constructor EuclideanVector a(1);
        EuclideanVector(const unsigned int dimension, double vecValue); //second constructor EuclideanVector a(2,4.0);
        EuclideanVector(const std::list<double>::const_iterator begin, const std::list<double>::const_iterator end);
        EuclideanVector(const std::list<double> l);
//        EuclideanVector(std::array);
        EuclideanVector(const std::vector<double>::const_iterator begin, const std::vector<double>::const_iterator end);
        EuclideanVector(const std::vector<double> l);
        EuclideanVector(const std::initializer_list<double> l);

        ~EuclideanVector(); //deconstructor

        //copy constructor
        EuclideanVector(const EuclideanVector& euclideanVector);

        //move consturctor
        EuclideanVector(EuclideanVector&& euclideanVector);

        //copy assignment
        EuclideanVector& operator=(const EuclideanVector &euclideanVector);

        //move assignment
        EuclideanVector& operator=(EuclideanVector &&euclideanVector);

        //opeartion
        unsigned int getNumDimensions() const; //const: never change the member of the class
        double get(unsigned int dimension) const;
        double getEuclideanNorm() const;
        EuclideanVector createUnitVector() const;

        double operator [] (unsigned int dimension) const; //getter
        double&operator [] (unsigned int dimension); //setter

        EuclideanVector& operator+=(const EuclideanVector &euclideanVector);
        EuclideanVector& operator-=(const EuclideanVector &euclideanVector);
        EuclideanVector& operator*=(const double times);
        EuclideanVector& operator/=(const double divisor);

        //type conversion
        operator std::vector<double>() const;
        operator std::list<double>() const;

        //friend
        friend std::ostream &operator<<(std::ostream &os, const EuclideanVector &euclideanVector);
        friend bool operator==(const EuclideanVector &lhs, const EuclideanVector &rhs);
        friend bool operator!=(const EuclideanVector &lhs, const EuclideanVector &rhs);
        friend EuclideanVector& operator+(const EuclideanVector &lhs, const EuclideanVector &rhs);
        friend EuclideanVector& operator-(const EuclideanVector &lhs, const EuclideanVector &rhs);
        friend double operator*(const EuclideanVector &lhs, const EuclideanVector &rhs);
        friend EuclideanVector& operator*(const EuclideanVector &euclideanVector, const double times);
        friend EuclideanVector& operator*(const double times, const EuclideanVector &euclideanVector);
        friend EuclideanVector& operator/(const EuclideanVector &euclideanVector, const double divisor);

    private:
        unsigned int dimension_;
        double *magnitude_ = nullptr;
    };

    //declaration in namespace
    std::ostream &operator<<(std::ostream &os, const EuclideanVector &euclideanVector);
    bool operator==(const EuclideanVector &lhs, const EuclideanVector &rhs);
    bool operator!=(const EuclideanVector &lhs, const EuclideanVector &rhs);
    EuclideanVector& operator+(const EuclideanVector &lhs, const EuclideanVector &rhs);
    EuclideanVector& operator-(const EuclideanVector &lhs, const EuclideanVector &rhs);
    double operator*(const EuclideanVector &lhs, const EuclideanVector &rhs);
    EuclideanVector& operator*(const EuclideanVector &euclideanVector, const double times);
    EuclideanVector& operator*(const double times, const EuclideanVector &euclideanVector);
    EuclideanVector& operator/(const EuclideanVector &euclideanVector, const double divisor);

}

//std::ostream &operator<<(std::ostream &os, const evec::EuclideanVector  &euclideanVector);

#endif //EUCLIDEANVECTOR_H
