// Author: vcordeir <vcordeir@student.42sp.org.br>
// 42 SP

#include "BitcoinExchange.h"

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h>

// ----------------------------------------------------------------------------

const std::string BitcoinExchange::mDatabaseFilePath = "data.csv";

// ----------------------------------------------------------------------------

BitcoinExchange::BitcoinExchange()
{
}

// ----------------------------------------------------------------------------

BitcoinExchange::BitcoinExchange( const BitcoinExchange& prBitcoinExchange )
{
    *this = prBitcoinExchange;
}

// ----------------------------------------------------------------------------

BitcoinExchange::~BitcoinExchange()
{
}

// ----------------------------------------------------------------------------

BitcoinExchange& BitcoinExchange::operator=( const BitcoinExchange& prBitcoinExchange )
{
    if ( this == &prBitcoinExchange ) return *this;

    mBitcoinCurrency = prBitcoinExchange.mBitcoinCurrency;

    return *this;
}

// ----------------------------------------------------------------------------

bool BitcoinExchange::PopulateDatabase()
{
    std::fstream lDatabaseFile( mDatabaseFilePath.c_str(), std::ios::in );
    if( lDatabaseFile.is_open() )
    {
        std::string lLine;
		std::getline( lDatabaseFile, lLine ); // First line: header
		std::getline( lDatabaseFile, lLine );

		LineInfo lInfo = GetLineInfo( lLine );
        while( std::getline( lDatabaseFile, lLine ) )
        {
			LineInfo lNextInfo = GetLineInfo( lLine );

			AddData( lInfo, lNextInfo );
			lInfo = lNextInfo;
        }

		AddData( lInfo, lInfo ); // Add last data

        return true;
    }
    else
    {
        std::cout << "Error: Could not open database file." << std::endl;
        return false;
    }
}

// ----------------------------------------------------------------------------

void BitcoinExchange::ExchangeCurrency( const std::string& prDate, float pValue )
{
    if ( !IsValidDate( prDate ) )
    {
        std::cout << "Error: bad input => " << prDate << std::endl;
        return;
    }
    
    if ( !IsValidValue( pValue ) ) return;
    
    std::map< std::string, float >::iterator lPair = mBitcoinCurrency.find( prDate );

    if ( lPair == mBitcoinCurrency.end() )
    {
        std::cout << "Error: date not in database => " << prDate << std::endl;
        return;
    }

    float lExchangeValue = lPair->second * pValue;

    std::cout << prDate << " => " << pValue << " = " << lExchangeValue << std::endl;
}

// ----------------------------------------------------------------------------

static bool IsLeap( int pYear )
{
    // Return true if year is a multiple of 4 AND NOT multiple of 100.
    // OR year is multiple of 400.
    return ( ( pYear % 4 == 0 ) && ( pYear % 100 != 0 ) ) || ( pYear % 400 == 0 );
}

// ----------------------------------------------------------------------------

bool BitcoinExchange::IsValidDate( const std::string& prDate )
{
	if ( prDate.length() != 10 ) return false;

	for ( int i = 0; i < (int)prDate.length(); ++i )
	{
		if ( i == 4 || i == 7 )
		{
			if ( prDate[ i ] != '-' ) return false; // Date delimiter
			continue;
		}

		if ( !isdigit( prDate[ i ] ) ) return false;
	}

    int lYear = atoi( prDate.substr( 0, 4 ).c_str() );
    int lMonth = atoi( prDate.substr( 5, 2 ).c_str() );
    int lDay = atoi( prDate.substr( 8, 2 ).c_str() );

    if ( lYear < 0 ) return false;

    if ( lMonth <= 0 || lMonth > 12 ) return false;

    if ( lDay <= 0 || lDay > 31 ) return false;

    // Handle February with leap year
    if ( lMonth == 2 )
    {
        if ( IsLeap( lYear ) ) return ( lDay <= 29 );

        return ( lDay <= 28 );
    }
  
    // April, June, Sept and Nov have 30 days
    if ( lMonth == 4 || lMonth == 6 || lMonth == 9 || lMonth == 11 )
    {
        return ( lDay <= 30 );
    }
  
    return true;
}

// ----------------------------------------------------------------------------

bool BitcoinExchange::IsValidValue( float pValue )
{
    if ( pValue < 0 )
    {
        std::cout << "Error: not a positive number." << std::endl;
        return false;
    }

    if ( pValue > 1000 )
    {
        std::cout << "Error: too large a number." << std::endl;
        return false;
    }

    return true;
}

// ----------------------------------------------------------------------------

LineInfo BitcoinExchange::GetLineInfo( const std::string& prLine )
{
	int lDelimiterPos = prLine.find( ',' );

	LineInfo lInfo;

	lInfo.mDate = prLine.substr( 0, lDelimiterPos );
	lInfo.mValue = atof( prLine.substr( lDelimiterPos + 1, prLine.length() - lDelimiterPos ).c_str() );

	return lInfo;
}

// ----------------------------------------------------------------------------

void BitcoinExchange::AddData( const LineInfo& prInfo, const LineInfo& prNextInfo )
{
	if ( mBitcoinCurrency.empty() || prInfo.mDate == prNextInfo.mDate )
	{
		mBitcoinCurrency.insert( std::pair< std::string, float >( prInfo.mDate, prInfo.mValue ) );
		return;
	}

	std::string lDate = prInfo.mDate;
	std::string lNextDate = prNextInfo.mDate;

	while ( lDate != lNextDate )
	{
		mBitcoinCurrency.insert( std::pair< std::string, float >( lDate, prInfo.mValue ) );
		lDate = GetNextDay( lDate );
	}
}

// ----------------------------------------------------------------------------

std::string BitcoinExchange::GetNextDay( const std::string& prDate )
{
	int lYear = atoi( prDate.substr( 0, 4 ).c_str() );
    int lMonth = atoi( prDate.substr( 5, 2 ).c_str() );
    int lDay = atoi( prDate.substr( 8, 2 ).c_str() );

    lDay++;

	// Handle February with leap year
    if ( lMonth == 2 )
    {
        if ( IsLeap( lYear ) )
		{
			if ( lDay == 30 )
			{
				lDay = 1;
				lMonth++;
			}
		}
		else
		{
			if ( lDay == 29 )
			{
				lDay = 1;
				lMonth++;
			}
		}
    }
	else if ( lMonth == 4 || lMonth == 6 || lMonth == 9 || lMonth == 11 )
	{
		if ( lDay == 31 )
		{
			lDay = 1;
			lMonth++;
		}
	}
	else if ( lMonth == 12 )
	{
		if ( lDay == 32 )
		{
			lDay = 1;
			lMonth = 1;
			lYear++;
		}
	}
	else
	{
		if ( lDay == 32 )
		{
			lDay = 1;
			lMonth++;
		}
	}

    std::stringstream lYearStr;
    lYearStr << lYear;

    std::string lNewDate = lYearStr.str() + "-" + SSTR( lMonth ) + "-" + SSTR( lDay );
    
    return lNewDate;
}

// ----------------------------------------------------------------------------
