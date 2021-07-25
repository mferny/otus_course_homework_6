#pragma once

#include "Logger.h"

class BlockProcessor
{
public:
    BlockProcessor(int bulkSize)
            : m_bulkSize(bulkSize)
    {}

    void onBrace()
    {
        Logger::logBulk(m_block);
        Logger::saveBulkToLogFile(m_block);

        m_block.clear();
    }

    void pushToBaseBulk(const std::string_view command)
    {
        m_block.emplace_back(command);

        if (m_block.size() == m_bulkSize)
        {
            Logger::logBulk(m_block);
            Logger::saveBulkToLogFile(m_block);

            m_block.clear();
        }
    }

    void pushToExtendedBulk(const std::string_view command)
    {
        m_block.emplace_back(command);
    }

    void checkOnExit()
    {
        if (not m_block.empty())
        {
            Logger::logBulk(m_block);
            Logger::saveBulkToLogFile(m_block);
        }
    }

private:
    int m_bulkSize = 0;
    std::deque<std::string> m_block;
};