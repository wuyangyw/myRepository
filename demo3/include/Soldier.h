#pragma once
#include "Gun.h"
#include <string>

#include <iostream>

class Soldier
{
public:
    Soldier(std::string name) : _name(name), _ptr_gun(nullptr){};
    ~Soldier();
    void AddGun(Gun *ptr_gun);
    void AddBulletToGun(int num);
    bool Fire();

private:
    std::string _name;
    Gun *_ptr_gun;
};