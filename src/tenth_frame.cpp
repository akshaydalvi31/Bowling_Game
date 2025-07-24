#include "tenth_frame.h"
#include <stdexcept>

TenthFrame::TenthFrame() : FrameBase(10)
{
}

bool TenthFrame::IsComplete() const
{
    const std::size_t roll_ = vec_u8_rolls_.size();
    bool b_complete = false;

    if (roll_ < 2U)
    {
        b_complete = false;
    }
    else if (roll_ == 2U)
    {
        // If not a strike and spare complete the rool
        b_complete = (!IsStrike()) && (!IsSpare());
    }
    else
    {
        b_complete = (roll_ == 3);
    }

    return b_complete;
}

void TenthFrame::AddRoll(const std::uint8_t u8_pins_knocked)
{
    if (IsComplete())
    {
        throw std::runtime_error("10th frame is already complete");
    }

    FrameBase::AddRoll(u8_pins_knocked);

    const std::size_t curr_rolls = vec_u8_rolls_.size();

    if (curr_rolls == 2U)
    {
        const bool b_first_strike = (vec_u8_rolls_[0] == 10);
        const bool b_current_spare = (!b_first_strike) && ((vec_u8_rolls_[0] + vec_u8_rolls_[1]) == 10);

        if ((!b_first_strike) && (!b_current_spare) && ((vec_u8_rolls_[0] + vec_u8_rolls_[1]) > 10))
        {
            throw std::invalid_argument("Invalid roll as it's greater than 10");
        }
    }
}

std::uint16_t TenthFrame::GetScore() const
{
    return CalculateBaseScore();
}
