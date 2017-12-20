#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stack>
#include <string>
#include <queue>

void showDoubleType(std::stack<double> doubleType);
void showTypeName(std::stack<std::string> typeName);
int checkDecimal(std::string string);
int checkResult(double a);
void reverseStack(int a, std::stack<std::string> typeName, std::stack<double> doubleType);

int main(int argc, char* argv[]) {

    // setup the print out format for the precision required.
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);

    // open the file for reading
    std::ifstream in;
    in.open(argv[1]);

    // string to be read into
    std::string s;
    std::string s1;
    //create two stacks
    std::stack <double> doubleType;
    std::stack <std::string> typeName;

    //check about repeat
    int numRp = 0;
    int numER = 0;
    while(in >> s1){
        if(!s1.compare("repeat")) {
            numRp++;
        }else if(!s1.compare("endrepeat")){
            numER++;
        }else{
            continue;
        }
        if(numER > numRp) {
            std::cout<<"Invalid input on repeat"<<std::endl;
            exit(1);
        }
    }
    if(numRp != numER) {
        std::cout<<"Invalid input on repeat"<<std::endl;
        exit(1);
    }
in.close();
in.open(argv[1]);

    // read the file while we have input.
    //每个string都是按空格分的
    while (in >> s) {
       
        //check num or operation
        std::size_t found_num = s.find_first_not_of("-1234567890.");
        /*
        if it is a number,then check it is an int or double
        - if it is an int, then put its type in the stack
          then transfer into double
        - if it is a double, same
        */
        if(found_num == std::string::npos){
            std::size_t found_dec = s.find(".");
            if(found_dec == std::string::npos) {
                double num = std::stod(s);
                doubleType.push(num);
                typeName.push("int");
                //std::cout<<"int:    "<<s<<std::endl;
            }else{
                if(checkDecimal(s) == 1) {
                    double num = std::stod(s);
                    doubleType.push(num);
                    typeName.push("double"); 
                   // std::cout<<"double:    "<<s<<std::endl;
                }else{
                    std::cout<<"Invalid decimal place"<<std::endl;
                    //continue;
                    exit(1);
                }                
            }
            //std::cout<<"hhhhhhhhhhh     "<<std::endl;

        } else {
           // std::cout<<"This is a operation:     "<<s<<std::endl;
            if(!s.compare("add")) {
                std::string str1 = typeName.top();
                typeName.pop();
                std::string str2 = typeName.top();
                typeName.pop(); 
                double num1 = doubleType.top();
                doubleType.pop();
                double num2 = doubleType.top();
                doubleType.pop();
                if(!str1.compare("double") || !str1.compare("double")) {
                    double newN = num1 + num2;
                    doubleType.push(newN);
                    typeName.push("double");                     
                } else {
                    double newN = num1 + num2;
                    if(checkResult(newN) == 1) {
                        doubleType.push(newN);
                        typeName.push("int"); 
                    }else {
                        doubleType.push(newN);
                        typeName.push("double"); 
                    }
                }
                std::string str3 = typeName.top();
                double num3 = doubleType.top();
                //str1 + str2 = newN
                if(!str1.compare("double")) {
                    std::cout<<num1;
                }else{
                    int temp = num1;
                    std::cout<<temp;
                }
                if(!str2.compare("double")) {
                    std::cout<<" + "<<num2;
                }else{
                    int temp = num2;
                    std::cout<<" + "<<temp;
                }
                if(!str3.compare("double")) {
                    std::cout<<" = "<<num3<<std::endl;
                }else{
                    int temp = num3;
                    std::cout<<" = "<<temp<<std::endl;
                }

            }else if(!s.compare("sub")){
                std::string str1 = typeName.top();
                typeName.pop();
                std::string str2 = typeName.top();
                typeName.pop(); 
                double num1 = doubleType.top();
                doubleType.pop();
                double num2 = doubleType.top();
                doubleType.pop();
                if(!str1.compare("double") || !str1.compare("double")) {
                    double newN = num1 - num2;
                    doubleType.push(newN);
                    typeName.push("double");                     
                } else {
                    double newN = num1 - num2;
                    if(checkResult(newN) == 1) {
                        doubleType.push(newN);
                        typeName.push("int"); 
                    }else {
                        doubleType.push(newN);
                        typeName.push("double"); 
                    }
                }
                std::string str3 = typeName.top();
                double num3 = doubleType.top();
                //str1 - str2 = newN
                if(!str1.compare("double")) {
                    std::cout<<num1;
                }else{
                    int temp = num1;
                    std::cout<<temp;
                }
                if(!str2.compare("double")) {
                    std::cout<<" - "<<num2;
                }else{
                    int temp = num2;
                    std::cout<<" - "<<temp;
                }
                if(!str3.compare("double")) {
                    std::cout<<" = "<<num3<<std::endl;
                }else{
                    int temp = num3;
                    std::cout<<" = "<<temp<<std::endl;
                }
            }else if(!s.compare("mult")){
                std::string str1 = typeName.top();
                typeName.pop();
                std::string str2 = typeName.top();
                typeName.pop(); 
                double num1 = doubleType.top();
                doubleType.pop();
                double num2 = doubleType.top();
                doubleType.pop();
                if(!str1.compare("double") || !str1.compare("double")) {
                    double newN = num1 * num2;
                    doubleType.push(newN);
                    typeName.push("double");                     
                } else {
                    double newN = num1 * num2;
                    if(checkResult(newN) == 1) {
                        doubleType.push(newN);
                        typeName.push("int"); 
                    }else {
                        doubleType.push(newN);
                        typeName.push("double"); 
                    }
                }
                std::string str3 = typeName.top();
                double num3 = doubleType.top();
                //str1 * str2 = newN
                if(!str1.compare("double")) {
                    std::cout<<num1;
                }else{
                    int temp = num1;
                    std::cout<<temp;
                }
                if(!str2.compare("double")) {
                    std::cout<<" * "<<num2;
                }else{
                    int temp = num2;
                    std::cout<<" * "<<temp;
                }
                if(!str3.compare("double")) {
                    std::cout<<" = "<<num3<<std::endl;
                }else{
                    int temp = num3;
                    std::cout<<" = "<<temp<<std::endl;
                }
            }else if(!s.compare("div")){
                std::string str1 = typeName.top();
                typeName.pop();
                std::string str2 = typeName.top();
                typeName.pop(); 
                double num1 = doubleType.top();
                doubleType.pop();
                double num2 = doubleType.top();
                doubleType.pop();
                if(!str1.compare("double") || !str1.compare("double")) {
                    double newN = num1 / num2;
                    doubleType.push(newN);
                    typeName.push("double");                     
                } else {
                    double newN = num1 / num2;
                    if(checkResult(newN) == 1) {
                        doubleType.push(newN);
                        typeName.push("int"); 
                    }else {
                        doubleType.push(newN);
                        typeName.push("double"); 
                    }
                }
                std::string str3 = typeName.top();
                double num3 = doubleType.top();
                //str1 - str2 = newN
                if(!str1.compare("double")) {
                    std::cout<<num1;
                }else{
                    int temp = num1;
                    std::cout<<temp;
                }
                if(!str2.compare("double")) {
                    std::cout<<" / "<<num2;
                }else{
                    int temp = num2;
                    std::cout<<" / "<<temp;
                }
                if(!str3.compare("double")) {
                    std::cout<<" = "<<num3<<std::endl;
                }else{
                    int temp = num3;
                    std::cout<<" = "<<temp<<std::endl;
                }
            }else if(!s.compare("sqrt")){
                std::string str1 = typeName.top();
                typeName.pop();
                double num1 = doubleType.top();
                doubleType.pop();
                if(num1 <= 0) {
                    std::cout<<"Sorry, sqrt cannot take non-positive num"<<std::endl;
                    exit(1);
                }else{
                    if(!str1.compare("double")) {
                        double newN = sqrt(num1);
                        doubleType.push(newN);
                        typeName.push("double");
                    }else{
                        double newN = sqrt(num1);
                        if(checkResult(newN) == 1) {
                            doubleType.push(newN);
                            typeName.push("int");
                        }else {
                            doubleType.push(newN);
                            typeName.push("double"); 
                        }
                    }
                    std::string str3 = typeName.top();
                    double num3 = doubleType.top();
                    std::cout<<"sqrt ";
                    if(!str1.compare("double")) {
                        std::cout<<num1<<" = ";
                    }else{
                        int temp = num1;
                        std::cout<<temp<<" = ";
                    }
                    if(!str3.compare("double")) {
                        std::cout<<num3<<std::endl;
                    }else{
                        int temp = num3;
                        std::cout<<temp<<std::endl;
                    }
                }
            }else if(!s.compare("pop")){
                doubleType.pop();
                typeName.pop();                
            }else if(!s.compare("reverse")){
                //printf("into reverse\n");
                //showDoubleType(doubleType);
                std::string str1 = typeName.top();
                typeName.pop();
                double num1 = doubleType.top();
                doubleType.pop();
                //printf("pop the reverse number\n");
                //showDoubleType(doubleType);
                if(!str1.compare("double") || num1 < 0) {
                    std::cout<<"sorry the number of reverse elements should be positive integer"<<std::endl;
                    exit(1);
                }
                reverseStack(num1,typeName,doubleType);












                
                //printf("after reverse\n");
               // showDoubleType(doubleType);
            }else if(!s.compare("repeat")) {
                std::cout<<" need to implement yet "<<std::endl;
            }
        }    
    }
    //showDoubleType(doubleType);
    //showTypeName(typeName);
    in.close();

}

