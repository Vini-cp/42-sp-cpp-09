// Author: vcordeir <vcordeir@student.42sp.org.br>
// 42 SP

#include "BitcoinExchange.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>

int main( int argc, char *argv[] )
{
    if ( argc != 2 )
    {
        std::cout << "Error: could not open file." << std::endl;
        return 0;
    }

    std::fstream lInput( argv[ 1 ], std::ios::in );
    BitcoinExchange lBitcoin;
    if( lInput.is_open() && lBitcoin.PopulateDatabase() )
    {
        std::string lLine;
        getline( lInput, lLine ); // header

        while( getline( lInput, lLine ) )
        {
            std::stringstream str( lLine );
 
            int lDelimiterPos = lLine.find( '|' );

            std::string lDate = lLine.substr( 0, lDelimiterPos - 1 );
            float lValue = atof( lLine.substr( lDelimiterPos + 2, lLine.length() - lDelimiterPos ).c_str() );

            lBitcoin.ExchangeCurrency( lDate, lValue );
        }
    }
    else
    {
        std::cout << "Error: Could not open file." << std::endl;
    }

    return 0;
}
