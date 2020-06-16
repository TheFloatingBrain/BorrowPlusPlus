# Borrow++

C++ borrow library with value semantics! NOT ready for use yet!

# Goals
* Add global allocation pool 
* Use pointer-to-pointer types to allow for ubiquitous nullification, nullable/unnullable semantics patial optional manual memory managment, future garbage collector. 
* Optional garbage collector. 
* Fix the one foot-gun (the move semantics) that exists in this library. This may be able to be done via template specialization, instantiating owning/non-owning Boxes. I credit https://github.com/ZisIsNotZis/cppBorrow by ZisIsNotZis with that idea. Im basically adding implicit value semantics and garbage collection to his idea. 
* Allow for thread safe or atomic storage. 
* Allow for contiguous storage (array/buffer allocation). 
* Add stack/compile time allocator. 

# Current Example
```C++
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
```

# Background

I created U.C.C (Universal C/C++ Compiler) over seven years ago https://github.com/TheFloatingBrain/UCC-UniversalCPPCompiler 
and ever since then I had thought about implementing its borrow semantics as a library. I thought for a while that borrow was a flawed model and smart 
pointers had taken over anyway, but with the rise of Swift, Rust, and Kotlin as well as constexpr or constexpr like things in multiple languages I thought 
I might give this a shot. I think potentially that having the compiler integration with little to no overhead is better, especially since it is 
portable as a source-to-source compiler, but I think this may be a worth while effort given I think this can be more efficent (due to not refrence 
counting and possibly easier to use than standard smart poitners, if not just to get it off my mind. I am taking a different approch (including the 
use of value semantics) but please take a look at https://github.com/ZisIsNotZis/cppBorrow as well! As ZisIsNotZis has done a great job and I "borrowed" (heh') a few ideas from there.
