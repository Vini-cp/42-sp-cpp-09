// Author: vcordeir <vcordeir@student.42sp.org.br>
// 42 SP

#include "PmergeMe.h"

#include <algorithm>
#include <stdlib.h>

// ----------------------------------------------------------------------------

PmergeMe::PmergeMe() :
    mMinSize( 5 ),
    mBadTextInput( false ),
    mDuplicateNumber( false ),
    mNegativeNumber( false )
{
}

// ----------------------------------------------------------------------------

PmergeMe::PmergeMe( char **ppNumbers, int pSize ) :
    mMinSize( 5 ),
    mBadTextInput( false ),
    mDuplicateNumber( false ),
    mNegativeNumber( false )
{
    for ( int i = 1; i < pSize; ++i ) // First element is always ./PmergeMe cmd
    {
        if ( !IsNumber( ppNumbers[ i ] ) )
        {
            mBadTextInput = true;
            break;
        }

        int lNumber = atoi( ppNumbers[ i ] );

        if ( lNumber < 0 )
        {
            mNegativeNumber = true;
            break;
        }

        if ( mSetNumbers.find( lNumber ) != mSetNumbers.end() )
        {
            mDuplicateNumber = true;
            break;
        }

        mSetNumbers.insert( lNumber );
        mVectorNumbers.push_back( lNumber );
        mDequeNumbers.push_back( lNumber );
    }
}

// ----------------------------------------------------------------------------

PmergeMe::PmergeMe( const PmergeMe& prPmergeMe )  :
    mMinSize( 5 )
{
    *this = prPmergeMe;
}

// ----------------------------------------------------------------------------

PmergeMe::~PmergeMe()
{
}

// ----------------------------------------------------------------------------

PmergeMe& PmergeMe::operator=( const PmergeMe& prPmergeMe )
{
    if ( this == &prPmergeMe ) return *this;

    mSetNumbers = prPmergeMe.mSetNumbers;
    mVectorNumbers = prPmergeMe.mVectorNumbers;
    mDequeNumbers = prPmergeMe.mDequeNumbers;

    mBadTextInput = prPmergeMe.mBadTextInput;
    mDuplicateNumber = prPmergeMe.mDuplicateNumber;
    mNegativeNumber = prPmergeMe.mNegativeNumber;

    return *this;
}

// ----------------------------------------------------------------------------

void PmergeMe::SetNumbers( const std::vector< int >& prNumbers )
{
    mSetNumbers.clear();
    mVectorNumbers.clear();
    mDequeNumbers.clear();

    mBadTextInput = false;
    mDuplicateNumber = false;

    for ( int i = 0; i < (int)prNumbers.size(); ++i )
    {
        if ( prNumbers[ i ] < 0 )
        {
            mNegativeNumber = true;
            break;
        }

        if ( mSetNumbers.find( prNumbers[ i ] ) != mSetNumbers.end() )
        {
            mDuplicateNumber = true;
            break;
        }

        mSetNumbers.insert( prNumbers[ i ] );
    }
}

// ----------------------------------------------------------------------------

bool PmergeMe::IsSequenceValid()
{
    return !mBadTextInput && !mDuplicateNumber && !mNegativeNumber;
}

// ----------------------------------------------------------------------------

void PmergeMe::SortContainers()
{
    std::cout << "Before: ";
    PrintContainer( mVectorNumbers );

    std::cout << "After: ";
    PrintContainer( mSetNumbers );

    SortContainer( mVectorNumbers );
    SortContainer( mDequeNumbers );

    if ( !CompareContainers( mVectorNumbers, mSetNumbers ) || !CompareContainers( mDequeNumbers, mSetNumbers ) )
    {
        std::cout << "Error: " << std::endl;
    }
}

// ----------------------------------------------------------------------------

bool PmergeMe::IsNumber( char* ppText )
{
    int i = 0;
    while ( ppText[ i ] != '\0' )
    {
        if ( !isdigit( ppText[ i ] ) ) return false;
        i++;
    }

    return true;
}

// ----------------------------------------------------------------------------
