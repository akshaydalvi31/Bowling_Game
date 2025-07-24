#include "regular_frame.h"
#include <stdexcept>

RegularFrame::RegularFrame(const std::uint8_t u8_frame_num) : FrameBase(u8_frame_num)
{
    if (u8_frame_num >= 10)
    {
        throw std::invalid_argument("Frame number should be betweeen 1 to 9");
    }
}

bool RegularFrame::IsComplete() const
{
    const std::size_t roll_ = vec_u8_rolls_.size();
    return (roll_ == 2) || IsStrike();
}

void RegularFrame::AddRoll(const std::uint8_t u8_pins_knocked)
{
    if (IsComplete())
    {
        throw std::runtime_error("Current Frame " + std::to_string(u8_frame_number_) + " is already completed");
    }

    FrameBase::AddRoll(u8_pins_knocked);

    if ((vec_u8_rolls_.size() == 2) && (!IsStrike()))
    {
        const std::uint8_t u8_total = vec_u8_rolls_[0] + vec_u8_rolls_[1];
        if (u8_total > 10)
        {
            throw std::invalid_argument("Two rolls cannot exceed 10 pins");
        }
    }
}

std::uint16_t RegularFrame::GetScore() const
{
    return CalculateBaseScore();
}
