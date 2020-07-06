#ifndef BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
    #define BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
#endif
#ifndef PRELUDE_HEADER_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
    #define PRELUDE_HEADER_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
    namespace BorrowPlusPlus
    {
        namespace Detail {
            template< typename DATA_TYPE >
            struct BorrowBase;
        }

        template< typename DATA_TYPE >
        class Refrence;

        template< typename DATA_TYPE, bool REFERABLE_CONSTANT >
        class Borrower;

        #define BORROW_PLUS_PLUS_CORE_REFRENCE_OPERATORS_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8 \
            constexpr DATA_TYPE& operator*() { \
                return *data; \
            } \
            constexpr DATA_TYPE* operator->() { \
                return data; \
            }
        #define BORROW_PLUS_PLUS_CORE_ASSIGNMENT_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( OPERATOR_EQUALS_BODY_PARAMETER ) \
            constexpr THIS_TYPE& operator=( const Box< DATA_TYPE >& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Box< DATA_TYPE >& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Box< DATA_TYPE > other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Box< DATA_TYPE >&& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( const Box< DATA_TYPE >&& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            /**************************************************************************************************/ \
            constexpr THIS_TYPE& operator=( const Refrence< DATA_TYPE >& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Refrence< DATA_TYPE >& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Refrence< DATA_TYPE > other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Refrence< DATA_TYPE >&& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( const Refrence< DATA_TYPE >&& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            /**************************************************************************************************/ \
            constexpr THIS_TYPE& operator=( const Borrower< DATA_TYPE, false >& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Borrower< DATA_TYPE, false >& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Borrower< DATA_TYPE, false > other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Borrower< DATA_TYPE, false >&& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( const Borrower< DATA_TYPE, false >&& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            /**************************************************************************************************/ \
            constexpr THIS_TYPE& operator=( const Borrower< DATA_TYPE, true >& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Borrower< DATA_TYPE, true >& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Borrower< DATA_TYPE, true > other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( Borrower< DATA_TYPE, true >&& other ) OPERATOR_EQUALS_BODY_PARAMETER \
            constexpr THIS_TYPE& operator=( const Borrower< DATA_TYPE, true >&& other ) OPERATOR_EQUALS_BODY_PARAMETER
    }
#endif
