#pragma once

#include <deque>
#include <string>

class Observer
{
public:
    virtual void update(std::deque<std::string>) = 0;
};