/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will print messages to the terminal, 
    depending on the minimum logging level defined.
*/

#pragma once
#include <iostream>
#include <string>
#include <ctime>

namespace Satellite {
    class Logger {
    public:
        enum class LogLevel {
            DEBUG, INFO, WARNING, SEVERE, ERROR
        };

        enum class LogPrefix {
            GENERAL, CLIENT, MAGNETOMETER
        };

        // Recommended minimal level:
        // - On debugging:     DEBUG/INFO
        // - Most of the time: WARNING
        // - When testing:     SEVERE
        static constexpr LogLevel MinLogLevel = LogLevel::INFO;
    private:
        static inline std::string current_time_string() {
            char buffer[11];
            time_t t;
            time(&t);
            tm *tmStruct = localtime(&t);
            strftime(buffer, sizeof(buffer), "[%H:%M:%S]", tmStruct);
            return buffer;
        }

        static inline std::string level_string(Logger::LogLevel level) {
            switch (level) {
            case Logger::LogLevel::DEBUG:
                return "DEBUG ";
            case Logger::LogLevel::INFO:
                return "INFO  ";
            case Logger::LogLevel::WARNING:
                return "WARN  ";
            case Logger::LogLevel::SEVERE:
                return "SEVERE";
            case Logger::LogLevel::ERROR:
                return "ERROR ";
            }
            return std::string();
        }

        static inline std::string prefix_string(Logger::LogPrefix prefix) {
            switch (prefix) {
            case Logger::LogPrefix::GENERAL:
                return "General";
            case Logger::LogPrefix::CLIENT:
                return "Client ";
            case Logger::LogPrefix::MAGNETOMETER:
                return "MGM    ";
            }
            return std::string();
        }

        template<class T>
        static inline void log(const T& t, LogPrefix prefix, LogLevel level) {
            std::cout << current_time_string();
            std::cout << " [" << level_string(level) << " - " << prefix_string(prefix) << "] ";
            std::cout << t << std::endl;
        }
    public:
        template<class T>
        static inline void debug(const T& t, LogPrefix prefix = LogPrefix::GENERAL) {
            if constexpr (MinLogLevel == LogLevel::DEBUG) {
                log(t, prefix, LogLevel::DEBUG);
            }
        }

        template<class T>
        static inline void info(const T& t, LogPrefix prefix = LogPrefix::GENERAL) {
            if constexpr (MinLogLevel <= LogLevel::INFO) {
                log(t, prefix, LogLevel::INFO);
            }
        }

        template<class T>
        static inline void warning(const T& t, LogPrefix prefix = LogPrefix::GENERAL) {
            if constexpr (MinLogLevel <= LogLevel::WARNING) {
                log(t, prefix, LogLevel::WARNING);
            }
        }
        
        template<class T>
        static inline void severe(const T& t, LogPrefix prefix = LogPrefix::GENERAL) {
            if constexpr (MinLogLevel <= LogLevel::SEVERE) {
                log(t, prefix, LogLevel::SEVERE);
            }
        }

        template<class T>
        static inline void error(const T& t, LogPrefix prefix = LogPrefix::GENERAL) {
            if constexpr (MinLogLevel <= LogLevel::ERROR) {
                log(t, prefix, LogLevel::ERROR);
            }
        }
    };
}