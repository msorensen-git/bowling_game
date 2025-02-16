// bowling_game.h
#ifndef BOWLING_GAME_H
#define BOWLING_GAME_H

#define MAX_FRAMES 10
#define MAX_PINS 10
#define STRIKE_SCORE 10

enum bowling_error {
    NO_ERROR,
    INCOMPLETE_GAME,
    INVALID_PINS,
    INVALID_FRAME_TYPE
};

enum frame_type
{
    STRIKE,     // 10 points plus value of next two balls
    SPARE,      // 10 points plus value of next one ball
    OPEN,       // value of two balls
    LAST_FRAME, // 10th frame has 3 balls
    UNDEFINED   // frame has not been played yet
};

struct frame_results
{
    enum frame_type type;
    int first_ball;         // pins for first ball
    int second_ball;        // pins for second ball
    int third_ball;         // third ball used for 10th frame
    int score;              // calculated points for this frame
};

void throw_frame(struct frame_results frames[MAX_FRAMES], int frame_number);
int ball(int pins);
void play_game(struct frame_results frames[MAX_FRAMES]);
void init_game_results(struct frame_results frames[MAX_FRAMES]);

#endif /* BOWLING_GAME_H */