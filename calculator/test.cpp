#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stack>


int checkDecimal(std::string string);
int main(int argc, char const *argv[])
{
	std::string s;
	std::cin>>s;
	int s1 = checkDecimal(s);
	std::cout<<s1<<std::endl;
	std::cout<<s.size()<<std::endl;
	std::cout<<s.size()-s1<<std::endl;
	//一样的话就加！compare  function returns 0 if strings are equal hence the '!'
	if(!s.compare("apple")){
		std::cout<<"same?"<<std::endl;
	}
	return 0;
}

int checkDecimal(std::string string) {
    std::string s = string;
    int find = s.find(".")+1;

    return find;
}
