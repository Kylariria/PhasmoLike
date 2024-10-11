#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

using namespace std;
using namespace sf;

#define STRING_ID(name) name + to_string(GetUniqueID())

int GetUniqueID();

int Random(const int _max, const int _min = 0);