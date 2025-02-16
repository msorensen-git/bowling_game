/**
 * @file game_display.c
 * @brief Bowling game score display functionality
 * 
 * This file contains functions for displaying bowling game scores in a formatted,
 * human-readable format. It provides functionality to display both complete games
 * and individual frames with proper bowling notation and formatting.
 * 
 * Key Features:
 * - Displays complete bowling game scores with frame-by-frame details
 * - Handles special formatting for strikes, spares, and open frames
 * - Provides proper alignment and spacing for all score elements
 * - Special handling for the 10th frame's unique scoring rules
 * 
 * The display format follows standard bowling notation:
 * - Strikes are marked with 'X'
 * - Spares are marked with '/'
 * - Open frames use '-' as a delimiter
 * - Running totals are maintained and displayed
 * 
 * Example output:
 * Frame  1: 10  -  X = 30 =  30
 * Frame  2: 10  -  X = 20 =  50
 * Frame  3:  7  2  - =  9 =  59
 * Frame  4:  8  2  / = 20 =  79
 * Frame  5: 10  -  X = 20 =  99
 * 
 * Functions:
 * - report_game_scores(): Displays scoring for a complete game
 * - print_frame(): Formats and displays a single frame's scoring
 * 
 * Note: All functions assume input data has been properly validated
 * before display. The file focuses solely on display formatting and
 * does not perform validation of bowling scores or game rules.
 */

#include "game_display.h"
#include <stdio.h>

/**
 * Displays the scoring results for a complete bowling game.
 * 
 * @param frames An array of frame_results structures containing the scoring data
 *              for all 10 frames of a bowling game
 * 
 * The function prints each frame's details in the following format:
 * - For regular frames (1-9):
 *   Strike:  "Frame XX: 10  -  X = YY = ZZZ"
 *   Spare:   "Frame XX: N  M  / = YY = ZZZ"
 *   Open:    "Frame XX: N  M  - = YY = ZZZ"
 * - For the tenth frame:
 *   "Frame 10: N  M  K = YY = ZZZ"
 * 
 * Where:
 * - XX is the frame number (1-10)
 * - N, M, K are the number of pins knocked down in each ball
 * - YY is the score for that frame
 * - ZZZ is the running total up to that frame
 * 
 * Special formatting:
 * - Strikes are displayed with 'X'
 * - Spares are displayed with '/'
 * - Open frames use '-' as the delimiter
 * - The 10th frame always shows all three balls if applicable
 * 
 * Example output:
 * Frame  1: 10  -  X = 30 =  30
 * Frame  2: 10  -  X = 20 =  50
 * Frame  3:  7  2  - =  9 =  59
 * Frame  4:  8  2  / = 20 =  79
 * Frame  5: 10  -  X = 20 =  99
 * 
 * Note: This function assumes the frames array contains valid bowling scores
 * that have already been validated and scored correctly.
 */
void report_game_scores(struct frame_results frames[MAX_FRAMES])
{
    int total = 0;
    for (int i = 0; i < MAX_FRAMES; i++)
    {
        total += frames[i].score;
        print_frame(frames[i], i, total);
    }
}
 
/**
 * Prints a single frame's scoring information in a formatted display.
 * 
 * @param frame The frame_results structure containing the scoring data for a single frame
 * @param frame_number The zero-based index of the frame (0-9)
 * @param subtotal The running total score up to and including this frame
 * 
 * Output Format:
 * The function formats the output differently based on frame type and position:
 * 
 * For frames 1-9:
 * - Strike: "Frame XX: 10  -  X = YY = ZZZ"
 *          Shows first ball (10), dash, and X symbol
 * - Spare: "Frame XX: N  M  / = YY = ZZZ"
 *          Shows both balls and spare symbol (/)
 * - Open:  "Frame XX: N  M  - = YY = ZZZ"
 *          Shows both balls and open frame symbol (-)
 * 
 * For frame 10:
 * "Frame 10: N  M  K = YY = ZZZ"
 * Always shows all three balls if applicable
 * 
 * Where:
 * - XX = frame number (1-10)
 * - N = first ball score
 * - M = second ball score
 * - K = third ball score (10th frame only)
 * - YY = frame score
 * - ZZZ = running total (subtotal)
 * 
 * Field Widths:
 * - Frame number: 2 characters, right-aligned
 * - Ball scores: 2 characters each, right-aligned
 * - Frame score: 2 characters, right-aligned
 * - Subtotal: 3 characters, right-aligned
 * 
 * Note: This function assumes the frame_results structure contains valid data
 * that has been previously validated.
 */
void print_frame(struct frame_results frame, int frame_number, int subtotal)
{
    if (frame_number == MAX_FRAMES - 1) // last frame
    {
        printf("Frame %2d: %2d %2d %2d = %2d = %3d\n", frame_number+1, frame.first_ball, frame.second_ball, frame.third_ball, frame.score, subtotal);
        return;
    }

    switch (frame.type)
    {
    case STRIKE:
        printf("Frame %2d: %2d  -  X = %2d = %3d\n", frame_number+1, frame.first_ball, frame.score, subtotal);
        break;
    case SPARE:
        printf("Frame %2d: %2d %2d  / = %2d = %3d\n", frame_number+1, frame.first_ball, frame.second_ball, frame.score, subtotal);
        break;
    case OPEN:
        printf("Frame %2d: %2d %2d  - = %2d = %3d\n", frame_number+1, frame.first_ball, frame.second_ball, frame.score, subtotal);
        break;
    default:
        printf("Error: unknown frame type\n");
        break;
    }
};
