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
