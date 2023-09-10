#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "../../includes/linked_list_functions/linkedlistfunctionsTemplated.h"
#include "assert.h"

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                               //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                          //default ctor
        Iterator(node<T>* p){_ptr = p;}                            //Point Iterator to where
                                                          //  p is pointing to
        T operator *(){     //dereference operator
            assert(_ptr);
            return _ptr->_item;
        }    
        bool is_null(){return _ptr == NULL;}            //true if _ptr is NULL
        friend bool operator !=(const Iterator& left,
                                const Iterator& right)  //true if left != right
        {return left._ptr != right._ptr;}

        friend bool operator ==(const Iterator& left,
                                const Iterator& right)  //true if left == right
        {return left._ptr == right._ptr;}


        Iterator& operator++(){                         //member operator:++it
                                                        // or ++it = new_value
            _ptr=_ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it,
                                   int unused){         //friend operator: it++
            assert(it._ptr!=NULL);
            Iterator next;
            next = it;
            ++it;
            return next;
        }

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;                                     //Iterator to the head node
    Iterator end() const;                                       //Iterator to NULL
    void print_pointers();
    int size() const { return _size;}
    // template<typename TT>
    // friend ostream& operator << (ostream& outs, const Queue<TT>& printMe){
    //     outs << "Queue:";
    //     _print_list(printMe._front);
    //     outs << endl;
    //     return outs;
    // }
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

//-------- -------- -------- -------- -------- --------
template<typename T>
Queue<T>::Queue(){
    _front = nullptr;       //initialize all ptrs to null
    _rear = nullptr;
    _size = 0;
}

template<typename T>
Queue<T>::Queue(const Queue<T>& copyMe){
    _front = nullptr;
    _rear = _copy_list(_front, copyMe._front);    //unlike stack, uses other copy_list
    _size = copyMe._size;                         //sets both front and rear within copy_list
}

template<typename T>
Queue<T>::~Queue(){
    _clear_list(_front);                          //deletes all nodes using clear queue
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
    if(this != &RHS){
        _clear_list(_front);
        _rear = _copy_list(_front, RHS._front);  //use rear item and search list to find
        _size = RHS._size;                       //copy of rear and properly set it
    }
    return *this;
}

template<typename T>
bool Queue<T>::empty(){
    return _front == nullptr;   //if head is empty nothing after so queue empty
}

template<typename T>
T Queue<T>::front(){
    return _front->_item;   //returns item within front of queue
}

template<typename T>
T Queue<T>::back(){
    return _rear->_item;    //returns item within end of queue
}

template<typename T>
void Queue<T>::push(T item){
    _rear = _insert_after(_front, _rear, item);     //uses insert after due to nature of queue
    _size++;      //adjust size as new item added to the queue
}

template<typename T>
T Queue<T>::pop(){
    _size--;    //adjust size as item removed from queue
    return _delete_node(_front, _front);    //delete node from front because queue, 
}

template<typename T>
typename Queue<T>::Iterator Queue<T>::begin() const{
    return Iterator(_front);    //returns iterator made on front of queue
}

template<typename T>
typename Queue<T>::Iterator Queue<T>::end() const{           
    return Iterator(_rear->_next);  //returns iterator of next of rear of queue
}

template<typename T>
void Queue<T>::print_pointers(){
    _print_list(_front);
}

#endif  //MYQUEUE_H