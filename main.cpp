// For Windows support, is checked on compile-time
#if defined (__WIN32__)
    #ifndef TINS_STATIC
    #define TINS_STATIC
    #endif //TINS_STATIC
#endif

#if defined (_WIN32)
    #ifndef TINS_STATIC
    #define TINS_STATIC
    #endif //TINS_STATIC
#endif

#if defined (_MSC_VER)
    #ifndef TINS_STATIC
    #define TINS_STATIC
    #endif //TINS_STATIC
#endif

#if defined (__CYGWIN32__)
    #ifndef TINS_STATIC
    #define TINS_STATIC
    #endif //TINS_STATIC
#endif
//------------------------------------------------------------

#include <tins/tins.h>

// "C:\Program Files\CMake\bin\cmake.exe" "../" -DPCAP_ROOT_DIR="C:\Users\loris\OneDrive\Dokumente\GitHub\cpp-ProbeRequests\libs\WinPcap\WpdPack" -DLIBTINS_ENABLE_WPA2=1 -DLIBTINS_BUILD_SHARED=0