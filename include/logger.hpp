#pragma once

#include <iostream>

static inline struct LogStream
{
      typedef LogStream& (*Manipulator)(LogStream&);
      typedef std::ostream& (*Manipulator_EndLine)(std::ostream&);

      LogStream& operator<<(Manipulator manipulator)
      {
            return manipulator(*this);
      }

      LogStream& operator<<(Manipulator_EndLine manipulator)
      {
#ifdef LOGGING
            manipulator(std::cout);
#endif // LOGGING
            return *this;
      }
      
      template<typename T>
      LogStream& operator<<(const T& x)
      {
#ifdef LOGGING
            std::cout << x;
#endif // LOGGING
            return *this;
      }
} log;