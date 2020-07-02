/*****************************************************************************
* Goals: *********************************************************************
*     * : Add global allocation pool *****************************************
*     * : Use pointer-to-pointer types to allow ******************************
*             for ubiquitous nullification, nullable/unnullable semantics ****
*             patial optional manual memory managment, future garbage ********
*             collector. *****************************************************
*     * : Optional garbage collector. ****************************************
*     X : Fix the one foot-gun (the move semantics) that exists **************
*             in this library. This may be able to be done via template ******
*             specialization, instantiating owning/non-owning Boxes. I *******
*             credit https://github.com/ZisIsNotZis/cppBorrow by ZisIsNotZis *
*             with that idea. Im basically adding implicit value semantics ***
*             and garbage collection to his idea. ****************************
*     * : Allow for thread safe or atomic storage. ***************************
*     * : Allow for contiguous storage (array/buffer allocation). ************
*     * : Add stack/compile time allocator. **********************************
*     * : Fix the one foot gun where it someone can write Box< DATA_TYPE > ***
*             instead of OWNED_BOX< DATA_TYPE > when returning from a ********
*             function. ******************************************************
*     * : Make borrwing allocator aware. *************************************
*     * : Make garbage collection allocator aware. ***************************
*****************************************************************************/

/*********************************************************************************
* Background: I created U.C.C (Universal C/C++ Compiler) over seven years ago ***
* https://github.com/TheFloatingBrain/UCC-UniversalCPPCompiler ******************
* and ever since then I had thought about implementing its borrow semantics as **
* a library. I thought for a while that borrow was a flawed model and smart *****
* pointers had taken over anyway, but with the rise of Swift, Rust, and Kotlin **
* as well as constexpr or constexpr like things in multiple languages I thought *
* I might give this a shot. I think potentially that having the compiler ********
* integration with little to no overhead is better, especially since it is ******
* portable as a source-to-source compiler, but I think this may be a worth ******
* while effort given I think this can be more efficent (due to not refrence *****
* counting *and possibly easier to use than standard smart poitners, if not *****
* just to get it off my mind. I am taking a different approch (including the ****
* use of value semantics) but please take a look at *****************************
* https://github.com/ZisIsNotZis/cppBorrow as well! As ZisIsNotZis has done *****
* a great job and I "borrowed" (heh') a few ideas from there. *******************
********************************************************************************/


#define BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8

#ifdef BORROW_PLUS_PLUS_ENABLE_ATOMIC_MEMORY_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
    #include <atomic>
#endif

namespace BorrowPlusPlus
{
    enum class Owner : bool {
        OWNER_ENUMERATION = true, 
        NOT_OWNER_ENUMERATION = false
    };

    namespace Detail {
        template< typename DATA_TYPE >
        struct BorrowBase;
    }

    template< typename DATA_TYPE >
    class Refrence;

    template< typename DATA_TYPE, bool OWNS_CONSTANT >
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
        constexpr THIS_TYPE& operator=( const Refrence< DATA_TYPE >&& other ) OPERATOR_EQUALS_BODY_PARAMETER //\
        /**************************************************************************************************/ \
        /*constexpr THIS_TYPE& operator=( const Borrower< DATA_TYPE >& other ) OPERATOR_EQUALS_BODY_PARAMETER \
        constexpr THIS_TYPE& operator=( Borrower< DATA_TYPE >& other ) OPERATOR_EQUALS_BODY_PARAMETER \
        constexpr THIS_TYPE& operator=( Borrower< DATA_TYPE > other ) OPERATOR_EQUALS_BODY_PARAMETER \
        constexpr THIS_TYPE& operator=( Borrower< DATA_TYPE >&& other ) OPERATOR_EQUALS_BODY_PARAMETER \
        constexpr THIS_TYPE& operator=( const Borrower< DATA_TYPE >&& other ) OPERATOR_EQUALS_BODY_PARAMETER*/

