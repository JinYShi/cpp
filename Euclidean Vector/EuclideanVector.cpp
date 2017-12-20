#include "EuclideanVector.h"

namespace evec {
    //default constructor
    EuclideanVector::EuclideanVector(): EuclideanVector(1U){normalFormCalculated = 0;}
    //constructor take dimensions only
    EuclideanVector::EuclideanVector(const unsigned numD): EuclideanVector(numD,0.0) {normalFormCalculated = 0;}
    //constructor take the demension and magnitude
    EuclideanVector::EuclideanVector(const unsigned numD, const double mag):numDimension{numD}{
        normalFormCalculated = 0;
        magnitude = new double[numDimension];
        int i = 0;
        int d = numDimension;
        while(i < d){
            magnitude[i] = mag;
            i++;
        }            
    }
    //construcor for initializer_list
    EuclideanVector::EuclideanVector(std::initializer_list<double> li){
        normalFormCalculated = 0;
        numDimension = static_cast<unsigned>(li.size());
        magnitude = new double[numDimension];
        int count = 0;
        for(auto i: li) {
            magnitude[count] = i;
            ++count;
        }
    } 
    //copy constructor
    EuclideanVector::EuclideanVector(const EuclideanVector &obj) {
        normalFormCalculated = 0;
        magnitude = new double[obj.getNumDimensions()];
        numDimension = obj.getNumDimensions();
        int d = obj.getNumDimensions();
        for(int i = 0;i < d;i++) {
            magnitude[i] = obj.get(i);
        }
         
    }
    //move constructor
    EuclideanVector::EuclideanVector(EuclideanVector &&obj){    
        // normalFormCalculated = 0;
        // magnitude = new double[obj.getNumDimensions()];    
        // numDimension = std::move(obj.getNumDimensions());
        // int d = numDimension;
        // for(int i = 0;i < d;i++) {
        //     magnitude[i] = std::move(obj.magnitude[i]);
        // }
        // delete[] obj.magnitude;
        // obj.magnitude = nullptr;
        // obj.normalFormCalculated = 0;
        // obj.numDimension = 0; 
        numDimension = obj.numDimension;
        magnitude = obj.magnitude;
        normalFormCalculated = obj.normalFormCalculated;
        obj.magnitude = nullptr;
        obj.numDimension = 0;       
    }
    //copy assignment operator 
    EuclideanVector& EuclideanVector::operator=(const EuclideanVector &obj) {
        if(this == &obj) return *this;
        delete[] magnitude;
        magnitude = new double[obj.getNumDimensions()];
        numDimension = obj.getNumDimensions();
        normalFormCalculated = 0;
        int d = obj.getNumDimensions();
        for(int i = 0;i < d;i++){
            magnitude[i] = obj.magnitude[i];
        }
        return *this;
    }
    //move assignemnt operator   
    EuclideanVector& EuclideanVector::operator=(EuclideanVector &&obj) {
        if(this == &obj) return *this;
        delete[] magnitude;
        // magnitude = new double[obj.getNumDimensions()];
        // numDimension = std::move(obj.getNumDimensions());
        magnitude = obj.magnitude;
        numDimension = obj.numDimension;
       // normalFormCalculated = 0;
        normalFormCalculated = obj.normalFormCalculated;
        // int d = obj.getNumDimensions();
        // for(int i = 0;i < d;i++){
        //     magnitude[i] = std::move(obj.magnitude[i]);
        // }
        // delete[] obj.magnitude;
        //obj.magnitude = new double[obj.numDimension];
        obj.magnitude = nullptr;
        obj.numDimension = 0;
        return *this;
    }
    //Destructor
    EuclideanVector::~EuclideanVector(){
        delete[] magnitude;
    }
    //dimension getter
    const unsigned int EuclideanVector::getNumDimensions()const {return numDimension;}
    //index getter
    const double EuclideanVector::get (int n) const {
        int d = numDimension;
        if (n > d) exit(1);
        return magnitude[n];
    }
    //Normal getter
    const double EuclideanVector::getEuclideanNorm() const  {
        normalFormCalculated = 0;
        int d = getNumDimensions();
        for(int i = 0;i < d;i++) {
            normalFormCalculated += get(i)*get(i);
        }
        return sqrt(normalFormCalculated);
    }
    //create the unit vector
    EuclideanVector EuclideanVector::createUnitVector() const {return EuclideanVector(*this) /= getEuclideanNorm();}
    //two overload set function
    double& EuclideanVector::operator[] (int i) {
        int d = numDimension;
        assert(i < d && "not match");
        return magnitude[i];
    }
    double EuclideanVector::operator[] (int i) const {
        int d = numDimension;
        assert(i < d && "not match");
        return magnitude[i];
    }
    
    /*--------operator----------*/
    EuclideanVector& EuclideanVector::operator+=(const EuclideanVector &obj) {
        //assert(this->getNumDimensions() == obj.getNumDimensions() && "Different size");
        if(this->getNumDimensions() == obj.getNumDimensions()) {
            int size = this->getNumDimensions();             
            for(int i = 0;i < size;i++) {
                this->magnitude[i] +=  obj.magnitude[i];
            }
        }
        return *this;
    }

    EuclideanVector& EuclideanVector::operator-=(const EuclideanVector &obj) {
        assert(this->getNumDimensions() == obj.getNumDimensions() && "Different size");
        int size = this->getNumDimensions();
        for(int i = 0;i < size;i++) {
            this->magnitude[i] -=  obj.magnitude[i];
        }  
        return *this;
    }

