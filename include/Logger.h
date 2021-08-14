#pragma once

#include "Observer.h"

#include <iostream>
#include <fstream>
#include <chrono>

class Logger : public Observer
{
public:
    void update(std::deque<std::string> bulk) override
    {
        logBulk(bulk);
        saveBulkToLogFile(bulk);
    }

    void logBulk(const std::deque<std::string>& bulk, std::ostream& ostream = std::cout)
    {
        if (bulk.empty())
        {
            return;
        }

        ostream << "bulk: ";
        for (auto iter = bulk.begin(); iter != bulk.end(); iter++)
        {
            ostream << *iter;
            if (iter != std::prev(bulk.end()))
            {
                ostream << ", ";
            }
        }
        ostream << std::endl;
    }

    void saveBulkToLogFile(const std::deque<std::string>& bulk)
    {
        if (bulk.empty())
        {
            return;
        }

        std::string timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>
                (std::chrono::system_clock::now().time_since_epoch()).count());
        std::string filename = "bulk";
        filename.append(timestamp).append(".log");

        std::fstream fstream(filename, std::ios::out | std::ios::app);
        if (not fstream.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        logBulk(bulk, fstream);
    }
};