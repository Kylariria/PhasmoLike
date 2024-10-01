#include "TextLibrary.h"

string TextLibrary::HauntString(const string& _originalString)
{
    string _finalString = "";
    const int _size = _originalString.length();
    const char _charList[4] = { '@', '€', '$', '#'};
    for (int _index = 0; _index < _size; _index++)
    {
        if (rand() % 100 + 1 < 25) // 25% to replace with other char
        {
            _finalString += _charList[rand() % 4];
        }
        else
        {
            if (rand() % 100 + 1 < 50)
            {
                _finalString += _originalString[_index];
            }
            else
            {
                _finalString += toupper(_originalString[_index]);
            }
        }
    }

    return _finalString;
}
