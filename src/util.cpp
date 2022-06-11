#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#include <winuser.h>

void shutdown() { ExitWindowsEx(EWX_POWEROFF, SHTDN_REASON_MINOR_OTHER); }
#endif

#ifdef __linux__
void shutdown() { system("poweroff"); }
#endif
