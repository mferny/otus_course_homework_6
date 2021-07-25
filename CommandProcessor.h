#pragma once

#include "BlockProcessor.h"

#include <string_view>

enum class BulkState
{
    BaseBlock,
    ExtendedBlock,
};

class CommandProcessor
{
public:
    explicit CommandProcessor(int blockSize)
            : m_state(BulkState::BaseBlock)
            , m_blockProcessor(blockSize)
    {
        //
    }

    void onEvent(const std::string_view command)
    {
        if (command == "{")
        {
            if (m_depth == 0)
            {
                m_state = BulkState::ExtendedBlock;
                m_blockProcessor.onBrace();
            }
            m_depth++;
        }
        else if (command == "}")
        {
            m_depth--;
            if (m_depth == 0)
            {
                m_state = BulkState::BaseBlock;
                m_blockProcessor.onBrace();
            }
        }
        else
        {
            if (m_state == BulkState::BaseBlock)
            {
                m_blockProcessor.pushToBaseBulk(command);
            }
            else
            {
                m_blockProcessor.pushToExtendedBulk(command);
            }
        }
    }

    void onExit()
    {
        if (m_state == BulkState::BaseBlock)
        {
            return m_blockProcessor.checkOnExit();
        }
    }

private:
    BlockProcessor m_blockProcessor;
    BulkState m_state;
    int m_depth = 0;
};
