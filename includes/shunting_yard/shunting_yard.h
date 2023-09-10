#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H

#include "../../includes/stack/MyStack.h"
#include "../../includes/queue/MyQueue.h"
#include "../token/child_tokens.h"
#include <vector>

class ShuntingYard
{
public:
    ShuntingYard();
    ShuntingYard(const vectorstr& str);
    ShuntingYard(Queue<Token*> infix);

    ~ShuntingYard();
    ShuntingYard(const ShuntingYard& copyMe);
    ShuntingYard& operator= (const ShuntingYard& rhs);

    void str_to_queue(const vectorstr& str);
    void set_infix(Queue<Token*> infix);
    Queue<Token*> convert();
private:
    Queue<Token*> _infix;
    Queue<Token*> _postfix;
    bool _evaluated;
};

#endif