#include "MyIrc.h"

int             main() {
    MyIrc	irc;
    char	buf[1024];
    DWORD 	dwCompNameLen = 1024;

    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    if (GetComputerName(buf, &dwCompNameLen)) {
        irc.setComputerName(std::string(buf));
        if (irc.load(false))
            return (true);
    }
    return (false);
}
