/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will contain useful functions.
*/

#pragma once

#include <ctime>
#include <chrono>
#include <thread>
#include <functional>
#include <iostream>
#include <string>
#include <sstream>

using Timepoint = std::chrono::high_resolution_clock::time_point;

class Helper {
public:
    static inline std::string time_period_to_string(const Timepoint& start, const Timepoint& end) {
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

    template<typename Rep, typename Period>
    static void draw_animation_with_dots(const bool& breakingCondition,
        const std::string baseText,
        const std::chrono::duration<Rep, Period>& delay,
        const uint8_t minDots,
        const uint8_t maxDots,
        const std::function<void(const std::string& text)> function)
    {
        bool increasingDotsCount = true;
        uint8_t dots = minDots;
        while (!breakingCondition) {
            std::string text = baseText;
            uint8_t i = 0;
            for (; i < dots; i++) {
                text += ".";
            }
            for (; i < maxDots; i++) {
                text += " ";
            }
            function(text);
            std::this_thread::sleep_for(delay);
            std::cout << "\033[A\33[2K\r" << std::flush; // Move to the previous line
            if (increasingDotsCount) {
                if (++dots == maxDots) {
                    increasingDotsCount = false;
                }
            } else {
                if (--dots == minDots) {
                    increasingDotsCount = true;
                }
            }
        }
    }
};