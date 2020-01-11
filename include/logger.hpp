#pragma once

#include <stdexcept>

#ifndef LOGGING

#define log_throw_exception(x)
#define log_catch_and_throw_exception()
#define log_catch_and_handle_exception()
#define log_function_call(...)

#else // LOGGING

#include <iostream>
#include <iomanip>
#include <sstream>
#include <memory>

#include <string.h>
#include <stdarg.h>
#include <cxxabi.h>

#ifdef LOGGING_FUNCTION_CALLS
#include <array>
#endif // LOGGING_FUNCTION_CALLS

namespace
{

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
#define WHITE "\e[39m"
#define RESET "\e[0m"

#define PADDING "                 "

static inline const std::string module_name(const char *fileName)
{
      // Trim the path
      const std::string fileName_noPath{strrchr(fileName, '/') ? strrchr(fileName, '/') + 1 : fileName};

      // Trim the ".cpp" suffix
      std::string fileName_noSuffix = fileName_noPath.substr(0, fileName_noPath.size() - 4);

      // Set the first character uppercase
      fileName_noSuffix[0] = toupper(fileName_noSuffix[0]);

      return fileName_noSuffix;
}

static inline void _log(const char *color, const char *fileName, const char *format, ...)
{
      va_list va;
      va_start(va, format);

      std::stringstream formatStr;

      formatStr << color;
      if (fileName != nullptr)
      {
            formatStr << std::left << std::setw(sizeof(PADDING) - sizeof(" -> ")) << std::setfill(' ') << module_name(fileName);
      }
      formatStr << " -> " << format << RESET << "\n";

      vprintf(formatStr.str().c_str(), va);
      va_end(va);
}

//

#define verbose_f(fileName, format, ...) \
      _log(WHITE, fileName, format __VA_OPT__(, ) __VA_ARGS__)

#define debug_f(fileName, format, ...) \
      _log(LIGHT_GREY, fileName, format __VA_OPT__(, ) __VA_ARGS__)

#define info_f(fileName, format, ...) \
      _log(CYAN, fileName, format __VA_OPT__(, ) __VA_ARGS__)

#define warn_f(fileName, format, ...) \
      _log(RED, fileName, format __VA_OPT__(, ) __VA_ARGS__)

#define err_f \
      warn_f // Meanwhile the same format

//

#define verbose(format, ...) \
      verbose_f(__FILE__, format __VA_OPT__(, ) __VA_ARGS__)

#define debug(format, ...) \
      debug_f(__FILE__, format __VA_OPT__(, ) __VA_ARGS__)

#define info(format, ...) \
      info_f(__FILE__, format __VA_OPT__(, ) __VA_ARGS__)

#define warn(format, ...) \
      warn_f(__FILE__, format __VA_OPT__(, ) __VA_ARGS__)

#define err \
      warn // Meanwhile the same format

//

static inline const std::string demangle(const char *name)
{
      int status;
      std::unique_ptr<char, void (*)(void *)> res{
          abi::__cxa_demangle(name, nullptr, nullptr, &status), free};
      return status ? name : res.get();
}

//

#define log_throw_exception(ex) \
      err(ITALIC CYAN "%s" RESET RED " has thrown an exception!\n" PADDING BOLD "%s: " RESET RED "%s", __PRETTY_FUNCTION__, demangle(typeid(ex).name()).c_str(), ex.what())

#define log_catch_and_throw_exception() \
      err(ITALIC CYAN "%s" RESET RED " has caught an exception, and thrown it forward!", __PRETTY_FUNCTION__)

#define log_catch_and_handle_exception() \
      err(ITALIC CYAN "%s" RESET RED " has caught an exception, but handled it!", __PRETTY_FUNCTION__)

#ifndef LOGGING_FUNCTION_CALLS

#define log_function_call(...)

#else // LOGGING_FUNCTION_CALLS

template <typename... Args>
static inline void _log_function_call(const char *fileName, const char *funcName, const Args &... args)
{
      verbose_f(fileName, ITALIC CYAN "%s", funcName);

      if constexpr (sizeof...(Args) > 0)
      { // Print the parameter types. They're embedded in the function's name
            std::string stripped(strchr(funcName, '('));
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

                  // std::cout << "\n";
                  ((std::cout << PADDING << i + 1 << ". " ITALIC CYAN << argsArr[j++] << RESET " => " ITALIC LIGHT_GREY << args << RESET << std::endl), ...);
            }
      }
}

#define log_function_call(...) \
      _log_function_call(__FILE__, __PRETTY_FUNCTION__ __VA_OPT__(, ) __VA_ARGS__)

#endif // LOGGING_FUNCTION_CALLS

} // namespace

#endif // LOGGING