    template< typename DATA_TYPE >
    struct Box
    {
        using THIS_TYPE = Box< DATA_TYPE >;
        //No floating pointers. This may become optional later, see "Goals".//
        constexpr Box() = delete;
        constexpr Box( const THIS_TYPE& other ) = delete;
        constexpr Box( const THIS_TYPE&& other ) : data( other.data ), passed( false ) {
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
            return Refrence< DATA_TYPE >{ *this };
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

    template< typename DATA_TYPE >
    struct BorrowPointer;

    template< typename DATA_TYPE, bool OWNS_CONSTANT = true >
    struct Borrower
    {
        using THIS_TYPE = Borrower< DATA_TYPE >;
        constexpr Borrower() = delete;
        constexpr Borrower( const THIS_TYPE& other ) = delete;
        constexpr Borrower( const THIS_TYPE&& other ) : data( other.data ), owns( true ) {
            const THIS_TYPE& leftValue = other;
            other.owns = false;
        }
        ~Borrower() {
            if( owns == true )
                delete data;
        }

        constexpr DATA_TYPE& operator*()
        {
            static_assert( owns == true, 
                    "Borrow++::Error::Borrower::DATA_TYPE& operator*(): Attempt to refrence data "
                    "when borrower doesent own the data.\n" );
            return *data;
        }
        constexpr DATA_TYPE* operator->()
        {
            static_assert( owns == true, 
                    "Borrow++::Error::Borrower::DATA_TYPE& operator->(): Attempt to refrence data "
                    "when borrower doesent own the data.\n" );
            return data;
        }

        constexpr operator Refrence< DATA_TYPE >()
        {
            static_assert( owns == true, 
                    "Borrow++::Error::Borrower::operator Refrence(): Attempt to refrence data "
                    "when borrower doesent own the data.\n" );
            return Refrence< DATA_TYPE >{ *this };
        }

        BORROW_PLUS_PLUS_CORE_ASSIGNMENT_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( = delete; )

        friend class Detail::BorrowBase< DATA_TYPE >;
        friend class Refrence< DATA_TYPE >;
        friend class BorrowPointer< DATA_TYPE >;
        protected: 
            constexpr Borrower( DATA_TYPE* data_ ) : data( data_ ) {}
            Borrower( const THIS_TYPE& other ) : data( other.data ) {}
            DATA_TYPE* data;
    };
    


    template< typename DATA_TYPE >
    struct Borrower< DATA_TYPE, false >
    {
        using THIS_TYPE = Borrower< DATA_TYPE, false >;
        constexpr DATA_TYPE* operator*()
        {
            static_assert( false, "Borrow++::Error::Borrower::DATA_TYPE& operator*(): Attempt to refrence data "
                    "when borrower doesent own the data.\n" );
            return nullptr;
        }
        constexpr DATA_TYPE* operator->()
        {
            static_assert( false, "Borrow++::Error::Borrower::DATA_TYPE& operator->(): Attempt to refrence data "
                    "when borrower doesent own the data.\n" );
            return nullptr;
        }

        constexpr operator Refrence< DATA_TYPE >()
        {
            static_assert( false, "Borrow++::Error::Borrower::operator Refrence(): Attempt to refrence data "
                    "when borrower doesent own the data.\n" );
            return Refrence< DATA_TYPE >{};
        }
        BORROW_PLUS_PLUS_CORE_ASSIGNMENT_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( = delete; )
        friend class BorrowPointer< DATA_TYPE >;
        protected: 
            constexpr Borrower() {}
            constexpr Borrower( Borrower< DATA_TYPE, false >& other ) {}
    };

    template< typename DATA_TYPE >
    struct BorrowPointer
    {
        constexpr DATA_TYPE& operator*()
        {
            if( owns == true ) {
                std::cout << "A\n";
                return borrower.operator*();
            }
            std::cout << "B\n";
            return *errorGenerator.operator*();
        }
        constexpr DATA_TYPE* operator->()
        {
            if( owns == true )
                return borrower.operator->();
            return errorGenerator.operator*();
        }

        constexpr operator Refrence< DATA_TYPE >()
        {
            if( owns == true )
                return borrower.operator Refrence< DATA_TYPE >();
            return errorGenerator.operator Refrence< DATA_TYPE >();
        }
        //protected: 
            constexpr BorrowPointer( Borrower< DATA_TYPE, true > borrower_ ) : borrower( borrower_ ), owns( true ) {}
            Borrower< DATA_TYPE, true > borrower;
            Borrower< DATA_TYPE, false > errorGenerator;
            bool owns;
    };

    template< typename DATA_TYPE >
    struct Refrence
    {
        using THIS_TYPE = Refrence< DATA_TYPE >;
        //No floating pointers. This may become optional later, see "Goals".//
        constexpr Refrence( const THIS_TYPE& other ) : data( other.data ) {}
        constexpr Refrence( const THIS_TYPE&& other ) : data( other.data ) {};
        constexpr Refrence( const Box< DATA_TYPE >& other ) : data( other.data ) {}
        constexpr Refrence( const Box< DATA_TYPE >&& other ) : data( other.data ) {}
        constexpr Refrence( const Borrower< DATA_TYPE >& other ) : data( other.data ) {}
        constexpr Refrence( const Borrower< DATA_TYPE >&& other ) : data( other.data ) {}
        BORROW_PLUS_PLUS_CORE_ASSIGNMENT_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( { return RefrenceAssign( other ); } )
        BORROW_PLUS_PLUS_CORE_REFRENCE_OPERATORS_COMMON_DEFINITIONS_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
        #define NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_FOR_TYPE_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( FROM_TYPE_PARAMETER ) \
            NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( FROM_TYPE_PARAMETER, /**/ ) \
            NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( FROM_TYPE_PARAMETER, & ) \
            NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( FROM_TYPE_PARAMETER, && ) \

        #define NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( FROM_TYPE_PARAMETER, MODIFIER_PARAMETER ) \
            constexpr THIS_TYPE& RefrenceAssign( const FROM_TYPE_PARAMETER MODIFIER_PARAMETER other ) { \
                data = other.data; \
                return *this; \
            }
        
        NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_FOR_TYPE_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( Refrence< DATA_TYPE > )
        NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_FOR_TYPE_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( Box< DATA_TYPE > )
        NAMESPACE_BORROW_CLASS_REFRENCE_REFRENCE_ASSIGN_FOR_TYPE_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8( Borrower< DATA_TYPE > )

        friend class Box< DATA_TYPE >;
        friend class Borrower< DATA_TYPE, true >;
        friend class Borrower< DATA_TYPE, false >;
        protected: 
            constexpr Refrence() {}
            DATA_TYPE* data;
    };

    #ifdef SHORT_NAMES_BORROW_PLUS_PLUS_GUID_eb68f065_567d_437b_9373_9fa3e17e65a8
        template< typename DATA_TYPE >
        using Ref< DATA_TYPE >= Refrence< DATA_TYPE >;
    #endif
    
    namespace Detail
    {
        template< typename DATA_TYPE >
        struct BorrowBase
        {
            constexpr auto ConstructBox( DATA_TYPE* data ) {
                return Box< DATA_TYPE >{ data };       
            }
            constexpr auto ConstructBorrower( DATA_TYPE* data ) {
                return Borrower< DATA_TYPE, true >{ data };       
            }
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
        constexpr operator Borrower< DATA_TYPE >() {
            return this->ConstructBorrower( data );
        }
    };
}

