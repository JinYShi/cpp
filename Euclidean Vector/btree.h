/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#include <iterator>



// we better include the iterator
#include "btree_iterator.h"

// we do this to avoid compiler errors about non-template friends
// what do we do, remember? :)
template <typename T> class btree;
template <typename T> std::ostream& operator<<(std::ostream& os, const btree<T>& tree)
{
    std::queue<typename btree<T>::Node*> nodeQueue;
    nodeQueue.push(tree.root);
    typename btree<T>::Node *curr;
    while(!nodeQueue.empty()){
        curr = nodeQueue.front();
        for(int i = 0;i < curr->getValuesSize(); ++i) {
            os << curr->values.at(i) << " ";
        }
        nodeQueue.pop();
        auto childL = curr->getChildren();
        for (auto it = childL.begin();it != childL.end();++it){
            nodeQueue.push(it->second);
        }
    }
    return os;
};

template <typename T> 
class btree {
public:
    /** Hmm, need some iterator typedefs here... friends? **/
    friend class btree_iterator<T>;
    typedef btree_iterator<T> iterator;

    friend class const_btree_iterator<T>;
    typedef const_btree_iterator<T> const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    /**
    * Constructs an empty btree.  Note that
    * the elements stored in your btree must
    * have a well-defined zero-arg constructor,
    * copy constructor, operator=, and destructor.
    * The elements must also know how to order themselves
    * relative to each other by implementing operator<
    * and operator==. (These are already implemented on
    * behalf of all built-ins: ints, doubles, strings, etc.)
    * 
    * @param maxNodeElems the maximum number of elements
    *        that can be stored in each B-Tree node
    */
    btree(size_t maxNodeElems = 2);

    /**
    * The copy constructor and  assignment operator.
    * They allow us to pass around B-Trees by value.
    * Although these operations are likely to be expensive
    * they make for an interesting programming exercise.
    * Implement these operations using value semantics and 
    * make sure they do not leak memory.
    */

    /** 
    * Copy constructor
    * Creates a new B-Tree as a copy of original.
    *
    * @param original a const lvalue reference to a B-Tree object
    */
    btree(const btree<T>& original);

    /** 
    * Move constructor
    * Creates a new B-Tree by "stealing" from original.
    *
    * @param original an rvalue reference to a B-Tree object
    */
    btree(btree<T>&& original);
  
  
    /** 
    * Copy assignment
    * Replaces the contents of this object with a copy of rhs.
    *
    * @param rhs a const lvalue reference to a B-Tree object
    */
    btree<T>& operator=(const btree<T>& rhs);

    /** 
    * Move assignment
    * Replaces the contents of this object with the "stolen"
    * contents of original.
    *
    * @param rhs a const reference to a B-Tree object
    */
    btree<T>& operator=(btree<T>&& rhs);

    /**
    * Puts a breadth-first traversal of the B-Tree onto the output
    * stream os. Elements must, in turn, support the output operator.
    * Elements are separated by space. Should not output any newlines.
    *
    * @param os a reference to a C++ output stream
    * @param tree a const reference to a B-Tree object
    * @return a reference to os
    */
    friend std::ostream& operator<< <T> (std::ostream& os, const btree<T>& tree);

    /**
    * The following can go here
    * -- begin() 
    * -- end() 
    * -- rbegin() 
    * -- rend() 
    * -- cbegin() 
    * -- cend() 
    * -- crbegin() 
    * -- crend() 
    */
    iterator begin() const;
    iterator end() const;
    reverse_iterator rbegin();
    reverse_iterator rend();

    const_iterator cbegin() const;
    const_iterator cend() const;
    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    /**
    * Returns an iterator to the matching element, or whatever 
    * the non-const end() returns if the element could 
    * not be found.  
    *
    * @param elem the client element we are trying to match.  The elem,
    *        if an instance of a true class, relies on the operator< and
    *        and operator== methods to compare elem to elements already 
    *        in the btree.  You must ensure that your class implements
    *        these things, else code making use of btree<T>::find will
    *        not compile.
    * @return an iterator to the matching element, or whatever the
    *         non-const end() returns if no such match was ever found.
    */
    iterator find(const T& elem);
    
