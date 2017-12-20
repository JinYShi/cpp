#include <iostream>
#include <fstream>
#include <cmath>
#include <stack>
#include <queue>

using namespace std;

/* 
    all_deque: store all strings to be handled
    my_stack: number stack
    n1, n2: first and second number popped from stack
    f1, f2: indicator of whether n1 & n2 is float or not
    t: result of operation
    depth: current depth of nested repeat loop
*/
deque<string> all_deque;
stack<string> my_stack;
double n1;
double n2;
double t;
bool f1;
bool f2;
int depth = 0;

// get 1 number from stack
void get_1() {
    if(my_stack.top().find(".")!=string::npos) f1 = true;
    n1 = stod(my_stack.top());
    my_stack.pop();
}

// get 2 number from stack
void get_2() {
    get_1();
    if(my_stack.top().find(".")!=string::npos) f2 = true;
    n2 = stod(my_stack.top());
    my_stack.pop();
}

// push number into stack
void push() {
    if(f1||f2) my_stack.push(to_string(t));
    else my_stack.push(to_string(int(t)));
}

// 2-argument operation function
void op(char op) {
    get_2();
    switch(op) {
        case '+': t = n1 + n2;break;
        case '-': t = n1 - n2;break;
        case '*': t = n1 * n2;break;
        case '/': t = n1 / n2;break;
    }
    push();
    if(f1) cout << n1;
    else cout << int(n1);
    cout << " " << op << " ";
    if(f2) cout << n2;
    else cout << int(n2);
    cout << " = ";
    if(f1||f2) cout << t;
    else cout << int(t);
    cout << endl;
}

// sqrt & output function
void msqrt() {
    get_1();
    t = sqrt(n1);
    push();
    if(f1) cout << "sqrt " << n1 << " = " << t << endl;
    else cout << "sqrt " << int(n1) << " = " << int(t) << endl;
}

// reverse function
void mreverse() {
    get_1();
    queue<string> r_queue;
    for(int i=0; i<n1; i++) {
        r_queue.push(my_stack.top());
        my_stack.pop();
    }
    for(int i=0; i<n1; i++) {
        my_stack.push(r_queue.front());
        r_queue.pop();
    }
}

// read from repeat to endrepeat, push them n times to the top of all_deque
// able to handle nested loop
void re() {
    get_1();
    deque<string> s1;
    string s;
    while (!all_deque.empty()) {
        s = all_deque.front();
        all_deque.pop_front();
        if(s=="repeat") {
            depth++;
        } else if(s=="endrepeat" && depth == 0) {
            for(int i = 0; i<int(n1); i++) {
                for (auto p = s1.begin();p != s1.end();p++) {
                    all_deque.push_front(*p);
                }
            }
            break;
        } else if(s=="endrepeat" && depth != 0){
            depth--;
        }
        s1.push_front(s);
    }
}

int main(int argc, char* argv[]) {
    // output format setting
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(3);
	ifstream in;
	in.open(argv[1]);
	string s;

    // read all string from file
    while (in >> s) {
        all_deque.push_back(s);
    }
	in.close();

    // process
	while (!all_deque.empty()) {
        s = all_deque.front();
        all_deque.pop_front();
        f1 = false;
        f2 = false;
        if(isdigit(s[0])||s[0]=='-') {
            my_stack.push(s);
        } else if(s=="add") {
            op('+');
        } else if(s=="sub") {
            op('-');
        } else if(s=="mult") {
            op('*');
        } else if(s=="div") {
            op('/');
        } else if(s=="sqrt") {
            msqrt();
        } else if(s=="pop") {
            my_stack.pop();
        } else if(s=="reverse") {
            mreverse();
        } else if(s=="repeat") {
            re();
        }
	}
}

