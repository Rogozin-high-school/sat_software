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
    VERBOSE, DEBUG, INFO, WARNING, SEVERE, ERROR
};

enum class LogPrefix {
    GENERAL, CLIENT, IMU, MAGNETORQUER, HBRIDGE, GPIO
};

constexpr LogLevel minLogLevel = LogLevel::VERBOSE;

class Logger {
public:
    template<LogPrefix prefix, class T, bool endl = true>
    static void verbose(const T& t) {
        if constexpr(minLogLevel == LogLevel::VERBOSE) {
            log<T, prefix, LogLevel::VERBOSE, endl>(t);
        }
    }

    template<LogPrefix prefix, class T, bool endl = true>
    static void debug(const T& t) {
        if constexpr(minLogLevel <= LogLevel::DEBUG) {
            log<T, prefix, LogLevel::DEBUG, endl>(t);
        }
    }

    template<LogPrefix prefix, class T, bool endl = true>
    static void info(const T& t) {
        if constexpr(minLogLevel <= LogLevel::INFO) {
            log<T, prefix, LogLevel::INFO, endl>(t);
        }
    }

    template<LogPrefix prefix, class T, bool endl = true>
    static void warn(const T& t) {
        if constexpr(minLogLevel <= LogLevel::WARNING) {
            log<T, prefix, LogLevel::WARNING, endl>(t);
        }
    }
    
    template<LogPrefix prefix, class T, bool endl = true>
    static void severe(const T& t) {
        if constexpr(minLogLevel <= LogLevel::SEVERE) {
            log<T, prefix, LogLevel::SEVERE, endl>(t);
        }
    }

    template<LogPrefix prefix, class T, bool endl = true>
    static void error(const T& t) {
        log<T, prefix, LogLevel::ERROR, endl>(t);
    }
private:
    static const tm *current_time_c() {
        time_t t;
        time(&t);
        return localtime(&t);
    }

    static const std::string current_time_string() {
        char buffer[9];
        strftime(buffer, sizeof(buffer), "%H:%M:%S", current_time_c());
        return buffer;
    }

    template<LogLevel level>
    static constexpr std::string level_string() {
        if constexpr(level == LogLevel::VERBOSE)
            return "VERBOSE";
        if constexpr(level == LogLevel::DEBUG)
            return "DEBUG  ";
        if constexpr(level == LogLevel::INFO)
            return "INFO   ";
        if constexpr(level == LogLevel::WARNING)
            return "WARNING";
        if constexpr(level == LogLevel::SEVERE)
            return "SEVERE ";
        if constexpr(level == LogLevel::ERROR)
            return "ERROR  ";
    }

    template<LogPrefix prefix>
    static constexpr std::string prefix_string() {
        if constexpr(prefix == LogPrefix::GENERAL)
            return "      General";
        if constexpr(prefix == LogPrefix::CLIENT)
            return "       Client";
        if constexpr(prefix == LogPrefix::IMU)
            return "          IMU";
        if constexpr(prefix == LogPrefix::MAGNETORQUER)
            return " Magnetorquer";
        if constexpr(prefix == LogPrefix::HBRIDGE)
            return "      HBridge";
        if constexpr(prefix == LogPrefix::GPIO)
            return "         GPIO";
    }

    template<class T, LogPrefix prefix, LogLevel level, bool endl>
    static void log(const T& t) {
        std::stringstream ss;
        ss << "[" << current_time_string() << "] ";
        ss << "[" << level_string<level>() << " - " << prefix_string<prefix>() << "] ";
        ss << t;

        if constexpr(endl) {
            ss << std::endl;
        }
        
        std::cout << ss.str();
    }
};