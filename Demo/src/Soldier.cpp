#include "Soldier.h"

Soldier::~Soldier()
{
    if (this->_ptr_gun = nullptr)
    {
        return;
    }
    delete this->_ptr_gun;
    this->_ptr_gun = nullptr;
}

void Soldier::AddGun(Gun *ptr_gun)
{
    this->_ptr_gun = ptr_gun;
}

void Soldier::AddBulletToGun(int num)
{
    this->_ptr_gun->AddBullet(num);
}

bool Soldier::Fire()
{
    return (this->_ptr_gun->Shoot());
}
