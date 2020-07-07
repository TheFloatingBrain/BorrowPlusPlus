#include <BorrowPlusPlus/Prelude.hpp>

#ifndef BOX_HEADER_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
    #define BOX_HEADER_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
    namespace BorrowPlusPlus
    {
        template< typename DATA_TYPE >
        struct Box
        {
            using THIS_TYPE = Box< DATA_TYPE >;
            //No floating pointers. This may become optional later, see "Goals".//
            constexpr Box() = delete;
            constexpr Box( const THIS_TYPE& other ) = delete;
            constexpr Box( const THIS_TYPE&& other ) : data( other.data ), passed( other.passed ) {
                const Box& leftValue = other;
                ( ( Box& ) leftValue ).passed = true;
            }
            ~Box() {
                if( passed == false )
                    delete data;
            }
            BORROW_PLUS_PLUS_CORE_ASSIGNMENT_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( = delete; )

            BORROW_PLUS_PLUS_CORE_REFRENCE_OPERATORS_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8

            constexpr operator Refrence< DATA_TYPE >() {
                return Refrence< DATA_TYPE >{ data };
            }

            friend class Detail::BorrowBase< DATA_TYPE >;
            friend class Refrence< DATA_TYPE >;
            protected: 
                constexpr Box( DATA_TYPE* data_ ) : data( data_ ), passed( false ) {}
                /************************************************
                * TODO: So a nullification will take effect on **
                * all instances, also allows for early deletion.*
                *************************************************/
                //const DATA_TYPE** data;
                DATA_TYPE* data;
                /**************************************************************
                * Essentially given that we can not change the value of the ***
                * pointer (not the object the pointer contains -- the pointer *
                * if something has been passed then its golden! ***************
                * We know we no longer have to worry about it, something can **
                * refrence it and the memory is not orphined. However if ******
                * the memory has not been passed (at least not to another Box)*
                * the memory could be orphined if this Box is deleted. ********
                * 'passed' being set to false is basically ownership. *********
                **************************************************************/
                bool passed = false;
        };
    }
#endif
