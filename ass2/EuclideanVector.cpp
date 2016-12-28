//
// Created by Haonan on 8/24/16.
//

#include <iostream>
#include <math.h>
#include <assert.h>
#include "EuclideanVector.h"


//constructor
evec::EuclideanVector::EuclideanVector() : evec::EuclideanVector::EuclideanVector(1) {}

evec::EuclideanVector::EuclideanVector(const unsigned int dimension) :
        dimension_{dimension}
{
    magnitude_ = new double [dimension_];
    for (unsigned int i = 0; i < dimension; i++) {
        *(magnitude_+i) = 0;
    }
}

evec::EuclideanVector::EuclideanVector(const unsigned int dimension, const double vecValue) :
        dimension_{dimension}
{
    magnitude_ = new double [dimension_];
    for (unsigned int i = 0; i < dimension; i++) {
        *(magnitude_+i) = vecValue;
    }
}

evec::EuclideanVector::EuclideanVector(const std::list<double>::const_iterator begin, const std::list<double>::const_iterator end) :
        dimension_{(unsigned int)std::distance(begin, end)}
{
    magnitude_ = new double [dimension_];
    unsigned int i = 0;
    for (std::list<double>::const_iterator it = begin; it != end; ++it) {
        *(magnitude_+i) = (*it);
        i++;
    }
}


evec::EuclideanVector::EuclideanVector(const std::list<double> l) :
        dimension_{(unsigned int)l.size()}
{
    magnitude_ = new double [dimension_];
    unsigned int i = 0;
    for (std::list<double>::const_iterator it = l.begin(); it!= l.end(); ++it) {
        *(magnitude_+i) = (*it);
        i++;
    }
}

evec::EuclideanVector::EuclideanVector(const std::vector<double>::const_iterator begin, const std::vector<double>::const_iterator end) :
        dimension_{(unsigned int)std::distance(begin, end)}
{
    magnitude_ = new double [dimension_];
    unsigned int i = 0;
    for (std::vector<double>::const_iterator it = begin; it != end; ++it) {
        *(magnitude_+i) = (*it);
        i++;
    }
}


evec::EuclideanVector::EuclideanVector(const std::vector<double> l) :
        dimension_{(unsigned int)l.size()}
{
    magnitude_ = new double [dimension_];
    unsigned int i = 0;
    for (std::vector<double>::const_iterator it = l.begin(); it!= l.end(); ++it) {
        *(magnitude_+i) = (*it);
        i++;
    }
}

evec::EuclideanVector::EuclideanVector(const std::initializer_list<double> l) :
        dimension_{(unsigned int)l.size()}
{
    magnitude_ = new double [dimension_];
    unsigned int i = 0;
    for(std::initializer_list<double>::const_iterator it = l.begin(); it != l.end(); ++it) {
        *(magnitude_+i) = (*it);
        i++;
    }
}


//deconstructor
evec::EuclideanVector::~EuclideanVector() {
    if (magnitude_ != nullptr) delete [] magnitude_;
    magnitude_ = nullptr;
    // std::cout<<"deconstructor"<<std::endl;
}


//copy consturctor
evec::EuclideanVector::EuclideanVector(const EuclideanVector& euclideanVector) :
        dimension_{euclideanVector.dimension_}
{
    if (magnitude_ != nullptr) {
        delete [] magnitude_; 
    }
    magnitude_ = new double [dimension_];
    double *val = euclideanVector.magnitude_;
    for (unsigned int i = 0; i < dimension_; i++) {
        *(magnitude_+i) = *(val+i);
    }

}


//move constructor
evec::EuclideanVector::EuclideanVector(EuclideanVector &&euclideanVector) :
        dimension_{std::move(euclideanVector.dimension_)}
{
    assert(this != &euclideanVector);
    if (magnitude_ != nullptr) {
        delete [] magnitude_; 
    }
    euclideanVector.dimension_ = 0;
    magnitude_ = std::move(euclideanVector.magnitude_);
    euclideanVector.magnitude_ = nullptr;
//    std::cout << "EuclideanVector move constructor" << std::endl;
}


