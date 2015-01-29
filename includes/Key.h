#ifndef KEY_H_
#define KEY_H_

#include <iostream>
#include <string>
#include <Windows.h>
#include <map>
#include <sstream>

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

public:
    Key();
    ~Key();
    bool                                                    getKey();
    std::string                                             getBuffer() const;
    void                                                    putKeyBuff(int);
    void                                                    putKeyBuff(std::string);
    void                                                    rmLastKeyBuff();
    void                                                    cleanBuff();
    void                                                    setStat();
};

#endif /* KEY_H_ */