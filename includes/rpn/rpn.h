#ifndef RPN_H
#define RPN_H

#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/child_tokens.h"

class RPN {
public:
    RPN();
    RPN(const Queue<Token*>& post_fix);

    ~RPN();
    RPN(const RPN& copyMe);
    RPN& operator= (const RPN& rhs);

    void set_input(Queue<Token*>& post_fix);
    vectorlong eval(Map<string, mmap_sl> index);
private:
    Queue<Token*> _post_fix;
    vectorlong _answer;
    bool _evaluated;
};

#endif