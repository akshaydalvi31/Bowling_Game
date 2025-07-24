#include "score_calculator.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

std::uint16_t ScoreCalculator::CalculateTotalScore(const std::vector<std::unique_ptr<FrameBase>> &vec_ptr_frames)
{

    if (vec_ptr_frames.size() != 10)
    {
        throw std::invalid_argument("Invalid number of frames");
    }

    std::uint16_t u16_total_score = 0U;
    for (std::size_t i = 0U; i < vec_ptr_frames.size(); ++i)
    {
        if (vec_ptr_frames[i] == nullptr)
        {
            throw std::invalid_argument("Null frame pointer detected");
        }

        std::uint16_t u16_frame_score = vec_ptr_frames[i]->GetScore();

        // Add bonus for strikes and spares but not for 10th frame
        if (i < 9)
        {
            if (vec_ptr_frames[i]->IsStrike())
            {
                u16_frame_score += GetStrikeBonus(vec_ptr_frames, i);
            }
            else if (vec_ptr_frames[i]->IsSpare())
            {
                u16_frame_score += GetSpareBonus(vec_ptr_frames, i);
            }
        }

        u16_total_score += u16_frame_score;
    }

    return u16_total_score;
}

std::uint16_t ScoreCalculator::GetStrikeBonus(const std::vector<std::unique_ptr<FrameBase>> &vec_ptr_frames,
    const std::size_t frame_index)
{

    std::uint16_t u16_bonus = 0U;

    if ((frame_index + 1U) >= vec_ptr_frames.size())
    {
        return u16_bonus;
    }

    const std::unique_ptr<FrameBase> &ptr_next_frame = vec_ptr_frames[frame_index + 1U];
    if (ptr_next_frame == nullptr)
    {
        return u16_bonus;
    }

    const std::vector<std::uint8_t> &vec_next_rolls = ptr_next_frame->GetRolls();

    if (ptr_next_frame->GetFrameNumber() == 10)
    {
        // Next frame is 10th frame
        if (vec_next_rolls.size() >= 2U)
        {
            u16_bonus = static_cast<std::uint16_t>(vec_next_rolls[0] + vec_next_rolls[1]);
        }
    }
    else if (ptr_next_frame->IsStrike())
    {
        // Next frame is also a strike
        u16_bonus = 10;
        if ((frame_index + 2U) < vec_ptr_frames.size())
        {
            const std::unique_ptr<FrameBase> &ptr_frame_after_next =
                vec_ptr_frames[frame_index + 2U];
            if ((ptr_frame_after_next != nullptr) && (!ptr_frame_after_next->GetRolls().empty()))
            {
                u16_bonus += static_cast<std::uint16_t>(ptr_frame_after_next->GetRolls()[0]);
            }
        }
    }
    else
    {
        // Next frame is regular
        if (vec_next_rolls.size() >= 2U)
        {
            u16_bonus = static_cast<std::uint16_t>(vec_next_rolls[0] + vec_next_rolls[1]);
        }
        else if (vec_next_rolls.size() == 1U)
        {
            u16_bonus = static_cast<std::uint16_t>(vec_next_rolls[0]);
        }
    }

    return u16_bonus;
}

std::uint16_t ScoreCalculator::GetSpareBonus(const std::vector<std::unique_ptr<FrameBase>> &vec_ptr_frames,
    const std::size_t frame_index)
{

    std::uint16_t u16_bonus = 0U;

    if ((frame_index + 1U) >= vec_ptr_frames.size())
    {
        return u16_bonus;
    }

    const std::unique_ptr<FrameBase> &ptr_next_frame = vec_ptr_frames[frame_index + 1U];
    if (ptr_next_frame != nullptr)
    {
        const std::vector<std::uint8_t> &vec_next_rolls = ptr_next_frame->GetRolls();
        if (!vec_next_rolls.empty())
        {
            u16_bonus = static_cast<std::uint16_t>(vec_next_rolls[0]);
        }
    }

    return u16_bonus;
}
