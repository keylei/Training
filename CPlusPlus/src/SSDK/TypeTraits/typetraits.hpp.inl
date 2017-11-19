#ifndef TYPETRAITS_HPP_INL
#define TYPETRAITS_HPP_INL

//memory leak is caused by __cxa_demangle, so wrap return value by shared_ptr
template<typename T>
std::shared_ptr<char> const Sung::SSDK::Core::TypeTraits::typeName( T const& t )
{
#ifdef __GNUC__
    int status;
    return std::shared_ptr<char>(abi::__cxa_demangle( typeid(t).name(), 0, 0, &status ));
#else
    return  std::shared_ptr<char>(typeid(t).name());
#endif
}

#endif
