#define BOOST_TEST_MODULE test_bulk

#include "../include/CommandProcessor.h"

#include <boost/test/unit_test.hpp>
#include <thread>
#include <regex>
#include <filesystem>
#include <algorithm>

std::vector<std::string> listFiles(std::filesystem::path dir, std::regex filename)
{
    std::vector<std::string> result;

    const std::filesystem::directory_iterator end;
    for(std::filesystem::directory_iterator iter { dir } ; iter != end ; ++iter )
    {
        if(std::filesystem::is_regular_file(*iter) and
            std::regex_match(iter->path().string(), filename))
        {
            result.push_back(iter->path().string());
        }
    }

    return result ;
}

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
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    const std::regex filename("\\.\\/bulk\\d{10}\\.log");
    const auto res = listFiles(".", filename);

    std::fstream fstream;
    for (const auto file : res)
    {
        fstream.open(file, std::fstream::in);
        if (not fstream.is_open())
        {
            std::cerr << "Error opening file: " << file << std::endl;
            return;
        }

        std::string input;
        std::getline(fstream, input);
        BOOST_CHECK_EQUAL(input, "bulk: cmd1, cmd2, cmd3");

        std::remove(file.c_str());
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
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }

        const std::regex filename("\\.\\/bulk\\d{10}\\.log");
        auto res = listFiles(".", filename);
        std::sort(res.begin(), res.end());

        std::vector<std::string> results = {
                "bulk: cmd1, cmd2, cmd3",
                "bulk: cmd4, cmd5",
                "bulk: cmd5, cmd6, cmd7, cmd8, cmd9"
        };

        std::fstream fstream;
        for (int i = 0; i < res.size() and i < results.size(); i++)
        {
            fstream.open(res[i], std::fstream::in);
            if (not fstream.is_open())
            {
                std::cerr << "Error opening file: " << res[i] << std::endl;
                return;
            }

            std::string input;
            std::getline(fstream, input);
            BOOST_CHECK_EQUAL(input, results[i]);
            std::cout << input << " is equal to " << results[i] << std::endl;
            fstream.close();
            std::remove(res[i].c_str());
        }

        for (const auto& file : res)
        {
            std::remove(file.data());
        }
    }

BOOST_AUTO_TEST_SUITE_END()