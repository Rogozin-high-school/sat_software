#pragma once

#ifndef LOGGING

static inline struct
{
      template<typename T>
      auto& operator<<(const T& x) { return *this; }
} cout, cerr, log, err; // Dummy stream, should be optimized out
#define endl nullptr
#define failure(...)

#else // LOGGING

#include <iostream>
#include <string.h>
#include <cxxabi.h>
#include <memory>

namespace Codes
{
      enum class Color
      {
            null = 0,

            black = 30,
            red,
            green,
            yellow,
            blue,
            magenta,
            cyan,
            white
      };

      enum class Face
      {
            reset = 0,
            
            bold = 1,
            underline = 4,
            inverse = 7,

            bold_off = 21,
            underline_off = 24,
            inverse_off = 27
      };
      
      static inline const auto get(Color color = Color::null, Face face = Face::reset)
      {
            if (color == Color::null)
            {
                  return "\033[" + std::to_string(int(face)) + "m";
            }
            else
            {
                  return "\033[" + std::to_string(int(face)) + ";" + std::to_string(int(color)) + "m";
            }
      }

      static inline const auto reset = get();
}

const static inline std::string demangle(const char* name) 
{
      int status;
      std::unique_ptr<char, void(*)(void*)> res 
      {
            abi::__cxa_demangle(name, nullptr, nullptr, &status), free
      };
      return status ? name : res.get();
}

#define FUNCTION_NAME \
      "\"" << __PRETTY_FUNCTION__ << "\""

#define FILE_NAME \
      (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define FILE_NAME_DECORATED \
      "[" << FILE_NAME << "]"

using std::cout;
using std::cerr;
#define endl Codes::reset << std::endl

#define log \
      cout << FILE_NAME_DECORATED << "\n\t"

#define err(ex) \
      cerr \
      << Codes::get(Codes::Color::red) \
      << "[" << FILE_NAME << "]\n\t" \
      << Codes::get(Codes::Color::red, Codes::Face::bold) \
      << demangle(typeid(ex).name()) \
      << Codes::get(Codes::Color::red) \
      << " in " << FUNCTION_NAME << ":\n\t" \
      << ex.what() << endl

#define failure() \
      cerr \
      << Codes::get(Codes::Color::red) \
      << "[" << FILE_NAME << "]\n\t" \
      << FUNCTION_NAME << " has failed!" << endl

#endif // LOGGING

#ifndef LOGGING_FUNCTION_CALLS

#define function_call(...)

#else // LOGGING_FUNCTION_CALLS

#define CALL_ARG(arg, num) \
      "\n\t- Arg #" << num << " (named \"" << #arg << "\") with value = \"" << arg << "\""

#define CALL_0() \
      "Called \"" << __PRETTY_FUNCTION__ << "\""

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

#define function_call(...) \
      log << GET_CALL(__VA_ARGS__ __VA_OPT__(,) CALL_5, CALL_4, CALL_3, CALL_2, CALL_1, CALL_0)(__VA_ARGS__) << endl

#endif // LOGGING_FUNCTION_CALLS