// -*- C++ -*-
/** @file */ 
#pragma once 

namespace arm_cmsis_dsp {

template< class T >
using remove_constref_t = std::remove_const_t<std::remove_reference_t<T>>;


/** \addtogroup FUSION Abstract syntax tree for fusion
 *  \ingroup DSPPP
 *  @{
 */

template<typename T> struct traits
{
    typedef T Scalar;
#if defined(HAS_VECTOR)
    typedef typename vector_traits<T>::vector Vector;
#endif
};


template<typename M>
struct Complexity
{
   constexpr static int value = 0;
};

/*

For mixed operations with complex / real

*/
template<typename TA,typename TB>
struct MixedRes;

/*

Check if expression is using mixed arithmetic
with complex and real

*/
template<typename TA>
struct IsMixed
{
    constexpr static bool value = false;
};

template<>
struct MixedRes<double,double>
{
   typedef double type;
};

template<>
struct MixedRes<float,float>
{
   typedef float type;
};

#if defined(ARM_FLOAT16_SUPPORTED)
template<>
struct MixedRes<float16_t,float16_t>
{
   typedef float16_t type;
};
#endif

template<>
struct MixedRes<Q31,Q31>
{
   typedef Q31 type;
};

template<>
struct MixedRes<Q15,Q15>
{
   typedef Q15 type;
};

template<>
struct MixedRes<Q7,Q7>
{
   typedef Q7 type;
};

template<typename T>
struct MixedRes<std::complex<T>,std::complex<T>>
{
   typedef std::complex<T> type;
};

template<typename T>
struct MixedRes<std::complex<T>,T>
{
   typedef std::complex<T> type;
};

template<typename T>
struct MixedRes<T,std::complex<T>>
{
   typedef std::complex<T> type;
};




/*

An unregular datatype has different strides like MatrixView
and can only be assigned to a MatrixView using a 2D functions.
So all normal eval functions will reject unregular structures.

*/
template<typename T>
struct HasMatrixIndexing
{
    constexpr static bool value = false;
};

template<typename T>
struct HasStaticStride
{
    constexpr static bool value = false;
};



template<typename T>
struct IsVector
{
    constexpr static bool value = false;
};

template<typename T>
struct IsMatrix
{
    constexpr static bool value = false;
};



template<typename T>
struct StaticLength
{
    constexpr static vector_length_t value = 0;
};

template<typename T>
struct ElementType
{
    typedef T type;
};

template<typename T>
struct IsComplexNumber
{
    constexpr static bool value = false;
};

template<typename T>
struct IsComplexNumber<std::complex<T>>
{
    constexpr static bool value = true;
};

/* Type of elements for a complex number including the real
 * numbers
 */
template<typename T>
struct ComplexNumberType
{
    typedef T type;
};

template<typename T>
struct ComplexNumberType<std::complex<T>>
{
    typedef T type;
};

template<typename T>
struct ComplexNumberType<const std::complex<T>>
{
    typedef const T type;
};


template<typename A,typename B>
using SameElementType=std::is_same<typename ElementType<remove_constref_t<A>>::type,typename ElementType<remove_constref_t<B>>::type>;

/**
 * @brief      Determines if vector datatype supports vector instruction
 *             on a current architecture
 *
 * @tparam     DA    Datatype
 *
 * @return     True if has vector instructions
 */
template<typename DA>
constexpr bool has_vector_inst() {return (vector_traits<typename ElementType<remove_constref_t<DA>>::type>::has_vector);}

/**
 * @brief      Check if predicated instructions are supported
 *
 * @tparam     DA    The datatype
 *
 * @return     True if predicated instructions are supported
 */
template<typename DA>
constexpr bool has_predicate() {return (vector_traits<typename ElementType<remove_constref_t<DA>>::type>::has_predicate);}

/**
 * @brief      Check if expression contains a mix of complex / real operations
 *
 * @tparam     DA    Expression datatype
 *
 * @return     True if mixed, False otherwise.
 */
template<typename DA>
constexpr bool is_mixed() {return IsMixed<DA>::value;}


/**
 * @brief      Check same number of lanes is used
 *
 * @tparam     A     Datatype
 * @tparam     B     Datatype
 *
 * @return     True is same number of lanes for A and B
 */
template<typename A,typename B>
constexpr bool same_nb_lanes() {
    using EA = typename ElementType<remove_constref_t<A>>::type;
    using EB = typename ElementType<remove_constref_t<B>>::type;
    return (vector_traits<EA>::nb_lanes == vector_traits<EB>::nb_lanes);
}


/**
 * @brief      Check if vector / matrix contains complex numbers
 *
 * @tparam     A     Datatype
 *
 * @return     True if complex, False otherwise.
 */
template<typename A>
constexpr bool is_complex() {
    using EA = typename ElementType<remove_constref_t<A>>::type;
    return (IsComplexNumber<EA>::value);

}


/**
 * @brief      Determines if datatype is a float (double, float, complex ...).
 *
 * @tparam     A     Datatype
 *
 * @return     True if float, False otherwise.
 */
template<typename A>
constexpr bool is_float() {
    using EA = typename ElementType<remove_constref_t<A>>::type;
    return (number_traits<EA>::is_float);
}

/**
 * @brief      Determines if datatype is fixed (Q31,Q15, complex<Q15> ...).
 *
 * @tparam     A     The datatype
 *
 * @return     True if fixed, False otherwise.
 */
template<typename A>
constexpr bool is_fixed() {
    using EA = typename ElementType<remove_constref_t<A>>::type;
    return (number_traits<EA>::is_fixed);
}

/**
 * @brief      Determines if datatype has predicated loop for current architecture
 *
 * @tparam     DA    Datatype
 *
 * @return     True if has predicated loops
 */
template<typename DA>
constexpr bool has_predicate_inst() {return (vector_traits<typename ElementType<remove_constref_t<DA>>::type>::has_predicate);}

/**
 * @brief      Determines if scalar datatype (not vector, vectorview, matrix, matrixview)
 *
 * @tparam     DA    { description }
 *
 * @return     True if scalar, False otherwise.
 */
template<typename DA>
constexpr bool is_scalar() {return (!IsVector<DA>::value && 
                                    !HasMatrixIndexing<DA>::value);}

/**
 * @brief      Check if datatype are compatible and accept mixed
 *             arithmetic complex with real
 *
 * @tparam     A     LHS datatype
 * @tparam     B     RHS datatype
 *
 * @return     True if types are compatible
 */


/*

Get float type for complex

*/
template<typename E>
struct FloatType
{
    using T = typename ElementType<remove_constref_t<E>>::type;

