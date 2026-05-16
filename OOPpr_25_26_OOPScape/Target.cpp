#include "Target.h"

Target::Target(int _x, int _y, int _hp, int _mhp) : Damageable(_hp, _mhp), Position(_x, _y) { }