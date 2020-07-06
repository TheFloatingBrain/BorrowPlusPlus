#include <BorrowPlusPlus/Box.hpp>
#include <BorrowPlusPlus/Refrence.hpp>
#include <BorrowPlusPlus/Borrower.hpp>

#ifdef BORROW_PLUS_PLUS_ENABLE_ATOMIC_MEMORY_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
    #include <atomic>
#endif

namespace BorrowPlusPlus
{
    namespace Detail
    {
        template< typename DATA_TYPE >
        struct BorrowBase
        {
            constexpr auto ConstructBox( DATA_TYPE* data ) {
                return Box< DATA_TYPE >{ data };       
            }
            #ifdef USE_BORROWERS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
                template< bool REFERABLE_CONSTANT >
                constexpr auto ConstructBorrower( DATA_TYPE* data ) {
                    return Borrower< DATA_TYPE, REFERABLE_CONSTANT >{ data };       
                }
            #endif
        };
    }

    template< typename DATA_TYPE, template< typename > class ALLOCATOR_TYPE = std::allocator >
    struct Borrow : public Detail::BorrowBase< DATA_TYPE >
    {
        DATA_TYPE* data = nullptr;
        constexpr Borrow() : data( new DATA_TYPE ) {};
        template< typename... ARGUMENT_TYPES >
        constexpr Borrow( ARGUMENT_TYPES... arguments ) {
            data = new DATA_TYPE( std::forward< ARGUMENT_TYPES >( arguments )... );
        }
        constexpr operator Box< DATA_TYPE >() {
            return this->ConstructBox( data );
        }
        #ifdef USE_BORROWERS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
            constexpr operator Borrower< DATA_TYPE, false >() {
                return this->template ConstructBorrower< false >( data );
            }
            Borrower< DATA_TYPE, true > ReferableBorrower() {
                return this->template ConstructBorrower< true >( data );
            }
        #endif
    };
}