    typedef std::conditional_t<
      IsComplexNumber<T>::value,   
      typename ComplexNumberType<T>::type,
      T> type;
};

template<typename A,typename B>
constexpr bool compatible_element() {
    using EA = typename ElementType<remove_constref_t<A>>::type;
    using EB = typename ElementType<remove_constref_t<B>>::type;
return std::is_same<typename FloatType<EA>::type,typename FloatType<EB>::type>::value ;
}

template<typename A,typename B>
constexpr bool compatible_assignment() {
    using EA = typename ElementType<remove_constref_t<A>>::type;
    using EB = typename ElementType<remove_constref_t<B>>::type;
return (std::is_same<EA,EB>::value);
}


template<typename A,typename B>
constexpr bool same_type_as() {
    using EA = typename FloatType<typename ElementType<remove_constref_t<A>>::type>::type;
    return (SameElementType<EA,B>::value);
}
/**
 * @brief      Check if datatype can only be used as a matrix (no vector addressing)
 *
 * @tparam     DA    Datatype
 *
 * @return     True if can only be used as a matrix (no vector indexing)
 */
template<typename DA>
constexpr bool must_use_matrix_idx() {return (!IsVector<DA>::value && 
                                       HasMatrixIndexing<DA>::value);}
/**
 * @brief      Check if both datatype have vector indexing and are
 *             same scalar datatype
 *
 * @tparam     DA    First datatype
 * @tparam     DB    Second datatype
 *
 * @return     True if both datatype have vector indexing and same scalar type
 */
template<typename DA,typename DB>
constexpr bool vector_idx_pair() {return (IsVector<DA>::value && 
                                          IsVector<DB>::value &&
                                          compatible_element<DA,DB>());}


// By default scalar has no vector size so can't be used
// to infer a size at build time. They are considered as dynamic
// Otherwise, by default vectors are considered static 
// except is there is a specialization of this template
// (and that is the case for dynamic vectors)
template<typename T>
struct IsDynamic
{
    constexpr static bool value = is_scalar<T>();
};

/*

Vector only not including matrixes (which are also vectors)

*/

/**
 * @brief      Check if has vector indexing
 *
 * @tparam     DA    Datatype
 *
 * @return     True if dtatype supports vector indexing
 */
template<typename DA>
constexpr bool is_only_vector() {return (IsVector<DA>::value && 
                                    !HasMatrixIndexing<DA>::value);}

/**
 * @brief      Check if datatypes have same scalar datatype and no vector indexing
 *
 * @tparam     DA    First datatype
 * @tparam     DB    Second datatype
 *
 * @return     True if datatypes have same scalar datatype and no vector indexing
 */
template<typename DA,typename DB>
constexpr bool must_use_matrix_idx_pair() {return ((must_use_matrix_idx<DA>() || must_use_matrix_idx<DB>()) &&
                                                 compatible_element<DA,DB>());}


/*

Static length is 0 for scalar and Dynamic vectors
*/

/**
 * @brief      Static length
 *
 * @tparam     DA    First datatype
 * @tparam     DB    Second datatype
 *
 * @return     Return the static length of the first datatype having
 *             a static length in the pair.
 */
template<typename DA,typename DB>
constexpr vector_length_t static_length() {
    return ((StaticLength<DA>::value==0) ? StaticLength<DB>::value : StaticLength<DA>::value);
}

/*

False only when DA and DB are static vector and with different size
Any other case is ok.

*/

/**
 * @brief      Check compatibility of length
 *
 * @tparam     DA    First datatype
 * @tparam     DB    Second datatype
 *
 * @return     False only when DA and DA have different static lengths.
 *             All other cases are True.
 */
template<typename DA,typename DB>
constexpr bool same_static_length()
{
    return((StaticLength<DA>::value == 0) || /* Scalar or dynamic case */
           (StaticLength<DB>::value == 0) || /* Scalar or dynamic case */
           (StaticLength<DA>::value == StaticLength<DB>::value));
}
/*

Vector operators at instruction level

*/
#include "fusion_ops.hpp"


/**
 * @brief  Expression template
 *
 * @tparam T Datatype representing the expression
 * 
 */
template<typename T>
struct _Expr {

