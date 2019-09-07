/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will print messages to the terminal, 
    depending on the minimum logging level defined.
*/

#pragma once
#include "helper.h"

namespace SatelliteSoftware {
    class Logger {
    public:
        enum class Level {
            DEBUG, INFO, WARNING, SEVERE, ERROR
        };

        enum class Prefix {
            GENERAL, CLIENT, IMU
        };

        // Recommended minimal level:
        // - On debugging:     DEBUG/INFO
        // - When testing:     SEVERE
        static constexpr Level MinLogLevel = Level::DEBUG;
    private:
        static std::string level_string(Logger::Level level) {
            switch (level) {
            case Logger::Level::DEBUG:
                return "DEBUG ";
            case Logger::Level::INFO:
                return "INFO  ";
            case Logger::Level::WARNING:
                return "WARN  ";
            case Logger::Level::SEVERE:
                return "SEVERE";
            case Logger::Level::ERROR:
                return "ERROR ";
            }
            return std::string();
        }

        static std::string prefix_string(Logger::Prefix prefix) {
            switch (prefix) {
            case Logger::Prefix::GENERAL:
                return "General";
            case Logger::Prefix::CLIENT:
                return " Client";
            case Logger::Prefix::IMU:
                return "    IMU";
            }
            return std::string();
        }

        template<class T>
        static void log(const T& t, Prefix prefix, Level level) {
            std::cout << "[" << Helper::current_time_string() << "] ";
            std::cout << "[" << level_string(level) << " - " << prefix_string(prefix) << "] ";
            std::cout << t << std::endl;
        }
    public:
        template<class T>
        static void debug(const T& t, Prefix prefix = Prefix::GENERAL) {
            if constexpr (MinLogLevel == Level::DEBUG) {
                log(t, prefix, Level::DEBUG);
            }
        }

        template<class T>
        static void info(const T& t, Prefix prefix = Prefix::GENERAL) {
            if constexpr (MinLogLevel <= Level::INFO) {
                log(t, prefix, Level::INFO);
            }
        }

        template<class T>
        static void warning(const T& t, Prefix prefix = Prefix::GENERAL) {
            if constexpr (MinLogLevel <= Level::WARNING) {
                log(t, prefix, Level::WARNING);
            }
        }
        
        template<class T>
        static void severe(const T& t, Prefix prefix = Prefix::GENERAL) {
            if constexpr (MinLogLevel <= Level::SEVERE) {
                log(t, prefix, Level::SEVERE);
            }
        }

        template<class T>
        static void error(const T& t, Prefix prefix = Prefix::GENERAL) {
            if constexpr (MinLogLevel <= Level::ERROR) {
                log(t, prefix, Level::ERROR);
            }
        }
    };
}