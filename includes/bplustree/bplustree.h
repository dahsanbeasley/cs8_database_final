#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include "../bplustree/btree_array_funcs.h"
#include <assert.h>

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):
                                                it(_it), key_ptr(_key_ptr){}

        T operator *(){
            //verify if it even exists, then return data at key_ptr
            if (it){
                return it->data[key_ptr];
            }
            return T();
        }

        Iterator operator++(int un_used){   //it++
            Iterator temp(it, key_ptr);
            key_ptr++;
            //iterate key_ptr, check if key_ptr is valid, if not reset key_ptr
            //  to 0, and make this iterator next if exists   
            if (key_ptr >= it->data_count){
                key_ptr = 0;
                if (it->next){
                    it = it->next;
                }
                else{
                    it = NULL;
                }
            }     
            return temp;
        }
        Iterator operator++(){  //++it
            key_ptr++;   
            if (key_ptr >= it->data_count){
                key_ptr = 0;
                if (it->next){
                    it = it->next;
                }
                else{
                    it = NULL;
                }
            }     
            return *this;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            //checks to see if both or one of the iterators is NULL, giving
            //  appropriate response for either
            if (!lhs.it && !rhs.it){
                return true;
            }
            if (!lhs.it || !rhs.it){
                return false;
            }
            //create copies of both lhs and rhs to access private info
            Iterator left(lhs.it, lhs.key_ptr);
            Iterator right(rhs.it, rhs.key_ptr);
            //retrieves data at key_ptr of both, and then sends comparison results
            return *left == *right;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            //exact same as above but flipped results
            if (!lhs.it && !rhs.it){
                return false;
            }
            if (!lhs.it || !rhs.it){
                return true;
            }
            Iterator left(lhs.it, lhs.key_ptr);
            Iterator right(rhs.it, rhs.key_ptr);
            return *left != *right;
        }
        void print_Iterator(){
            //didnt write, but really straight forward
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }
        bool is_null(){return !it;}
        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_leaf);  //copy other into this object
    //void copy_tree(const BPlusTree<T>& other, stack<BPlusTree<T>*>& s);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    Iterator find(const T& key);         //return an iterator to this key.
                                         //     NULL if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs,
                               const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string pre_order();
    string post_order();

    Iterator begin();
    Iterator end();
    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
    bool is_leaf() const
    {return child_count==0;}             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};

template <class T>
BPlusTree<T>::BPlusTree(bool dups){
    //need to set dc and cc to 0, otherwise other functs dont work
    dups_ok = dups;
    data_count = 0;
    child_count = 0;
    next = NULL;
}

template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups){
    //insert all elements of array using size and insert funct
    dups_ok = dups;
    data_count = 0;
    child_count = 0;
    next = NULL;
    for (int i = 0; i < size; i++){
        insert(a[i]);   //utilizes fact insert takes care of everything
    }
}

template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other){
    //creates tree copying off of another tree
    dups_ok = other.dups_ok;
    data_count = 0;
    child_count = 0;
    next = NULL;
    BPlusTree<T>* temp = nullptr;
    copy_tree(other, temp);
}

template <class T>
BPlusTree<T>::~BPlusTree(){
    clear_tree();
}

template <class T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS){
    BPlusTree<T>* temp = nullptr;
    clear_tree();
    copy_tree(RHS, temp);
    return *this;
}

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_leaf){
    dups_ok = other.dups_ok;
    data_count = other.data_count;
    for (int i = 0; i < data_count; i++){
        data[i] = other.data[i];
    }
    next = NULL;
    child_count = other.child_count;
    //if not leaf copy children, otherwise do last_leaf stuff
    if (!other.is_leaf()){
        child_count = other.child_count;
        for (int i = 0; i < child_count; i++){  //order matters
                subset[i] = new BPlusTree<T>;
                subset[i]->copy_tree(*other.subset[i], last_leaf);
        }
    }
    else{
        //if last_leaf isnt null, set up next using this
        //  set next last_leaf
        if (last_leaf){
            last_leaf->next = this;
        }
        last_leaf = this;
    }
}

