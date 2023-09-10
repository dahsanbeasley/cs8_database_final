#include "token.h"

Token::Token(){
    _token = "";
    _type = 0;
}


Token::Token(string str, int type){
    _token = str;
    _type = type;
}

ostream& operator <<(ostream& outs, const Token& t){
    cout << "|" << t._token << "|";
    return outs;
}

int Token::type() const{
    return _type;
}

string Token::type_string() const{
    if (_type == TOKEN_NUMBER){
        return "NUMBER";
    }
    if (_type == TOKEN_ALPHA){
        return "ALPHA";
    }
    if (_type == TOKEN_SPACE){
        return "SPACE";
    }
    if (_type == TOKEN_OPERATOR){
        return "OPERATOR";
    }
    if (_type == TOKEN_PUNC){
        return "PUNC";
    }
    if (_type == TOKEN_END){
        return "END";
    }
    return "UNKNOWN";
}

string Token::token_str() const{
    return _token;
}

//---------------------------------------------------------
Token::Token(string str){
    _token = str;
}

TOKEN_TYPE Token::get_type() const{
    return UNKNOWN;
}

vectorlong Token::recnos(){

}

vectorlong Token::eval(vectorlong left, vectorlong right){

}

vectorlong Token::eval(Map<string, mmap_sl>& index, Token* left, Token* right){

}