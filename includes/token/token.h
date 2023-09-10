#ifndef TOKEN_H
#define TOKEN_H

#include "../../includes/tokenizer/constants.h"
#include "../../includes/table/typedefs.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

enum TOKEN_TYPE{
    UNKNOWN,
    SET,
    TOKEN_STR,
    LOGIC_OR,
    LOGIC_AND,
    RELATIONAL,
    L_PAREN,
    R_PAREN,
};

class Token
{
public:
    //ctor
    Token();
    //ctor with inputs
    Token(string str); 
    Token(string str, int type);

    friend ostream& operator <<(ostream& outs, const Token& t);
    int type() const;   //returns _type of token
    string type_string() const; //returns string of type of the token
    string token_str() const;   //returns string in _token
    //----------NEW STUFF----------
    virtual TOKEN_TYPE get_type() const;
    virtual vectorlong recnos();
    virtual vectorlong eval(vectorlong left, vectorlong right);
    virtual vectorlong eval(Map<string, mmap_sl>& index, Token* left, Token* right);
    
private:
    string _token;
    int _type;
};

#endif