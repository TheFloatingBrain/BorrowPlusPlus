#include <BorrowPlusPlus/Test/Unit/CommonProcedures.hpp>
#include <catch/catch.hpp>
using namespace BorrowPlusPlus;
using namespace BorrowPlusPlus::Test;

TEST_CASE( "Test all referable borrower functions", "[referable-borrower]" )
{
    SECTION( "Get refrence from borrower, pass refrence to function, and inspect" )
    {
        GIVEN( "A referable borrower, and a random number" )
        {
            int testNumber = RandomNumber();
            Borrower< int, true > testBorrower = Borrow< int >( testNumber ).ReferableBorrower();
            WHEN( "A refrence is constructed from the borrower" )
            {
                REQUIRE( testBorrower.ToRefrence().has_value() == true );
                THEN( "The value of a produced refrence should equal the random test value "
                        "when read from the produced refrence" )
                {
                    REQUIRE( *( testBorrower.ToRefrence().value() ) == testNumber );
                    AND_THEN( "The borrower should still be able to produce refrences." ) {
                        REQUIRE( testBorrower.ToRefrence().has_value() == true );
                    }
                }
            }
        }
    }
    SECTION( "Get refrence from borrower, pass refrence to function, inspect, pass & inspect, then inspect again on outer scope" )
    {
        GIVEN( "A referable borrower, and a refrence and a random number" )
        {
            int testNumber = RandomNumber();
            Borrower< int, true > testBorrower = Borrow< int >( testNumber ).ReferableBorrower();
            Refrence< int > topLevelRefrence = testBorrower.ToRefrence().value();
            WHEN( "The refrence's value is equal to the random test value" )
            {
                REQUIRE( ( *topLevelRefrence ) == testNumber );
                THEN( "The refrence is passed to a function and its value is inspected" )
                {
                    RefrenceInspect( topLevelRefrence, testNumber );
                    AND_THEN( "The refrence's value is still equal to the test random value, and the borrower still has a value" ) {
                        REQUIRE( ( *topLevelRefrence ) == testNumber );
                        REQUIRE( testBorrower.ToRefrence().has_value() == true );
                    }
                }
            }
        }
    }
    SECTION( "Get refrence from borrower, pass refrence to function, inspect, pass & inspect modify & inspect, then inspect again on outer scope" )
    {
        GIVEN( "A referable borrower, and a refrence and a random number" )
        {
            int testNumber = RandomNumber();
            Borrower< int, true > testBorrower = Borrow< int >( testNumber ).ReferableBorrower();
            Refrence< int > topLevelRefrence = testBorrower.ToRefrence().value();
            WHEN( "The refrence's value equals the test random number" )
            {
                REQUIRE( ( *topLevelRefrence ) == testNumber );
                THEN( "The value is modified in a function where the refrence is passed" )
                {
                    RefrenceInspectModifyInspect( topLevelRefrence, testNumber );
                    THEN( "The borrower still has the value" )
                    {
                        REQUIRE( testBorrower.Refer().has_value() == true );
                        REQUIRE( testBorrower.ToRefrence().has_value() == true );
                        AND_THEN( "The refrence's value is equal to the test random number + 1, and the borrower's value" ) {
                            REQUIRE( ( *topLevelRefrence ) == ( testNumber + 1 ) );
                            REQUIRE( ( *topLevelRefrence ) == ( testBorrower.Refer().value() ) );
                        }
                    }
                }
            }
        }
    }
    SECTION( "Get refrence from borrower, pass refrence to function, inspect, pass & inspect modify & inspect, then inspect again on outer scope, pass borrower to read inspect modify inspect as well" )
    {
        GIVEN( "A referable borrower, a refrence, and a random number" )
        {
            int testNumber = RandomNumber();
            Borrower< int, true > testBorrower = Borrow< int >( testNumber ).ReferableBorrower();
            Refrence< int > topLevelRefrence = testBorrower.ToRefrence().value();
            REQUIRE( ( *topLevelRefrence ) == testNumber );
            WHEN( "The refrence is passed and the value is modified" )
            {
                RefrenceInspectModifyInspect( topLevelRefrence, testNumber );
                THEN( "The borrower is passed and value the modified" )
                {
                    ReferableBorrowerInspectModifyInspectReturn( std::move( testBorrower ), testNumber + 1 );
                    AND_THEN( "The borrower should no longer be able to produce a refrence or refer tot he value." ) {
                        REQUIRE( testBorrower.Refer().has_value() == false );
                        REQUIRE( testBorrower.ToRefrence().has_value() == false );
                    }
                }
            }
        }
    }
    SECTION( "Get refrence from borrower, pass refrence to function, inspect, pass & inspect modify & inspect, then inspect again on outer scope, pass borrower to read inspect modify inspect as well, then return and assign" )
    {
        GIVEN( "A referable borrower, a refrence, and a random number" )
        {
            int testNumber = RandomNumber();
            Borrower< int, true > testBorrower = Borrow< int >( testNumber ).ReferableBorrower();
            Refrence< int > topLevelRefrence = testBorrower.ToRefrence().value();
            REQUIRE( ( *topLevelRefrence ) == testNumber );
            WHEN( "The refrence and borrower are passed and the value is modified and a borrower is returned and assigned" )
            {
                RefrenceInspectModifyInspect( topLevelRefrence, testNumber );
                auto newBorrower = ReferableBorrowerInspectModifyInspectReturn( std::move( testBorrower ), testNumber + 1 );
                RefrenceInspectModifyInspect( topLevelRefrence, testNumber + 2 );
                THEN( "The refrence should be the same as the test random integer + 3, the original brorrow should no longer "
                        "hold a value and should no longer produce refrences." )
                {
                    REQUIRE( ( *topLevelRefrence ) == ( testNumber + 3 ) );
                    REQUIRE( testBorrower.Refer().has_value() == false );
                    REQUIRE( testBorrower.ToRefrence().has_value() == false );
                    AND_THEN( "The new borrower should hold the value, and be able to produce refrences, the new borrower "
                            "should hold the same value as the refrence." )
                    {
                        REQUIRE( newBorrower.Refer().has_value() == true );
                        REQUIRE( newBorrower.ToRefrence().has_value() == true );
                        REQUIRE( ( newBorrower.Refer().value().get() ) == ( *topLevelRefrence ) );
                        GIVEN( "Another refrence" )
                        {
                            Refrence< int > newRefrence = topLevelRefrence;
                            WHEN( "That refrence is assigned to the original and the value is incremented" )
                            {
                                ++( *newRefrence );
                                THEN( "The value of both refrences should equal eachother" ) {
                                    REQUIRE( *newRefrence  == *topLevelRefrence );
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

