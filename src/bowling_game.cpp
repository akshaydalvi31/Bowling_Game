#include "bowling_game.h"
#include "regular_frame.h"
#include "tenth_frame.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

BowlingGame::BowlingGame(const std::string &str_name): vec_ptr_frames_{}, str_player_name_{str_name}, 
                                            b_game_complete_{false}
{

    ValidatePlayerName(str_name);
    vec_ptr_frames_.reserve(10u);
    InitializeFrames();
}

void BowlingGame::Roll(const std::uint8_t u8_pins)
{
    if (b_game_complete_)
    {
        throw std::runtime_error("Game is already complete");
    }

    FrameBase *ptr_current_frame = GetCurrentFrame();
    if (ptr_current_frame == nullptr)
    {
        throw std::runtime_error("No available frame for roll");
    }

    ptr_current_frame->AddRoll(u8_pins);
    UpdateGameStatus();
}

std::uint16_t BowlingGame::GetTotalScore() const
{
    return ScoreCalculator::CalculateTotalScore(vec_ptr_frames_);
}

bool BowlingGame::IsGameComplete() const
{
    return b_game_complete_;
}

void BowlingGame::DisplayScorecard() const
{
    std::cout << "\n" << std::string(80U, '=') << std::endl;
    std::cout << "BOWLING SCORECARD - Player: " << str_player_name_ << std::endl;
    std::cout << std::string(80U, '=') << std::endl;

    const std::uint16_t u16_final_score = GetTotalScore();

    std::cout << "FINAL SCORE: " << u16_final_score << std::endl;
    std::cout << std::string(80U, '=') << std::endl;
}

const std::string &BowlingGame::GetPlayerName() const
{
    return str_player_name_;
}

void BowlingGame::InitializeFrames()
{
    for (std::uint8_t u8_i = 1U; u8_i <= 9; ++u8_i)
    {
        vec_ptr_frames_.push_back(std::make_unique<RegularFrame>(u8_i));
    }
    vec_ptr_frames_.push_back(std::make_unique<TenthFrame>());
}

FrameBase *BowlingGame::GetCurrentFrame()
{
    FrameBase *ptr_result = nullptr;

    for (auto &ptr_frame : vec_ptr_frames_)
    {
        if ((ptr_frame != nullptr) && (!ptr_frame->IsComplete()))
        {
            ptr_result = ptr_frame.get();
            break;
        }
    }

    return ptr_result;
}

void BowlingGame::UpdateGameStatus()
{
    b_game_complete_ = std::all_of(vec_ptr_frames_.cbegin(), vec_ptr_frames_.cend(),
                                   [](const std::unique_ptr<FrameBase> &ptr_frame) -> bool
                                   {
                                       return (ptr_frame != nullptr) && ptr_frame->IsComplete();
                                   });
}

void BowlingGame::ValidatePlayerName(const std::string &str_name)
{
    if (str_name.empty())
    {
        throw std::invalid_argument("Player name cannot be empty");
    }

    if (str_name.length() > 100)
    {
        throw std::invalid_argument("Player name too long (max 100 characters)");
    }
}
