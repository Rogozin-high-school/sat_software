#pragma once

#ifndef LOGGING

static inline struct
{
      template<typename T>
      auto& operator<<(const T& x) { return *this; }
} cout, cerr, log; // Dummy stream, should be optimized out

#define endl nullptr
#define print_throw_exception(x)
#define print_catch_and_throw_exception()
#define print_catch_and_handle_exception()

#else // LOGGING

#include <iostream>
#include <string.h>

#include <cxxabi.h>
#include <memory>

#ifdef LOGGING_FUNCTION_CALLS
#include <sstream>
#include <array>
#endif // LOGGING_FUNCTION_CALLS

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

#define BOLD "\e[1m"
#define RBOLD "\e[21m"
#define UNDERLINE "\e[4m"
#define RUNDERLINE "\e[24m"
#define ITALIC "\e[3m"
#define RITALIC "\e[23m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define CYAN "\e[36m"
#define LIGHT_GREY "\e[37m"
#define RESET "\e[0m"

using std::cout;
using std::cerr;
#define endl RESET << std::endl
#define log cout << UNDERLINE << FILE_NAME << RUNDERLINE << "\n\t"

#define FILE_NAME \
      (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define FUNCTION_NAME \
      __PRETTY_FUNCTION__

template<typename Exception>
static inline void print_throw_exception_raw(const std::string&& flName, const std::string&& fnName, const Exception& ex)
{
      fprintf(stderr, 
            "%s\n"
            "\t%s has thrown an exception!\n"
            "\t%s: %s\n" 
            RESET,
            
            (RED UNDERLINE + flName + RUNDERLINE).c_str(),
            (ITALIC CYAN + fnName + RESET RED).c_str(),
            (BOLD + demangle(typeid(ex).name()) + RESET RED).c_str(),
            ex.what());
      fflush(stderr);
}

static inline void print_catch_and_throw_exception_raw(const std::string&& flName, const std::string&& fnName)
{
      fprintf(stderr, 
            "%s\n"
            "\t%s has caught an exception, and thrown it forward!\n"
            RESET,
            
            (RED UNDERLINE + flName + RUNDERLINE).c_str(),
            (ITALIC CYAN + fnName + RESET RED).c_str());
      fflush(stderr);
}

static inline void print_catch_and_handle_exception_raw(const std::string&& flName, const std::string&& fnName)
{
      fprintf(stderr, 
            "%s\n"
            "\t%s has caught an exception, but handled it!\n"
            RESET,
            
            (RED UNDERLINE + flName + RUNDERLINE).c_str(),
            (ITALIC CYAN + fnName + RESET RED).c_str());
      fflush(stderr);
}

#define print_throw_exception(ex) \
      print_throw_exception_raw(FILE_NAME, FUNCTION_NAME, ex)

#define print_catch_and_throw_exception() \
      print_catch_and_throw_exception_raw(FILE_NAME, FUNCTION_NAME)

#define print_catch_and_handle_exception() \
      print_catch_and_handle_exception_raw(FILE_NAME, FUNCTION_NAME)

#endif // LOGGING

#ifndef LOGGING_FUNCTION_CALLS

#define print_function_call(...)

#else // LOGGING_FUNCTION_CALLS

template<typename ...Args>
static inline void print_function_call_raw(const std::string&& flName, const std::string&& fnName, const Args&... args)
{
      fprintf(stdout, 
            "%s\n"
            "\t%s has been called\n",

            (UNDERLINE + flName + RUNDERLINE).c_str(),
            (ITALIC CYAN + fnName + RESET).c_str());

      if constexpr(sizeof...(Args) > 0)
      { // Print the parameter types. They're embedded in the function's name
            std::string stripped(strchr(fnName.c_str(), '('));
            stripped = stripped.substr(1, stripped.length() - 2);

            if (stripped.length() > 0)
            {
                  std::string token;
                  std::stringstream stream(std::move(stripped));
                  std::array<std::string, sizeof...(Args)> argsArr;

                  int i, &j = i; // Just to reduce the compiler's warning...
                  for (i = 0; std::getline(stream, token, ','); i++)
                  {
                        argsArr[i] = token;
                        stream.ignore();
                  }
                  i = 0;

                  cout << "\n";
                  ((cout << "\t" << i + 1 << ". " CYAN ITALIC << argsArr[j++] << RESET " => " LIGHT_GREY ITALIC << args << RESET "\n"), ...);
            }
      }

      fflush(stdout);
}

#define print_function_call(...) \
      print_function_call_raw(FILE_NAME, FUNCTION_NAME __VA_OPT__(,) __VA_ARGS__)

#endif // LOGGING_FUNCTION_CALLS

}