    using Scalar = typename traits<T>::Scalar;
#if defined(HAS_VECTOR)
    using Vector = typename traits<T>::Vector;
#endif

  /**
   * @brief      Derived datatype
   *
   * @return     Return the derived datatype
   */
  T& derived()  {return(static_cast<T&>(*this));}

  /**
   * @brief      Derived datatype
   *
   * @return     Return the derived datatype
   */
  T const& derived() const {return(static_cast<T const&>(*this));}

  /**
   * @brief      Vector indexing in the expression
   *
   * @param[in]  i     Index
   *
   * @return     The result of the vector indexer
   */
  Scalar const operator[](const index_t i) const {return(this->derived()[i]);}
  
  /**
   * @brief      Matrix indexing
   *
   * @param[in]  r     Row index
   * @param[in]  c     Column index
   *
   * @return     Element at index
   */
  Scalar const operator()(const index_t r,const index_t c) const {return(this->derived()(r,c));}

#if defined(HAS_VECTOR)
  /**
   * @brief      Vector operation at given index
   *
   * @param[in]  i     Vector index
   *
   * @return     Evaluation of vector at the index
   */
  Vector const vector_op(const index_t i) const {return(this->derived().vector_op(i));}
  
  /**
   * @brief      Vector operation at index with loop predicate
   *
   * @param[in]  i          Vector index
   * @param[in]  remaining  Remaining elements in the loop
   *
   * @return     Evaluation of vector at index with tail predication
   */
  Vector const vector_op_tail(const index_t i,const vector_length_t remaining) const {return(this->derived().vector_op_tail(i,remaining));}

  /**
   * @brief      Matrix operation at index
   *
   * @param[in]  r     row index
   * @param[in]  c     column index
   *
   * @return     Evaluation of matrix expression at index
   */
  Vector const matrix_op(const index_t r,const index_t c) const {return(this->derived().matrix_op(r,c));}
  
