#include "../../includes/token/child_tokens.h"
//--------------------------TOKENSTR---------------------------
TokenStr::TokenStr(string str) : Token(str){
    type = TOKEN_STR;
}

TOKEN_TYPE TokenStr::get_type() const {
    return type;
}

LParen::LParen() : Token("("){
    type = L_PAREN;
}

TOKEN_TYPE LParen::get_type() const {
    return type;
}

RParen::RParen() : Token(")"){
    type = R_PAREN;
}

TOKEN_TYPE RParen::get_type() const {
    return type;
}

//--------------------------RESULTSET---------------------------
ResultSet::ResultSet() : Token(""){
    type = SET;
}

ResultSet::ResultSet(vectorlong recnos) : Token(""){
    type = SET;
    _recnos = recnos;
}

TOKEN_TYPE ResultSet::get_type() const{
    return type;
}

vectorlong ResultSet::recnos(){
    return _recnos;
}

//--------------------------OPERATOR---------------------------
Operator::Operator(string str){
    _op = str;
    Token(str, 4);
}

//--------------------------RELATIONAL---------------------------
Relational::Relational(string str) : Token(str){
    type = RELATIONAL;
}

vectorlong Relational::eval(Map<string, mmap_sl>& index, Token* left, Token* right){
    vectorlong results;
    mmap_sl::Iterator first;
    mmap_sl::Iterator second;
    string temp = left->token_str();
    string temp2 = right->token_str();
    
    if (token_str() == "="){
        results = index.at(left->token_str())[right->token_str()];
    }
    else if (token_str() == ">"){
        first = index[temp].upper_bound(temp2);
                second = index[temp].end();
    }
    else if (token_str() == "<"){
        first = index[temp].begin();
        second = index[temp].lower_bound(temp2);
    }
    else if (token_str() == "<="){
        first = index[temp].begin();
        second = index[temp].upper_bound(temp2);
    }
    else if (token_str() == ">="){
        first = index[temp].lower_bound(temp2);
        second = index[temp].end();
    }
    for (; first != second; first++){
                MPair<string, long> temp3 = *first;
                for (int i = 0; i < temp3.value_list.size(); i++){
                    results.push_back(temp3.value_list[i]);
                }
    }

    return results; 
}

TOKEN_TYPE Relational::get_type() const{
    return type;
}

//--------------------------LOGICAL---------------------------
Logical::Logical(string str) : Token(str){
    if (str == "or"){
        type = LOGIC_OR;
    }
    else{
        type = LOGIC_AND;
    }
}   

TOKEN_TYPE Logical::get_type() const{
    return type;
}

vectorlong Logical::eval(vectorlong left, vectorlong right){
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());
    vectorlong results;
    
    if (type == LOGIC_AND){
        set_intersection(left.begin(), left.end(), right.begin(),
             right.end(), back_inserter(results));
    }
    else if(type == LOGIC_OR){
        set_union(left.begin(), left.end(), right.begin(),
             right.end(), back_inserter(results));
    }
    return results;
}
