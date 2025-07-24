#ifndef TENTH_FRAME_H
#define TENTH_FRAME_H

#include "frame_base.h"

class TenthFrame final : public FrameBase
{
public:
    /**
     * @brief Constructor for tenth frame
     */
    TenthFrame();

    /**
     * @brief Destructor
     */
    ~TenthFrame() override = default;

    TenthFrame(const TenthFrame &) = delete;
    TenthFrame &operator=(const TenthFrame &) = delete;
    TenthFrame(TenthFrame &&) = delete;
    TenthFrame &operator=(TenthFrame &&) = delete;

    /**
     * @brief Check if tenth frame is complete
     * @return true if complete based on 10th frame rules
     */
    bool IsComplete() const override;

    /**
     * @brief Add roll with tenth frame validation
     * @param[in] u8_pins_knocked Number of pins knocked
     * @throw std::runtime_error if frame complete
     * @throw std::invalid_argument if invalid combination
     */
    void AddRoll(const std::uint8_t u8_pins_knocked) override;

    /**
     * @brief Get tenth frame score (no bonus)
     * @return Sum of all rolls in tenth frame
     */
    std::uint16_t GetScore() const override;

};

#endif // TENTH_FRAME_H