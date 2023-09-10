#include "parser.h"

Parser::Parser(){  
    build_keyword_list();
    make_table();
}

Parser::Parser(string str){  
    build_keyword_list();
    make_table();
    set_string(str);
}

void Parser::set_string(string str){
    //fill up queue of tokens until string is done
    stk.set_string(str);    
    Token t;
    stk>>t;
    while(stk.more()){
        //ignore spaces and commas
        if (t.type_string() != "SPACE" && t.token_str() != ","){
            input_q.push(t);
        }
        t = Token();
        stk>>t;
    }
    //runs off of old stokenize loop^ then build parse tree
    fail_flag = get_parse_tree();
}

string Parser::get_column(Token t){
    if(keywords.contains(t.token_str())){
        return t.token_str();
    }
    else 
        return "sym";
    //returns sym in cases of something that isnt recognized
}

bool Parser::get_parse_tree(){
    //clear ptree incase theres already values within it
    ptree.clear();
    Token t;
    int col_num;
    int state = 0;
    string hold;
    //read tokens from queue until empty
    while (!input_q.empty()){
        t = input_q.pop();
        if (t.token_str() == "\""){
            t = input_q.pop();
            //builds tokens of words in quotations
            while (t.token_str() != "\""){
                hold += t.token_str();
                hold += " ";
                t = input_q.pop();
            }
            hold.pop_back();
            t=Token(hold, 2);
            hold.clear();
    
        }
        //find colnum for this keyword
        col_num = keywords[get_column(t)];
        //find current state from last state and colnum
        state = a_table[state][col_num];
        //switch state to fill up ptree
        switch(state){
            case 1:
            case 11:
            case 21:
                ptree["command"] +=  t.token_str();break;
            case 2:
                ptree["fields"] += t.token_str();break;
            case 4:
            case 13:
            case 23:
                ptree["table_name"] += t.token_str();break;
            case 5:{
                string temp = "yes";
                ptree["where"] += temp;break;}
            case 6:
            case 7:
            case 8:
            case 9:
                ptree["condition"] += t.token_str();break;
            case 15:
                ptree["col"] += t.token_str();break;
            case 25:
                ptree["values"] += t.token_str();break;
        }
        if (state == -1){
            return false;
        }

    }
    return true;
}

void Parser::build_keyword_list(){
    keywords["select"] = 1;
    keywords["*"] = 2;
    keywords["star"] = 2;
    keywords["from"] = 3;
    keywords["where"] = 4;
    keywords["were"] = 4;
    keywords["or"] = 5;
    keywords["and"] = 6;
    keywords["OR"] = 5;
    keywords["AND"] = 6;

    keywords["make"] = 10;
    keywords["table"] = 11;
    keywords["fields"] = 12;

    keywords["insert"] = 20;
    keywords["into"] = 21;
    keywords["values"] = 22;

    keywords["sym"] = 50;

    keywords["<"] = 51;
    keywords[">"] = 52; 
    keywords["="] = 53;
    keywords["<="] = 54; 
    keywords[">="] = 55;    
}

void Parser::make_table(){
    init_table(a_table);
    
    //Select state markings
    mark_fail(a_table, 0);
    mark_fail(a_table, 1);
    mark_fail(a_table, 2);
    mark_fail(a_table, 3);
    mark_success(a_table, 4);
    mark_fail(a_table, 5);
    mark_fail(a_table, 6);
    mark_fail(a_table, 7);
    mark_success(a_table, 8);
    mark_fail(a_table, 9);

    mark_cell(0, a_table, keywords["select"], 1);   //state [0] --- 'SELECT' ---> [1]
    mark_cell(1, a_table, keywords["*"], 2);        //state [1] --- 'STAR'   ---> [2]
    mark_cell(1, a_table, keywords["sym"], 2);      //state [1] --- 'SYM'    ---> [2]
    mark_cell(2, a_table, keywords["sym"], 2);      //state [2] --- 'SYM'    ---> [2]
    mark_cell(2, a_table, keywords["from"], 3);     //state [2] --- 'FROM'   ---> [3]
    mark_cell(3, a_table, keywords["sym"], 4);      //state [3] --- 'SYM'    ---> [4]
    mark_cell(4, a_table, keywords["where"], 5);    //state [4] --- 'WHERE'  ---> [5]
    mark_cell(4, a_table, keywords["were"], 5);    //state [4] --- 'WHERE'  ---> [5]
    mark_cell(5, a_table, keywords["sym"], 6);      //state [5] --- 'SYM'    ---> [6]
    mark_cell(6, a_table, keywords["sym"], 6);      //state [6] --- 'SYM'    ---> [6]    
    mark_cell(6, a_table, keywords["<"], 7);        //state [6] --- '<'      ---> [7]
    mark_cell(6, a_table, keywords[">"], 7);        //state [6] --- '>'      ---> [7]
    mark_cell(6, a_table, keywords["="], 7);        //state [6] --- '='      ---> [7]
    mark_cell(6, a_table, keywords["<="], 7);       //state [6] --- '<='     ---> [7]
    mark_cell(6, a_table, keywords[">="], 7);       //state [6] --- '>='     ---> [7]
    mark_cell(7, a_table, keywords["sym"], 8);      //state [7] --- 'SYM'    ---> [8]
    mark_cell(8, a_table, keywords["sym"], 8);      //state [8] --- 'SYM'    ---> [8]
    mark_cell(8, a_table, keywords["and"], 9);      //state [8] --- 'AND'    ---> [5]
    mark_cell(8, a_table, keywords["or"], 9);       //state [8] --- 'OR'     ---> [5]
    mark_cell(8, a_table, keywords["AND"], 9);      //state [8] --- 'AND'    ---> [5]
    mark_cell(8, a_table, keywords["OR"], 9);       //state [8] --- 'OR'     ---> [5]
    mark_cell(9, a_table, keywords["sym"], 6);      //state [9] --- 'SYM'    ---> [6]


    //Make state markings
    mark_fail(a_table, 11);
    mark_fail(a_table, 12);
    mark_fail(a_table, 13);
    mark_success(a_table, 14);

    mark_cell(0, a_table, keywords["make"], 11);    //state [0] --- 'MAKE'    ---> [11]
    mark_cell(11, a_table, keywords["table"], 12);  //state [11] --- 'TABLE'  ---> [12]
    mark_cell(12, a_table, keywords["sym"], 13);    //state [12] --- 'SYM'    ---> [13]
    mark_cell(13, a_table, keywords["fields"], 14); //state [13] --- 'FIELDS' ---> [14]
    mark_cell(14, a_table, keywords["sym"], 15);    //state [14] --- 'SYM'    ---> [15]
    mark_cell(15, a_table, keywords["sym"], 15);    //state [15] --- 'SYM'    ---> [15]

    //Insert state markings
    mark_fail(a_table, 21);
    mark_fail(a_table, 22);
    mark_fail(a_table, 23);
    mark_success(a_table, 24);

    mark_cell(0, a_table, keywords["insert"], 21);   //state [0] --- 'INSERT'  ---> [21]
    mark_cell(21, a_table, keywords["into"], 22);    //state [21] --- 'INTO'   ---> [22]
    mark_cell(22, a_table, keywords["sym"], 23);     //state [22] --- 'SYM'    ---> [23]
    mark_cell(23, a_table, keywords["values"], 24);  //state [23] --- 'VALUES' ---> [24]
    mark_cell(24, a_table, keywords["sym"], 25);     //state [24] --- 'SYM'    ---> [25]
    mark_cell(25, a_table, keywords["sym"], 25);     //state [25] --- 'SYM'    ---> [25]


}