/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will print messages to the terminal, 
    depending on the minimum logging level defined.
*/

#pragma once

#include "main.h"
#include "helper.h"

namespace SatelliteSoftware {
    enum class LogLevel {
        DEBUG, INFO, WARNING, SEVERE, ERROR
    };

    constexpr LogLevel MinLogLevel = LogLevel::INFO;

    enum class LogPrefix {
        GENERAL, CLIENT, REALIMU, FAKEIMU, IMU
    };

    class Logger {
    private:
        static std::string level_string(LogLevel level) {
            switch (level) {
            case LogLevel::DEBUG:
                return "DEBUG ";
            case LogLevel::INFO:
                return "INFO  ";
            case LogLevel::WARNING:
                return "WARN  ";
            case LogLevel::SEVERE:
                return "SEVERE";
            case LogLevel::ERROR:
                return "ERROR ";
            }
            return std::string();
        }

        static std::string prefix_string(LogPrefix prefix) {
            if (prefix == LogPrefix::IMU)
                prefix = IsRaspberryPi ? LogPrefix::REALIMU : LogPrefix::FAKEIMU;

            switch (prefix) {
            case LogPrefix::GENERAL:
                return "General";
            case LogPrefix::CLIENT:
                return " Client";
            case LogPrefix::REALIMU:
                return "RealIMU";
            case LogPrefix::FAKEIMU:
                return "FakeIMU";
            }
            return std::string();
        }

        template<typename T>
        static void log(const T& t, LogPrefix prefix, LogLevel level) {
            std::cout << "[" << Helper::current_time_string() << "] ";
            std::cout << "[" << level_string(level) << " - " << prefix_string(prefix) << "] ";
            std::cout << t << std::endl;
        }
    public:
        template<typename T>
        static void debug(const T& t, LogPrefix prefix = LogPrefix::GENERAL) {
            if constexpr(MinLogLevel == LogLevel::DEBUG) {
                log(t, prefix, LogLevel::DEBUG);
            }
        }

        template<typename T>
        static void info(const T& t, LogPrefix prefix = LogPrefix::GENERAL) {
            if constexpr(MinLogLevel <= LogLevel::INFO) {
                log(t, prefix, LogLevel::INFO);
            }
        }

        template<typename T>
        static void warn(const T& t, LogPrefix prefix = LogPrefix::GENERAL) {
            if constexpr(MinLogLevel <= LogLevel::WARNING) {
                log(t, prefix, LogLevel::WARNING);
            }
        }
        
        template<typename T>
        static void severe(const T& t, LogPrefix prefix = LogPrefix::GENERAL) {
            if constexpr(MinLogLevel <= LogLevel::SEVERE) {
                log(t, prefix, LogLevel::SEVERE);
            }
        }

        template<typename T>
        static void error(const T& t, LogPrefix prefix = LogPrefix::GENERAL) {
            if constexpr(MinLogLevel <= LogLevel::ERROR) {
                log(t, prefix, LogLevel::ERROR);
            }
        }
    };
}