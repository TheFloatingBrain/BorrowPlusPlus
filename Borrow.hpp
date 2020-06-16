/*****************************************************************************
* Goals: *********************************************************************
*     * : Add global allocation pool *****************************************
*     * : Use pointer-to-pointer types to allow ******************************
*             for ubiquitous nullification, nullable/unnullable semantics ****
*             patial optional manual memory managment, future garbage ********
*             collector. *****************************************************
*     * : Optional garbage collector. ****************************************
*     * : Fix the one foot-gun (the move semantics) that exists **************
*             in this library. This may be able to be done via template ******
*             specialization, instantiating owning/non-owning Boxes. I *******
*             credit https://github.com/ZisIsNotZis/cppBorrow by ZisIsNotZis *
*             with that idea. Im basically adding implicit value semantics ***
*             and garbage collection to his idea. ****************************
*     * : Allow for thread safe or atomic storage. ***************************
*     * : Allow for contiguous storage (array/buffer allocation). ************
*     * : Add stack/compile time allocator. **********************************
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


#ifdef BORROW_ENABLE_ATOMIC_MEMORY_eb68f065_567d_437b_9373_9fa3e17e65a8
    #include <atomic>
#endif

namespace BorrowBox
{
    template< typename DATA_TYPE, template< typename > class ALLOCATOR_TYPE >
    struct Borrow;

    template< typename DATA_TYPE, template< typename > class ALLOCATOR_TYPE = 
            std::allocator >
    struct Box
    {
        //No floating pointers. This may become optional later, see "Goals".//
        Box() = delete;
        constexpr Box( const Box& other ) : data( other.data ), passed( false ) {
            ( ( Box& ) other ).passed = true;
        }
        constexpr Box( const Box&& other ) : data( other.data ), passed( true ) {}
        ~Box() {
            if( passed == false )
                delete data;
        }
        constexpr DATA_TYPE& operator*() {
            return *data;
        }
        constexpr DATA_TYPE* operator->() {
            return data;
        }
        constexpr Box< DATA_TYPE >& RefrenceAssign( const Box< DATA_TYPE >& other )
        {
            data = other.data;
            other.passed = true;
            passed = false;
            return *this;
        }

        constexpr Box< DATA_TYPE >& operator=( const Box< DATA_TYPE >& other ) {
            return RefrenceAssign( other );
        }

        constexpr Box< DATA_TYPE >& operator=( Box< DATA_TYPE >& other ) {
            return RefrenceAssign( other );
        }

        constexpr Box< DATA_TYPE >& operator=( Box< DATA_TYPE > other ) {
            return RefrenceAssign( other );
        }

        constexpr Box< DATA_TYPE >& operator=( Box< DATA_TYPE >&& other )
        {
            data = other.data;
            other.passed = true;
            passed = true;
            return *this;
        }
        friend class Borrow< DATA_TYPE, ALLOCATOR_TYPE >;
        private: 
            constexpr Box( DATA_TYPE* data_ ) : data( data_ ), passed( false ) {}
            /************************************************
            * TODO: So a nullification will take effect on **
            * all instances, also allows for early deletion.*
            *************************************************/
            //const DATA_TYPE** data;
            DATA_TYPE* data;
            /**************************************************************
            * Essentially if something has been passed then its golden! ***
            * We know we no longer have to worry about it, something can **
            * refrence it and the memory is not orphined. However if ******
            * the memory has not been passed (at least not to another Box)*
            * the memory could be orphined if this Box is deleted. ********
            * 'passed' being set to false is basically ownership. *********
            **************************************************************/
            bool passed = false;
    };

    template< typename DATA_TYPE, template< typename > class ALLOCATOR_TYPE = std::allocator >
    struct Borrow
    {
        DATA_TYPE* data = nullptr;
        constexpr Borrow() : data( new DATA_TYPE ) {};
        template< typename... ARGUMENT_TYPES >
        constexpr Borrow( ARGUMENT_TYPES... arguments ) : 
                data( new DATA_TYPE( std::forward< ARGUMENT_TYPES >( arguments )... ) ) {}
        friend class Box< DATA_TYPE >;
        constexpr operator Box< DATA_TYPE >() {
            return Box< DATA_TYPE >( data );
        }
    };
}

