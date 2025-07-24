#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <string>
#include <cstdint>

class GameController final
{
public:
    /**
     * @brief Play single game from file
     * @param[in] str_filename Path to input file
     */
    static void PlayGameFromFile(const std::string &str_filename);

    /**
     * @brief Play multiple games from file
     * @param[in] str_filename Path to input file
     */
    static void PlayMultipleGamesFromFile(const std::string &str_filename);

    /**
     * @brief Run Sample game
     */
    static void RunSampleGame();

    /**
     * @brief Main application entry point
     * @return Exit code (0 for success)
     */
    static std::int32_t RunApplication();

private:
    /**
     * @brief Display main menu
     */
    static void DisplayMenu();

    /**
     * @brief Handle file errors
     * @param[in] str_filename Filename that caused error
     * @param[in] str_error Error message
     */
    static void HandleFileError(const std::string &str_filename, const std::string &str_error);

    /**
     * @brief Validate filename
     * @param[in] str_filename Filename to validate
     * @throw std::invalid_argument if filename invalid
     */
    static void ValidateFilename(const std::string &str_filename);

    GameController() = delete;
    ~GameController() = delete;
    GameController(const GameController &) = delete;
    GameController &operator=(const GameController &) = delete;
    GameController(GameController &&) = delete;
    GameController &operator=(GameController &&) = delete;
};

#endif // GAME_CONTROLLER_H