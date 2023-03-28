// Author: vcordeir <vcordeir@student.42sp.org.br>
// 42 SP

#include "PmergeMe.h"

int main( int argc, char *argv[] )
{
    if ( argc < 2 )
    {
        std::cout << "Error" << std::endl;
    }

    PmergeMe lNumbers( argv, argc );

    if ( !lNumbers.IsSequenceValid() )
    {
        std::cout << "Error" << std::endl;
        return 0;
    }

    lNumbers.SortContainers();
    return 0;
}
