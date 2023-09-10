#ifndef CHILD_TOKENS_H
#define CHILD_TOKENS_H

#include "../../includes/token/token.h"
#include "../../includes/bplustree/multimap.h"
#include <algorithm>
#include <vector>
#include <string>



class TokenStr : public Token
{
public:
    TokenStr(string str);
    TOKEN_TYPE get_type() const;
private:
    TOKEN_TYPE type;
};

class LParen : public Token
{ 
public:
    LParen();
    TOKEN_TYPE get_type() const;
private:
    TOKEN_TYPE type;
};

class RParen : public Token
{
public:
    RParen();
    TOKEN_TYPE get_type() const;
private:
    TOKEN_TYPE type;
};

class ResultSet : public Token
{
public:
    ResultSet();
    ResultSet(vectorlong recnos);
    TOKEN_TYPE get_type() const;
    vectorlong recnos();
private:
    vectorlong _recnos;
    TOKEN_TYPE type;
};

class Operator : public Token
{
public:
    Operator(string str);
private:
    string _op;
};

class Relational : public Token
{
public:
    Relational(string str);
    //should be a const index, need a const iterator type to do so 
    vectorlong eval(Map<string, mmap_sl>& index, Token* left, Token* right);
    TOKEN_TYPE get_type() const;
private:
    TOKEN_TYPE type;
};

class Logical : public Token
{
public:
    Logical(string str);
    TOKEN_TYPE get_type()const ;
    vectorlong eval(vectorlong left, vectorlong right);

private:
    TOKEN_TYPE type;
};

#endif