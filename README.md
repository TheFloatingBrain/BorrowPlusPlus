# Borrow++

C++ borrow library with value semantics! This is very much a work in progress and does not have a stable API. However I do provide examples and unit tests, so please gitfeel free to comment, or post issues.

# Goals
- [ ] Make copy/clone methods
- [ ] Add rules to/restrict non-owning boxes passing to functions
- [ ] Fix borrower unit tests
- [ ] .Borrow() methods?
- [ ] Modularize
- [ ] Fix interface too or eliminate "borrowers"
- [ ] Differentiate between mutable & immutable
- [ ] Use pointer-to-pointer types to allow for ubiquitous nullification, nullable/unnullable semantics patial optional manual memory managment, future garbage collector. 
- [ ] Get rid of all STL headers
- [ ] Make borrowing allocator aware.
- [ ] Make "borrow vector/list/container"
- [ ] Make suitable for use atomic-less with lock free programing
- [ ] Add stack/compile time allocator. 
- [ ] Allow for thread safe or atomic storage. 
- [ ] Allow for contiguous storage (array/buffer allocation). 
- [ ] Optional garbage collector. 
- [ ] Make garbage collection allocator aware.
- [ ] Add global allocation pool 

## Completed
- [x] Fix moving and referencing unowned boxes.
- [x] Fix the one foot-gun (the move semantics) that exists in this library. This may be able to be done via template specialization, instantiating owning/non-owning Boxes. I credit https://github.com/ZisIsNotZis/cppBorrow by ZisIsNotZis with that idea. Im basically adding implicit value semantics and garbage collection to his idea. 
- [x] Fix the one foot gun where it someone can write Box< DATA_TYPE > instead of OWNED_BOX< DATA_TYPE > when returning from a function.

# Current Example (Other Examples of Borrowers Availible in /Examples)
```C++
#include <BorrowPlusPlus/Borrow.hpp>
#include <random>
#include <chrono>

using namespace BorrowPlusPlus;

int RandomNumber() {
    return ( std::minstd_rand0( 
            std::chrono::system_clock::now().time_since_epoch().count() ) )();
}

/******************************************************
* 'from' takes ownership of the memory, then the ******
* value passed back does and finaly anything assigned *
* to the temporary takes ownership, if anything, ******
* i.e Box< int > x = ModifyAndReturn( myOtherBox ); ***
* x has ownership. However in: ************************
* ModifyAndReturn( std::move( myOtherBox ) ); *********
* memory returned is deallocated to avoid dangling ****
* refrence. *******************************************
******************************************************/
Box< int >&& ModifyAndReturn( Box< int >&& from )
{
    //Add one to the number and return.//
    ++*from;
    return std::move( from );
}

//Does NOT take ownership, but can modify/inspect value.//
void Modify( Refrence< int > someInt ) {
    //Add 1 to the number.//
    ++*someInt;
}

int main( int argc, char** args )
{
    Box< int > firstBox = Borrow< int >{ RandomNumber() };
    /*******************************************************
    * Parallel boxes existing in the same scope, this case *
    * must be very explicilty and purposfully done, but ****
    * it can be done. *************************************/
    Box< int > secondBox = std::move( firstBox );
    //Pass a non-owning refrence to the function.//
    Modify( firstBox );
    //Works with either one -- rules for this in the future.//
    Modify( secondBox );
    ( *firstBox ) == ( *secondBox ); //True!//    
    Refrence< int > firstRefrence = secondBox;
    //Below line is equal to the line written 3 lines above 'Modify( secondBox );'//
    Modify( firstRefrence );
    //'secondBox' no longer owns, 'thirdBox' now owns.//
    Box< int > thirdBox = ModifyAndReturn( std::move( secondBox ) );
    ( *firstBox ) == ( ( *secondBox ) == ( *thirdBox ) ); //True.//

    {
        /**********************************************
        * Here 'fourthBox' is created from 'firstBox' *
        * 'firstBox' lost ownership when it was *******
        * moved to 'secondBox'. Since 'firstBox' does *
        * not own the value, 'fourthBox' has no *******
        * ownership and when it goes out of scope *****
        * the value will NOT be deallocated. **********
        **********************************************/
        Box< int > fourthBox = std::move( firstBox );
    }

    {
        /**********************************************
        * Unlike the last example here 'fourthBox' is *
        * created from 'thirdBox', 'thirdBox' gained **
        * ownership when it was assigned to the *******
        * return value of 'ModifyAndReturn' a few *****
        * lines ago. Since 'thirdBox' owns the value **
        * and is being moved to 'fourthBox', **********
        * 'fourthBox has ownership. Unless 'fourthBox *
        * is moved to something from a higher scope ***
        * it will deallocate the value at the end of **
        * this scope. *********************************
        **********************************************/
        Box< int > forthBox = std::move( thirdBox );
    }
    /**********************************************
    * Because 'fourthBox' deallocated the memory, *
    * the following will result in a runtime ******
    * error (commented out so you can run this ****
    * example). Uncomment to try. Saftey features *
    * for this are planned, or use Borrower. ******
    **********************************************/
    // ( *fourthBox ) += RandomNumber(); //


    Box< int > aboutToLoseOwnership = Borrow< int >{ RandomNumber() };
    /****************************************************************
    * 'aboutToLoseOwnership's value is passed to 'ModifyAndReturn', *
    * because of this, it will loose its ownership of the value. ****
    * since nothing is assigned to the return value of **************
    * 'ModifyAndReturn', ownership can not be passed on and the *****
    * the value will be deallocated. ********************************
    ****************************************************************/
    ModifyAndReturn( std::move( aboutToLoseOwnership ) );

    /**********************************************************************
    * Because of the line above, the following line would cause a runtime *
    * error (uncomment to try). *******************************************
    **********************************************************************/

    // ( *aboutToLoseOwnership ) -= RandomNumber(); //
    return 0;
}

```
# Background

I created U.C.C or [Universal C/C++ Compiler](https://github.com/TheFloatingBrain/UCC-UniversalCPPCompiler) over seven years ago  
and ever since then I had thought about implementing its borrow semantics as a library. I thought for a while that borrow was a flawed model and smart pointers had taken over anyway, but with the rise of Swift, Rust, and Kotlin as well as constexpr or constexpr like things in multiple languages I thought I might give this a shot. I think potentially that having the compiler integration with little to no overhead is better, especially since it is portable as a source-to-source compiler, but I think this may be a worth while effort given I think this can be more efficient (due to not reference counting and possibly easier to use than standard smart pointers, if not just to get it off my mind. I am taking a different approch (including the use of value semantics) but please take a look at https://github.com/ZisIsNotZis/cppBorrow as well! As ZisIsNotZis has done a great job and I "borrowed" (heh') a few ideas from there.
