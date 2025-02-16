// game_display.h
#ifndef GAME_DISPLAY_H
#define GAME_DISPLAY_H

#include "bowling_game.h"

void print_frame(struct frame_results frame, int frame_number, int subtotal);
void report_game_scores(struct frame_results frames[MAX_FRAMES]);

#endif // GAME_DISPLAY_H
