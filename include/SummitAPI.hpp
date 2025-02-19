
#ifdef GEODE_IS_WINDOWS
#ifdef KM7DEV_SUMMIT_EXPORTING
#define SUMMIT_DLL __declspec(dllexport)
#else
#define SUMMIT_DLL __declspec(dllimport)
#endif
#else
#define SUMMIT_DLL __attribute__((visibility("default")))
#endif