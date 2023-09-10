#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

#include "../../includes/table/typedefs.h"
#include "../../includes/bplustree/map.h"
#include "../../includes/token/child_tokens.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/binary_files/file_record.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/rpn/rpn.h"

using namespace std;

class Table{
public:
    //ctors
    Table();
    Table(const string name);               //constructor using already existing file
    Table(const string name, vectorstr s);  //constructor creating an new empty binary file

    //modifiers
    void insert_into(vectorstr s);          //writes s into binary file and into index

    //accessors
    Table select_all();                     //creates select table with all fields and records
    Table select_all(vectorstr fields);     //creates select table with specified fields and all records
    Table select(vectorstr fields,          // "poor man's select"
        const char f_cond[],const char s_cond[], const char t_cond[]);
    Table select(vectorstr fields, Queue<Token*> cond);     //select functioning with post fix of tokens
    Table select(vectorstr fields, vectorstr cond);         //select works with vector of strings, sends to ^
    vectorlong select_recnos();             //returns select_recs, numbers from last select_recs
    

    friend ostream& operator<<(ostream& outs, const Table& print_me);
private:
    string filename;                //name of the table and its file
    vectorstr field_names;          //names of all fields in table
    int table_num;                  //number of elements in index
    map_sl names;                   //map holding field_names and order 
    FileRecord records;             //record object to communicate with binary files
    Map<string, mmap_sl> index;     //temporary location tables hold records
    bool empty;                     //(not sure if even need yet honestly)
    long last_recno;                //last recno inserted
    vectorlong select_recs;         //holds longs of #s copied from last select
    //--------------------------------------------------------------------
    void set_fields(vectorstr s);   //sets field_names vectorstr and index
    vectorstr get_fields();         //returns field_names
};

#endif