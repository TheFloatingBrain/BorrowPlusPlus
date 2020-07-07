#include <BorrowPlusPlus/Prelude.hpp>
#include <BorrowPlusPlus/Box.hpp>
#include <BorrowPlusPlus/Borrower.hpp>

#ifndef REFRENCE_HEADER_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
    #define REFRENCE_HEADER_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
    namespace BorrowPlusPlus
    {
        template< typename DATA_TYPE >
        struct Refrence
        {
            using THIS_TYPE = Refrence< DATA_TYPE >;
            //No floating pointers. This may become optional later, see "Goals".//
            constexpr Refrence( const THIS_TYPE& other ) : data( other.data ) {}
            constexpr Refrence( const THIS_TYPE&& other ) : data( other.data ) {};
            constexpr Refrence( const Box< DATA_TYPE >& other ) : data( other.data ) {}
            constexpr Refrence( const Box< DATA_TYPE >&& other ) = delete;
            #ifdef USE_BORROWERS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
                constexpr Refrence( const Borrower< DATA_TYPE, true >& other ) : data( other.data ) {}
                constexpr Refrence( const Borrower< DATA_TYPE, true >&& other )  = delete;
            #endif
            BORROW_PLUS_PLUS_CORE_ASSIGNMENT_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( { return RefrenceAssign( other ); } )
            BORROW_PLUS_PLUS_CORE_REFRENCE_OPERATORS_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
            #define NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_FOR_TYPE_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( FROM_TYPE_PARAMETER, ... ) \
                NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( FROM_TYPE_PARAMETER, /**/, __VA_ARGS__ ) \
                NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( FROM_TYPE_PARAMETER, &, __VA_ARGS__ ) \
                NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( FROM_TYPE_PARAMETER, &&, __VA_ARGS__ ) \

            #define NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( FROM_TYPE_PARAMETER, MODIFIER_PARAMETER, ... ) \
                constexpr THIS_TYPE& RefrenceAssign( const FROM_TYPE_PARAMETER< __VA_ARGS__ > MODIFIER_PARAMETER other ) { \
                    data = other.data; \
                    return *this; \
                }
            

            friend class Box< DATA_TYPE >;
            NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_FOR_TYPE_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( Refrence, DATA_TYPE )
            NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_FOR_TYPE_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( Box, DATA_TYPE )
            #ifdef USE_BORROWERS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
                NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_FOR_TYPE_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( Borrower, DATA_TYPE, true )
                friend class Borrower< DATA_TYPE, true >;
            #endif
            protected: 
                constexpr Refrence() {}
                constexpr Refrence( DATA_TYPE* data_ ) : data( data_ ) {}
                DATA_TYPE* data;
        };
    }
    #ifdef SHORT_NAMES_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
        template< typename DATA_TYPE >
        using Ref< DATA_TYPE >= Refrence< DATA_TYPE >;
    #endif
#endif
