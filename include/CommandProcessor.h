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

    void onEvent(const std::string_view command);

    void onExit();

private:
    BlockProcessor m_blockProcessor;
    BulkState m_state;
    int m_depth = 0;
};
