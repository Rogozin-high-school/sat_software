/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will contain useful functions.
*/

#pragma once

#include "main.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <sstream>

namespace SatelliteSoftware {
    struct Helper {
        static std::string current_time_string() {
            char buffer[9];
            time_t t;
            time(&t);
            tm *tmStruct = localtime(&t);
            strftime(buffer, sizeof(buffer), "%H:%M:%S", tmStruct);
            return buffer;
        }

        static std::string current_date_string() {
            char buffer[23];
            time_t t;
            time(&t);
            tm *tmStruct = localtime(&t);
            strftime(buffer, sizeof(buffer), "%a, %d %b %Y", tmStruct);
            return buffer;
        }

        static void clear_screen() {
            int unused = system("clear");
        }

        static void print_date() {
            std::string date = current_date_string();
            int len = date.length();
            std::cout << "+";
            for (int i = 0; i < len + 2; i++)
                std::cout << "-";
            std::cout << "+\n| " << date << " |\n+";
            for (int i = 0; i < len + 2; i++)
                std::cout << "-";
            std::cout << "+" << std::endl;
        }

        static std::string address_to_string(const std::array<int, 4>& address) {
            return std::to_string(address[0]) + "." + 
                std::to_string(address[1]) + "." + 
                std::to_string(address[2]) + "." + 
                std::to_string(address[3]);
        }

        static std::string time_period_to_string(
            const std::chrono::high_resolution_clock::time_point& start, 
            const std::chrono::high_resolution_clock::time_point& end) 
        {
            auto duration = (end - start).count() > 0 ? end - start : start - end;
            int64_t h = std::chrono::duration_cast<std::chrono::hours>(duration).count();
            duration %= std::chrono::hours(1);
            int64_t m = std::chrono::duration_cast<std::chrono::minutes>(duration).count();
            duration %= std::chrono::minutes(1);
            int64_t s = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
            duration %= std::chrono::seconds(1);
            int64_t ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
            duration %= std::chrono::milliseconds(1);
            int64_t us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
            std::stringstream ss;

            if (h > 0) {
                if (m > 0) {
                    if (s > 0) {
                        if (ms > 0) {
                            if (us > 0)
                                ss << h << "h, " << m << "m, " << s << "s, " << ms << "ms and " << us << "µs";
                            else
                                ss << h << "h, " << m << "m, " << s << "s and " << ms << "ms";
                        } else {
                            if (us > 0)
                                ss << h << "h, " << m << "m, " << s << "s and " << us << "µs";
                            else
                                ss << h << "h, " << m << "m and " << s << "s";
                        }
                    } else {
                        if (ms > 0) {
                            if (us > 0)
                                ss << h << "h, " << m << "m, " << ms << "ms and " << us << "µs";
                            else
                                ss << h << "h, " << m << "m and " << ms << "ms";
                        } else {
                            if (us > 0)
                                ss << h << "h, " << m << "m and " << us << "µs";
                            else
                                ss << h << "h and " << m << "m";
                        }
                    }
                } else {
                    if (s > 0) {
                        if (ms > 0) {
                            if (us > 0)
                                ss << h << "h, " << s << "s, " << ms << "ms and " << us << "µs";
                            else
                                ss << h << "h, " << s << "s and " << ms << "ms";
                        } else {
                            if (us > 0)
                                ss << h << "h, " << s << "s and " << us << "µs";
                            else
                                ss << h << "h and " << s << "s";
                        }
                    } else {
                        if (ms > 0) {
                            if (us > 0)
                                ss << h << "h, " << ms << "ms and " << us << "µs";
                            else
                                ss << h << "h and " << ms << "ms";
                        } else {
                            if (us > 0)
                                ss << h << "h and " << us << "µs";
                            else
                                ss << h << "h";
                        }
                    }
                }
            } else {
                if (m > 0) {
                    if (s > 0) {
                        if (ms > 0) {
                            if (us > 0)
                                ss << m << "m, " << s << "s, " << ms << "ms and " << us << "µs";
                            else
                                ss << m << "m, " << s << "s and " << ms << "ms";
                        } else {
                            if (us > 0)
                                ss << m << "m, " << s << "s and " << us << "µs";
                            else
                                ss << m << "m and " << s << "s";
                        }
                    } else {
                        if (ms > 0) {
                            if (us > 0)
                                ss << m << "m, " << ms << "ms and " << us << "µs";
                            else
                                ss << m << "m and " << ms << "ms";
                        } else {
                            if (us > 0)
                                ss << m << "m and " << us << "µs";
                            else
                                ss << m << "m";
                        }
                    }
                } else {
                    if (s > 0) {
                        if (ms > 0) {
                            if (us > 0)
                                ss << s << "s, " << ms << "ms and " << us << "µs";
                            else
                                ss << s << "s and " << ms << "ms";
                        } else {
                            if (us > 0)
                                ss << s << "s and " << us << "µs";
                            else
                                ss << s << "s";
                        }
                    } else {
                        if (ms > 0) {
                            if (us > 0)
                                ss << ms << "ms and " << us << "µs";
                            else
                                ss << ms << "ms";
                        } else if (us > 0)
                            ss << us << "µs";
                    }
                }
            }
            return ss.str();
        }
    };
}