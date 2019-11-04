/*
    Created by Maor Gershman, 9.9.2019
    ---
    This class will contain useful functions.
*/

#include <helper.hpp>
#include <iostream>
#include <sstream>

const tm *Helper::current_time_c() {
    time_t t;
    time(&t);
    return localtime(&t);
}

const Timepoint Helper::current_time() {
    return std::chrono::high_resolution_clock::now();
}

std::string Helper::current_time_string() {
    char buffer[9];
    strftime(buffer, sizeof(buffer), "%H:%M:%S", current_time_c());
    return buffer;
}

std::string Helper::current_date_string() {
    char buffer[23];
    strftime(buffer, sizeof(buffer), "%a, %d %b %Y", current_time_c());
    return buffer;
}

void Helper::clear_screen() {
    int unused = system("clear");
}

void Helper::print_date() {
    const std::string date = current_date_string();
    const int len = date.length();
    std::stringstream ss;

    ss << "+";
    for (int i = 0; i < len + 2; i++)
        ss << "-";
    ss << "+\n| " << date << " |\n+";
    for (int i = 0; i < len + 2; i++)
        ss << "-";
    ss << "+" << std::endl;

    std::cout << ss.str();
}

std::string Helper::time_period_to_string(const Timepoint& start, const Timepoint& end) {
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