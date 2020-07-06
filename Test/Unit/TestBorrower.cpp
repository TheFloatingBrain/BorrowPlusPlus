#include <BorrowPlusPlus/Test/Unit/CommonProcedures.hpp>
#include <catch/catch.hpp>
using namespace BorrowPlusPlus;
using namespace BorrowPlusPlus::Test;

TEST_CASE( "Test non-referable all borrower functions", "[borrower]" )
{
    SECTION( "Constructing/Destructing Borrower" ) {
        Borrower< int > constructedBorrower = Borrow< int >( RandomNumber() );
    }
    SECTION( "Inspecting borrower value" )
    {
            const int RANDOM_NUMBER_CONSTANT = RandomNumber();
            Borrower< const int > testBorrower = Borrow< const int >( RANDOM_NUMBER_CONSTANT );
            REQUIRE( testBorrower.Refer().value() == RANDOM_NUMBER_CONSTANT );
    }
    SECTION( "Passing borrower to a function, inspecting, modifying, then inspecting the value" )
    {
        GIVEN( "Given a borrower and a random value" )
        {
            int testNumber = RandomNumber();
            Borrower< int > testBorrower = Borrow< int >( testNumber );
            WHEN( "The borrower refers to the same value as the random number and that number is accessable" )
            {
                REQUIRE( testBorrower.Refer().has_value() == true );
                REQUIRE( testBorrower.Refer().value() == testNumber );
                THEN( "The borrower  should be able to be passed, and have its value inspected and modified, "
                        "and destruct without error" ) {
                    BorrowerInspectModifyInspect( std::move( testBorrower ), testNumber );
                }
            }
        }
    }
    SECTION( "Pass borrower to a function, inspect value, then try to use afterword without returning" )
    {
        GIVEN( "Given a borrower and a random value" )
        {
            int testNumber = RandomNumber();
            Borrower< int > testBorrower = Borrow< int >( testNumber );
            WHEN( "The borrower refers to the same value as the random number and that number is accessable" )
            {
                REQUIRE( testBorrower.Refer().value() == testNumber );
                THEN( "The borrower  should be able to be passed, and have its value inspected and modified, "
                        "and destruct without error, and the top level borrower should no longer hold a value" ) {
                    BorrowerInspectModifyInspect( std::move( testBorrower ), testNumber );
                    REQUIRE( testBorrower.Refer().has_value() == false );
                }
            }
        }
    }
    SECTION( "Pass borrower to a function, inspect value, pass, inspect, modify, return" )
    {
        GIVEN( "Given a borrower and a random value" )
        {
            int testNumber = RandomNumber();
            Borrower< int > testBorrower = Borrow< int >( testNumber );
            WHEN( "The borrower refers to the same value as the random number and that number is accessable" )
            {
                REQUIRE( testBorrower.Refer().value() == testNumber );
                THEN( "The borrower  should be able to be passed, and have its value inspected and modified, "
                        "and destruct without error, and the top level borrower should no longer hold a value" ) {
                    BorrowerInspectModifyInspectReturn( std::move( testBorrower ), testNumber );
                    REQUIRE( testBorrower.Refer().has_value() == false );
                }
            }
        }

    }
    SECTION( "Pass borrower to a function, inspect value, pass, inspect, modify, return/assign, inspect" )
    {
        GIVEN( "Given a borrower and a random value" )
        {
            int testNumber = RandomNumber();
            Borrower< int > testBorrower = Borrow< int >( testNumber );
            WHEN( "The borrower refers to the same value as the random number and that number is accessable" )
            {
                REQUIRE( testBorrower.Refer().value() == testNumber );
                THEN( "The borrower  should be able to be passed, and have its value inspected and modified, "
                        "and destruct without error, and the top level borrower should no longer hold a value"
                        "however a returned/assigned new borrower should hold a value equal to the original random"
                        "value + 1" )
                {
                    auto newBorrower = BorrowerInspectModifyInspectReturn( std::move( testBorrower ), testNumber );
                    REQUIRE( testBorrower.Refer().has_value() == false );
                    REQUIRE( newBorrower.Refer().has_value() == true );
                    REQUIRE( newBorrower.Refer().value() == ( testNumber + 1 ) );
                }
            }
        }
    }
    SECTION( "Pass borrower to a function, inspect value, pass, inspect, modify, return/assign, inspect, modify, inspect" )
    {
        GIVEN( "Given a borrower and a random value" )
        {
            int testNumber = RandomNumber();
            Borrower< int > testBorrower = Borrow< int >( testNumber );
            WHEN( "The borrower refers to the same value as the random number and that number is accessable" )
            {
                REQUIRE( testBorrower.Refer().value() == testNumber );
                THEN( "The borrower  should be able to be passed, and have its value inspected and modified, "
                        "and destruct without error, and the top level borrower should no longer hold a value" )
                {
                    auto newBorrower = BorrowerInspectModifyInspectReturn( std::move( testBorrower ), testNumber );
                    REQUIRE( testBorrower.Refer().has_value() == false );
                    AND_THEN( "A new borrower should hold the original random value + 1" )
                    {
                        REQUIRE( newBorrower.Refer().has_value() == true );
                        REQUIRE( newBorrower.Refer().value() == ( testNumber + 1 ) );
                        AND_THEN( "The new borrower has its value added too by 2" )
                        {
                            newBorrower.Refer().value() += 2;
                            AND_THEN( "The new borrower's value should be equal to the original test value + 3" ) {
                                REQUIRE( newBorrower.Refer().value() == ( testNumber + 3 ) );
                            }
                        }
                    }
                }
            }
        }
    }
}
