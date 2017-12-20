#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stack>
#include <string>
#include <queue>

using namespace std;

//check the number if it is an int or double
void checkNum(string s, stack<pair<double,double> > &n){
	if(s.find('.') != string::npos) {
		n.push(make_pair(stod(s),0.0));
	}else{
		n.push(make_pair(stod(s),1.0));
	}
}
//get the number from stack and pop out
pair<double,double> getOne(stack<pair<double,double> > &n) {
	if(n.empty()){
		cout<<"Sorry,the stack is empty"<<endl;
		exit(1);
	}
	pair<double,double> a = n.top();
	n.pop();
	if(a.second == 1.0) a.first = round(a.first);
	return a;
}

//print the calculation result
void printR(pair<double,double> a, pair<double,double> b, double r, string s,stack<pair<double,double> > &n){
	if(a.second == 0.0) cout<<a.first;
	else cout<<(int)a.first;
	if(!s.compare("+")) cout<<" + ";
	else if(!s.compare("-")) cout<<" - ";
	else if(!s.compare("*")) cout<<" * ";
	else if(!s.compare("/")) cout<<" / ";
	if(b.second == 0.0) cout<<b.first<<" = ";
	else cout<<(int)b.first<<" = ";
	if(a.second == 1.0 && b.second == 1.0) {
		cout<<(int)r<<endl;
		n.push(make_pair(r,1.0));
	}else{
		cout<<r<<endl;
		n.push(make_pair(r,0.0));
	}
}
//add two number
void addNum(stack<pair<double,double> > &n) {
	pair<double,double> a = getOne(n);
	pair<double,double> b = getOne(n);
	printR(a,b, a.first+b.first,"+",n);
}
//division between two numbers
void divNum(stack<pair<double,double> > &n) {
	pair<double,double> a = getOne(n);
	pair<double,double> b = getOne(n);
	if(b.first == 0.0) {
		cout<<"Sorry, cannot divided by 0"<<endl;
		exit(1);
	}
	printR(a,b, a.first/b.first,"/",n);
}
//multi two numbers
void multNum(stack<pair<double,double> > &n) {
	pair<double,double> a = getOne(n);
	pair<double,double> b = getOne(n);
	printR(a,b, a.first*b.first,"*",n);
}
//sub two numbers
void subNum(stack<pair<double,double> > &n) {
	pair<double,double> a = getOne(n);
	pair<double,double> b = getOne(n);
	printR(a,b, a.first-b.first,"-",n);
}
//pop
void popNum(stack<pair<double,double> > &n) {
	if(!n.empty()) n.pop();
	else {
		cout<<"Sorry no more pop"<<endl;
		exit(1);
	}
}
//square root
void sqrtNum(stack<pair<double,double> > &n) {
	pair<double,double> a = getOne(n);
	if(a.first <= 0) {
		cout<<"Square just for positive number"<<endl;
		exit(1);
	}
	if(a.second == 1.0){
		cout<<"sqrt "<<(int)a.first<<" = "<<(int)sqrt(a.first)<<endl;
		n.push(make_pair(sqrt(a.first),1.0));
	} else{
		cout<<"sqrt "<<a.first<<" = "<<sqrt(a.first)<<endl;
		n.push(make_pair(sqrt(a.first),0.0));		
	}
	return;
}
//By using of queue to reverse the stack
void reverseNum(stack<pair<double,double> > &n) {
	queue<pair<double,double> > q;
	pair<double,double> a = getOne(n);
	if(a.second == 0.0 || a.first < 0 || a.first > n.size()) {
		cout<<"The reverse number should be positive integer which is less than stack size"<<endl;
		exit(1);	
	} 
	for(int i = 0;i < (int)a.first;i++){
		pair<double,double> b = getOne(n);
		q.push(b);
	}
	for(int i = 0;i < (int)a.first;i++) {
		pair<double,double> c = q.front();
		q.pop();
		n.push(c);
	}
}

//process repeat part when the check flag is 1
void rePro(stack<pair<double,double> > &n, queue<string> &q,int &check) {
	pair<double,double> a = getOne(n);
	if(a.second == 0.0 || a.first < 0) {
		cout<<"The repeat number must be an positive integer"<<endl;
		exit(1);
	} 
	if(a.first != 0.0){
		int i = 0;
		string s;
		while(!q.empty()){
			if(i == (int)a.first) {
				break;
			}
			s = q.front();
			if(s.find_first_not_of("-1234567890.") == string::npos) checkNum(s,n);
			else if(!s.compare("add")) addNum(n);
			else if(!s.compare("sub")) subNum(n);
			else if(!s.compare("mult")) multNum(n);
			else if(!s.compare("div")) divNum(n);
			else if(!s.compare("sqrt")) sqrtNum(n);
			else if(!s.compare("pop")) popNum(n);
			else if(!s.compare("reverse")) reverseNum(n);
			else if(!s.compare("endrepeat")) i++;
			q.pop();
			q.push(s);
		}
	} 
	while(!q.empty()){
		q.pop();
	}
	check = 0;
}
int main(int argc, char* argv[])
{
	
	// setup the print out format for the precision required.
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(3);

	// open the file for reading
	ifstream in;
	in.open(argv[1]);

	// string to be read into
	string s;

	//first is each number as double, second is number type, 0.0 is double, 1.0 is int
	stack<pair<double,double> > num_stack;
	//queue to store all operation during repeat
	queue<string> repeat_queue;
	//a flag to store the operation into queue
	int check = 0;
	// read the file while we have input.
	while (in >> s) {
		if(check == 0) {
			if(s.find_first_not_of("-1234567890.") == string::npos) checkNum(s,num_stack);
			else if(!s.compare("add")) addNum(num_stack);
			else if(!s.compare("sub")) subNum(num_stack);
			else if(!s.compare("mult")) multNum(num_stack);
			else if(!s.compare("div")) divNum(num_stack);
			else if(!s.compare("sqrt")) sqrtNum(num_stack);
			else if(!s.compare("pop")) popNum(num_stack);
			else if(!s.compare("reverse")) reverseNum(num_stack);
			else if(!s.compare("repeat")) check = 1;
			else{
				cout<<"Sorry no matched repeat"<<endl;
				exit(1);
			}			
		} else {
			if(!s.compare("repeat")){
				cout<<"Sorry, no nested repeat"<<endl;
				exit(1);
			}
			if(s.compare("endrepeat")) repeat_queue.push(s);
			else {
				repeat_queue.push(s);
				rePro(num_stack,repeat_queue,check);
			}
		}		
	}
	in.close();
	return 0;
}

























