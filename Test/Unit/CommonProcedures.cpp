#include <BorrowPlusPlus/Test/Unit/CommonProcedures.hpp>
#include <chrono>
#include <random>
#include <catch/catch.hpp>

namespace BorrowPlusPlus::Test
{
    int RandomNumber() {
        return ( std::minstd_rand0( 
                std::chrono::system_clock::now().time_since_epoch().count() ) )();
    }
    void BorrowerInspectModifyInspect( Borrower< int > canidate, int test )
    {
        REQUIRE( ( *canidate ).value() == test );
        ++( ( *canidate ).value() );
        REQUIRE( ( *canidate ).value() == ( test + 1 ) );
    }
    Borrower< int > BorrowerInspectModifyInspectReturn( Borrower< int > canidate, int test )
    {
        REQUIRE( ( *canidate ).value() == test );
        ++( ( *canidate ).value() );
        REQUIRE( ( *canidate ).value() == ( test + 1 ) );
        return canidate;
    }
    Borrower< int, true > ReferableBorrowerInspectModifyInspectReturn( 
            Borrower< int, true > canidate, int test )
    {
        REQUIRE( ( *canidate ).value() == test );
        ++( ( *canidate ).value() );
        REQUIRE( ( *canidate ).value() == ( test + 1 ) );
        return canidate;
    }
    void RefrenceInspect( Refrence< int > canidate, int test ) {
        REQUIRE( ( *canidate ) == test );
    }
    void RefrenceInspectModifyInspect( Refrence< int > canidate, int test ) {
        REQUIRE( ( *canidate ) == test );
        REQUIRE( ++(*canidate) == ( test + 1 ) );
    }
    Refrence< int > RefrenceInspectModifyInspectReturn( Refrence< int > canidate, int test ) {
        REQUIRE( ( *canidate ) == test );
        REQUIRE( ++(*canidate) == test + 1 );
        return canidate;
    }
    void BoxInspect( Box< int > box, int testInteger ) {
        REQUIRE( ( *box ) == testInteger );
    }
    void BoxInespectModifyInspect( Box< int > box, int testInteger ) {
        REQUIRE( ( *box ) == testInteger );
        REQUIRE( ( ++( *box ) ) == ( testInteger + 1 ) );
    }
    Box< int > BoxInespectModifyInspectReturn( Box< int > box, int testInteger )
    {
        REQUIRE( ( *box ) == testInteger );
        REQUIRE( ( ++( *box ) ) == ( testInteger + 1 ) );
        return box;
    }
}
