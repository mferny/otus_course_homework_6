#pragma once

#include "Logger.h"

#include <vector>
#include <string>
#include <deque>

class BlockProcessor
{
public:
    explicit BlockProcessor(int bulkSize);

    void subscribe(Observer* obs);

    void notify();

    void onBrace();

    void pushToBaseBulk(const std::string_view command);

    void pushToExtendedBulk(const std::string_view command);

    void checkOnExit();

private:
    int m_bulkSize = 0;
    std::deque<std::string> m_block;
    std::vector<Observer*> m_subs;
    Logger m_logger;
};