//copy assignment operator
evec::EuclideanVector& evec::EuclideanVector::operator=(const evec::EuclideanVector &euclideanVector)
{
    if (this != &euclideanVector) {
        if (magnitude_ != nullptr) {
            // std::cout<<"Leak"<<std::endl;
            delete [] magnitude_; //Eg h = h*2, delete h's manitude
        }
        dimension_ = euclideanVector.dimension_;
        magnitude_ = new double [dimension_];
        double *val = euclideanVector.magnitude_;
        for (unsigned int i = 0; i< dimension_;i++) {
            *(magnitude_+i) = *(val+i);
        }
    }

    return *this;
}

//move assignment operator
evec::EuclideanVector& evec::EuclideanVector::operator=(evec::EuclideanVector &&euclideanVector)
{
    if (this != &euclideanVector) {
        dimension_ = std::move(euclideanVector.dimension_);
        euclideanVector.dimension_ = 0;
        if (magnitude_ != nullptr) {;
            delete [] magnitude_; //Eg h = h*2, delete h's manitude
        }
        magnitude_ = std::move(euclideanVector.magnitude_);
        euclideanVector.magnitude_ = nullptr;
    }
    return *this;
}


//member function
unsigned int evec::EuclideanVector::getNumDimensions() const {return dimension_; };

double evec::EuclideanVector::get(unsigned int dimension) const
{
    assert(dimension >= 0 && dimension < dimension_);
    double *val = magnitude_;
    return *(val+dimension);

}


double evec::EuclideanVector::getEuclideanNorm() const
{
    double result;
    double sum = 0;
    double *val = magnitude_;
    for (unsigned int i = 0; i< dimension_; i++) {
        sum += (*(val+i))*(*(val+i));
    }
    result = sqrt(sum);
    return result;
}

evec::EuclideanVector evec::EuclideanVector::createUnitVector() const
{
    double dimensionNorm = this->getEuclideanNorm();
//    unsigned int dimension = dimension_;
    std::vector<double> vec;
    double *val = magnitude_;
    for (unsigned int i = 0; i < dimension_; i++) {
        vec.push_back(*(val+i)/dimensionNorm);
    }
    EuclideanVector *unit = new EuclideanVector(vec.begin(), vec.end()); //use the existing consturctor
    return *unit;
}


//operator for getter and setter
double evec::EuclideanVector::operator [] (unsigned int dimension) const
{
    assert(dimension>=0 && dimension < dimension_);
    double *val = magnitude_;
    return *(val+dimension);
}

double& evec::EuclideanVector::operator[](unsigned int dimension)
{
    assert(dimension>=0 && dimension < dimension_);
    double *val = magnitude_;
    return *(val+dimension);
}

//operator
evec::EuclideanVector& evec::EuclideanVector::operator+=(const evec::EuclideanVector &euclideanVector)
{
    assert(dimension_ == euclideanVector.dimension_);
    for (unsigned int i = 0; i < dimension_; i++) {
        *(magnitude_+i) += *(euclideanVector.magnitude_+i);
    }
    return *this;
}

evec::EuclideanVector& evec::EuclideanVector::operator-=(const evec::EuclideanVector &euclideanVector)
{
    assert(dimension_ == euclideanVector.dimension_);
    for (unsigned int i = 0; i < dimension_; i++) {
        *(magnitude_+i) -= *(euclideanVector.magnitude_+i);
    }
    return *this;
}

evec::EuclideanVector& evec::EuclideanVector::operator*=(const double times)
{
    for (unsigned int i = 0; i < dimension_; i++) {
        *(magnitude_+i) *= times;
    }
    return *this;
}

evec::EuclideanVector& evec::EuclideanVector::operator/=(const double divisor)
{
    for (unsigned int i = 0; i < dimension_; i++) {
        *(magnitude_+i) /= divisor;
    }
    return *this;
}

