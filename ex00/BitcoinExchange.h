// Author: vcordeir <vcordeir@student.42sp.org.br>
// 42 SP

#ifndef BITCOINEXCHANGE_H
#define BITCOINEXCHANGE_H

#include <iostream>
#include <map>
#include <iomanip>

#define SSTR( x ) static_cast< std::ostringstream & >( \
	( std::ostringstream() << std::dec << std::setfill('0') << std::setw(2) << x ) ).str()

struct LineInfo
{
	std::string mDate;
	float mValue;
};

class BitcoinExchange
{
public:

    BitcoinExchange();
    BitcoinExchange( const BitcoinExchange& prBitcoinExchange );
    ~BitcoinExchange();

    BitcoinExchange& operator=( const BitcoinExchange& prBitcoinExchange );

    bool PopulateDatabase();

    void ExchangeCurrency( const std::string& prDate, float pValue );

private:

    static const std::string mDatabaseFilePath;
	std::string mFirstDate;
    std::map< std::string, float > mBitcoinCurrency;

    bool IsValidDate( const std::string& prDate );
    bool IsValidValue( float pValue );

	LineInfo GetLineInfo( const std::string& prLine );

	void AddData( const LineInfo& prNewInfo, const LineInfo& prLastInfo );
    std::string GetNextDay( const std::string& prDate );
};

#endif