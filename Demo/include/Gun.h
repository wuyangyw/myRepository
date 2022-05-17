#pragma once
#include <string>

class Gun
{
public:
    Gun(std::string type) : _bullet_count(0), _type(type){};
    void AddBullet(int bullet_num);
    bool Shoot();

private:
    int _bullet_count;
    std::string _type;
};