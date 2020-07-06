#include <iostream>

#define USE_BORROWERS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
#include <BorrowPlusPlus/Borrow.hpp>

using namespace BorrowPlusPlus;

int main( int argc, char** args )
{
    Box< int > b = Borrow< int >( 5 );
    Box< int > c = b;
    //runtime error
    return 0;
}
