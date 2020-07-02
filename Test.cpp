#include <iostream>
#include "Borrow.hpp"

using namespace BorrowPlusPlus;


template< typename DATA_TYPE >
void FunctionToPassToo( Borrower< DATA_TYPE > from ) {
    std::cout << "Passed value: " << *from << "\n";
}


template< typename DATA_TYPE >
/*Borrower< DATA_TYPE > */ void BorrowData( const DATA_TYPE value )
{
    BorrowPointer< DATA_TYPE > meep{ Borrow< DATA_TYPE >{ value } };
    std::cout << "Derp: " << *meep << "\n";
    //meep.owns = false;
    (*meep);
    //std::cout << "Herp: " << val << "\n";
    //Borrower< DATA_TYPE > firstPointer = Borrow< DATA_TYPE >{ value };
    //std::cout << "firstPointer: " << *firstPointer << "\n";
    //FunctionToPassToo< int >( firstPointer );
    //std::cout << "firstPointer again: " << *firstPointer << "\n";
    /*constexpr Refrence< DATA_TYPE > evenLevelPointer = firstPointer;
    std::cout << "evenLevelPointer: " << *evenLevelPointer << "\n";
    {
        Refrence< DATA_TYPE > scopedPointer = firstPointer;
        std::cout << "scopedPointer: " << *scopedPointer << "\n";
        FunctionToPassToo( scopedPointer );
    }
    FunctionToPassToo( evenLevelPointer ); //Ok.//
    auto newPointer = FunctionToPassToo( std::move( firstPointer ) );
    //FunctionToPassToo( evenLevelPointer ); //Error at this point.//
    evenLevelPointer = newPointer;
    FunctionToPassToo( evenLevelPointer ); //Okay now, newPointer is a valid refrence.//
    //return newPointer; //Error at this point.//
    return newPointer;*/
}

int main( int argc, char** args )
{
    BorrowData< int >( 42 );
    return 0;
}
