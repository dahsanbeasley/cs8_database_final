#include "shunting_yard.h"

ShuntingYard::ShuntingYard(){
    _evaluated = false;
}

ShuntingYard::ShuntingYard(const vectorstr& str){
    _evaluated = false;
    str_to_queue(str);    
}

ShuntingYard::ShuntingYard(Queue<Token*> infix){
    _evaluated = false;
    _infix = infix;
}

ShuntingYard::~ShuntingYard(){

}

ShuntingYard::ShuntingYard(const ShuntingYard& copyMe){
    _evaluated = copyMe._evaluated;
    _infix = copyMe._infix;
    _postfix = copyMe._postfix;
}

ShuntingYard& ShuntingYard::operator= (const ShuntingYard& rhs){
    if (this != &rhs){
        _evaluated = rhs._evaluated;
        _infix = rhs._infix;
        _postfix = rhs._postfix;
    }
    return *this;
}

void ShuntingYard::str_to_queue(const vectorstr& str){
    for (int i = 0; i < str.size(); i++){
        if(str[i] == "("){
            _infix.push(new LParen());
        }
        else if(str[i] == ")"){
            _infix.push(new RParen());
        }
        else if(str[i] == ">"){
            _infix.push(new Relational(str[i]));
        }
        else if(str[i] == "<"){
            _infix.push(new Relational(str[i]));
        }
        else if(str[i] == "="){
            _infix.push(new Relational(str[i]));
        }
        else if(str[i] == ">="){
            _infix.push(new Relational(str[i]));
        }
        else if(str[i] == "<="){
            _infix.push(new Relational(str[i]));
        }
        else if(str[i] == "and"){
            _infix.push(new Logical(str[i]));
        }
        else if(str[i] == "or"){
            _infix.push(new Logical(str[i]));
        }
        else{
            _infix.push(new TokenStr(str[i]));
        }
    }
}

void ShuntingYard::set_infix(Queue<Token*> infix){
    _evaluated = false;
    _infix = infix;
}

Queue<Token*> ShuntingYard::convert(){
    Queue<Token*> output;
    Stack<Token*> op_stack;
    while (!_infix.empty()){
        Token* op = _infix.pop();
        if (op->get_type() == TOKEN_STR){
            output.push(op);
        }
        else if (op->get_type() >= LOGIC_OR && op->get_type() <= RELATIONAL){
            if (!op_stack.empty()){
                // Stack<Token*> temp = op_stack;
                // while (!temp.empty()){
                //     Token* t1 = temp.pop();
                //     cout << t1->token_str() << endl;
                // }
                bool done = false;
                while(!done){
                    if(op_stack.top()->get_type() != L_PAREN && 
                    (op_stack.top()->get_type() > op->get_type())){
                        output.push(op_stack.pop());
                    }
                    else
                        done = true;
                    if(op_stack.empty())
                        done = true;
                }
            }
            op_stack.push(op);
        }
        else if (op->get_type() == L_PAREN){
            op_stack.push(op);
        }
        else if (op->get_type() == R_PAREN){
            if (!op_stack.empty()){
                while(op_stack.top()->get_type() != L_PAREN){
                    output.push(op_stack.pop());
                }
                assert(op_stack.top()->get_type() == L_PAREN);
                op_stack.pop();
            }
        }
    }
    while(!op_stack.empty()){
        assert(op_stack.top()->get_type() != L_PAREN);
        output.push(op_stack.pop());
    }
    _postfix = output;
    _evaluated = true;
    return output;
}
