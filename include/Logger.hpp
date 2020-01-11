#pragma once

#include <stdexcept>

#ifndef LOGGING

#define verbose(...)
#define debug(...)
#define info(...)
#define warn(...)
#define err(...)
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
#define ENDL "\n" PADDING

#define FUNCTION_NAME (strrchr(__PRETTY_FUNCTION__, ' ') + 1)
#define MODULE_NAME module_name(__FILE__).c_str()

static inline const auto module_name(const char *fileName)
{
      const std::string fileName_noPath{strrchr(fileName, '/') ? strrchr(fileName, '/') + 1 : fileName};
      return fileName_noPath.substr(0, fileName_noPath.size() - (sizeof(".cpp") - 1));
}

static inline void log(const char *color, const char *moduleName, const char *format, ...)
{
      va_list va;
      va_start(va, format);

      std::stringstream formatStr;

      formatStr << color;
      if (moduleName != nullptr)
      {
            formatStr << std::left << std::setw(sizeof(PADDING) - sizeof(" -> ")) << std::setfill(' ') << moduleName;
      }
      formatStr << RESET " -> " << format << RESET << "\n";

      vprintf(formatStr.str().c_str(), va);
      va_end(va);
}

#define verbose(format, ...) log(CYAN, MODULE_NAME, format __VA_OPT__(, ) __VA_ARGS__)
#define debug(format, ...) log(LIGHT_GREY, MODULE_NAME, format __VA_OPT__(, ) __VA_ARGS__)
#define info(format, ...) log(WHITE, MODULE_NAME, format __VA_OPT__(, ) __VA_ARGS__)
#define warn(format, ...) log(RED, MODULE_NAME, format __VA_OPT__(, ) __VA_ARGS__)
#define err warn // Meanwhile the same format

static inline const std::string demangle(const char *name)
{
      int status;
      std::unique_ptr<char, void (*)(void *)> res{
          abi::__cxa_demangle(name, nullptr, nullptr, &status), free};
      return status ? name : res.get();
}

#define log_throw_exception(ex) \
      err(ITALIC CYAN "%s" RESET RED " has thrown an exception!" ENDL BOLD "%s: " RESET RED "%s", FUNCTION_NAME, demangle(typeid(ex).name()).c_str(), ex.what())
#define log_catch_and_throw_exception() \
      err(ITALIC CYAN "%s" RESET RED " has caught an exception, and thrown it forward!", FUNCTION_NAME)
#define log_catch_and_handle_exception() \
      err(ITALIC CYAN "%s" RESET RED " has caught an exception, but handled it!", FUNCTION_NAME)

#ifndef LOGGING_FUNCTION_CALLS

#define log_function_call(...)

#else // LOGGING_FUNCTION_CALLS

template <typename... Args>
static inline void _log_function_call(const char *moduleName, const char *funcName, const Args &... args)
{
      log(CYAN, moduleName, ITALIC CYAN "%s", funcName); // verbose

      if constexpr (sizeof...(Args) > 0)
      {
            ((std::cout << PADDING "- \"" ITALIC LIGHT_GREY << args << RESET "\"" << std::endl), ...);
      }
}

#define log_function_call(...) _log_function_call(MODULE_NAME, FUNCTION_NAME __VA_OPT__(, ) __VA_ARGS__)

#endif // LOGGING_FUNCTION_CALLS

} // namespace

#endif // LOGGING
