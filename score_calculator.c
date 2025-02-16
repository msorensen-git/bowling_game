/**
 * @file score_calculator.h
 * @brief Bowling game score calculation definitions and interface
 * 
 * This header file defines the structures and functions needed for
 * calculating bowling game scores, including frame types, scoring
 * constants, and error handling.
 * 
 * Constants:
 * @def MAX_FRAMES 10
 *     Number of frames in a standard bowling game
 * 
 * @def MAX_PINS 10
 *     Maximum number of pins in a standard bowling frame
 * 
 * @def STRIKE_SCORE 10
 *     Score value for knocking down all pins with first ball
 * 
 * Enumerations:
 * @enum frame_type
 *     Defines the possible types of bowling frames:
 *     - UNDEFINED: Frame not yet played
 *     - STRIKE: All pins knocked down on first ball
 *     - SPARE: All pins knocked down using both balls
 *     - OPEN: Some pins left standing after both balls
 * 
 * @enum bowling_error
 *     Defines possible error conditions during score calculation:
 *     - NO_ERROR: Calculation completed successfully
 *     - INCOMPLETE_GAME: Not all frames have been played
 *     - INVALID_PINS: Invalid number of pins recorded
 *     - INVALID_FRAME_TYPE: Frame type doesn't match pin count
 * 
 * Structures:
 * @struct frame_results
 *     Stores the results of a single bowling frame:
 *     @member type Frame type (UNDEFINED, STRIKE, SPARE, OPEN)
 *     @member first_ball Number of pins knocked down with first ball
 *     @member second_ball Number of pins knocked down with second ball
 *     @member third_ball Number of pins knocked down with third ball (10th frame only)
 *     @member score Total score for this frame including bonus points
 * 
 * Function Prototypes:
 * @fn calculate_game_scores()
 *     Calculates the scores for all frames in a bowling game
 *     @param frames Array of frame results for all 10 frames
 *     @return bowling_error indicating success or specific error condition
 * 
 * Score Calculation Rules:
 * - Strike: 10 points plus next two balls
 * - Spare: 10 points plus next ball
 * - Open: Sum of pins knocked down
 * - 10th frame: Special handling for bonus balls
 * 
 * Usage Example:
 * @code
 * struct frame_results frames[MAX_FRAMES];
 * // ... populate frames with game results ...
 * enum bowling_error result = calculate_game_scores(frames);
 * if (result == NO_ERROR) {
 *     // scores calculated successfully
 * }
 * @endcode
 * 
 * Note: This header assumes standard bowling rules and scoring.
 * Frame validation should be performed before score calculation.
 */
#include "score_calculator.h"

enum bowling_error 
calculate_game_scores(struct frame_results frames[MAX_FRAMES])
{
    // calculate the scores
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        // if frame 1-9, score normally
        if (i < 9)
        {
            // if we threw a strike, 10 plus next two balls
            if (frames[i].type == STRIKE)
            {
                frames[i].score = STRIKE_SCORE; 
                if (i == 8) // if in frame 9  
                    frames[i].score += frames[i+1].first_ball + frames[i+1].second_ball;
                else
                    frames[i].score += frames[i+1].first_ball + frames[i+2].first_ball;
            }
            else if (frames[i].type == SPARE)
            {
                frames[i].score = STRIKE_SCORE;
                frames[i].score += frames[i+1].first_ball;
            }
            else if (frames[i].type == OPEN)
                frames[i].score = frames[i].first_ball + frames[i].second_ball;
            else
                return INVALID_FRAME_TYPE;
        }
        else
            // 10th frame
            frames[i].score = frames[i].first_ball + frames[i].second_ball + frames[i].third_ball;
    }
    return NO_ERROR;
}
