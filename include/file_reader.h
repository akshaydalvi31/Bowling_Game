#ifndef FILE_READER_H
#define FILE_READER_H

#include <string>
#include <vector>
#include <cstdint>

class FileReader final
{
public:
    /**
     * @brief Structure to hold game data from file
     */
    struct GameData
    {
        std::string str_player_name;
        std::vector<std::uint8_t> vec_u8_rolls;

        /**
         * @brief Default constructor
         */
        GameData() = default;

        /**
         * @brief Constructor with parameters
         * @param[in] str_name Player name
         * @param[in] vec_rolls Vector of rolls
         */
        GameData(const std::string &str_name, const std::vector<std::uint8_t> &vec_rolls)
            : str_player_name(str_name), vec_u8_rolls(vec_rolls) {}
    };

    /**
     * @brief Read single game from file
     * @param[in] str_filename Path to input file
     * @return GameData structure with player and rolls
     * @throw std::runtime_error if file cannot be opened
     * @throw std::invalid_argument if file format invalid
     */
    static GameData ReadGameFromFile(const std::string &str_filename);

    /**
     * @brief Read multiple games from file
     * @param[in] str_filename Path to input file
     * @return Vector of GameData structures
     * @throw std::runtime_error if file cannot be opened
     * @throw std::invalid_argument if file format invalid
     */
    static std::vector<GameData> ReadMultipleGamesFromFile(const std::string &str_filename);

private:
    /**
     * @brief Parse rolls from comma-separated string
     * @param[in] str_rolls_line Line containing rolls
     * @return Vector of roll values
     * @throw std::invalid_argument if parsing fails
     */
    static std::vector<std::uint8_t> ParseRolls(const std::string &str_rolls_line);

    /**
     * @brief Validate single roll value
     * @param[in] i32_roll Roll value to validate
     * @throw std::invalid_argument if invalid
     */
    static void ValidateRoll(const std::int32_t i32_roll);

    FileReader() = delete;
    ~FileReader() = delete;
    FileReader(const FileReader &) = delete;
    FileReader &operator=(const FileReader &) = delete;
    FileReader(FileReader &&) = delete;
    FileReader &operator=(FileReader &&) = delete;
};

#endif // FILE_READER_H