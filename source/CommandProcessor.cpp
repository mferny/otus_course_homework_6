#include "CommandProcessor.h"

void CommandProcessor::onEvent(const std::string_view command)
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

void CommandProcessor::onExit()
{
    if (m_state == BulkState::BaseBlock)
    {
        return m_blockProcessor.checkOnExit();
    }
}