// Author: vcordeir <vcordeir@student.42sp.org.br>
// 42 SP

#ifndef RPN_H
#define RPN_H

#include <iostream>

class RPN
{
public:

    RPN();
    RPN( const std::string& prExpression );
    RPN( const RPN& prRPN );
    ~RPN();

    void SetExpression( const std::string& prExpression );

    RPN& operator=( const RPN& prRPN );

    bool IsExpressionValid();

    int Calculate();

private:

    std::string mExpression;

    bool IsOperatorSymbol( char c );
};

#endif