// Author: vcordeir <vcordeir@student.42sp.org.br>
// 42 SP

#ifndef PMERGEME_H
#define PMERGEME_H

#include <deque>
#include <iomanip>
#include <iostream>
#include <set>
#include <stdio.h>
#include <sys/time.h>
#include <vector>

class PmergeMe
{
public:

    PmergeMe();
    PmergeMe( char **ppNumbers, int pSize );
    PmergeMe( const PmergeMe& prPmergeMe );
    ~PmergeMe();

    void SetNumbers( const std::vector< int >& prNumbers );

    PmergeMe& operator=( const PmergeMe& prPmergeMe );

    bool IsSequenceValid();

    void SortContainers();

private:

    const int mMinSize;
    bool mBadTextInput;
    bool mDuplicateNumber;
    bool mNegativeNumber;

    std::set< int > mSetNumbers;
    std::vector< int > mVectorNumbers;
    std::deque< int > mDequeNumbers;

    bool IsNumber( char* ppText );

    template< typename T >
    void Sort( T& prContainer, int pStart, int pEnd )
    {
        if ( pEnd - pStart > mMinSize )
        {
            int lMiddle = ( pStart + pEnd ) / 2;

            Sort( prContainer, pStart, lMiddle );
            Sort( prContainer, lMiddle + 1, pEnd );
            MergeSort( prContainer, pStart, lMiddle, pEnd );
        }
        else
        {
            InsertionSort( prContainer, pStart, pEnd );
        }
    };
    
    template< typename T >
    void InsertionSort( T& prContainer, int pStart, int pEnd )
    {
        for ( int i = pStart; i < pEnd; ++i )
        {
            int tmp = prContainer[ i + 1 ];
            int j = i + 1;

            while ( j > pStart && prContainer[ j - 1 ] > tmp )
            {
                prContainer[ j ] = prContainer[ j - 1 ];
                j--;
            }
            
            prContainer[ j ] = tmp;
        }
    };

    template< typename T >
    void MergeSort( T& prContainer, int pStart, int pMiddle, int pEnd )
    {
        int lLeftNbElements = pMiddle - pStart + 1;
        int lRightNbElements = pEnd - pMiddle;

        T lLeftContainer = CopyRange( prContainer, pStart, pMiddle + 1 );
        T lRightContainer = CopyRange( prContainer, pMiddle + 1, pEnd + 1 );

        int i, j, k;
        i = 0;
        j = 0;
        k = pStart;

        // Until we reach either end of either L or M, pick larger among
        // elements L and M and place them in the correct position at A[p..r]
        while ( i < lLeftNbElements && j < lRightNbElements )
        {
            if ( lLeftContainer[ i ] <= lRightContainer[ j ] )
            {
                prContainer[ k ] = lLeftContainer[ i ];
                ++i;
            }
            else
            {
                prContainer[ k ] = lRightContainer[ j ];
                ++j;
            }
            ++k;
        }

        while ( i < lLeftNbElements )
        {
            prContainer[ k ] = lLeftContainer[ i ];
            ++i;
            ++k;
        }

        while ( j < lRightNbElements )
        {
            prContainer[ k ] = lRightContainer[ j ];
            ++j;
            ++k;
        }
    };

    template< typename T >
    T CopyRange( T& prContainer, int pStart, int pEnd )
    {
        T lContainer;

        for ( int i = pStart; i < pEnd; ++i )
        {
            lContainer.push_back( prContainer[ i ] );
        }
        
        return lContainer;
    };

    template< typename T >
    void PrintContainer( T& prContainer )
    {
        typename T::iterator it;
        for ( it = prContainer.begin(); it != prContainer.end(); ++it )
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    };

    template< typename T >
    void SortContainer( T& prContainer )
    {
        struct timeval begin, end;
        gettimeofday(&begin, 0);

        Sort( prContainer, 0, prContainer.size() - 1 );

        gettimeofday(&end, 0);
        long seconds = end.tv_sec - begin.tv_sec;
        long microseconds = end.tv_usec - begin.tv_usec;
        double elapsed = seconds + microseconds * 1e-6;

        std::cout << "Time to process a range of " << prContainer.size()
            << " elements with std::vector: " << std::fixed << std::setprecision(6) << elapsed << "us" << std::endl;
    };

    template< typename T, typename U >
    bool CompareContainers( T& prContainer1, U& prContainer2 )
    {
        if ( prContainer1.size() != prContainer2.size() ) return false;

        typename T::iterator it1 = prContainer1.begin();
        typename U::iterator it2 = prContainer2.begin();

        while ( it1 != prContainer1.end() && it2 != prContainer2.end() )
        {
            if ( *it1 != *it2 ) return false;

            ++it1;
            ++it2;
        }
        
        return true;
    };

};

#endif
