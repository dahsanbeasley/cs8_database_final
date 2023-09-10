#ifndef MYSTACK_H
#define MYSTACK_H

#include "../../includes/linked_list_functions/linkedlistfunctionsTemplated.h"
#include "assert.h"

template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                 //give access to list to access _ptr
        Iterator(){_ptr = NULL;}            //default ctor
        Iterator(node<ITEM_TYPE>* p){_ptr = p;}      //Point Iterator to where
                                            //  p is pointing to
        ITEM_TYPE operator *(){             //dereference operator
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


        Iterator& operator++(){                        //member operator:++it
                                                       // or ++it = new_value
            _ptr=_ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it,
                                   int unused){        //friend operator: it++
            assert(it._ptr!=NULL);
            Iterator next;
            next = it;
            ++it;
            return next;
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<ITEM_TYPE>& copyMe);
    ~Stack();
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS);
    ITEM_TYPE top();
    bool empty();
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe){
        outs << "Stack:";
        _print_list(printMe._top);
        return outs;
    }
    Iterator begin() const;                   //Iterator to the head node
    Iterator end() const;                     //Iterator to NULL
    int size() const { return _size; }

private:
    node<ITEM_TYPE>* _top;
    int _size;
};

//-------- -------- -------- -------- -------- --------
template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(){
    _top = nullptr;
    _size = 0;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE>& copyMe){
    _top = _copy_list(copyMe._top);
    _size = copyMe._size;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::~Stack(){
    _clear_list(_top);
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>& Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE>& RHS){
    if (this != &RHS){
        _clear_list(_top);
        _top = _copy_list(RHS._top);
        _size = RHS._size;
    }
    return *this;
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::top(){
    assert(_top!=NULL);
    return _top->_item;
}

template <typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty(){
    return _top == nullptr; //check to see if head is null to verify
}

template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE item){
    _top = _insert_head(_top, item);
    _size++;
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop(){
    _size--;
    return _delete_node(_top, _top);
}

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::begin() const{                   
    return Iterator(_top);
}

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::end() const{
    ITEM_TYPE search;
    node<ITEM_TYPE>* temp = nullptr;
    search = _at(_top, size());
    temp = _search_list(_top, search);
    return Iterator(temp);
}

#endif  //MYQUEUE_H