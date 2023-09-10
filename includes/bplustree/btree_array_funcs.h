#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

template <class T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <class T>
void swap(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme


// -----------------------------------------------------------------
template <class T>
T maximal(const T& a, const T& b){
    return max(a,b);
}

template <class T>
void swap(T& a, T& b){
    T& temp = a;
    a = b;
    b = temp;
}

template <class T>
int index_of_maximal(T data[ ], int n){
    T max = T();
    int maximal = n;
    for (int i = 0; i < n; i++){
        if (data[i] > max){
            max = data[i];
            i = maximal;
        }
    }
    return maximal;
}

template <class T>
void ordered_insert(T data[ ], int& n, T entry){
    int r = 0;
    for (int i = 0; i < n; i++){
        if (entry > data[i]){
            r++;
        }
    }
    for (int i = n; i > r; i--){
            data[i] = data[i-1];
        }
    data[r] = entry;
    n++;
}

template <class T>
int first_ge(const T data[ ], int n, const T& entry){
    for (int i = 0; i < n; i++){
        if (data[i] >= entry){
            return i;
        }
    }
    return n;
}

template <class T>
void attach_item(T data[ ], int& n, const T& entry){
    data[n] = entry;
    n++;
}

template <class T>
void insert_item(T data[ ], int i, int& n, T entry){
    for (int r = n; r > i; r--){
            data[r] = data[r-1];
    }
    data[i] = entry;
    n++;
}

template <class T>
void detach_item(T data[ ], int& n, T& entry){
    n--;
    entry = data[n];
}

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry){
    n--;
    entry = data[i];
    for (int r = i; r < n; r++){
        data[r] = data[r+1];
    }
}

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2){
     for (int i = 0; i < n2; i++){
         data1[i+n1] = data2[i];
     }
     n1+=n2;
     n2 = 0;
}

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2){
    int count = 0;
    T temp;
    for (int i = ((n1+1)/2); i < n1; i++){
        insert_item(data2, count, n2, data1[i]);
        delete_item(data1, i, n1, temp);
        n1++;
        count++;
    }
    n1-=count;
}

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size){
    for (int i = 0; i < src_size; i++){
        dest[i] = src[i];
    }
    dest_size = src_size;     
}

template <class T>
void print_array(const T data[], int n, int pos){
    for (int i = 0; i < n; i++){
        cout << "[" << data[i] << "] ";
    }
}

template <class T>
bool is_gt(const T data[], int n, const T& item){
    for (int i = 0; i < n; i++){
        if (item <= data[i]){
            return false;
        }
    }
    return true;
}

template <class T>
bool is_le(const T data[], int n, const T& item){
    for (int i = 0; i < n; i++){
        if (item > data[i]){
            return false;
        }
    }
    return true;
}
//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list){
    outs << "[";
    for (int i = 0; i < list.size(); i++){
        outs  << list[i] << " ";
    }
    outs << "]";
    return outs;
}

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme){
    list.push_back(addme);
    return list;
}
#endif