    EuclideanVector& EuclideanVector::operator*=(const double d) {
        int size = this->getNumDimensions();
        for(int i = 0;i <size;i++) {
            this->magnitude[i] *= d;
        }
        return *this;
    }

    EuclideanVector& EuclideanVector::operator/=(const double d) {
        assert(d != 0.0);
        int size = this->getNumDimensions();
        for(int i = 0;i < size;i++) {
            magnitude[i] /= d;
        } 
        return *this;
    }

    std::ostream& operator<<(std::ostream &os, const EuclideanVector &obj) {
        if(obj.getNumDimensions() == 0) {
            os << "[]";
            return os;
        }else{
            const std::vector<double> ve = obj;
            os << "[";
            int d = obj.getNumDimensions();
            for(int i = 0;i < d-1;i++){                
                os << obj[i]<<" ";
            }
            os<<obj[d-1]<<"]";
            return os;
        }   
    }
    bool operator==(const EuclideanVector &obj1, const EuclideanVector &obj2) {
        if(obj1.getNumDimensions() != obj2.getNumDimensions()) return false;
        int d = obj1.getNumDimensions();
        for(int i = 0;i < d;i++) {
            if(obj1.get(i) != obj2.get(i)) return false;
        }
        return true;
    }
    bool operator!=(const EuclideanVector &obj1, const EuclideanVector &obj2) {
        return !(obj1 == obj2);
    }

    EuclideanVector& operator+(const EuclideanVector &obj1, const EuclideanVector &obj2) {
        if(obj1.getNumDimensions() != obj2.getNumDimensions()) exit(1);
        EuclideanVector *newE = new EuclideanVector(obj1);
        int d = obj1.getNumDimensions();
        for(int i = 0;i < d;i++) {
            newE->magnitude[i] = obj1.get(i)+obj2.get(i);
        }
        return *newE;
    }

    EuclideanVector& operator-(const EuclideanVector &obj1, const EuclideanVector &obj2) {
        if(obj1.getNumDimensions() != obj2.getNumDimensions()) exit(1);
        EuclideanVector *newE = new EuclideanVector(obj1);
        int d = obj1.getNumDimensions();
        for(int i = 0;i < d;i++) {
            newE->magnitude[i] = obj1.get(i)-obj2.get(i);
        }
        return *newE;
    }

    double operator*(const EuclideanVector &obj1, const EuclideanVector &obj2) {
        if(obj1.getNumDimensions() != obj2.getNumDimensions()) exit(1);
        double result = 0;
        int d = obj1.getNumDimensions();
        for(int i = 0;i < d;i++){
            result += obj1.get(i)*obj2.get(i);
        }
        return result;
    }

    EuclideanVector& operator*(const EuclideanVector &obj1, const double numD) {
        EuclideanVector *newE = new EuclideanVector(obj1);
        int d = obj1.getNumDimensions();
        for(int i = 0;i < d;i++){
            newE->magnitude[i] = obj1.get(i)*numD;
        }
        return *newE;
    }
    EuclideanVector& operator*(const EuclideanVector &obj1, const int numI) {
        EuclideanVector *newE = new EuclideanVector(obj1);
        int d = obj1.getNumDimensions();
        for(int i = 0;i < d;i++){
            newE->magnitude[i] = obj1.get(i)*numI;
        }
        return *newE;
    }
    EuclideanVector& operator*(const double numD, const EuclideanVector &obj1) {
        EuclideanVector *newE = new EuclideanVector(obj1);
        int d = obj1.getNumDimensions();
        for(int i = 0;i < d;i++){
            newE->magnitude[i] = obj1.get(i)*numD;
        }
        return *newE;
    }
    EuclideanVector& operator*(const int numI, const EuclideanVector &obj1) {
        EuclideanVector *newE = new EuclideanVector(obj1);
        int d = obj1.getNumDimensions();
        for(int i = 0;i < d;i++){
            newE->magnitude[i] = obj1.get(i)*numI;
        }
        return *newE;
    }

    EuclideanVector& operator/(const EuclideanVector &obj1, const double numD) {
        if(numD == 0) exit(1);
        EuclideanVector *newE = new EuclideanVector(obj1);
        int d = obj1.getNumDimensions();
        for(int i = 0;i < d;i++){
            newE->magnitude[i] = obj1.get(i)/numD;
        }
        return *newE;
    }

    EuclideanVector& operator/(const EuclideanVector &obj1, const int numI) {
        if(numI == 0) exit(1);
        EuclideanVector *newE = new EuclideanVector(obj1);
        int d = obj1.getNumDimensions();
        for(int i = 0;i < d;i++){
            newE->magnitude[i] = obj1.get(i)/numI;
        }
        return *newE;
    }
    //Vector type conversion
    EuclideanVector::operator std::vector<double>() const {
        std::vector<double> ve;
        assert(magnitude != nullptr);
        int d = numDimension;
        for(int i = 0;i < d;i++) {
            ve.push_back(magnitude[i]);
        }
        return ve;
    }
    //List type conversion
    EuclideanVector::operator std::list<double>() const {
        std::list<double> li;
        assert(magnitude != nullptr);
        int d = numDimension;
        for(int i = 0;i < d;i++) {
            li.push_back(magnitude[i]);
        }
        return li;           
    }

}