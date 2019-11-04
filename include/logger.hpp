/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will print messages to the terminal, 
    depending on the minimum logging level defined.
*/

#pragma once

#include <helper.hpp>
#include <sstream>

enum class LogLevel {
    DEBUG, INFO, WARNING, SEVERE, ERROR
};

enum class LogPrefix {
    GENERAL, CLIENT, IMU
};

constexpr LogLevel minLogLevel = LogLevel::DEBUG;

class Logger {
    #ifdef RASPBERRY_PI
    static constexpr bool isRaspberryPi = true;
    #else
    static constexpr bool isRaspberryPi = false;
    #endif // RASPBERRY_PI
public:
    template<typename T>
    static inline void debug(const T& t, const LogPrefix prefix = LogPrefix::GENERAL) {
        if constexpr(minLogLevel == LogLevel::DEBUG) {
            log(t, prefix, LogLevel::DEBUG);
        }
    }

    template<typename T>
    static inline void info(const T& t, const LogPrefix prefix = LogPrefix::GENERAL) {
        if constexpr(minLogLevel <= LogLevel::INFO) {
            log(t, prefix, LogLevel::INFO);
        }
    }

    template<typename T>
    static inline void warn(const T& t, const LogPrefix prefix = LogPrefix::GENERAL) {
        if constexpr(minLogLevel <= LogLevel::WARNING) {
            log(t, prefix, LogLevel::WARNING);
        }
    }
    
    template<typename T>
    static inline void severe(const T& t, const LogPrefix prefix = LogPrefix::GENERAL) {
        if constexpr(minLogLevel <= LogLevel::SEVERE) {
            log(t, prefix, LogLevel::SEVERE);
        }
    }

    template<typename T>
    static inline void error(const T& t, const LogPrefix prefix = LogPrefix::GENERAL) {
        if constexpr(minLogLevel <= LogLevel::ERROR) {
            log(t, prefix, LogLevel::ERROR);
        }
    }
private:
    static inline const std::string level_string(const LogLevel level) {
        switch (level) {
        case LogLevel::DEBUG:
            return "DEBUG  ";
        case LogLevel::INFO:
            return "INFO   ";
        case LogLevel::WARNING:
            return "WARNING";
        case LogLevel::SEVERE:
            return "SEVERE ";
        case LogLevel::ERROR:
            return "ERROR  ";
        }
        throw std::invalid_argument("Invalid logging level!");
    }

    static inline const std::string prefix_string(const LogPrefix prefix) {
        switch (prefix) {
        case LogPrefix::GENERAL:
            return  "General";
        case LogPrefix::CLIENT:
            return  " Client";
        case LogPrefix::IMU:
            return isRaspberryPi ? 
                    "    IMU" : 
                    "FakeIMU";
        }
        throw std::invalid_argument("Invalid logging prefix!");
    }

    template<typename T>
    static inline void log(const T& t, const LogPrefix prefix, const LogLevel level) {
        std::stringstream ss;
        
        ss << "[" << Helper::current_time_string() << "] ";
        ss << "[" << level_string(level) << " - " << prefix_string(prefix) << "] ";
        ss << t << std::endl;

        std::cout << ss.str();
    }
};