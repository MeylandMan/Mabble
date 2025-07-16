#pragma once

#ifdef MABBLE_SHARED
  #ifdef MABBLE_BUILD
    #define MABBLE_API __declspec(dllexport)
  #else
    #define MABBLE_API __declspec(dllimport)
  #endif
#else
  #define MABBLE_API
#endif