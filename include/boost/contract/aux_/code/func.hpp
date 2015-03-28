
#ifndef BOOST_CONTRACT_AUX_FUNC_HPP_
#define BOOST_CONTRACT_AUX_FUNC_HPP_

#include <boost/contract/ext_/preprocessor/traits/func.hpp> // f
#include <boost/contract/ext_/preprocessor/parenthesize.hpp>

/* PUBLIC */

#define BOOST_CONTRACT_AUX_FUNC_D_R(d, r, id, tpl, f) \
    BOOST_CONTRACT_AUX_NAMED_FUNC_DECL_D_R(d, r, id, tpl, f, \
        BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_OPERATOR_NAME(f)), \
            BOOST_CONTRACT_AUX_FUNC_NAME_ \
        , \
            BOOST_CONTRACT_AUX_FUNC_OPERATOR_ \
        )(f) \
    )

#define BOOST_CONTRACT_AUX_NAMED_FUNC_DECL_D_R(d, r, id, tpl, f, \
        parenthesized_name) \
    BOOST_CONTRACT_AUX_FUNC_DECL_(d, r, id, tpl, f, \
        parenthesized_name, \
        BOOST_CONTRACT_AUX_PARAMS_WITH_DEFAULTS_D_R, BOOST_PP_EMPTY(), \
        (1, 1, 1) \
    )

/* PRIVATE */

#define BOOST_CONTRACT_AUX_FUNC_NAME_(f) \
    (BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_NAME(f))

// Precondition: OPERATOR_NAME(f) != EMPTY().
#define BOOST_CONTRACT_AUX_FUNC_OPERATOR_(f) \
    (operator BOOST_PP_TUPLE_REM_CTOR( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_OPERATOR_NAME(f)))

#define BOOST_CONTRACT_AUX_FUNC_DECL_(d, r, id, tpl, f, parenthesized_name, \
        params_macro, extra_params, access_classifiers_virt) \
    BOOST_CONTRACT_AUX_FUNC_DECL_ARGS_(d, r, id, tpl, f, \
        parenthesized_name, \
        params_macro, extra_params, \
        BOOST_PP_TUPLE_ELEM(3, 0, access_classifiers_virt), \
        BOOST_PP_TUPLE_ELEM(3, 1, access_classifiers_virt), \
        BOOST_PP_TUPLE_ELEM(3, 2, access_classifiers_virt) \
    )

// Name is passed within parenthesis in case it is an operator with commas,
// for example: `operator std::map<U,V>`, `operator,`.
#define BOOST_CONTRACT_AUX_FUNC_DECL_ARGS_(d, r, id, tpl, f, \
    parenthesized_name, \
    params_macro, extra_params, \
    has_access, has_classifiers, has_virtual_specifiers \
) \
    BOOST_PP_IIF(BOOST_PP_COMPL(has_access), \
        BOOST_PP_TUPLE_EAT(1) \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS(f)), \
        BOOST_PP_TUPLE_EAT(1) \
    , \
        BOOST_PP_TUPLE_REM(1) \
    ))(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_ACCESS(f):) \
    BOOST_CONTRACT_EXT_PP_UNPARENTHESIZE( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VERBATIM(f)) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPORT(f) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE(f) \
    BOOST_CONTRACT_EXT_PP_VARIADIC_WRAP_IIF( \
        BOOST_PP_COMPL(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
                BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE(f)) \
    ), \
        <, >, \
        BOOST_CONTRACT_AUX_TEMPLATE_PARAMS_WITH_DEFAULTS_D_R(d, r, id, tpl, \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TEMPLATE_PARAMS(f), \
            BOOST_PP_EMPTY() \
        ) \
    ) \
    BOOST_PP_IIF(has_classifiers, \
        BOOST_CONTRACT_AUX_CLASSIFIERS_ \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(f) \
    BOOST_CONTRACT_EXT_PP_UNPARENTHESIZE( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_RETURN(f)) \
    BOOST_CONTRACT_EXT_PP_UNPARENTHESIZE(parenthesized_name) \
    (params_macro(d, r, id, tpl, BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_PARAMS(f), \
            extra_params)) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_CONST(f) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VOLATILE(f) \
    BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_IS_REF_REF( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF(f)), \
        && \
    , BOOST_PP_IIF(BOOST_CONTRACT_EXT_PP_KEYWORD_IS_REF_FRONT( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_REF(f)), \
        & \
    , \
        BOOST_PP_EMPTY() \
    )) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXCEPT(f) \
    BOOST_PP_EXPR_IIF(BOOST_PP_COMPL(BOOST_CONTRACT_EXT_PP_IS_EMPTY( \
            BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN(f))), \
        -> BOOST_CONTRACT_EXT_PP_UNPARENTHESIZE \
    ) BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_TRAILING_RETURN(f) \
    BOOST_PP_IIF(has_virtual_specifiers, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_FINAL \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(f) \
    BOOST_PP_IIF(has_virtual_specifiers, \
        BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_OVERRIDE \
    , \
        BOOST_PP_TUPLE_EAT(1) \
    )(f)
        
#define BOOST_CONTRACT_AUX_CLASSIFIERS_(f) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_INLINE(f) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_STATIC(f) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXTERN(f) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_EXPLICIT(f) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_VIRTUAL(f) \
    BOOST_CONTRACT_EXT_PP_FUNC_TRAITS_FRIEND(f)

#endif // #include guard

