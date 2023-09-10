#ifndef MULTIMAP_H
#define MULTIMAP_H

#include "../../includes/bplustree/bplustree.h"

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K()){
        key = k;
    }
    MPair(const K& k, const V& v){
        key = k;
        value_list.push_back(v);
    }
    MPair(const K& k, const vector<V>& vlist){
        key = k;
        value_list = vlist;
    }
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me){
        outs << setw(10) << print_me.key << " :" << setw(4) << "";
        for (int i = 0; i < print_me.value_list.size(); i++){
            outs << print_me.value_list[i] << " ";
        }
        return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key == rhs.key;
    }
    friend bool operator !=(const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key != rhs.key;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key < rhs.key;
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key <= rhs.key;
    }
    friend bool operator >= (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key >= rhs.key;
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        return lhs.key > rhs.key;
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs){
        assert(lhs.key == rhs.key);
        vector<V> temp = lhs;
        for (int i = 0; i < rhs.size(); i++){
            temp.push_back(rhs[i]);
        }
        return MPair<K,V>(lhs.key, temp);
    }
};
 

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(){
            _it = typename map_base::Iterator();
        }
        Iterator(typename map_base::Iterator it){
            _it = it;
        }
        Iterator operator ++(int unused){
            return _it++;
        }
        Iterator operator ++(){
            return ++_it;
        }
        MPair<K, V> operator *(){
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return lhs._it != rhs._it;
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

//  Iterators
    Iterator begin();
    Iterator end();

    Iterator lower_bound(const K& key);  
    Iterator upper_bound(const K& key);  

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);
    vector<V>& at(const K& key);

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const ;
    vector<V> &get(const K& key);
    

    Iterator find(const K& key);
    int count(const K& key);
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    equal_range:

    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

    void print_lookup();
private:
    BPlusTree<MPair<K, V> > mmap;
};

//-----------------------------------------------
template <typename K, typename V>
MMap<K,V>::MMap(){

}

//  Iterators
template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::begin(){
    return Iterator(mmap.begin());
}

template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::end(){
    return Iterator(mmap.end());
}

template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::lower_bound(const K& key){
    MPair<K,V> temp(key);
    return mmap.lower_bound(temp);
}  

template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::upper_bound(const K& key){
    MPair<K,V> temp(key);
    return mmap.upper_bound(temp);
}  

//  Capacity
template <typename K, typename V>
int MMap<K,V>::size() const{
    return mmap.size();
}

template <typename K, typename V>
bool MMap<K,V>::empty() const{
    return mmap.empty();
}

//  Element Access
template <typename K, typename V>
const vector<V>& MMap<K,V>::operator[](const K& key) const{
    MPair<K,V> temp(key);
    return mmap.get(temp).value_list;
}

template <typename K, typename V>
vector<V>& MMap<K,V>::operator[](const K& key){
    MPair<K,V> temp(key);
    return mmap.get(temp).value_list;
}

template <typename K, typename V>
vector<V>& MMap<K,V>::at(const K& key){
    MPair<K,V> temp(key);
    return mmap.get(temp).value_list;
}

//  Modifiers
template <typename K, typename V>
void MMap<K,V>::insert(const K& k, const V& v){
    MPair<K,V> temp(k,v);
    mmap.insert(temp);
}

template <typename K, typename V>
void MMap<K,V>::erase(const K& key){
    
}

template <typename K, typename V>
void MMap<K,V>::clear(){
    mmap.clear_tree();
}

//  Operations:
template <typename K, typename V>
bool MMap<K,V>::contains(const K& key) const{
    MPair<K,V> temp(key);
    return mmap.contains(temp);
}

template <typename K, typename V>
vector<V> &MMap<K,V>::get(const K& key){
    MPair<K,V> temp = mmap.get(key);
    return temp.value_list;
}

template <typename K, typename V>
typename MMap<K,V>::Iterator MMap<K,V>::find(const K& key){
    MPair<K,V> temp(key);
    return Iterator(mmap.find(temp));
}

template <typename K, typename V>
int MMap<K,V>::count(const K& key){
    return 1;
}

template <typename K, typename V>
bool MMap<K,V>::is_valid(){
    return mmap.is_valid();
}

template <typename K, typename V>
void MMap<K,V>::print_lookup(){
    Iterator i = begin(); 
    for (; i != end(); i++){
        cout << *i << endl;
    }
    cout << endl;
}

#endif