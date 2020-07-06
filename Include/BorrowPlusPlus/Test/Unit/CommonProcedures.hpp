#define USE_BORROWERS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
#include <BorrowPlusPlus/Borrow.hpp>

#ifndef COMMON_PROCEDURES_HEARDER_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
#define COMMON_PROCEDURES_HEARDER_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
namespace BorrowPlusPlus::Test
{
    int RandomNumber();
    void BorrowerInspectModifyInspect( Borrower< int > canidate, int test );
    Borrower< int > BorrowerInspectModifyInspectReturn( Borrower< int > canidate, int test );
    Borrower< int, true > ReferableBorrowerInspectModifyInspectReturn( 
            Borrower< int, true > canidate, int test );
    void RefrenceInspect( Refrence< int > canidate, int test );
    void RefrenceInspectModifyInspect( Refrence< int > canidate, int test );
    Refrence< int > RefrenceInspectModifyInspectReturn( Refrence< int > canidate, int test );
    void BoxInspect( Box< int > box, int testInteger );
    void BoxInespectModifyInspect( Box< int > box, int testInteger );
    Box< int > BoxInespectModifyInspectReturn( Box< int > box, int testInteger );
}
#endif
