#pragma once

#ifndef LOGGING

static inline struct
{
      template<typename T>
      auto& operator<<(const T& x) { return *this; }
} cout, cerr, log; // Dummy stream, should be optimized out

#define endl nullptr
#define print_exception(x)
#define print_failure()

#else // LOGGING

#include <iostream>
#include <string.h>

#include <cxxabi.h>
#include <memory>

namespace
{

const static inline std::string demangle(const char* name) 
{
      int status;
      std::unique_ptr<char, void(*)(void*)> res 
      {
            abi::__cxa_demangle(name, nullptr, nullptr, &status), free
      };
      return status ? name : res.get();
}

#define DEMANGLE(type) demangle(typeid(type).name())

// Color codes
constexpr auto reset = "\e[0m";

constexpr auto bold = "\e[1m";
constexpr auto rbold = "\e[21m";

constexpr auto underline = "\e[4m";
constexpr auto runderline = "\e[24m";

constexpr auto italic = "\e[3m";
constexpr auto ritalic = "\e[23m";

constexpr auto red = "\e[31m";

using std::cout;
using std::cerr;
#define endl reset << std::endl

#define FILE_NAME underline << (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) << runderline << "\n\t"

#define FUNCTION_NAME italic << __PRETTY_FUNCTION__ << ritalic

#define log cout << FILE_NAME

#define print_exception(exception) \
      cerr << red << FILE_NAME << \
      bold << DEMANGLE(exception) << reset << red << " caught in " << FUNCTION_NAME << ":\n\t" << \
      ex.what() << endl

#define print_failure() \
      cerr << red << FILE_NAME << FUNCTION_NAME << " has failed!" << endl

#endif // LOGGING

#ifndef LOGGING_FUNCTION_CALLS

#define print_function_call(...)

#else // LOGGING_FUNCTION_CALLS

#define CALL_ARG(arg, num) \
      "\n\t- Arg #" << num << " (named \"" << #arg << "\") with value = \"" << arg << "\""

#define CALL_0() \
      "Called " << FUNCTION_NAME << ""

#define CALL_1(arg0) \
      CALL_0() << "\n" << CALL_ARG(arg0, 0)

#define CALL_2(arg0, arg1) \
      CALL_1(arg0) << CALL_ARG(arg1, 1)

#define CALL_3(arg0, arg1, arg2) \
      CALL_2(arg0, arg1) << CALL_ARG(arg2, 2)

#define CALL_4(arg0, arg1, arg2, arg3) \
      CALL_3(arg0, arg1, arg2) << CALL_ARG(arg3, 3)

#define CALL_5(arg0, arg1, arg2, arg3, arg4) \
      CALL_4(arg0, arg1, arg2, arg3) << CALL_ARG(arg4, 4)

// Max number of arguments = 5 for now

#define GET_CALL(_1, _2, _3, _4, _5, NAME, ...) NAME

#define print_function_call(...) \
      log << GET_CALL(__VA_ARGS__ __VA_OPT__(,) CALL_5, CALL_4, CALL_3, CALL_2, CALL_1, CALL_0)(__VA_ARGS__) << endl

#endif // LOGGING_FUNCTION_CALLS

}