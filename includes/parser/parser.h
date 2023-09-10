#ifndef PARSER_H
#define PARSER_H

#include "../../includes/table/typedefs.h"
#include "../../includes/queue/MyQueue.h"
#include "../../includes/token/child_tokens.h"
#include "../../includes/tokenizer/stokenize.h"
#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"

class Parser
{
public:
    //ctors
    Parser();
    Parser(string str);                     //intiailizes parser and uses set string
    
    void set_string(string str);            //sets string to parsed
    bool fail(){return fail_flag;}          //i dont even think i use this 
    mmap_ss parse_tree(){return ptree;}     //returns the ptree in parser
    
private:
    mmap_ss ptree;                          //holds sql comamand and its fields
    map_sl keywords;                        //keywords for state machines
    int a_table[MAX_ROWS][MAX_COLUMNS];     //state machine to parse string
    STokenizer stk;                         //string tokenizer
    bool fail_flag;                         //is set during set string
    Queue<Token> input_q;                   //string converted into tokens

    string get_column(Token t);             //used during the parsing to communicate with keywords
    bool get_parse_tree();                  //returns ptree
    void build_keyword_list();              //builds keywords map to use with statemachine
    void make_table();                      //intializes state machine table
};

#endif