#include "Soldier.h"
#include "Gun.h"
#include <iostream>

void Test()
{
    Soldier soldier("XuSanDuo");
    soldier.AddGun(new Gun("AK47"));
    soldier.AddBulletToGun(20);
    soldier.Fire();
}

int main()
{
    std::cout << "this is a test!" << std::endl;
    Test();
    return 0;
}