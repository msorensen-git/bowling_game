/**
 * Validates the entire bowling game frame results for correctness.
 * 
 * @param frames An array of frame_results structures representing all 10 frames
 *              of a bowling game
 * 
 * @return enum bowling_error indicating the validation result:
 *         - NO_ERROR: Game is valid
 *         - INCOMPLETE_GAME: Not all frames have been played
 *         - INVALID_PINS: Invalid number of pins knocked down
 *         - INVALID_FRAME_TYPE: Frame type doesn't match the pins knocked down
 * 
 * The function performs the following validations:
 * 
 * For frames 1-9:
 * - Checks if all frames have been played (not UNDEFINED)
 * - Validates first ball is between 0 and MAX_PINS (10)
 * - For STRIKE frames:
 *   - First ball must be MAX_PINS (10)
 *   - Second ball must be 0
 * - For SPARE frames:
 *   - Sum of first and second balls must equal MAX_PINS (10)
 * - For OPEN frames:
 *   - Sum of first and second balls must be less than MAX_PINS
 * 
 * For the 10th frame:
 * - Validates first ball is between 0 and MAX_PINS
 * - If first ball is strike:
 *   - Second and third balls must be between 0 and MAX_PINS
 * - If not strike:
 *   - Second ball must be between 0 and remaining pins
 *   - If spare (first + second = MAX_PINS):
 *     - Third ball must be between 0 and MAX_PINS
 *   - If open frame:
 *     - Third ball must be 0
 */
#include "frame_validator.h"
#include "bowling_game.h"

enum bowling_error 
validate_game(struct frame_results frames[MAX_FRAMES])
{
    // Validate each frame
    for (int i = 0; i < MAX_FRAMES; i++) 
    {
        // Check if frame was played
        if (frames[i].type == UNDEFINED) 
            return INCOMPLETE_GAME;

        // Regular frames (1-9)
        if (i < 9) 
        {
            // Validate first ball
            if (frames[i].first_ball < 0 || frames[i].first_ball > MAX_PINS) 
                return INVALID_PINS;

            // Validate second ball and frame type
            switch (frames[i].type) 
            {
                case STRIKE:
                    if (frames[i].first_ball != MAX_PINS || frames[i].second_ball != 0) 
                        return INVALID_FRAME_TYPE;
                    break;

                case SPARE:
                    if ((frames[i].first_ball + frames[i].second_ball) != MAX_PINS) 
                        return INVALID_FRAME_TYPE;
                    break;

                case OPEN:
                    if ((frames[i].first_ball + frames[i].second_ball) >= MAX_PINS) 
                        return INVALID_FRAME_TYPE;
                    break;

                default:
                    return INVALID_FRAME_TYPE;
            }
        }
        // Last frame (10th)
        else 
        {
            // Validate first ball
            if (frames[i].first_ball < 0 || frames[i].first_ball > MAX_PINS) 
                return INVALID_PINS;

            // Validate second and third balls based on first ball result
            if (frames[i].first_ball == MAX_PINS) 
                // Strike on first ball - get two more balls
                if (frames[i].second_ball < 0 || frames[i].second_ball > MAX_PINS ||
                    frames[i].third_ball < 0 || frames[i].third_ball > MAX_PINS) 
                    return INVALID_PINS;
            else 
            {
                // Check second ball doesn't exceed remaining pins
                if (frames[i].second_ball < 0 || 
                    frames[i].second_ball > (MAX_PINS - frames[i].first_ball)) 
                    return INVALID_PINS;

                // If spare, get one more ball
                if (frames[i].first_ball + frames[i].second_ball == MAX_PINS) 
                    if (frames[i].third_ball < 0 || frames[i].third_ball > MAX_PINS) 
                        return INVALID_PINS;
                else 
                    // No spare, no third ball allowed
                    if (frames[i].third_ball != 0) 
                        return INVALID_PINS;
            }
        }
    }

    return NO_ERROR;
}
