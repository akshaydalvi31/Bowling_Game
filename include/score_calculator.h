#ifndef SCORE_CALCULATOR_H
#define SCORE_CALCULATOR_H

#include "frame_base.h"
#include <vector>
#include <memory>
#include <cstdint>

class ScoreCalculator final
{
public:
    /**
     * @brief Calculate total game score
     * @param[in] vec_ptr_frames Vector of frame pointers
     * @return Total game score
     * @throw std::invalid_argument if frames vector invalid
     */
    static std::uint16_t CalculateTotalScore(const std::vector<std::unique_ptr<FrameBase>> &vec_ptr_frames);

private:
    /**
     * @brief Calculate strike bonus
     * @param[in] vec_ptr_frames Reference to frames vector
     * @param[in] frame_index Current frame index
     * @return Strike bonus points
     */
    static std::uint16_t GetStrikeBonus(const std::vector<std::unique_ptr<FrameBase>> &vec_ptr_frames, const std::size_t frame_index);

    /**
     * @brief Calculate spare bonus
     * @param[in] vec_ptr_frames Reference to frames vector
     * @param[in] frame_index Current frame index
     * @return Spare bonus points
     */
    static std::uint16_t GetSpareBonus(const std::vector<std::unique_ptr<FrameBase>> &vec_ptr_frames, const std::size_t frame_index);

    ScoreCalculator() = delete;
    ~ScoreCalculator() = delete;
    ScoreCalculator(const ScoreCalculator &) = delete;
    ScoreCalculator &operator=(const ScoreCalculator &) = delete;
    ScoreCalculator(ScoreCalculator &&) = delete;
    ScoreCalculator &operator=(ScoreCalculator &&) = delete;
};

#endif // SCORE_CALCULATOR_H