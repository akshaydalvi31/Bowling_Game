#ifndef REGULAR_FRAME_H
#define REGULAR_FRAME_H

#include "frame_base.h"

class RegularFrame final : public FrameBase
{
public:
    /**
     * @brief Explicit constructor for regular frame
     * @param[in] u8_frame_num Frame number (1-9)
     */
    explicit RegularFrame(const std::uint8_t u8_frame_num);

    /**
     * @brief Destructor
     */
    ~RegularFrame() override = default;

    RegularFrame(const RegularFrame &) = delete;
    RegularFrame &operator=(const RegularFrame &) = delete;
    RegularFrame(RegularFrame &&) = delete;
    RegularFrame &operator=(RegularFrame &&) = delete;

    /**
     * @brief Check if frame is complete
     * @return true if 2 rolls or strike
     */
    bool IsComplete() const override;

    /**
     * @brief Add roll with validation
     * @param[in] u8_pins_knocked Number of pins knocked
     * @throw std::runtime_error if frame complete
     * @throw std::invalid_argument if invalid total
     */
    void AddRoll(const std::uint8_t u8_pins_knocked) override;

    /**
     * @brief Get frame score
     * @return Base score of frame
     */
    std::uint16_t GetScore() const override;

};

#endif // REGULAR_FRAME_H
