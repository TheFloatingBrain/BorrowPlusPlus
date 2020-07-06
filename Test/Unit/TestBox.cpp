#include <BorrowPlusPlus/Test/Unit/CommonProcedures.hpp>
#include <catch/catch.hpp>
using namespace BorrowPlusPlus;
using namespace BorrowPlusPlus::Test;

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
/*    SECTION( "Create a box and pass it to a function & a refrence, then inspect that value" )
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
    }*/
}
