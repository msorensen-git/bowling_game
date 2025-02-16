/**
 * @file bowling_game.c
 * @brief Main bowling game implementation and game play logic
 * 
 * This file implements the core bowling game functionality, including game
 * initialization, frame throwing mechanics, and random pin generation with
 * realistic probability distributions.
 * 
 * Key Components:
 * - Game initialization and setup
 * - Frame-by-frame gameplay mechanics
 * - Realistic bowling pin probability distribution
 * - Special handling for the 10th frame
 * 
 * Main Functions:
 * @fn main()
 *     Entry point that coordinates the complete game flow:
 *     1. Initializes random number generator
 *     2. Sets up initial game state
 *     3. Executes game play
 *     4. Validates game results
 *     5. Calculates final scores
 *     6. Displays game results
 * 
 * @fn play_game()
 *     Executes the frame-by-frame gameplay for all 10 frames
 * 
 * @fn throw_frame()
 *     Simulates throwing a single frame, handling:
 *     - Regular frames (1-9)
 *       * First ball logic
 *       * Second ball logic for non-strikes
 *       * Frame type determination (STRIKE, SPARE, OPEN)
 *     - Tenth frame special rules
 *       * Up to three balls
 *       * Bonus balls for strikes/spares
 * 
 * @fn ball()
 *     Generates realistic random pin counts with weighted probabilities:
 *     For first ball (10 pins):
 *     - 20% chance for strike
 *     - 15% chance for 9 pins
 *     - 15% chance for 8 pins
 *     - 50% distributed normally
 *     
 *     For remaining pins:
 *     - 30% chance for all remaining pins (spare)
 *     - 20% chance for all but 1-2 pins
 *     - 50% distributed normally
 * 
 * @fn init_game_results()
 *     Initializes the game state with undefined frames and zero scores
 * 
 * Dependencies:
 * - bowling_game.h: Game structures and constants
 * - frame_validator.h: Frame validation functionality
 * - score_calculator.h: Score calculation logic
 * - game_display.h: Score display formatting
 * 
 * Note: The game uses a seeded random number generator to ensure
 * different results for each game while maintaining realistic
 * bowling score distributions.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bowling_game.h"
#include "frame_validator.h"
#include "score_calculator.h"
#include "game_display.h"

int main()
{
    struct frame_results frames[MAX_FRAMES];
    
    // seed random number generator
    srand(time(NULL));

    // Initiate game results
    init_game_results(frames);

    play_game(frames);

    // Validate game results
    enum bowling_error error = validate_game(frames);
    if (error != NO_ERROR)
    {
        printf("Error: %d\n", error);
        return 0;
    }

    calculate_game_scores(frames);
    
    report_game_scores(frames);

    return 1;
}

void play_game(struct frame_results frames[MAX_FRAMES])
{
    for (int i = 0; i < 10; i++)
        throw_frame(frames, i);
}

// return 1 if good or 0 if bad
// the results of a thrown frame go in the frame_results
void throw_frame(struct frame_results frames[MAX_FRAMES], int frame)
{
    if (frames[frame].type == UNDEFINED)
    {
        // if 10th frame, it has 3 balls
        if (frame == 9)
        {
            frames[frame].type = LAST_FRAME;

            frames[frame].first_ball = ball(MAX_PINS);    // first ball
            if (frames[frame].first_ball == STRIKE_SCORE)     // strike
            {
                frames[frame].second_ball = ball(MAX_PINS);   // second ball
                if (frames[frame].second_ball == STRIKE_SCORE)    // second strike
                    frames[frame].third_ball = ball(MAX_PINS);    // third ball
                else
                    frames[frame].third_ball = ball(MAX_PINS - frames[frame].second_ball);
            }
            else
            {
                // first ball is not a strike
                frames[frame].second_ball = ball(MAX_PINS - frames[frame].first_ball);    // second ball
                frames[frame].third_ball = 0;
            }
        } 
        else
        {
            // frames 1-9
            frames[frame].first_ball = ball(MAX_PINS);    // first ball
            if (frames[frame].first_ball == STRIKE_SCORE)
            {
                frames[frame].second_ball = 0;
                frames[frame].type = STRIKE;
            }
            else
            {
                // Second ball
                frames[frame].second_ball = ball(MAX_PINS - frames[frame].first_ball);
                if (frames[frame].second_ball == MAX_PINS - frames[frame].first_ball)
                    frames[frame].type = SPARE;
                else
                    frames[frame].type = OPEN;
            }
        }
    }
}

 // return a random number between 0 and 'pins'
int ball( int pins ) 
{
    int r = rand() % 100;  // Get number between 0-99

    if (0)
        return 10;
    
    // Adjust these thresholds to change the distribution
    if (pins == MAX_PINS)
    {
        if (r < 20)      return pins;        // 20% chance for strike
        else if (r < 35) return pins - 1;    // 15% chance for 9
        else if (r < 50) return pins - 2;    // 15% chance for 8
        else             return rand() % (pins+1); // Remaining distributed normally
    }
    else
    {
        if (r < 30)      return pins;        // 30% chance for spare
        else if (r < 50) return pins>=1 ? pins-1 : 0;    // 15% chance for 9
        else if (r < 80) return pins>=2 ? pins-2 : 0;    // 15% chance for 8
        else             return rand() % (pins+1); // Remaining distributed normally
    }
}

/// @brief All frames are undefined and zero scores
/// @param frames 
void init_game_results(struct frame_results frames[MAX_FRAMES])
{
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        frames[i].type = UNDEFINED;
        frames[i].first_ball = 0;
        frames[i].second_ball = 0;
        frames[i].third_ball = 0;
        frames[i].score = 0;
    }
}