  /**
   * @brief      Matrix operation at index with tail predication
   *
   * @param[in]  r          row index
   * @param[in]  c          column index
   * @param[in]  remaining  Remaining elements in the loop
   *
   * @return     Evaluation of matrix operation at index
   */
  Vector const matrix_op_tail(const index_t r,const index_t c,const vector_length_t remaining) const {return(this->derived().matrix_op_tail(r,c,remaining));}
#endif 

  /**
   * @brief      Length of result
   *
   * @return     The vector length.
   */
  vector_length_t length() const {return(this->derived().length());}

  /**
   * @brief      Number of rows for result
   *
   * @return     Number of rows
   */
  vector_length_t rows() const {return(this->derived().rows());}

  /**
   * @brief      Number of columns for result
   *
   * @return     Number of columns
   */
  vector_length_t columns() const {return(this->derived().columns());}

  virtual ~_Expr(){};

protected:
   _Expr() = default;
   _Expr(const _Expr&) = default;
   _Expr(_Expr&&) = default;
   _Expr& operator=(const _Expr& other) = delete;
   _Expr& operator=(_Expr&& other) = delete;
};

/*****************
 * 
 * BINARY AST
 */

/**
 * @brief  Expression for binary operator
 *
 * @tparam LHS Left hand side datatype
 * @tparam RHS Right hand side datatype
 * @tparam DerivedOp Operator for the binary operation
 * 
 */
template<typename LHS,typename RHS,typename DerivedOp>
struct _Binary: _Expr<_Binary<LHS,RHS,DerivedOp>>
{
    using ScalarLHS = typename traits<LHS>::Scalar;
    using ScalarRHS = typename traits<RHS>::Scalar;
#if defined(HAS_VECTOR)
    using VectorLHS = typename traits<LHS>::Vector;
    using VectorRHS = typename traits<RHS>::Vector;
#endif
    _Binary(const LHS &lhs,
            const RHS &rhs,
            const _BinaryOperator<ScalarLHS,ScalarRHS,DerivedOp> &op):
            lhs_(lhs),rhs_(rhs),op_(op){
    }

    
    _Binary(const _Binary &other):
    lhs_(other.lhs_),rhs_(other.rhs_),op_(other.op_){
    }

    _Binary& operator=(const _Binary& other) = delete;
    _Binary& operator=(_Binary&& other) = delete;

