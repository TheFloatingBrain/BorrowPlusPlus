#include <iostream>
#include "Borrow.hpp"

using namespace BorrowBox;

struct TestStruct
{
    int value;
    void PrintValue() {
        std::cout << "TestStruct::void PrintValue(): The value is " << value << "\n";
    }
};

template< typename DATA_TYPE >
void FunctionToPassToo( Box< DATA_TYPE >&& from ) {
    std::cout << "Passed value: " << *from << "\n";
}

void FunctionToPassToo( Box< TestStruct >&& from ) {
    std::cout << "Passed value: " << from->value << "\n";
}

template< typename DATA_TYPE >
Box< DATA_TYPE > MakeInt( DATA_TYPE value )
{
    Box< DATA_TYPE > firstPointer = Borrow< DATA_TYPE >( value );
    std::cout << "firstPointer: " << *firstPointer << "\n";
    Box< DATA_TYPE > evenLevelPointer = firstPointer;
    std::cout << "evenLevelPointer: " << *evenLevelPointer << "\n";
    {
        Box< DATA_TYPE > scopedPointer = std::move( firstPointer );
        std::cout << "scopedPointer: " << *scopedPointer << "\n";
        FunctionToPassToo( std::move( scopedPointer ) );
    }
    FunctionToPassToo( std::move( firstPointer ) );
    FunctionToPassToo( std::move( evenLevelPointer ) );
    /***********************************************************************
    * Foot-gun stemming from the move - semantics foot-gun, need to return *
    * most recently passed pointer. Currently can only be avoided by using *
    * move semantics like in the code block. *******************************
    ***********************************************************************/
    return evenLevelPointer;
}

int main( int argc, char** args )
{
    int value = 0;
    std::cout << 
            "Please enter a value to allocate inside a "
            "function but not use outside that function.\n";
    std::cin >> value;
    MakeInt( value );
    std::cout << 
            "Please enter a value to allocate inside a fucntion"
            "then USE outside that function.\n";
    std::cin >> value;
    auto outPointer = MakeInt( value );
    std::cout << "outPointer: " << *outPointer << "\n";
    Box< TestStruct > structPointer = Borrow< TestStruct >{};
    std::cout << "Please enter a test value to demonstrate Boxing classes/structs.\n";
    std::cin >> structPointer->value;
    structPointer->PrintValue();
    FunctionToPassToo( std::move( structPointer ) );
    return 0;
}