template <class T>
void BPlusTree<T>::insert(const T& entry){
    //loose insert, then check self to see if excess
    loose_insert(entry);
    if (data_count == MAXIMUM+1){
        //create new node, copy self into child and empty self
        //  fix excess on new copy of self in child
        BPlusTree<T>* grow_ptr = new BPlusTree<T>;
        copy_array(grow_ptr->data, data, 
            grow_ptr->data_count, data_count);
        copy_array(grow_ptr->subset, subset, 
            grow_ptr->child_count, child_count);
    data_count = 0;
    subset[0] = grow_ptr;
    child_count = 1;
    fix_excess(0);     
    }
}
template <class T>
void BPlusTree<T>::remove(const T& entry){
    
}

template <class T>
void BPlusTree<T>::clear_tree(){
    for (int i = 0; i < child_count; i++){
        
        subset[i]->clear_tree();
        delete subset[i];
        subset[i] = nullptr;
    }
    child_count = 0;
    data_count = 0;
    next = NULL;
}

template <class T>
bool BPlusTree<T>::contains(const T& entry) const{
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if (found && is_leaf()){
        return true;
    }
    else if (!found && is_leaf()){
        return false;;
    }
    else if (found && !is_leaf()){
        return subset[i+1]->contains(entry);
    }
    else{
        return subset[i]->contains(entry);
    }
}

template <class T>
T& BPlusTree<T>::get(const T& entry){
    if (!contains(entry)) 
         insert(entry); 

     return get_existing(entry); 
}

template <class T>
const T& BPlusTree<T>::get(const T& entry)const{
    assert(contains(entry));
    return get_existing(entry);
}

template <class T>
T& BPlusTree<T>::get_existing(const T& entry){
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if (found && is_leaf()){
        return data[i];
    }
    else if (found && !is_leaf()){
        return subset[i+1]->get_existing(entry);
    }
    else{
        return subset[i]->get_existing(entry);
    }
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& key){
    int i = first_ge(data, data_count, key);
    bool found = (i<data_count && data[i] == key);
    if (found && is_leaf()){
        return Iterator(this, i);
    }
    else if (!found && is_leaf()){
        return Iterator();
    }
    else if (found && !is_leaf()){
        return subset[i+1]->find(key);
    }
    else{
        return subset[i]->find(key);
    }
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key){
    for (Iterator i = begin(); i != end(); i++){
        if (*i >= key){
            return i;
        }
    }
    return Iterator(next);
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key){
    for (Iterator i = begin(); i != end(); i++){
        if (*i > key){
            return i;
        }
    }
    return Iterator();
}

template <class T>
int BPlusTree<T>::size() const{
    int num = 0;
    if (empty()){
        return num;
    }
    for (int i = 0; i < child_count; i++){
        num+=subset[i]->size();
    }
    return data_count+num;
}

template <class T>
bool BPlusTree<T>::empty() const{
    return data_count == 0;
}

template <class T>
void BPlusTree<T>::print_tree(int level,
                    ostream &outs) const{
    if (data_count > 0){
        if (child_count > 0){
            subset[child_count-1]->print_tree(level+1);
        }
        outs << setw(4*level) << "" << "--\n"; 
        for (int i = data_count-1; i >= 0; i--){
            outs << setw(4*level) << "" << data[i] << endl;
            if (i == 0){
              outs << setw(4*level) << "" << "--\n";  
            }
            if(child_count > 0 && i <= child_count-1){
                subset[i]->print_tree(level+1);
            }
        }
    }
}

template <class T>
bool BPlusTree<T>::is_valid(){
    
}

template <class T>
string BPlusTree<T>::in_order(){
    string temp;
    if (data_count > 0){
        if (child_count > 0){
            temp += subset[0]->in_order();
        }
        for (int i = 0; i < data_count; i++){
            temp+= to_string(data[i]);
            temp += "|";
            if(child_count > 0 && i <= child_count-1){
                temp += subset[i+1]->in_order();
            }
        }
        return temp;
    }
    else{
        return "";
    }
}