    /**
    * Identical in functionality to the non-const version of find, 
    * save the fact that what's pointed to by the returned iterator
    * is deemed as const and immutable.
    *
    * @param elem the client element we are trying to match.
    * @return an iterator to the matching element, or whatever the
    *         const end() returns if no such match was ever found.
    */
    const_iterator find(const T& elem) const;
      
    /**
    * Operation which inserts the specified element
    * into the btree if a matching element isn't already
    * present.  In the event where the element truly needs
    * to be inserted, the size of the btree is effectively
    * increases by one, and the pair that gets returned contains
    * an iterator to the inserted element and true in its first and
    * second fields.  
    *
    * If a matching element already exists in the btree, nothing
    * is added at all, and the size of the btree stays the same.  The 
    * returned pair still returns an iterator to the matching element, but
    * the second field of the returned pair will store false.  This
    * second value can be checked to after an insertion to decide whether
    * or not the btree got bigger.
    *
    * The insert method makes use of T's zero-arg constructor and 
    * operator= method, and if these things aren't available, 
    * then the call to btree<T>::insert will not compile.  The implementation
    * also makes use of the class's operator== and operator< as well.
    *
    * @param elem the element to be inserted.
    * @return a pair whose first field is an iterator positioned at
    *         the matching element in the btree, and whose second field 
    *         stores true if and only if the element needed to be added 
    *         because no matching element was there prior to the insert call.
    */
    std::pair<iterator, bool> insert(const T& elem);

    /**
    * Disposes of all internal resources, which includes
    * the disposal of any client objects previously
    * inserted using the insert operation. 
    * Check that your implementation does not leak memory!
    */
    ~btree();


private:
    // The details of your implementation go here
    class Node{
    public:
        //constructor
//        Node(size_t max = 40):values{std::vector<T>(max)},
//                                     children{std::vector<Node*>(max+1, nullptr)}{}
        Node(){}
        //destructor
        //delete all the element of children
        ~Node() {
            for(auto it = children.begin();it != children.end();++it){
                delete it->second;
            }
            children.clear();
            values.clear();
        }
        //copy constructor 
        Node(const Node& no) {
            values = no.values;
            level = no.level;
            parent = no.parent;
            paIndex = no.paIndex;
            children.clear();
            for(auto i = no.children.begin();i != no.children.end();++i){
                children[i->first] = new Node(*i->second);
            }
        }

        //copy the assignment
        Node& operator=(const Node &no) {
            if(this == &no) return *this;
            values = no.values;
            level = no.level;
            parent = no.parent;
            paIndex = no.paIndex;
            children.clear();
            for(auto i = no.children.begin();i != no.children.end();++i) {
                children[i->first] = new Node(*(i->second));
            }
            return *this;
        }


        int insertEle(const T& elem){
            auto itr = std::lower_bound(values.begin(),values.end(),elem);
            values.insert(itr,elem);

            return itr - values.begin();
        }

        int getLevelNum(){
            return level;
        }

        void setLevelNum(int le){
            level = le;
        }

        Node* getParent(){
            return parent;
        }
        void setParent(Node *pa){
            parent = pa;
        }

        int getPaIndex(){
            return paIndex;
        }

        void setPaIndex(int index){
            paIndex = index;
        }
        // std::vector<T> getValues(){
        //     return values;
        // }

        int getElePos(const T& elem){
            int pos = -1;
//            if(values.empty()) return -1;
            auto itr = std::find(values.begin(), values.end(),elem); //using find algorithm
            if(itr != values.end()) {   //if found
                pos = itr - values.begin();  //getting position as an int
            }
            return pos;
        }

        int getChildPos(const T& elem) {
//            if(children.empty()) return -1;
            auto it = std::lower_bound(values.begin(),values.end(),elem); //finding child position
            return (it - values.begin());
        }

        std::map<int,Node*> getChildren(){
            return children;
        }

