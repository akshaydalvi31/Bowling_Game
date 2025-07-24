#include "frame_base.h"
#include <stdexcept>
#include <numeric>

FrameBase::FrameBase(const std::uint8_t u8_frame_num): vec_u8_rolls_{}, u8_frame_number_{u8_frame_num}
{
    vec_u8_rolls_.reserve(3U);

    if ((u8_frame_num < 1U) || (u8_frame_num > 10))
    {
        throw std::invalid_argument("Frame number must be between 1 and 10");
    }
}

std::uint16_t FrameBase::CalculateBaseScore() const
{
    return static_cast<std::uint16_t>(std::accumulate(vec_u8_rolls_.cbegin(), vec_u8_rolls_.cend(), 0U));
}

void FrameBase::AddRoll(const std::uint8_t u8_pins_knocked)
{
    ValidateRoll(u8_pins_knocked);
    vec_u8_rolls_.push_back(u8_pins_knocked);
}

bool FrameBase::IsStrike() const
{
    return (!vec_u8_rolls_.empty()) && (vec_u8_rolls_[0] == 10);
}

bool FrameBase::IsSpare() const
{
    bool b_result = false;

    if (vec_u8_rolls_.size() >= 2U)
    {
        const std::uint8_t u8_total = vec_u8_rolls_[0] + vec_u8_rolls_[1];
        b_result = (u8_total == 10) && (!IsStrike());
    }

    return b_result;
}

std::uint8_t FrameBase::GetFrameNumber() const
{
    return u8_frame_number_;
}

const std::vector<std::uint8_t> &FrameBase::GetRolls() const
{
    return vec_u8_rolls_;
}

void FrameBase::ValidateRoll(const std::uint8_t u8_pins) const
{
    if (u8_pins > 10)
    {
        throw std::invalid_argument("Invalid number of pins: " + std::to_string(u8_pins));
    }
}
