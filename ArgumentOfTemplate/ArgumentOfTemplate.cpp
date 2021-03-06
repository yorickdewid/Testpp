/**
* A struct with one or two members, type and returnType.
*
* type is the type of the indicated argument to the passed method or function.
* returnType is the returnType of the passed method or function.
*
* Examples:
*  static_assert(std::is_same<std::size_t, ArgumentOf<decltype(memcpy), 2>::type>::value);
*  static_assert(std::is_same<std::size_t, ArgumentOf<decltype(std::string::size())>::returnType>::value);
*  static_assert(std::is_same<ArgumentOf<decltype(std::find<char*, char>)>::returnType, char*>::value);
*  static_assert(std::is_same<ArgumentOf<decltype(std::find<char*, char>, 0)>::type, char*>::value);
*
* Compiler errors:
*  ArgumentOf<decltype(std::string::size(), 0)>::returnType x; // Parameter index too high (::type does not exist)
*  ArgumentOf<decltype(std::string::size())>::type x; // Only return type extracted (::type does not exist)
*
* @tparam   Function     A function or method to inspect.
* @tparam   index        The 0-based index of the argument to extract. -1 (default)
*                                     to only extract the return type.
*/

template<class Function, int index = -1>
struct ArgumentOf;

template<class ReturnType, int index>
struct ArgumentOf<ReturnType(), index>
{
	using returnType = typename decltype(ReturnType);
};

template<class ReturnType, class Arg0, class Args...>
struct ArgumentOf<ReturnType (Arg0, Args...), 0>
{
	using type = typename Function::type;
};

template<class ReturnType, class Arg0, class Args..., int index>
struct ArgumentOf<ReturnType(Arg0, Args...), index> : public ArgumentOf<ReturnType(Args...), index - 1>
{
};

template<class Function>
struct ArgumentOf<Function, 1>
{
	using type = typename Function::type;
};

template<class Function>
struct ArgumentOf<Function, 2>
{
	using type = typename Function::type;
};

#include <iostream>
#include <memory.h>
int main()
{
	//ArgumentOf<decltype(memcpy), 2>::type 7;
	std::cout << typeid(decltype(memcpy)).name() << std::endl;
	/*static_assert(std::is_same<std::size_t, ArgumentOf<decltype(memcpy), 2>::type>::value);
	static_assert(std::is_same<std::size_t, ArgumentOf<decltype(std::string::size())>::returnType>::value);
	static_assert(std::is_same<ArgumentOf<decltype(std::find<char*, char>)>::returnType, char*>::value);
	static_assert(std::is_same<ArgumentOf<decltype(std::find<char*, char>, 0)>::type, char*>::value);*/

	return 0;
}
