#ifndef LINKEDLISTFUNCTIONSTEMPLATED_H
#define LINKEDLISTFUNCTIONSTEMPLATED_H

#include "../node/node.h"
#include <iostream>
using namespace std;

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head,
                            T key);


template <typename T>
node<T>* _insert_head(node<T> *&head,
                            T insert_this);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head,
                                node<T> *after_this,
                                T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head,
                                node<T>* before_this,
                                T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

//-------- -------- -------- -------- -------- -------- -------- --------

template <typename T>
void _print_list(node<T>* head){
  //print through entire list using a walker node until null
  if (head != NULL){
    cout << "Head->";
    for (node<T>* walker = head;
         walker != NULL;
         walker=walker->_next){
             cout << *walker;     //outputs until end of nodes
         }
  }
    cout << "|||";   //outputs for last nullptr
}

template <typename T>
node<T>* _search_list(node<T>* head, T key){
  //walker to go through node passed in and find key
  node<T>* walker = head;
  //walker goes through all nodes until hits nullptr
  for (node<T>* walker = head;
       walker != NULL;
       walker = walker->_next){
         //checks every node until it finds key passed in
         if (walker->_item == key){
           return walker;
         }
       }
  return NULL;
}

template <typename T>
node<T>* _insert_head(node<T>* &head, T item){
  node<T>* temp = new node<T>(item, head);  //init new node with item
  if (head != NULL){    //can initialize nodes with item
    head->_prev = temp;
  }
  head = temp;
  return head;
}

template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this,
                                        T insert_this){
    //if nodes empty, insert item as head
    if (head == NULL){
      _insert_head(head, insert_this);
      return head;
    }
    node<T>* insert = new node<T>(insert_this);  //node to be insert
    insert->_prev = after_this;     
    node<T>* after = after_this->_next;  //need to prevent losing address
    after_this->_next = insert;
    if (after != NULL){    //if node has valid _next
      insert->_next = after;
      after->_prev = insert;
    }
    return insert;
}

template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this,
                                          T insert_this){
  //incase of empty head ptr
  if (head == NULL){
        _insert_head(head, insert_this);
        return head;
  }
  node<T>* insert = new node<T>(insert_this);  //node to be insert
  if (head == before_this){
    _insert_head(head, insert_this);
    return head;
  }
  insert->_next = before_this;
  node<T>* previ = before_this->_prev;   //need to prevent losing node address
  before_this->_prev = insert;
  if (previ != NULL){                    //if node has valid _prev
    insert->_prev = previ;
    previ->_next = insert;
  }
  return insert;                                      
}

template <typename T>
node<T>* _previous_node(node<T>* prev_to_this){
  //to prevent crash, return null if empty head
  if (prev_to_this == NULL){
    return NULL;
  }
  //simply return _prev of node pushed in
  return prev_to_this->_prev;
}

template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this){
  //if either is null, just delete nothing return nothing
  if (head == NULL || delete_this == NULL){
          return T();
  }
 //stores item in the node to be deleted
 T gone = delete_this->_item;
    //if head is deleted, just have to set next node to the new head
    if (head == delete_this){
          head = delete_this->_next;
    }
    //makes sure not to reach _prev into a null node
    if (delete_this->_next != NULL){
        delete_this->_next->_prev = delete_this->_prev;
    }
    //makes sure not ro reach _next into a null node
    if (delete_this->_prev != NULL){
        delete_this->_prev->_next = delete_this->_next;
    }
    
    free(delete_this); //deallocate memory of the node after list is stitched back together
    return gone;
}

template <typename T>
node<T>* _copy_list(node<T>* head){
  //deep copy creator
  node<T>* copyHead = nullptr;
  //if empty list gives null
  if(head == NULL){
    return NULL;
  }
  //intialize copy, and set temp to the head for the for loop
  _insert_head(copyHead, head->_item);
  node<T>* temp = copyHead;

  for (node<T>* walker = head->_next;
      walker != NULL;
      walker=walker->_next){
        //constantly insert after to deep copy list
        _insert_after(copyHead, temp, walker->_item);
        temp=temp->_next;   //need to make sure temp is also iterating forward
      }
  
  //return deep copy of list
  return copyHead;
}

template <typename T>
node<T>* _copy_list(node<T> *&dest, node<T>* src){
  //if empty list gives null
  if(src == NULL){
    return NULL;
  }
  if (dest != NULL){
    _clear_list(dest);
    dest = NULL;
  }
  //intialize copy, and set temp to the head for the for loop
  _insert_head(dest, src->_item);
  node<T>* temp = dest;
  for (node<T>* walker = src->_next;
      walker != NULL;
      walker=walker->_next){
        //constantly insert after to deep copy list
        _insert_after(dest, temp, walker->_item);
        temp=temp->_next;   //need to make sure temp is also iterating forward
      }
      temp->_next = NULL;
  //return ptr to end of list
  return temp;
}

template <typename T>
void _clear_list(node<T>*& head){
  //delete head through entire list until NULL
  while(head != NULL){
       _delete_node(head, head);  //simply delete head and repeat
  }   
}

template <typename T>
T& _at(node<T>* head, int pos){
  //using for loop with i = pos instead of node walker
  //cycles through list until reaches position of node = to pos
  node<T>* temp = head;
  for (int i = 1; i < pos; i++){
    if (temp->_next != NULL){
      temp=temp->_next;   //if next isnt null, cycles to next node
    }
  }
  return temp->_item;     //return item of node requested
}

#endif  //LINKEDLISTFUNCTIONSTEMPLATED_H