//type conversion
evec::EuclideanVector::operator std::vector<double>() const
{
    std::vector<double> vec;
    double *val = magnitude_;
    for (unsigned int i = 0; i < dimension_; i++) {
        vec.push_back(*(val+i));
    }
    return vec;
}

evec::EuclideanVector::operator std::list<double>() const
{
    std::list<double> l;
    double *val = magnitude_;
    for (unsigned int i = 0; i < dimension_; i++) {
        l.push_back(*(val+i));
    }
    return l;
}


//friend function
std::ostream& evec::operator<<(std::ostream &os, const evec::EuclideanVector &euclideanVector)
{

    unsigned int dimension = euclideanVector.getNumDimensions();
    double *val = euclideanVector.magnitude_;
    os << "[";
    if (dimension != 0) {
        for (unsigned int i = 0; i < dimension; i++) {
            os<<*(val+i);
            if (i != dimension - 1) os<<" ";
        }
    }
    os<< "]";
    return os;

}

bool evec::operator==(const evec::EuclideanVector &lhs, const evec::EuclideanVector &rhs)
{
    if (lhs.getNumDimensions() != rhs.getNumDimensions()) return false;
    if (lhs.getNumDimensions() == rhs.getNumDimensions() && lhs.getNumDimensions() == 0) return true;
    for (unsigned int i = 0; i < lhs.getNumDimensions(); i++) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

bool evec::operator!=(const evec::EuclideanVector &lhs, const evec::EuclideanVector &rhs)
{
    return !(lhs==rhs);
}

evec::EuclideanVector& evec::operator+(const evec::EuclideanVector &lhs, const evec::EuclideanVector &rhs)
{
    assert(lhs.getNumDimensions() == rhs.getNumDimensions());
    std::vector<double> vec;
    for (unsigned int i = 0; i< lhs.getNumDimensions(); i++) {
        double val = lhs[i] + rhs[i];
        vec.push_back(val);
    }
    evec::EuclideanVector *result = new evec::EuclideanVector(vec.begin(), vec.end()); //use the existing vector constructor
    return *result;

}

evec::EuclideanVector& evec::operator-(const evec::EuclideanVector &lhs, const evec::EuclideanVector &rhs)
{
    assert(lhs.getNumDimensions() == rhs.getNumDimensions());
    std::vector<double> vec;
    for (unsigned int i = 0; i< lhs.getNumDimensions(); i++) {
        double val = lhs[i] - rhs[i];
        vec.push_back(val);
    }
    evec::EuclideanVector *result = new evec::EuclideanVector(vec.begin(), vec.end()); //use the existing vector constructor
    return *result;

}

double evec::operator*(const evec::EuclideanVector &lhs, const evec::EuclideanVector &rhs)
{
    assert(lhs.getNumDimensions() == rhs.getNumDimensions());
    double result = 0;
    for (unsigned int i = 0; i< lhs.getNumDimensions(); i++) {
        result += lhs[i]*rhs[i];
    }
    return result;
}

evec::EuclideanVector& evec::operator*(const evec::EuclideanVector &euclideanVector, const double times)
{
    std::vector<double> vec;
    for (unsigned int i = 0; i< euclideanVector.getNumDimensions(); i++) {
        double val = euclideanVector[i]*times;
        vec.push_back(val);
    }

    evec::EuclideanVector *result = new evec::EuclideanVector(vec.begin(), vec.end()); //use the existing vector constructor
    return *result;
}

evec::EuclideanVector& evec::operator*(const double times, const evec::EuclideanVector &euclideanVector)
{
    return euclideanVector*times;
}

evec::EuclideanVector& evec::operator/(const evec::EuclideanVector &euclideanVector, const double divisor) {
    std::vector<double> vec;
    for (unsigned int i = 0; i< euclideanVector.getNumDimensions(); i++) {
        double val = euclideanVector[i]/divisor;
        vec.push_back(val);
    }
    evec::EuclideanVector *result = new evec::EuclideanVector(vec.begin(), vec.end()); //use the existing vector constructor
    return *result;
}