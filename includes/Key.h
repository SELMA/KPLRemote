#ifndef KEY_H_
#define KEY_H_

#include <iostream>
#include <string>
#include <Windows.h>
#include <map>
#include <sstream>
#include <Winuser.h>

#define MAPVK_VK_TO_VSC         0
#define MAPVK_VSC_TO_VK         1
#define MAPVK_VK_TO_CHAR        2
#define MAPVK_VSC_TO_VK_EX      3
#define MAPVK_VK_TO_VSC_EX      4

#define X                       0
#define Y                       1

class Key
{
private:
    std::map<int, bool (Key::*)()>                          _key;
    std::string                                             _buffer;
    bool                                                    _stat;
    int                                                     _lastKey;
    bool                                                    _upper;
    bool                                                    vkKey(int);
    bool                                                    vkBack();
    bool                                                    vkLbutton();
    bool                                                    vkRbutton();
    bool                                                    vkTab();
    bool                                                    vkReturn();
    bool                                                    vkShift();
    bool                                                    vkControl();
    bool                                                    vkEscape();
    bool                                                    vkUp();
    bool                                                    vkRight();
    bool                                                    vkLeft();
    bool                                                    vkDown();
    bool                                                    vkInsert();
    bool                                                    vkDelete();
    bool                                                    vkCapital();
    std::string                                             getCursorPos(int);

public:
    Key();
    ~Key();
    bool                                                    getKey();
    std::string                                             getBuffer() const;
    void                                                    putKeyBuff(int);
    void                                                    putKeyBuff(std::string);
    void                                                    putKeyBuff(std::string, std::string, std::string);
    void                                                    rmLastKeyBuff();
    void                                                    cleanBuff();
    void                                                    setStat();
};

#endif /* KEY_H_ */