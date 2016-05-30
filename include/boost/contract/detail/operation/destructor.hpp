
#ifndef BOOST_CONTRACT_DETAIL_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DETAIL_DESTRUCTOR_HPP_

// Copyright (C) 2008-2016 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/core/exception.hpp>
#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/condition/check_pre_post_inv.hpp>
#include <boost/contract/detail/none.hpp>
#if !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #include <boost/contract/detail/check_guard.hpp>
#endif
#if !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
        !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
    #include <boost/config.hpp>
    #include <exception>
#endif

namespace boost { namespace contract { namespace detail {

// Dtor subcontracting impl via C++ obj destruction mechanism.
template<class C>
class destructor :
        public check_pre_post_inv</* VR = */ none, C> { // Non-copyable base.
public:
    explicit destructor(C* obj) : check_pre_post_inv</* VR = */ none, C>(
            boost::contract::from_destructor, obj) {}

private:
    #if !defined(BOOST_CONTRACT_NO_ENTRY_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
        void init() /* override */ {
            if(check_guard::checking()) return;

            #ifndef BOOST_CONTRACT_NO_ENTRY_INVARIANTS
                {
                    check_guard checking;
                    // Obj exists (before dtor body), check static and non- inv.
                    this->check_entry_all_inv();
                    // Dtor cannot have pre because it has no parameters.
                }
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                this->copy_old();
            #endif
        }
    #endif
    
public:
    #if !defined(BOOST_CONTRACT_NO_EXIT_INVARIANTS) || \
            !defined(BOOST_CONTRACT_NO_POSTCONDITIONS)
        ~destructor() BOOST_NOEXCEPT_IF(false) {
            this->assert_guarded();
            if(check_guard::checking()) return;
            check_guard checking;

            // If dtor body threw, obj still exists so check subcontracted
            // static and non- inv (but no post because of throw). Otherwise,
            // obj destructed so check static inv and post (even if there is no
            // obj after dtor body, this library allows dtor post, for example
            // to check static members for an instance counter class).
            // NOTE: In theory C++ destructors should not throw, but the
            // language allows for that (even if in C++11 dtors declarations are
            // implicitly noexcept(true) unless specified otherwise) so this
            // library must handle such a case.
            bool body_threw = std::uncaught_exception();
            
            #ifndef BOOST_CONTRACT_NO_EXIT_INVARIANTS
                if(body_threw) this->check_exit_all_inv();
                else this->check_exit_static_inv();
            #endif
            #ifndef BOOST_CONTRACT_NO_POSTCONDITIONS
                if(!body_threw) this->check_post(none());
            #endif
        }
    #endif
};

} } } // namespace

#endif // #include guard

