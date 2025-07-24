#ifndef BOWLING_GAME_H
#define BOWLING_GAME_H

#include "frame_base.h"
#include "score_calculator.h"
#include <vector>
#include <memory>
#include <string>
#include <cstdint>

class BowlingGame final
{
public:
    /**
     * @brief Explicit constructor with player name
     * @param[in] str_name Player name (non-empty, max 100 chars)
     * @throw std::invalid_argument if name invalid
     */
    explicit BowlingGame(const std::string &str_name);

    /**
     * @brief Destructor
     */
    ~BowlingGame() = default;

    BowlingGame(const BowlingGame &) = delete;
    BowlingGame &operator=(const BowlingGame &) = delete;
    BowlingGame(BowlingGame &&) = default;
    BowlingGame &operator=(BowlingGame &&) = default;

    /**
     * @brief Add a roll to the game
     * @param[in] u8_pins Number of pins knocked down (0-10)
     * @throw std::runtime_error if game complete
     * @throw std::invalid_argument if invalid pins value
     */
    void Roll(const std::uint8_t u8_pins);

    /**
     * @brief Get total game score
     * @return Total score including bonuses
     */
    std::uint16_t GetTotalScore() const;

    /**
     * @brief Check if game is complete
     * @return true if all frames complete
     */
    bool IsGameComplete() const;

    /**
     * @brief Display formatted scorecard
     */
    void DisplayScorecard() const;

    /**
     * @brief Get player name
     * @return Const reference to player name
     */
    const std::string &GetPlayerName() const;

private:
    std::vector<std::unique_ptr<FrameBase>> vec_ptr_frames_;
    std::string str_player_name_;
    bool b_game_complete_;

    /**
     * @brief Initialize all frames for the game
     */     
    void InitializeFrames();

    /**
     * @brief Get pointer to current incomplete frame
     * @return Pointer to current frame or nullptr if all complete
     */
    FrameBase *GetCurrentFrame();

    /**
     * @brief Update game completion status
     */
    void UpdateGameStatus();

    /**
     * @brief Validate player name
     * @param[in] str_name Player name to validate
     * @throw std::invalid_argument if name invalid
     */
    static void ValidatePlayerName(const std::string &str_name);
};

#endif // BOWLING_GAME_H