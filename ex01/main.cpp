// Author: vcordeir <vcordeir@student.42sp.org.br>
// 42 SP

#include "RPN.h"

int main( int argc, char *argv[] )
{
    if ( argc != 2 )
    {
        std::cout << "Error" << std::endl;
    }

    RPN lExpression( argv[ 1 ] );

    if ( !lExpression.IsExpressionValid() )
    {
        std::cout << "Error" << std::endl;
        return 0;
    }

    std::cout << lExpression.Calculate() << std::endl;
    return 0;
}
