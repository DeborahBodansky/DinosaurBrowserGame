//
// Created by Deborah Bodansky on 4/10/22.
//

#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;

namespace dinosaurgame {

/**
 * This class represents a single cactus within the dinosaur game.
 */
class Cactus {
public:
    /**
     * Default constructor for the Cactus class.
     */
    Cactus();

    /**
     * Constructor for the Cactus class. Sets all internal variables.
     * @param square_size the size of each "pixel" for this cactus
     * @param height the height of this cactus' trunk
     * @param width the width of this cactus' trunk
     * @param base_position the base position of the cactus (bottom center of trunk)
     * @param horizontal_arm_length the length of the horizontal portion of each cactus arm
     * @param dist_from_ground_left how far from the cactus base the cactus' left arm starts
     * @param dist_from_ground_right how far from the cactus base the cactus' right arm starts
     * @param arm_height_left the (vertical) height of the cactus' left arm
     * @param arm_height_right the (vertical) height of the cactus' right arm
     * @param arm_width_right the width of the cactus' arms
     */
    Cactus(float square_size, int height, int width, vec2 base_position, int horizontal_arm_length,
        int dist_from_ground_left, int dist_from_ground_right, int arm_height_left, int arm_height_right,
        int arm_width);

    ~Cactus() = default;

    /**
     * Sets the base position of the cactus.
     * @param base_position coordinates to set the base position of the cactus
     */
    void SetBasePosition(vec2 base_position);

    /**
     * Gets the base position of the cactus.
     * @return coordinates of this cactus' base position
     */
    vec2 GetBasePosition() const;

    /**
     * Manually sets the height of this cactus' trunk. Used for testing.
     * @param height height to set the height of this cactus to
     */
    void SetHeight(int height);

    /**
     * Manually sets the width of this cactus' trunk. Used for testing.
     * @param width width to set the width of this cactus to
     */
    void SetWidth(int width);

    /**
     * Manually sets the horizontal arm/branch length of this cactus. Used for testing.
     * @param horizontal_arm_length length to set this cactus' horizontal arm length to
     */
    void SetHorizontalArmLength(int horizontal_arm_length);

    /**
     * Manually sets the distance from the ground at which this cactus' left arm/branch starts. Used for testing.
     * @param dist_from_ground_left distance to set this cactus' left arm's distance from the ground to
     */
    void SetDistFromGroundLeft(int dist_from_ground_left);

    /**
     * Manually sets the distance from the ground at which this cactus' right arm/branch starts. Used for testing.
     * @param dist_from_ground_right distance to set this cactus' right arm's distance from the ground to
     */
    void SetDistFromGroundRight(int dist_from_ground_right);

    /**
     * Manually sets the height of this cactus' left arm/branch. Used for testing.
     * @param arm_height_left height to set this cactus' left arm's height to
     */
    void SetArmHeightLeft(int arm_height_left);

    /**
     * Manually sets the height of this cactus' right arm/branch. Used for testing.
     * @param arm_height_right height to set this cactus' right arm's height to
     */
    void SetArmHeightRight(int arm_height_right);

    /**
     * Manually sets the width of this cactus' arms/branches. Used for testing.
     * @param arm_width width to set this cactus' arm width to
     */
    void SetArmWidth(int arm_width);

    /**
     * Draws the cactus in Cinder.
     */
    void Display() const;

    /**
     * Gets the x-coordinate of the cactus' overall left edge (i.e. the left edge of its left arm).
     * @return x-coordinate of cactus' left edge
     */
    float GetLeftMostPoint() const;

    /**
     * Gets the x-coordinate of the cactus' overall right edge (i.e. the right edge of its right arm).
     * @return x-coordinate of the cactus' right edge
     */
    float GetRightMostPoint() const;

    /**
     * Gets the width of this cactus' trunk, **multiplied by its square size** (i.e. its actual width in Cinder).
     * @return the width of the trunk multiplied by square size
     */
    int GetWidth() const;

    /**
     * Gets the arm width of this cactus, **multiplied by its square size** (i.e. the actual width of the arms in
     * Cinder.)
     * @return arm width multiplied by square size
     */
    int GetArmWidth() const;

    /**
     * Gets the y-coordinate of the top of the cactus' left arm.
     * @return y-coordinate of the top of the left arm
     */
    int GetTopMostLeft() const;

    /**
     * Gets the y-coordinate of the top of the cactus' right arm.
     * @return y-coordinate of the top of the right arm
     */
    int GetTopMostRight() const;

    /**
     * Gets the y-coordinate of the top of the cactus' trunk.
     * @return y-coordinate of the top of the trunk
     */
    int GetTopMostTrunk() const;

    /**
     * Shifts the cactus' base position `horizontal_movement` to the left.
     * @param horizontal_movement distance to move cactus to the left by
     */
    void MoveCactus(float horizontal_movement);

private:

    /* Size of square representing each unit of size for this cactus. */
    float square_size_;

    /* Height of cactus trunk. */
    int height_;

    /* Width of cactus trunk. */
    int width_;

    /* Base position (bottom center of trunk). */
    vec2 base_position_;

    /* Length of horizontal portion of both cactus arms. */
    int horizontal_arm_length_;

    /* Distance from the ground of cactus left arm. */
    int dist_from_ground_left_;

    /* Distance from the ground of cactus right arm. */
    int dist_from_ground_right_;

    /* Height of cactus left arm. */
    int arm_height_left_;

    /* Height of cactus right arm. */
    int arm_height_right_;

    /* Width of cactus arms. */
    int arm_width_;

    /* Minimum height of cactus. */
    static const int kMinHeight = 15;

    /* Maximum height of cactus. */
    static const int kMaxHeight = 23;
};

}