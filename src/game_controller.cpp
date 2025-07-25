#include "game_controller.h"
#include "bowling_game.h"
#include "file_reader.h"
#include <iostream>
#include <stdexcept>

std::int32_t GameController::RunApplication()
{
    std::cout << "Bowling Game" << std::endl;

    std::int32_t choice = 0;
    std::string str_input_filename;
    std::string str_filename;

    do
    {
        DisplayMenu();
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1)
        {
            std::cout << "Enter filename for single game (default: input.txt): ";
            std::getline(std::cin, str_input_filename);
            if (str_input_filename.empty())
            {
                str_filename = std::string(DATA_PATH) + "/input.txt";
            }
            else
            {
                str_filename = std::string(DATA_PATH) + "/" + str_input_filename;   
            }
            PlayGameFromFile(str_filename);
        }
        else if (choice == 2)
        {
            std::cout << "Enter filename for multiple games (default: multiple_games.txt): ";
            std::getline(std::cin, str_input_filename);
            if (str_input_filename.empty())
            {
                str_filename = std::string(DATA_PATH) + "/multiple_games.txt";
            }
            else
            {
                str_filename = std::string(DATA_PATH) + "/" + str_input_filename;
            }
            PlayMultipleGamesFromFile(str_filename);
        }
        else if (choice == 3)
        {
            RunSampleGame();
        }
        else if (choice == 4)
        {
            std::cout << "Thank you, Game ended" << std::endl;
        }
        else
        {
            std::cout << "Invalid choice try again" << std::endl;
        }

        if (choice != 4)
        {
            std::cout << "\nPress Enter to continue:";
            std::cin.get();
        }

    } while (choice != 4);

    return 0;
}

void GameController::PlayGameFromFile(const std::string &str_filename)
{
    try
    {
        ValidateFilename(str_filename);

        std::cout << "Reading game data from file: " << str_filename << std::endl;
        const FileReader::GameData game_data = FileReader::ReadGameFromFile(str_filename);

        std::cout << "Starting game for player name: " << game_data.str_player_name << std::endl;
        std::cout << "Rolls to process: " << game_data.vec_u8_rolls.size() << std::endl;

        BowlingGame bowling_game(game_data.str_player_name);

        for (std::size_t i = 0U; i < game_data.vec_u8_rolls.size(); ++i)
        {
            const std::uint8_t u8_pins = game_data.vec_u8_rolls[i];
            std::cout << "Current Roll " << (i + 1U) << ": " << static_cast<std::uint16_t>(u8_pins) << " pins knocked down" << std::endl;

            bowling_game.Roll(u8_pins);
            std::cout << "Current total score: " << bowling_game.GetTotalScore() << std::endl;

            if (bowling_game.IsGameComplete())
            {
                std::cout << "Game is completed" << std::endl;
                break;
            }
        }

        if (!bowling_game.IsGameComplete())
        {
            std::cout << "Game is not complete will need more rolls." << std::endl;
        }

        bowling_game.DisplayScorecard();
    }
    catch (const std::exception &e)
    {
        HandleFileError(str_filename, e.what());
    }
}

void GameController::PlayMultipleGamesFromFile(const std::string &str_filename)
{
    try
    {
        ValidateFilename(str_filename);

        std::cout << "Multiple Games Reading from file with name: " << str_filename << std::endl;
        const std::vector<FileReader::GameData> vec_games = FileReader::ReadMultipleGamesFromFile(str_filename);

        std::cout << "Found " << vec_games.size() << " number of games to process\n" << std::endl;

        for (std::size_t curr_game = 0U; curr_game < vec_games.size(); ++curr_game)
        {
            const FileReader::GameData &game_data = vec_games[curr_game];

            std::cout << "\n"<< std::string(50, '*') << std::endl;
            std::cout << "GAME " << (curr_game + 1U) << " - Player: " << game_data.str_player_name << std::endl;
            std::cout << std::string(50, '*') << std::endl;

            BowlingGame bowling_game(game_data.str_player_name);

            for (const std::uint8_t u8_pins : game_data.vec_u8_rolls)
            {
                bowling_game.Roll(u8_pins);
                if (bowling_game.IsGameComplete())
                {
                    break;
                }
            }

            bowling_game.DisplayScorecard();
        }
    }
    catch (const std::exception &e)
    {
        HandleFileError(str_filename, e.what());
    }
}

void GameController::RunSampleGame()
{
    try
    {
        BowlingGame bowling_game("Player");

        const std::vector<std::uint8_t> vec_rolls = {1U, 4U, 4U, 5U, 6U, 4U, 5U, 5U, 10U,
                                                     0U, 1U, 7U, 3U, 6U, 4U, 10U, 2U, 8U, 6U};

        std::cout << "Sample example game: " << std::endl;
        std::cout << "Rolls: ";
        for (std::size_t i = 0U; i < vec_rolls.size(); ++i)
        {
            std::cout << static_cast<std::uint16_t>(vec_rolls[i]);
            if (i < (vec_rolls.size() - 1U))
            {
                std::cout << ",";
            }
        }
        std::cout << std::endl;

        for (std::size_t i = 0U; i < vec_rolls.size(); ++i)
        {
            const std::uint8_t u8_pins = vec_rolls[i];
            bowling_game.Roll(u8_pins);
            std::cout << "Roll " << (i + 1U) << ": " << static_cast<std::uint16_t>(u8_pins)
                      << " pins. Current score: " << bowling_game.GetTotalScore() << std::endl;
        }

        bowling_game.DisplayScorecard();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Sample Error: " << e.what() << std::endl;
    }
}

void GameController::DisplayMenu()
{
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "BOWLING GAME" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. Play single game for single player file" << std::endl;
    std::cout << "2. Play multiple games from file" << std::endl;
    std::cout << "3. Play Sample game" << std::endl;
    std::cout << "4. Quit the Game" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Choose option (1-4): ";
}

void GameController::HandleFileError(const std::string &str_filename, const std::string &str_error)
{
    std::cerr << "\nFile Error with '" << str_filename << "':" << std::endl;
    std::cerr << "  " << str_error << std::endl;
}

void GameController::ValidateFilename(const std::string &str_filename)
{
    if (str_filename.empty())
    {
        throw std::invalid_argument("Filename cannot be empty");
    }

    if (str_filename.length() > 100)
    {
        throw std::invalid_argument("Filename too long");
    }
}
