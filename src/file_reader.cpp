#include "file_reader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

FileReader::GameData FileReader::ReadGameFromFile(const std::string &str_filename)
{
    std::ifstream ifs_file(str_filename);
    if (!ifs_file.is_open())
    {
        throw std::runtime_error("Unable to open file: " + str_filename);
    }

    GameData game_data;
    std::string str_line;

    if (std::getline(ifs_file, str_line))
    {
        if (str_line.length() > 100u)
        {
            throw std::invalid_argument("Line is very long in file");
        }
        game_data.str_player_name = str_line;
    }
    else
    {
        throw std::runtime_error("File is empty or invalid format");
    }

    if (std::getline(ifs_file, str_line))
    {
        if (str_line.length() > 100U)
        {
            throw std::invalid_argument("Line is very long in file");
        }
        game_data.vec_u8_rolls = ParseRolls(str_line);
    }
    else
    {
        throw std::runtime_error("Missing rolls data in file");
    }

    ifs_file.close();
    return game_data;
}

std::vector<FileReader::GameData> FileReader::ReadMultipleGamesFromFile(const std::string &str_filename)
{
    std::ifstream ifs_file(str_filename);
    if (!ifs_file.is_open())
    {
        throw std::runtime_error("Unable to open file: " + str_filename);
    }

    std::vector<GameData> vec_games;
    std::string str_line;

    while (std::getline(ifs_file, str_line))
    {
        if (str_line.empty())
        {
            // This will skip the empty lines in file
            continue;
        }

        if (str_line.length() > 100u)
        {
            throw std::invalid_argument("Line is very long in file");
        }

        GameData game_data;
        game_data.str_player_name = str_line;

        if (std::getline(ifs_file, str_line))
        {
            if (str_line.length() > 100u)
            {
                throw std::invalid_argument("Line is very long in file");
            }
            game_data.vec_u8_rolls = ParseRolls(str_line);
            vec_games.push_back(game_data);
        }
        else
        {
            std::cerr << "Warning: Missing rolls for player " << game_data.str_player_name << std::endl;
        }
    }

    ifs_file.close();
    return vec_games;
}

std::vector<std::uint8_t> FileReader::ParseRolls(const std::string &str_rolls_line)
{
    std::vector<std::uint8_t> vec_rolls;
    std::istringstream iss_stream(str_rolls_line);
    std::string str_token;

    while (std::getline(iss_stream, str_token, ','))
    {
        std::size_t sz_start = str_token.find_first_not_of(" \t");
        if (sz_start == std::string::npos)
        {
            continue;
        }

        std::size_t sz_end = str_token.find_last_not_of(" \t");
        str_token = str_token.substr(sz_start, (sz_end - sz_start) + 1U);

        if (!str_token.empty())
        {
            try
            {
                const std::int32_t i32_roll = std::stoi(str_token);
                ValidateRoll(i32_roll);
                vec_rolls.push_back(static_cast<std::uint8_t>(i32_roll));
            }
            catch (const std::exception &e)
            {
                throw std::runtime_error("Invalid roll value: " + str_token);
            }
        }
    }

    return vec_rolls;
}

void FileReader::ValidateRoll(const std::int32_t i32_roll)
{
    if ((i32_roll < static_cast<std::int32_t>(0U)) || (i32_roll > static_cast<std::int32_t>(10U)))
    {
        throw std::invalid_argument("Roll value must be between 0 and 10: " + std::to_string(i32_roll));
    }
}