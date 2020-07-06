#include <iostream>
#include <chrono>
#include <random>
#define USE_BORROWERS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
#include <BorrowPlusPlus/Borrow.hpp>
#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

using namespace BorrowPlusPlus;


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

TEST_CASE( "Test boxes", "[box]" )
{
    SECTION( "Create a box and store a random number" ) {
        Box< int > box = Borrow< int >{ RandomNumber() };
    }
    SECTION( "Create a box and pass it to a function, then inspact that value" )
    {
        int testValue = RandomNumber();
        Box< int > box = Borrow< int >{ testValue };
        BoxInspect( std::move( box ), testValue );
    }
    SECTION( "Create a box and pass it to a function & a refrence, then inspect that value" )
    {
        GIVEN( "A box, a refrence and a random test value" )
        {
            int testValue = RandomNumber();
            Box< int > box = Borrow< int >{ testValue };
            Refrence< int > testRefrence = box;
            WHEN( "The refrence is passed to inspecting functions" )
            {
                REQUIRE( *box == testValue );
                REQUIRE( *testRefrence == testValue );
                RefrenceInspect( testRefrence, testValue + 1 );
                THEN( "The box's value should equal the test value and the refrence's value" ) {
                    REQUIRE( *box == testValue );
                    REQUIRE( *testRefrence == *box );
                }
            }
        }
    }
    SECTION( "Create a box and pass it to a function, then inspact, modify, and inspect that value" )
    {
        GIVEN( "A box, a refrence and a random test value" )
        {
            int testValue = RandomNumber();
            Box< int > box = Borrow< int >{ testValue };
            WHEN( "The box's value equals the random value" )
            {
                REQUIRE( *box == testValue );
                THEN( "The box is passed to a function, then inspect, modify, and inspect it's value without returning" ) {
                    BoxInespectModifyInspect( std::move( box ), testValue );
                }
            }
        }                
    }
    SECTION( "Create a box and a refrence and pass them to a function, then inspact, modify, and inspect the value" )
    {
        GIVEN( "A box, a refrence and a random test value" )
        {
            int testValue = RandomNumber();
            Box< int > box = Borrow< int >{ testValue };
            Refrence< int > testRefrence = box;
            WHEN( "The box & the refrence are passed to inspect, modify, inspect functions without returning" )
            {
                REQUIRE( *box == testValue );
                REQUIRE( *testRefrence == testValue );
                RefrenceInspectModifyInspect( testRefrence, testValue );
                THEN( "The box's value should equal the test value + 1 and the refrence's value" ) {
                    REQUIRE( *box == ( testValue + 1 ) );
                    REQUIRE( *testRefrence == *box );
                }
            }
        }
    }
    SECTION( "Create a box and a refrence and pass them to a function, then inspact, modify, and inspect the value, then return but dont assign" )
    {
        GIVEN( "A box, a refrence and a random test value" )
        {
            int testValue = RandomNumber();
            Box< int > box = Borrow< int >{ testValue };
            Refrence< int > testRefrence = box;
            WHEN( "The box & the refrence are passed to inspect, modify, inspect functions, returning but not assigning" )
            {
                REQUIRE( *box == testValue );
                REQUIRE( *testRefrence == testValue );
                RefrenceInspectModifyInspectReturn( testRefrence, testValue );
                THEN( "The box's value should equal the test value + 1 and the refrence's value" ) {
                    REQUIRE( *box == ( testValue + 1 ) );
                    REQUIRE( *testRefrence == *box );
                }
            }
        }
    }
    SECTION( "Create a box and a refrence and pass them to a function, then inspact, modify, and inspect the value, then returning and assigning" )
    {
        GIVEN( "A box, a refrence and a random test value" )
        {
            int testValue = RandomNumber();
            Box< int > box = Borrow< int >{ testValue };
            Refrence< int > testRefrence = box;
            WHEN( "The box & the refrence are passed to inspect, modify, inspect functions, returning and assigning to new refrences" )
            {
                REQUIRE( *box == testValue );
                REQUIRE( *testRefrence == testValue );
                Box< int > newBox = BoxInespectModifyInspectReturn( std::move( box ), testValue );
                Refrence< int > newRefrence = RefrenceInspectModifyInspectReturn( testRefrence, testValue + 1 );
                THEN( "The box's value should equal the test value + 2 and the refrence's value" )
                {
                    REQUIRE( *box == ( testValue + 2 ) );
                    REQUIRE( *testRefrence == *box );
                    AND_THEN( "The box's value should equal the new box's value and the new refrenc's value, everything should destruct successfully" ) {
                        REQUIRE( *box == *newBox );
                        REQUIRE( *box == *testRefrence );
                    }
                }
            }
        }
    }
    SECTION( "Parallel boxes" )
    {
        GIVEN( "A box, a random test value, and a second box constructed from the first in the same scope" )
        {
            int testValue = RandomNumber();
            Box< int > box = Borrow< int >{ testValue };
            Box< int > secondBox = std::move( box );
            WHEN( "One box is passed to a function" )
            {
                REQUIRE( *box == testValue );
                REQUIRE( *secondBox == testValue );
                RefrenceInspectModifyInspect( box, testValue );
                THEN( "The box's value should equal the test value + 1 and the other box's value" ) {
                    REQUIRE( *box == ( testValue + 1 ) );
                    REQUIRE( *secondBox == *box );
                }
            }
        }
    }
    SECTION( "Three boxes" )
    {
        GIVEN( "A box, a random test value, and a second & third box constructed from the first in the same scope" )
        {
            int testValue = RandomNumber();
            Box< int > box = Borrow< int >{ testValue };
            Box< int > secondBox = std::move( box );
            Box< int > thirdBox = std::move( box );
            WHEN( "One box is passed to a function" )
            {
                REQUIRE( *box == testValue );
                REQUIRE( *secondBox == testValue );
                RefrenceInspectModifyInspect( thirdBox, testValue );
                THEN( "The box's value should equal the test value + 1 and the other boxs' values" )
                {
                    REQUIRE( *box == ( testValue + 1 ) );
                    REQUIRE( *secondBox == *box );
                    REQUIRE( *thirdBox == *secondBox );
                    ++*thirdBox;
                    REQUIRE( *thirdBox == *secondBox );
                    ++*secondBox;
                    REQUIRE( *thirdBox == *secondBox );
                }
            }
        }
    }
    SECTION( "Returned fourth box boxes" )
    {
        GIVEN( "A box, a random test value, and a second box constructed from the first in the same scope and a third constructed from one of the others in a second scope" )
        {
            int testValue = RandomNumber();
            Box< int > box = Borrow< int >{ testValue };
            Box< int > secondBox = std::move( box );
            WHEN( "One box is passed to a function returning but not assigning a box" )
            {
                Box< int > thirdBox = std::move( box );
                REQUIRE( *box == testValue );
                REQUIRE( *secondBox == testValue );
                RefrenceInspectModifyInspect( secondBox, testValue );
                THEN( "The box's value should equal the test value + 1 and the other boxs' values" )
                {
                    REQUIRE( *box == ( testValue + 1 ) );
                    REQUIRE( *secondBox == *box );
                    REQUIRE( *thirdBox == *secondBox );
                    ++*thirdBox;
                    REQUIRE( *thirdBox == *secondBox );
                    ++*secondBox;
                    REQUIRE( *thirdBox == *secondBox );
                }
            }
        }
    }
    SECTION( "Returned fourth box boxes" )
    {
        GIVEN( "A box, a random test value, and a second & third box constructed from the first in the same scope" )
        {
            int testValue = RandomNumber();
            Box< int > box = Borrow< int >{ testValue };
            Box< int > secondBox = std::move( box );
            Box< int > thirdBox = std::move( box );
            WHEN( "One box is passed to a function returning a box creating a fourth box" )
            {
                REQUIRE( *box == testValue );
                REQUIRE( *secondBox == testValue );
                auto fourthBox = BoxInespectModifyInspectReturn( std::move( secondBox ), testValue );
                THEN( "The box's value should equal the test value + 1 and the other boxs' values" )
                {
                    REQUIRE( *box == ( testValue + 1 ) );
                    REQUIRE( *secondBox == *box );
                    REQUIRE( *thirdBox == *secondBox );
                    REQUIRE( *fourthBox == *box );
                    ++*secondBox;
                    REQUIRE( *thirdBox == *secondBox );
                    REQUIRE( *thirdBox == *fourthBox );
                    ++*fourthBox;
                    REQUIRE( *thirdBox == *secondBox );
                    REQUIRE( *thirdBox == *fourthBox );
                    REQUIRE( *fourthBox == *box );
                    ++*thirdBox;
                    REQUIRE( *thirdBox == *box );
                    REQUIRE( *fourthBox == *box );
                }
            }
        }
    }
}
