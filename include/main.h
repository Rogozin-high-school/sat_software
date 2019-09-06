/*
    Created by Maor Gershman, 25.8.2019
    ---
    This file will contains important constants,
    and other things needed in global scope.
*/

#pragma once
#include <string>

// AFAIK, __arm__ is only defined in Raspberry Pi.
#ifdef __arm__
#define RASPBERRY_PI // A much clearer name :)
#endif

namespace Satellite {
    /*
        Contants. 
        Convention: CamelCase.
    */

    constexpr bool Debug = true;
    constexpr const char *Address = "10.17.110.69";
    constexpr int Port = 550;
    constexpr int SocketTimeoutSeconds = 5;
}