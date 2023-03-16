// Author: vcordeir <vcordeir@student.42sp.org.br>
// 42 SP

#include "RPN.h"

#include <stack>

// ----------------------------------------------------------------------------

RPN::RPN()
{
}

// ----------------------------------------------------------------------------

RPN::RPN( const std::string& prExpression ) : mExpression( prExpression )
{
}

// ----------------------------------------------------------------------------

RPN::RPN( const RPN& prRPN )
{
    *this = prRPN;
}

// ----------------------------------------------------------------------------

RPN::~RPN()
{
}

// ----------------------------------------------------------------------------

RPN& RPN::operator=( const RPN& prRPN )
{
    if ( this == &prRPN ) return *this;

    mExpression = prRPN.mExpression;

    return *this;
}

// ----------------------------------------------------------------------------

void RPN::SetExpression( const std::string& prExpression )
{
	mExpression = prExpression;
}

// ----------------------------------------------------------------------------

bool RPN::IsExpressionValid()
{
    // First two characters must be digits
    if ( !isdigit( mExpression[ 0 ] ) || !isdigit( mExpression[ 2 ] ) ) return false;

    for ( int i = 0; i < (int)mExpression.length(); ++i )
    {
        if ( i % 2 != 0 ) // odd numbers
        {
			// It must have an empty every other espace bc the numbers
			// used in this operation will always be integers less than 10.
            if ( mExpression[ i ] != ' ' ) return false;
        }

        if ( i > 2 && i % 2 == 0 ) // all even after the two first digits
        {
			// We must find alternately: operators and digits
            if ( ( i / 2 ) % 2 == 0 )
            {
                if ( !IsOperatorSymbol( mExpression[ i ] ) ) return false;
            }
            else
            {
                if ( !isdigit( mExpression[ i ] ) ) return false;
            }
        }
    }

    return true;
}

// ----------------------------------------------------------------------------

int RPN::Calculate()
{
    std::stack< int > lNumbers;
    std::stack< char > lOperations;

    for ( int i = mExpression.length() - 1; i > 0 ; --i )
    {
        if ( i % 2 == 0 )
        {
            if ( isdigit( mExpression[ i ] ) )
            {
                lNumbers.push( mExpression[ i ] - '0' );
            }
            else
            {
                lOperations.push( mExpression[ i ] );
            }
        }
    }

    if ( lNumbers.size() != lOperations.size() )
    {
        std::cout << "Error" << std::endl;
        return 0;
    }

    int lResult = mExpression[ 0 ] - '0';

    while ( !lOperations.empty() && !lNumbers.empty() )
    {
        switch( lOperations.top() )
        {
            case '+':
                lResult += lNumbers.top();
                break;

            case '-':
                lResult -= lNumbers.top();
                break;

            case '*':
                lResult *= lNumbers.top();
                break;

            case '/':
                lResult /= lNumbers.top();
                break;
        }

        lNumbers.pop();
        lOperations.pop();
    }

    return lResult;
}

// ----------------------------------------------------------------------------

bool RPN::IsOperatorSymbol( char c )
{
	// We only handle basic operators
    return c == '+' || c == '-' || c == '/' || c == '*';
}

// ----------------------------------------------------------------------------