        void addChild(int pos, Node* ch){
            children[pos] = ch;
        }

        bool checkChildAt(int index){
            if(children.find(index) != children.end()) { //if the iterator isnt the end of the map
                return true;                          //child found at the given position
            }
            return false;
        }

        Node* getChild(int index){
            return children.at(index);
        }
        int getValuesSize(){
            return values.size();
        }


        std::vector<T> values;// the values of the node
        std::map<int,Node*> children;//list of children
        Node *parent;//parent node
        int level;//the level of current node
        int paIndex;
        size_t nodeSize;
    private:
    };

    Node *root;
    size_t nodeSize;

};


/**
* The template implementation needs to be visible to whatever
* translation unit makes use of templatized btree methods.
* The unconventional practice is to #include the implementation
* file just before the end of the interface (sort of like
* sneaking it in and hoping it isn't noticed).  Because the
* .tem file is included here, the .h file is NOT #included in 
* the .tem file.  We'd otherwise have circular inclusions
* and the compiler would be peeved.
*/

//#include "btree.tem"

// your btree implementation goes here
template <typename T>
btree<T>::btree(size_t maxNodeElems){
    nodeSize = maxNodeElems;
    root = new Node();
    root->setParent(nullptr);
}

//copy constructor
template <typename T>
btree<T>::btree(const btree<T>& original){
    root = new Node(*original.root);
    nodeSize = original.nodeSize;
}

//move constructor
template <typename T>
btree<T>::btree(btree<T>&& original) {
    root = original.root;
    nodeSize = original.nodeSize;
    original = nullptr;
}

//destructor
template <typename T>
btree<T>::~btree() {
    delete root;
}

//copy assignment
template <typename T>
btree<T>& btree<T>::operator=(const btree<T>& rhs) {
    if(this == &rhs) return *this;
    //std::cout << rhs.root->getValues().at(0) << " copy here " << std::endl;
    nodeSize = rhs.nodeSize;
    delete root;
    root = new Node(*rhs.root);
    return *this;
}

//move assignment
template <typename T>
btree<T>& btree<T>::operator=(btree<T>&& rhs) {
    if(this == &rhs) return *this;
    nodeSize = rhs.nodeSize;
    root = rhs.root;
    rhs.nodeSize = 0;
    rhs.root = nullptr;
    return *this;
}

template <typename T>
btree_iterator<T> btree<T>::begin() const {
    Node *no = root;
    
    // if(!no->checkChildAt(0)) {
    // //std::cout<<"start ite check node size"<<no->getValuesSize()<<std::endl;
    // //std::cout<<"end ite check node size"<<no->getChild(1)->getValuesSize()<<std::endl;
    //     std::cout<<"first ele    "<<no->getValues().at(0)<<std::endl;
    //     return btree_iterator<T>(no,0);
    // }
    // using namespace std;
    // cout << "LOL" << no->values.at(0) << endl;
    while(no->checkChildAt(0)){
        no = no->getChild(0);
    }
    //std::cout<<"first ele    "<<no->getValues().at(0)<<std::endl;
    return btree_iterator<T>(no,0);
}

template <typename T>
btree_iterator<T> btree<T>::end() const {
    Node *no = root;
    if(!no->checkChildAt(no->getValuesSize())) {
        return btree_iterator<T>(root,root->values.size()+1);
    }
    while(no->checkChildAt(no->getValuesSize())){
        no = no->getChild(no->getValuesSize());
    }
    // std::cout<<"end ite check node size"<<no->values.at(0)<<std::endl;
    return btree_iterator<T>(root,root->values.size()+1);
}

template <typename T>
typename btree<T>::reverse_iterator btree<T>::rbegin() {
    return reverse_iterator(end());
}

template <typename T>
typename btree<T>::reverse_iterator btree<T>::rend() {
    return reverse_iterator(begin());
}

template <typename T>
const_btree_iterator<T> btree<T>::cbegin() const {
    Node* no = root;
    while(no->checkChildAt(0)){
        no = no->getChild(0);
    }
    return const_btree_iterator<T>(no,0);
}

