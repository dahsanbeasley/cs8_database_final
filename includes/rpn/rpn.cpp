#include "rpn.h"

RPN::RPN(){
    _post_fix = Queue<Token*>();
    _evaluated = false;
}

RPN::RPN(const Queue<Token*>& post_fix) : _post_fix (post_fix){
    _evaluated = false;
}

RPN::~RPN(){

}

RPN::RPN(const RPN& copyMe){
    _post_fix = copyMe._post_fix;
    _answer = copyMe._answer;
    _evaluated = copyMe._evaluated;
}

RPN& RPN::operator= (const RPN& rhs){
    if (this != &rhs){
        _post_fix = rhs._post_fix;
        _answer = rhs._answer;
        _evaluated = rhs._evaluated;
    }

    return *this;
}

void RPN::set_input(Queue<Token*>& post_fix){
    _evaluated = false;
    _post_fix = post_fix;
}

vectorlong RPN::eval(Map<string, mmap_sl> index){
    if (!_evaluated){
        Queue<Token*> pop_this = _post_fix;
        Stack<Token*> evaluate_this;
        
        while (!pop_this.empty()){
            evaluate_this.push(pop_this.pop());
           if (evaluate_this.top()->get_type() >= LOGIC_OR && evaluate_this.top()->get_type() <= LOGIC_AND){
               Token* op = evaluate_this.pop();
               vectorlong right = evaluate_this.pop()->recnos();
               vectorlong left = evaluate_this.pop()->recnos();
               //cout << "RPN: "<< __LINE__ << endl;
               evaluate_this.push(new ResultSet(op->eval(left, right)));
               //cout << "RPN: "<< __LINE__ << endl;
           }
           if (evaluate_this.top()->get_type() == RELATIONAL) {
               Token* op = evaluate_this.pop();
               Token* right = evaluate_this.pop();
               Token* left = evaluate_this.pop();
               //cout << "RPN: "<< __LINE__ << endl;
               evaluate_this.push(new ResultSet( op->eval(index, left, right)));
               //cout << "RPN: "<< __LINE__ << endl;
           }
        }
        //cout << "RPN: " << __LINE__ << endl;
        _answer = evaluate_this.pop()->recnos();
        //cout << "RPN: "<< __LINE__ << endl;
        _evaluated = true;
    }
    //cout << "RPN: "<< __LINE__ << endl;
    return _answer;
}