template <class T>
string BPlusTree<T>::pre_order(){
    string temp;
    if (data_count > 0){
        for (int i = 0; i < data_count; i++){
            temp+= to_string(data[i]);
            temp += "|";
            if(child_count > 0 && i <= child_count-1){
                temp += subset[i]->pre_order();
            }
        }
        if(child_count > 0){
                temp += subset[child_count-1]->pre_order();
        }
        return temp;
    }
    else{
        return "";
    }
}

template <class T>
string BPlusTree<T>::post_order(){
    string temp;
    if (data_count > 0){
        if (child_count > 0){
            temp += subset[0]->post_order();
        }
        for (int i = 0; i < data_count; i++){
            if(child_count > 0 && i <= child_count-1){
                temp += subset[i+1]->post_order();
            }
            temp+= to_string(data[i]);
            temp += "|";
        }
        return temp;
    }
    else{
        return "";
    }
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin(){
    return Iterator(get_smallest_node(), 0);
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end(){
    return Iterator();
}

template <class T>
T* BPlusTree<T>::find_ptr(const T& entry){
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if (found && is_leaf()){
        return &data[i];
    }
    else if (!found && is_leaf()){
        return NULL;
    }
    else if (found && !is_leaf()){
        return subset[i+1]->contains(entry);
    }
    else{
        return subset[i]->contains(entry);
    }
}

template <class T>
void BPlusTree<T>::loose_insert(const T& entry){
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i] == entry);
    if (found && is_leaf()){
        data[i] = entry;
    }
    else if (!found && is_leaf()){
        insert_item(data, i, data_count, entry);
    }
    else if (found && !is_leaf()){
        subset[i+1]->loose_insert(entry);
        fix_excess(i);
    }
    else if (!found && !is_leaf()){
        subset[i]->loose_insert(entry);
        fix_excess(i);
    }
}

template <class T>
void BPlusTree<T>::fix_excess(int i){
    if (subset[i]->data_count ==  MAXIMUM+1){
        T temp;
        insert_item(subset, i+1, child_count, new BPlusTree<T>);
        split(subset[i]->data, subset[i]->data_count,
                subset[i+1]->data, subset[i+1]->data_count);
        split(subset[i]->subset, subset[i]->child_count,
                    subset[i+1]->subset, subset[i+1]->child_count);
        ordered_insert(data, data_count, 
            subset[i]->data[subset[i]->data_count-1]);
        detach_item(subset[i]->data, subset[i]->data_count, temp);
        //-------------------------------------------------------
        if (subset[i]->is_leaf()){
            insert_item(subset[i+1]->data, 0, subset[i+1]->data_count, data[i]);
            subset[i+1]->next = subset[i]->next;
            subset[i]->next = subset[i+1];
        }
    }
}

template <class T>
void BPlusTree<T>::loose_remove(const T& entry){
    
}

template <class T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i){
    return subset[0];
}

template <class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node(){
    if (is_leaf()){
        return this;
    }
    else{
        return subset[0]->get_smallest_node();
    }
}

template <class T>
void BPlusTree<T>::get_smallest(T& entry){
    if (is_leaf()){
        entry = data[0];
    }
    else{
        subset[0]->get_smallest(entry);
    } 
}

template <class T>
void BPlusTree<T>::get_biggest(T& entry){
    if (is_leaf()){
        if (data_count > 0)
            entry = data[data_count-1];
    }
    else{
        subset[child_count-1]->get_biggest(entry);
    }
}

template <class T>
void BPlusTree<T>::remove_biggest(T& entry){
    
}

template <class T>
void BPlusTree<T>::transfer_left(int i){
    
}

template <class T>
void BPlusTree<T>::transfer_right(int i){
    
}

template <class T>
BPlusTree<T> *BPlusTree<T>::merge_with_next_subset(int i){
    return *this;
}

#endif 