#include "Macro.h"

int GetUniqueID()
{
    static int _value = 0;
    return _value++;
}

int Random(const int _max, const int _min)
{
    random_device _rd;
    mt19937 _seed(_rd());
    uniform_int_distribution<int> _distribution(_min, _max);
    return _distribution(_seed);
}
