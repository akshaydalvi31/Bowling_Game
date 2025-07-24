#ifndef FRAME_BASE_H
#define FRAME_BASE_H

// #include "i_frame.h"
#include <vector>
#include <cstdint>

class FrameBase
{
public:
    /**
     * @brief Explicit constructor
     * @param[in] u8_frame_num Frame number (1-10)
     */
    explicit FrameBase(const std::uint8_t u8_frame_num);

    /**
     * @brief Virtual destructor
     */
    virtual ~FrameBase() = default;

    FrameBase(const FrameBase &) = delete;
    FrameBase &operator=(const FrameBase &) = delete;
    FrameBase(FrameBase &&) = default;
    FrameBase &operator=(FrameBase &&) = default;

    /**
     * @brief Add roll implementation
     * @param[in] u8_pins_knocked Number of pins knocked
     */
    virtual void AddRoll(const std::uint8_t u8_pins_knocked);

    /**
     * @brief Check if strike
     * @return true if first roll is 10
     */
    bool IsStrike() const;

    /**
     * @brief Check if spare
     * @return true if two rolls sum to 10 (not strike)
     */
    bool IsSpare() const;

    /**
     * @brief Get frame number
     * @return Frame number (1-10)
     */
    std::uint8_t GetFrameNumber() const;

    /**
     * @brief Get rolls vector
     * @return Const reference to rolls vector
     */
    const std::vector<std::uint8_t> &GetRolls() const;

    /**
     * @brief Check if frame is complete
     * @return true if frame is complete, false otherwise
     */
    virtual bool IsComplete() const = 0;

    /**
     * @brief Get the frame score
     * @return Frame score as unsigned integer
     */
    virtual std::uint16_t GetScore() const = 0;

protected:
    std::vector<std::uint8_t> vec_u8_rolls_;
    std::uint8_t u8_frame_number_;

    /**
     * @brief Calculate base score for the frame
     * @return Sum of all rolls in frame
     */
    virtual std::uint16_t CalculateBaseScore() const;

    /**
     * @brief Validate roll value
     * @param[in] u8_pins Number of pins to validate
     * @throw std::invalid_argument if invalid
     */
    void ValidateRoll(const std::uint8_t u8_pins) const;
};

#endif // FRAME_BASE_H