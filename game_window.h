//
// Created by Deborah Bodansky on 4/19/22.
//

#pragma once

#include "cinder/gl/gl.h"
#include "dinosaur.h"
#include "cactus.h"
#include "bird.h"

using glm::vec2;
using std::vector;

namespace dinosaurgame {

/**
 * Enumerator class of possible game states.
 */
enum GameStatus { GAME_READY, GAME_IN_PROGRESS, GAME_OVER };

/**
 * This class represents the actual game window. As such, it handles all objects within the game (dinosaur, bird(s),
 * cactus(es)) and their movement within the space.
 */
class GameWindow {

public:

    /**
     * Constructor for the GameWindow class.
     */
    GameWindow();

    /**
     * Destructor for the GameWindow class.
     */
    ~GameWindow() = default;

    /**
     * Draws all elements of the game in Cinder.
     */
    void Display() const;

    /**
     * Updates the current state of the game and all objects within it.
     */
    void AdvanceOneFrame();

    /**
     * Executed when the space key is pressed. Sets the dinosaur to the beginning of his jump trajectory. If the game
     * has not yet started, starts the game.
     */
    void OnKeyPress();

    /**
     * Updates the dinosaur's position according to its vertical velocity and its vertical velocity based on the
     * acceleration constant. If the dinosaur is below regular ground level, exits him out of his jump trajectory and
     * returns him to normal running mode.
     */
    void DinosaurJump();

    /**
     * Creates `num_cacti` cacti, sets them to initial position, and adds them to the cacti vector.
     * @param num_cacti number of cacti to create
     */
    void GenerateCacti(int num_cacti);

    /**
     * Moves all cacti in the cacti vector if the preceding cactus is far enough in front of them. If the first cactus
     * in the cacti vector has exited the bounds of the game, removes it from the vector.
     */
    void MoveCacti();

    /**
     * Moves all birds in the bird vector and shifts their wings once every `kFrameInterval` frames. If the first bird
     * in the birds vector has exited the bounds of the game, removes it from the vector.
     */
    void MoveBirds();

    /**
     * Handles all game functionality assuming that the current game status is GAME_READY: dinosaur blinking.
     */
    void WaitForStartGame();

    /**
     * Handles all game functionality assuming that the current game status is GAME_IN_PROGRESS: makes dinosaur run,
     * executes jumps when the dinosaur is jumping, creates and moves cacti and birds, executes day-to-night transitions
     * and vice versa, keeps track of how many frames have elapsed since start of game (used to calculate score).
     */
    void PlayGame();

    /**
     * Updates all cacti by one frame.
     */
    void UpdateCacti();

    /**
     * Updates all birds by one frame.
     */
    void UpdateBirds();

    /**
     * For any cacti within the dinosaur's range, checks whether or not the dinosaur is colliding with them. If a
     * collision is occurring, sets the dinosaur's death status to dead and ends the game.
     */
    void CheckForCactiCollisions();

    /**
     * For any birds within the dinosaur's range, checks whether or not the dinosaur is colliding with them. If a
     * collision is occurring, sets the dinosaur's death status to dead and ends the game.
     */
    void CheckForBirdCollisions();

    /**
     * Displays text as needed in Cinder, with the passed-in `color`. While the game is in progress, displays a score at
     * top right of the game window. When the game is over, displays the text "GAME OVER" with the score achieved below.
     * @param color color with which to display the text in Cinder
     */
    void DisplayText(ci::Color color) const;

private:
    /* Color with which to draw background in Cinder. */
    ci::Color background_color_;

    /* Color with which to draw all non-background elements in Cinder. */
    ci::Color elements_color_;

    /* The current status of the game (ready to begin, in progress, or over). */
    GameStatus game_status_;

    /* Number of times AdvanceOneFrame() has been called since the dinosaur landed from a jump. */
    int frames_since_landing_;

    /* Number of times AdvanceOneFrame() has been called since the game started. */
    int frames_since_game_start_;

    /* The dinosaur instance associated with this game. */
    Dinosaur dinosaur_;

    /* Vector of operational cacti in the game. */
    vector<Cactus> cacti_;

    /* Vector of operational birds in the game. */
    vector<Bird> birds_;

    /* The y-coordinates at which to draw the line representing the ground in Cinder. */
    int ground_coordinates_;

    /* Dinosaur's position within the game window. */
    vec2 dinosaur_position_;

    /* Dinosaur's vertical velocity (will be 0 when not jumping). */
    float vertical_velocity_;

    /* Time left until dinosaur blinks. */
    int time_until_next_blink_;

    /* Time remaining of the dinosaur's next/current blink. */
    int time_blink_remaining_;

    /* Whether the dinosaur is currently in a jump trajectory. */
    bool dinosaur_is_jumping_;

    /* Whether it is currently day or night within the game. */
    bool is_day_;

    /* Time left until the next cactus(es) are generated. */
    int next_cacti_time_;

    /* The altitude (i.e. y-coordinate) at which birds fly in this game. */
    int bird_altitude_;

    /* Time left until the next bird is generated. */
    int next_bird_time_;

    /* Height from the ground at which to display the text "GAME OVER" when game is over. */
    int game_over_altitude_;

    /* Font in which to display all needed text. */
    std::string text_font_;

    /* Size with which to display the "GAME OVER" text when the game is over. */
    float game_over_size_;

    /* Height from the ground at which to display the score while the game is in progress. */
    int score_altitude_;

    /* Size with which to display the score when the game is over. */
    float score_size_;

    /* Leftmost endpoint of the ground line. */
    static const int kLeftCoordinate = 100;

    /* Rightmost endpoint of the ground line. */
    static const int kRightCoordinate = 700;

    /* Length of time the dinosaur takes to blink. */
    static const int kBlinkTime = 3;

    /* Length of time the dinosaur takes between blinks. */
    static const int kBlinkIntervalTime = 50;

    /* Ratio between what Cinder considers one frame and what I consider one frame to be.*/
    static const int kFrameInterval = 5;

    /* Constant downward acceleration with which to modify the dinosaur's vertical velocity. */
    static constexpr float kDownwardAcceleration = 1;

    /* Distance from left edge of game window to dinosaur's position. */
    static const int kLeftMargin = 20;

    /* Distance between dinosaur base and ground line. */
    static const int kGroundMargin = 5;

    /* Length of time between day-to-night change and vice versa. */
    static const int kDayLength = 500;

    /* Vertical velocity at the beginning of the dinosaur's jump trajectory. */
    static constexpr float kInitialVerticalVelocity = 12.5;

    /* Time after start of game when first cactus(es) are generated. */
    static const int kTimeCactiFirstAppearance = 100;

    /* Distance each cactus moves per frame. */
    static constexpr float kCactusSpeed = 3;

    /* Time after start of game when first bird is generated. */
    static const int kTimeBirdsFirstAppearance = 300;

    /* Distance each bird moves per frame. */
    static constexpr float kBirdSpeed = 5;
};

}