    _Binary(_Binary &&other): 
    lhs_(std::move(other.lhs_)),rhs_(std::move(other.rhs_)),op_(std::move(other.op_))
    {
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<IsVector<L>::value,bool>::type = true>
    vector_length_t length() const {
        return(lhs_.length());
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<!IsVector<L>::value && IsVector<R>::value,bool>::type = true>
    vector_length_t length() const {
        return(rhs_.length());
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<HasMatrixIndexing<L>::value,bool>::type = true>
    vector_length_t rows() const {
        return(lhs_.rows());
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<!HasMatrixIndexing<L>::value && HasMatrixIndexing<R>::value,bool>::type = true>
    vector_length_t rows() const {
        return(rhs_.rows());
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<HasMatrixIndexing<L>::value,bool>::type = true>
    vector_length_t columns() const {
        return(lhs_.columns());
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<!HasMatrixIndexing<L>::value && HasMatrixIndexing<R>::value,bool>::type = true>
    vector_length_t columns() const {
        return(rhs_.columns());
    }


   
    template<typename R=RHS, typename L=LHS,
             typename std::enable_if< 
                        IsVector<L>::value && 
                        IsVector<R>::value,bool>::type = true>
    auto  operator[](const index_t i) const {
        return(op_(lhs_[i],rhs_[i]));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<IsVector<L>::value && 
                       is_scalar<R>(),bool>::type = true>
    auto  operator[](const index_t i) const {
        return(op_(lhs_[i],rhs_));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<is_scalar<L>() && 
                        IsVector<R>::value,bool>::type = true>
    auto  operator[](const index_t i) const {
        return(op_(lhs_,rhs_[i]));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<HasMatrixIndexing<L>::value && 
                        HasMatrixIndexing<R>::value,bool>::type = true>
    auto  operator()(const index_t r,const index_t c) const
    {
        return(op_(lhs_(r,c),rhs_(r,c)));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<is_scalar<L>() && 
                        HasMatrixIndexing<R>::value,bool>::type = true>
    auto  operator()(const index_t r,const index_t c) const
    {
        return(op_(lhs_,rhs_(r,c)));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<HasMatrixIndexing<L>::value && 
                        is_scalar<R>(),bool>::type = true>
    auto  operator()(const index_t r,const index_t c) const
    {
        return(op_(lhs_(r,c),rhs_));
    }

#if defined(HAS_VECTOR)
    /* V + V */
    template<typename R=RHS, typename L=LHS,
             typename std::enable_if< 
                        IsVector<L>::value && 
                        IsVector<R>::value,bool>::type = true>
    auto  vector_op(const index_t i) const
    {
        return(op_(lhs_.vector_op(i),rhs_.vector_op(i)));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if< 
                        has_predicate_inst<L>() &&
                        IsVector<L>::value && 
                        IsVector<R>::value,bool>::type = true>
    auto  vector_op_tail(const index_t i,const vector_length_t remaining) const
    {
        return(op_(lhs_.vector_op_tail(i,remaining),rhs_.vector_op_tail(i,remaining),inner::vctpq<ScalarLHS>::mk(remaining)));
    }

    /* V + S */
    template<typename R=RHS, typename L=LHS,
            typename std::enable_if< 
                        IsVector<L>::value && 
                        is_scalar<R>(),bool>::type = true>
    auto  vector_op(const index_t i) const
    {
        return(op_(lhs_.vector_op(i),rhs_));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if< 
                        has_predicate_inst<L>() &&
                        IsVector<L>::value && 
                        is_scalar<R>(),bool>::type = true>
    auto  vector_op_tail(const index_t i,const vector_length_t remaining) const
    {
        return(op_(lhs_.vector_op_tail(i,remaining),rhs_,inner::vctpq<ScalarLHS>::mk(remaining)));
    }



    /* S + V */
    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<is_scalar<L>() && 
                        IsVector<R>::value,bool>::type = true>
    auto  vector_op(const index_t i) const
    {
        return(op_(lhs_,rhs_.vector_op(i)));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if< 
                        has_predicate_inst<L>() &&
                        is_scalar<L>() && 
                        IsVector<R>::value,bool>::type = true>
    auto  vector_op_tail(const index_t i,const vector_length_t remaining) const
    {
        return(op_(lhs_,rhs_.vector_op_tail(i,remaining),inner::vctpq<ScalarLHS>::mk(remaining)));
    }


    /*************
     * 
     * For matrix
     * 
     */

    /* V + V */
    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<HasMatrixIndexing<L>::value && 
                        HasMatrixIndexing<R>::value,bool>::type = true>
    auto  matrix_op(const index_t r,const index_t c) const
    {
        return(op_(lhs_.matrix_op(r,c),rhs_.matrix_op(r,c)));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<
                        has_predicate_inst<L>() &&
                        HasMatrixIndexing<L>::value && 
                        HasMatrixIndexing<R>::value,bool>::type = true>
    auto  matrix_op_tail(const index_t r,const index_t c,const vector_length_t remaining) const
    {
        return(op_(lhs_.matrix_op_tail(r,c,remaining),rhs_.matrix_op_tail(r,c,remaining),inner::vctpq<ScalarLHS>::mk(remaining)));
    }

    /* V + S */
    template<typename R=RHS, typename L=LHS,
            typename std::enable_if<HasMatrixIndexing<L>::value && 
                                    is_scalar<R>(),bool>::type = true>
    auto  matrix_op(const index_t r,const index_t c) const
    {
        return(op_(lhs_.matrix_op(r,c),rhs_));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<has_predicate_inst<L>() &&
                                     HasMatrixIndexing<L>::value && 
                                     is_scalar<R>(),bool>::type = true>
    auto  matrix_op_tail(const index_t r,const index_t c,const vector_length_t remaining) const
    {
        return(op_(lhs_.matrix_op_tail(r,c,remaining),rhs_,inner::vctpq<ScalarLHS>::mk(remaining)));
    }



    /* S + V */
    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<is_scalar<L>() && 
                        HasMatrixIndexing<R>::value,bool>::type = true>
    auto  matrix_op(const index_t r,const index_t c) const
    {
        return(op_(lhs_,rhs_.matrix_op(r,c)));
    }

    template<typename R=RHS, typename L=LHS,
             typename std::enable_if<has_predicate_inst<L>() &&
                                     is_scalar<L>() && 
                                     HasMatrixIndexing<R>::value,bool>::type = true>
    auto  matrix_op_tail(const index_t r,const index_t c,const vector_length_t remaining) const
    {
        return(op_(lhs_,rhs_.matrix_op_tail(r,c,remaining),inner::vctpq<ScalarLHS>::mk(remaining)));
    }


#endif
    const LHS lhs_;
    const RHS rhs_;
    const _BinaryOperator<ScalarLHS,ScalarRHS,DerivedOp> op_;
};


template<typename DerivedOp>
struct Complexity<_Expr<DerivedOp>>
{
   constexpr static int value = Complexity<DerivedOp>::value;
};

template<typename DerivedOp>
struct ElementType<_Expr<DerivedOp>>
{
    typedef typename ElementType<remove_constref_t<DerivedOp>>::type type;
};

template<typename LHS,typename RHS,typename DerivedOp>
struct Complexity<_Binary<LHS,RHS,DerivedOp>>
{
   constexpr static int lhsv = Complexity<LHS>::value;
   constexpr static int rhsv = Complexity<RHS>::value;
   constexpr static int value = lhsv + rhsv + 1;
};

template<typename LHS,typename RHS,typename DerivedOp>
struct IsMixed<_Binary<LHS,RHS,DerivedOp>>
{
    using EA = typename ElementType<remove_constref_t<LHS>>::type;
    using EB = typename ElementType<remove_constref_t<RHS>>::type;
    constexpr static bool value = (IsComplexNumber<EA>::value != IsComplexNumber<EB>::value)
      || IsMixed<LHS>::value || IsMixed<RHS>::value;
};

template<typename LHS,typename RHS,typename DerivedOp>
struct ElementType<_Binary<LHS,RHS,DerivedOp>>
{
    using EA = typename ElementType<remove_constref_t<LHS>>::type;
    using EB = typename ElementType<remove_constref_t<RHS>>::type;

    typedef std::conditional_t <
    IsComplexNumber<EA>::value && !IsComplexNumber<EB>::value,EA,
    std::conditional_t <!IsComplexNumber<EA>::value && IsComplexNumber<EB>::value,
    EB,EA>> type;
};


template<typename DerivedOp>
struct IsVector<_Expr<DerivedOp>>
{
    constexpr static bool value = IsVector<DerivedOp>::value;
};

template<typename DerivedOp>
struct HasMatrixIndexing<_Expr<DerivedOp>>
{
    constexpr static bool value = HasMatrixIndexing<DerivedOp>::value;
};

template<typename LHS,typename RHS,typename DerivedOp>
struct IsVector<_Binary<LHS,RHS,DerivedOp>>
{
    constexpr static bool value = 
    (IsVector<LHS>::value && IsVector<RHS>::value) ||
    (IsVector<LHS>::value && is_scalar<RHS>()) ||
    (is_scalar<LHS>()     && IsVector<RHS>::value);
};

template<typename LHS,typename RHS,typename DerivedOp>
struct HasMatrixIndexing<_Binary<LHS,RHS,DerivedOp>>
{
    constexpr static bool value = 
    (HasMatrixIndexing<LHS>::value && HasMatrixIndexing<RHS>::value) ||
    (HasMatrixIndexing<LHS>::value && is_scalar<RHS>()) ||
    (is_scalar<LHS>()     && HasMatrixIndexing<RHS>::value);
};

template<typename DerivedOp>
struct IsDynamic<_Expr<DerivedOp>>
{
    constexpr static bool value = IsDynamic<DerivedOp>::value;
};

template<typename LHS,typename RHS,typename DerivedOp>
struct IsDynamic<_Binary<LHS,RHS,DerivedOp>>
{
    constexpr static bool value = IsDynamic<LHS>::value && IsDynamic<RHS>::value;
};

template<typename DerivedOp>
struct StaticLength<_Expr<DerivedOp>>
{
    constexpr static vector_length_t value = StaticLength<DerivedOp>::value;
};

template<typename LHS,typename RHS,typename DerivedOp>
struct StaticLength<_Binary<LHS,RHS,DerivedOp>>
{
    constexpr static vector_length_t value = static_length<LHS,RHS>();
   
};

template<typename DerivedOp>
struct traits<_Expr<DerivedOp>>
{
    typedef typename traits<DerivedOp>::Scalar Scalar;
#if defined(HAS_VECTOR)
    typedef typename traits<DerivedOp>::Vector Vector;
#endif
};

template<typename LHS,typename RHS,typename DerivedOp>
struct traits<_Binary<LHS,RHS,DerivedOp>>
{
    using LScalar = typename traits<LHS>::Scalar;
    using RScalar = typename traits<RHS>::Scalar;

    typedef typename MixedRes<LScalar,RScalar>::type Scalar;
#if defined(HAS_VECTOR)
    typedef typename traits<Scalar>::Vector Vector;
#endif
};


/*****************
 * 
 * UNARY AST
 */

/**
 * @brief  Expression for unary operator
 *
 * @tparam LHS Left hand side datatype
 * @tparam DerivedOp Operator for the binary operation
 * 
 */
template<typename LHS,typename DerivedOp>
struct _Unary: _Expr<_Unary<LHS,DerivedOp>>
{
    using Scalar = typename traits<LHS>::Scalar;
#if defined(HAS_VECTOR)
    using Vector = typename traits<LHS>::Vector;
#endif
    _Unary(const LHS &lhs,
           const _UnaryOperator<Scalar,DerivedOp> &op):
            lhs_(lhs),op_(op){
    }

    _Unary(const _Unary &other):
    lhs_(other.lhs_),op_(other.op_){
    }

    _Unary(LHS &&other):
    lhs_(std::move(other.lhs_)),op_(std::move(other.op_)){
    }

    _Unary& operator=(const _Unary& other) = delete;
    _Unary& operator=(_Unary&& other) = delete;


    vector_length_t length() const {
        return(lhs_.length());
    }

    template<typename L=LHS,
             typename std::enable_if<HasMatrixIndexing<L>::value,bool>::type = true>
    vector_length_t rows() const {
        return(lhs_.rows());
    }

    template<typename L=LHS,
             typename std::enable_if<HasMatrixIndexing<L>::value,bool>::type = true>
    vector_length_t columns() const {
        return(lhs_.columns());
    }

    template<typename L=LHS,
             typename std::enable_if<IsVector<L>::value ,bool>::type = true>
    Scalar const operator[](const index_t i) const {
        return(op_(lhs_[i]));
    }

    template<typename L=LHS,
             typename std::enable_if<HasMatrixIndexing<L>::value ,bool>::type = true>
    Scalar const operator()(const index_t r,const index_t c) const
    {
        return(op_(lhs_(r,c)));
    }


#if defined(HAS_VECTOR)
    /* V */
    template<typename L=LHS,
             typename std::enable_if<
                        IsVector<L>::value ,bool>::type = true>
    Vector const vector_op(const index_t i) const
    {
        return(op_(lhs_.vector_op(i)));
    }

    template<typename L=LHS,
             typename std::enable_if<has_predicate_inst<L>() &&
                                     IsVector<L>::value ,bool>::type = true>
    Vector const vector_op_tail(const index_t i,const vector_length_t remaining) const
    {
        return(op_(lhs_.vector_op_tail(i,remaining),inner::vctpq<Scalar>::mk(remaining)));
    }

    /*

    For Matrix

    */

    /* V */
    template<typename L=LHS,
             typename std::enable_if<HasMatrixIndexing<L>::value ,bool>::type = true>
    Vector const matrix_op(const index_t r,const index_t c) const
    {
        return(op_(lhs_.matrix_op(r,c)));
    }

    template<typename L=LHS,
             typename std::enable_if<has_predicate_inst<L>() &&
                                     HasMatrixIndexing<L>::value ,bool>::type = true>
    Vector const matrix_op_tail(const index_t r,const index_t c,const vector_length_t remaining) const
    {
        return(op_(lhs_.matrix_op_tail(r,c,remaining),inner::vctpq<Scalar>::mk(remaining)));
    }

    
#endif
    const LHS lhs_;
    const _UnaryOperator<Scalar,DerivedOp> op_;
};

template<typename LHS,typename DerivedOp>
struct Complexity<_Unary<LHS,DerivedOp>>
{
   constexpr static int value = 1 + Complexity<LHS>::value;
};

template<typename LHS,typename DerivedOp>
struct IsMixed<_Unary<LHS,DerivedOp>>
{
    constexpr static bool value = IsMixed<LHS>::value;
};

template<typename LHS,typename DerivedOp>
struct ElementType<_Unary<LHS,DerivedOp>>
{
    typedef typename ElementType<remove_constref_t<LHS>>::type type;
};

template<typename LHS,typename DerivedOp>
struct IsVector<_Unary<LHS,DerivedOp>>
{
    constexpr static bool value = IsVector<LHS>::value;
};

template<typename LHS,typename DerivedOp>
struct HasMatrixIndexing<_Unary<LHS,DerivedOp>>
{
    constexpr static bool value = HasMatrixIndexing<LHS>::value;
};

template<typename LHS,typename DerivedOp>
struct IsDynamic<_Unary<LHS,DerivedOp>>
{
    constexpr static bool value = IsDynamic<LHS>::value;
};

template<typename LHS,typename DerivedOp>
struct StaticLength<_Unary<LHS,DerivedOp>>
{
    constexpr static vector_length_t value = StaticLength<LHS>::value;
};


template<typename LHS,typename DerivedOp>
struct traits<_Unary<LHS,DerivedOp>>
{
    typedef typename traits<LHS>::Scalar Scalar;
#if defined(HAS_VECTOR)
    typedef typename traits<LHS>::Vector Vector;
#endif
};


/*

Dot product 

*/

template<typename DT>
using DotResult = typename number_traits<DT>::accumulator;

// T or std::complex<T>
// and from this we can infer the types of the accumulators.
template<typename DA,typename DB>
using DotFieldResult = typename MixedRes<typename traits<DA>::Scalar,typename traits<DB>::Scalar>::type;



/**
 * @brief  Dot product
 *
 * @tparam VA Left hand side vector datatype
 * @tparam VB Right hand side vector datatype
 * @param a left hand side vector
 * @param b right hand side vector
 * @return The dot product
 * 
 * The vector can be vector, vector views or expressions.
 * 
 */
template<typename VA,typename VB,
         typename std::enable_if<vector_idx_pair<VA,VB>() &&
         is_only_vector<VA>() &&
         is_only_vector<VB>() &&
         (!IsDynamic<VA>::value || !IsDynamic<VB>::value),bool>::type = true>
inline DotResult<DotFieldResult<VA,VB>> dot(const VA& a,
                                            const VB& b)
{
   constexpr vector_length_t l = static_length<VA,VB>();
   return(_dot(a,b,l,CURRENT_ARCH));
}


template<typename VA,typename VB,
         typename std::enable_if<vector_idx_pair<VA,VB>() &&
         is_only_vector<VA>() &&
         is_only_vector<VB>() &&
         (IsDynamic<VA>::value && IsDynamic<VB>::value),bool>::type = true>
inline DotResult<DotFieldResult<VA,VB>> dot(const VA& a,
                                            const VB& b)
{
   const vector_length_t l = a.length();
   
   return(_dot(a,b,l,CURRENT_ARCH));
}




/**
 * @brief  Swap vectors
 *
 * @tparam VA Left hand side vector datatype
 * @tparam VB Right hand side vector datatype
 * @param a left hand side vector
 * @param b right hand side vector
 * 
 * The vector can be vector, vector views or expressions.
 * 
 * The content of vector is swapped.
 * 
 */
template<typename VA,typename VB,
         typename std::enable_if<vector_idx_pair<VA,VB>() &&
         (!IsDynamic<VA>::value || !IsDynamic<VB>::value),bool>::type = true>
inline void swap(VA&& a,
                 VB&& b)
{
   constexpr vector_length_t l = static_length<VA,VB>();
   
   _swap(std::forward<VA>(a),std::forward<VB>(b),l,CURRENT_ARCH);
}


template<typename VA,typename VB,
         typename std::enable_if<vector_idx_pair<VA,VB>() &&
         (IsDynamic<VA>::value && IsDynamic<VB>::value),bool>::type = true>
inline void swap(VA&& a,
                 VB&& b)
{
   const vector_length_t l = a.length();
   
   _swap(std::forward<VA>(a),std::forward<VB>(b),l,CURRENT_ARCH);
}

/*! @} */

}