void showDoubleType(std::stack<double> doubleType) {
    std::stack<double> d = doubleType;
    while(!d.empty()) {
        std::cout<<d.top()<<std::endl;
        d.pop();
    }
}

void showTypeName(std::stack<std::string> typeName) {
    std::stack<std::string> d = typeName;
    while(!d.empty()) {
        std::cout<<d.top()<<std::endl;
        d.pop();
    }
    std::cout<<"done~"<<std::endl;
}

//avliable deci input, return 1, else return 0
int checkDecimal(std::string string) {
    std::string s = string;
    int find = s.find(".")+1;
    int dec = s.size() - find;
    if(dec == 1) {
        return 1;
    }else{
        return 0;
    }
}

/*
check result of two int work, since they are double format,
if the result is int, then put int type into stack
else, put double type into stack
double result == 0
int result == 1
*/
int checkResult(double a) {
    int x = std::abs(a);
    double y = std::fabs(a);
    if(y - x > 0) return 0;
    return 1;
}

void reverseStack(int a, std::stack<std::string> typeName, std::stack<double> doubleType) {
    std::stack<double> b = doubleType;
    std::stack<std::string> c = typeName;
    std::queue<double> d;
    std::queue<std::string> e;
    if(a > b.size() || a > c.size()) {
        std::cout<<"Sorry reverse number over amount"<<std::endl;
    }
    int i = 0;
    double temb;
    std::string temc;
    while(i < a) {
        temb = b.top();
        temc = c.top();
        b.pop();
        c.pop();
        d.push(temb);
        e.push(temc);
        i++;
        //std::cout<<"the number pop from stack and put into queue     "<<temb<<std::endl;
    }
    i = 0;
    while(i < a) {
        temb = d.front();
        temc = e.front();
        d.pop();
        e.pop();
        b.push(temb);
        c.push(temc);
        i++;
        
       // std::cout<<"the number pop from queue and put into stack     "<<temb<<std::endl;

    }
    showDoubleType(b);

}














