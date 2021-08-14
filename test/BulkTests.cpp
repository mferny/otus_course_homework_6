#define BOOST_TEST_MODULE test_bulk

#include "../include/CommandProcessor.h"

#include <boost/test/unit_test.hpp>
#include <thread>

BOOST_AUTO_TEST_SUITE(CheckBase)

BOOST_AUTO_TEST_CASE(CheckFile)
{
    std::vector<std::string_view> commands = {
            "cmd1",
            "cmd2",
            "cmd3",
    };

    CommandProcessor processor(3);
    for(const auto cmd : commands)
    {
        processor.onEvent(cmd);
    }

    std::string timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>
            (std::chrono::system_clock::now().time_since_epoch()).count());
    std::string filename = "bulk";
    filename.append(timestamp).append(".log");

    std::fstream fstream;
    fstream.open(filename, std::fstream::in);
    if (not fstream.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string input;
    while (std::getline(fstream, input))
    {
        BOOST_CHECK_EQUAL(input, "bulk: cmd1, cmd2, cmd3");
    }
}

    BOOST_AUTO_TEST_CASE(CheckExtendedBlock)
    {
        std::vector<std::string_view> commands = {
                "cmd1",
                "cmd2",
                "cmd3",
                "{",
                "cmd4",
                "cmd5",
                "}",
                "{",
                "cmd5",
                "cmd6",
                "{",
                "cmd7",
                "cmd8",
                "}",
                "cmd9",
                "}"
        };

        CommandProcessor processor(3);
        for(const auto cmd : commands)
        {
            processor.onEvent(cmd);
            //std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        std::string timestamp = std::to_string(std::chrono::duration_cast<std::chrono::seconds>
                (std::chrono::system_clock::now().time_since_epoch()).count());
        std::string filename = "bulk";
        filename.append(timestamp).append(".log");

        std::fstream fstream;
        fstream.open(filename, std::fstream::in);
        if (not fstream.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        // keep all strings in one file for simpleness
        std::vector<std::string> results = {
                "bulk: cmd1, cmd2, cmd3",
                "bulk: cmd4, cmd5",
                "bulk: cmd5, cmd6, cmd7, cmd8, cmd9"
        };
        std::string input;
        int i = 0;
        while (std::getline(fstream, input))
        {
            BOOST_CHECK_EQUAL(input, results[i]);
            i++;
        }
    }

BOOST_AUTO_TEST_SUITE_END()