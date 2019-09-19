/*
    Created by Maor Gershman, 25.8.2019
    ---
    This class will contain useful functions.
*/

#pragma once

#include "main.h"
#include <ctime>
#include <functional>

namespace SatelliteSoftware {
    struct Helper {
        static const tm *current_time_c();

        static const Timepoint current_time();

        static std::string current_time_string();

        static std::string current_date_string();

        static void clear_screen();

        static void print_date();

        static void start_date_printing_loop();

        static std::string time_period_to_string(const Timepoint& start, const Timepoint& end);
    
        template<typename Rep, typename Period>
        static void draw_animation_with_dots(
            const bool& breakingCondition,
            const std::string baseText,
            const std::chrono::duration<Rep, Period>& delay,
            const int minDots,
            const int maxDots,
            const std::function<void(const std::string& text)> function
        )
        {
            bool increasingDotsCount = true;
            int dots = minDots;
            while (!breakingCondition) {
                std::string text = baseText;
                int i = 0;
                for (; i < dots; i++)
                    text += ".";
                for (; i < maxDots; i++)
                    text += " ";
                function(text);
                std::this_thread::sleep_for(delay);
                std::cout << "\x1B[1F" << std::flush; // Move to the previous line
                if (increasingDotsCount) {
                    if (++dots == maxDots)
                        increasingDotsCount = false;
                } else {
                    if (--dots == minDots)
                        increasingDotsCount = true;
                }
            }
        }
    };
}