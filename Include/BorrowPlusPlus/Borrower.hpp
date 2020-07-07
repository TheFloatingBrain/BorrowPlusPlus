#ifdef USE_BORROWERS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
    #include <BorrowPlusPlus/Prelude.hpp>
    #ifndef BORROWER_HEADER_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
        #define BORROWER_HEADER_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
        #include <optional>
        #include <functional>
        namespace BorrowPlusPlus
        {
            #define BORROWER_COMMON_PROTECTED_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8 \
                    constexpr Borrower( DATA_TYPE* data_ ) : data( data_ ), owns( true ) {} \
                    DATA_TYPE* data; \
                    bool owns;
            #define BORROWER_COMMON_PUBLIC_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8 \
                    constexpr Borrower() = delete; \
                    constexpr Borrower( const THIS_TYPE& other ) = delete; \
                    constexpr Borrower( const THIS_TYPE&& other ) : data( other.data ), owns( other.owns ) { \
                        const THIS_TYPE& leftValue = other; \
                        ( ( THIS_TYPE& ) other ).owns = false; \
                    } \
                    ~Borrower() { \
                        if( owns == true ) \
                            delete data; \
                    } \
                    constexpr std::optional< std::reference_wrapper< DATA_TYPE > > Refer() { \
                        if( owns == false ) \
                            return std::nullopt; \
                        return std::optional< std::reference_wrapper< DATA_TYPE > >{ *data }; \
                    } \
                    constexpr std::optional< std::reference_wrapper< DATA_TYPE > > operator*() { \
                        return Refer(); \
                    } \
                    BORROW_PLUS_PLUS_CORE_ASSIGNMENT_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( = delete; ) \
                    friend class Detail::BorrowBase< DATA_TYPE >; \
                    friend class Refrence< DATA_TYPE >;


            template< typename DATA_TYPE, bool REFERABLE_CONSTANT = false >
            struct Borrower
            {
                using THIS_TYPE = Borrower< DATA_TYPE, false >;
                BORROWER_COMMON_PUBLIC_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
                protected: 
                    BORROWER_COMMON_PROTECTED_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
            };
            
            template< typename DATA_TYPE >
            struct Borrower< DATA_TYPE, true >
            {
                using THIS_TYPE = Borrower< DATA_TYPE, true >;
                constexpr std::optional< Refrence< DATA_TYPE > > ToRefrence()
                {
                    if( owns == true ) {
                        return std::optional< Refrence< DATA_TYPE > >{
                            Refrence< DATA_TYPE >{ *this } };
                    }
                    return std::nullopt;
                }
                constexpr operator std::optional< Refrence< DATA_TYPE > >() {
                    return ToRefrence();
                }
                BORROWER_COMMON_PUBLIC_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
                protected: 
                    BORROWER_COMMON_PROTECTED_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
            };
        }
    #endif
#endif
