#define USE_BORROWERS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
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
* i.e Borrower< int > x = ModifyAndReturn( myOtherBorrower ); ***
* x has ownership. However in: ************************
* ModifyAndReturn( std::move( myOtherBorrower ) ); *********
* memory returned is deallocated to avoid dangling ****
* refrence. *******************************************
******************************************************/
Borrower< int >&& ModifyAndReturn( Borrower< int >&& from )
{
    //Add one to the number and return.//
    ++( from.Refer().value() );
    return std::move( from );
}

/***********************************************
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!! NOTE !!!!!!!!!!!!!!!!!!!!!
! ALL BORROWER'S REFRENCES AND VALUES ARE !!!!!!
! WRAPPED WITHIN std::optional TO ALLOW FOR !!!!
! SAFTEY CHECKING! CODE HERE: !!!!!!!!!!!!!!!!!!
! A: Uses explicit methods and conversions to !!
!!!!!!!!!! make that clear !!!!!!!!!!!!!!!!!!!!!
! B: Does not perform saftey checking for the !!
!!!!!!!!!! breavity of this example, though !!!!
!!!!!!!!!! this is highly encouraged! !!!!!!!!!!
!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
***********************************************/

int main( int argc, char** args )
{
    Borrower< int > firstBorrower = Borrow< int >{ RandomNumber() };
    /*******************************************************
    * Parallel boxes existing in the same scope, this case *
    * must be very explicilty and purposfully done, but ****
    * it can be done. *************************************/
    Borrower< int > secondBorrower = std::move( firstBorrower );

    //'secondBorrower' no longer owns, 'thirdBorrower' now owns.//
    Borrower< int > thirdBorrower = ModifyAndReturn( std::move( secondBorrower ) );
    ( *firstBorrower ).value() == ( ( *secondBorrower ).value() == ( *thirdBorrower ).value() ); //True.//

    {
        /**********************************************
        * Here 'fourthBorrower' is created from 'firstBorrower' *
        * 'firstBorrower' lost ownership when it was *******
        * moved to 'secondBorrower'. Since 'firstBorrower' does *
        * not own the value, 'fourthBorrower' has no *******
        * ownership and when it goes out of scope *****
        * the value will NOT be deallocated. **********
        **********************************************/
        Borrower< int > fourthBorrower = std::move( firstBorrower );
    }

    {
        /*********************************************************
        * Unlike the last example here 'fourthBorrower' is *******
        * created from 'thirdBorrower', 'thirdBorrower' gained ***
        * ownership when it was assigned to the ******************
        * return value of 'ModifyAndReturn' a few ****************
        * lines ago. Since 'thirdBorrower' owns the value ********
        * and is being moved to 'fourthBorrower', ****************
        * 'fourthBorrower has ownership. Unless 'fourthBorrower **
        * is moved to something from a higher scope **************
        * it will deallocate the value at the end of this scope. *
        *********************************************************/
        Borrower< int > forthBorrower = std::move( thirdBorrower );
    }
    /***************************************************
    * Because 'fourthBorrower' deallocated the memory, *
    * the following will result in a runtime error *****
    * (commented out so you can run this example). *****
    ***************************************************/
    // ( *fourthBorrower ) += RandomNumber(); //


    Borrower< int > aboutToLoseOwnership = Borrow< int >{ RandomNumber() };
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
