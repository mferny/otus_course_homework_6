#pragma once

#include <deque>

class Observer
{
public:
    virtual void update(std::deque<std::string>) = 0;
};