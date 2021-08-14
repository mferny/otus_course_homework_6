#include "BlockProcessor.h"

BlockProcessor::BlockProcessor(int bulkSize)
    : m_bulkSize(bulkSize)
    , m_logger{}
{
    subscribe(&m_logger);
}

void BlockProcessor::subscribe(Observer* obs)
{
    m_subs.push_back(obs);
}

void BlockProcessor::notify()
{
    for (auto s : m_subs)
    {
        s->update(m_block);
    }
}

void BlockProcessor::onBrace()
{
    notify();

    m_block.clear();
}

void BlockProcessor::pushToBaseBulk(const std::string_view command)
{
    m_block.emplace_back(command);

    if (m_block.size() == m_bulkSize)
    {
        notify();

        m_block.clear();
    }
}

void BlockProcessor::pushToExtendedBulk(const std::string_view command)
{
    m_block.emplace_back(command);
}

void BlockProcessor::checkOnExit()
{
    if (not m_block.empty())
    {
        notify();
    }
}