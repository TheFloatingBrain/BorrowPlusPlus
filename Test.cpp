#include <iostream>
#include "Borrow.hpp"

using namespace BorrowPlusPlus;


void OtherTest( Borrower< int > other ) {
    std::cout << "val2: " << (*other).value() << "\n";    
}

void Test()
{

}

int main( int argc, char** args )
{
    Test();
    return 0;
}