template <typename T>
const_btree_iterator<T> btree<T>::cend() const {
    Node* no = root;
    if(!no->checkChildAt(no->getValuesSize())) {
        return const_btree_iterator<T>(no, no->getValuesSize());
    }
    while(no->checkChildAt(no->getValuesSize())){
        no = no->getChild(no->getValuesSize());
    }
    return const_btree_iterator<T>(no,no->getValuesSize());
}


template <typename T>
typename btree<T>::const_reverse_iterator btree<T>::crbegin() const {
    return const_reverse_iterator(cend());
}

template <typename T>
typename btree<T>::const_reverse_iterator btree<T>::crend() const {
    return const_reverse_iterator(cbegin());
}


template <typename T>
btree_iterator<T> btree<T>::find(const T& elem){
    if(root == nullptr) return end();
    else{
        Node* no = root;
        int result = -1;
        result = no->getElePos(elem);
        if(result != -1){ // find the
            return btree_iterator<T>(no,result);
        }else if(no->getChildren().empty()){

            return this->end();
        }else{
            int nod = no->getChildPos(elem);
            while(no->checkChildAt(nod)){
                no = no->getChild(nod);
                result = no->getElePos(elem);
                if(result != -1){
                    return btree_iterator<T>(no,result);
                }else{
                    nod = no->getChildPos(elem);
                }
            }
            return end();
        }
    }
}


template <typename T>
const_btree_iterator<T> btree<T>::find(const T& elem) const {
    if(root == nullptr) return cend();
    else{
        Node* no = root;
        int result = -1;
        result = no->getElePos(elem);

        if(result != -1){ // find the
            return const_btree_iterator<T>(no,result);
        }else if(no->getChildren().empty()){

            return this->cend();
        }else{
            int nod = no->getChildPos(elem);
            while(no->checkChildAt(nod)){
                no = no->getChild(nod);
                result = no->getElePos(elem);
                if(result != -1){
                    return const_btree_iterator<T>(no,result);
                }else{
                    nod = no->getChildPos(elem);
                }
            }
            return cend();
        }
    }
}

template <typename T>
std::pair<btree_iterator<T> , bool> btree<T>::insert(const T& elem) {
//    std::cout<<"into insert! "<<std::endl;
    iterator result = find(elem);
    if(result != end()){
        return std::make_pair(result,false);
    }
        Node *curr = root;
        if(!curr->getChildren().empty()){
//            std::cout<<"hss children"<<std::endl;
            int posi = curr->getChildPos(elem);
            while(curr->checkChildAt(posi)){
                curr = curr->getChild(posi);
                posi = curr->getChildPos(elem);
            }
        }
        if(curr->values.size() != nodeSize){//not full of the node
           // std::cout<<"check Node size"<<nodeSize<<std::endl;
            int inPos = curr->insertEle(elem);
            //------------------------
           // std::cout<<"check value size and nodesize 0 "<<curr->getValues().at(0)<<std::endl;
           // if(curr->getValuesSize() > 1){
            //    std::cout<<"check value size and nodesize 1 "<<curr->getValues().at(1)<<std::endl;
            //}
            //if(curr->getParent() != nullptr) std::cout<<"check parent "<<curr->getParent()->getValues()[0]<<std::endl;
            //-----------------------
            result = btree_iterator<T>(curr,inPos);
            return std::make_pair(result,true);
        }else{//full
            int chPos = curr->getChildPos(elem);
            Node *ch = new Node();
            ch->insertEle(elem);
            ch->setParent(curr);
            ch->setPaIndex(chPos);
            ch->setLevelNum(curr->getLevelNum()+1);
            curr->addChild(chPos,ch);
 //           std::cout << "parent " << ch->getParent()->getValues()[0] << " element: " << elem << std::endl;
//            std::cout << "childPos in children 0: " << curr->getRightChild(0)->getValues()[0] << " element: " << elem << std::endl;
            result = btree_iterator<T>(ch,chPos);

            return std::make_pair(result,true);
        }

}


#endif
