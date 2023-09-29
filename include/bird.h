//
// Created by Deborah Bodansky on 4/10/22.
//
#pragma once

#include "cinder/gl/gl.h"

using glm::vec2;
using std::vector;

namespace dinosaurgame {

/**
 * This class represents a single bird within the dinosaur game.
 */
class Bird {
public:
    /**
     * Default constructor for the Bird class.
     */
    Bird();

    /**
     * Destructor for the Bird class.
     */
    ~Bird() = default;

    /**
     * Constructor for the Bird class. Sets internal variables manually.
     * @param square_size size of square representing each element in internal matrix
     * @param wing_up whether the bird's wing is up
     * @param position coordinates at which to draw the bottom left corner of the matrix
     * @param color color with which to draw this bird in Cinder
     */
    Bird(float square_size, bool wing_up, vec2 position);

    /**
     * Draws bird in Cinder.
     */
    void Display() const;

    /**
     * Updates the bird matrix according to current internal variables.
     */
    void Animate();

    /**
     * Fills in portion of bird matrix that remains the same regardless of wing configuration.
     */
    void DrawBirdGeneral();

    /**
     * Clears bird matrix by setting all values to false.
     */
    void ResetBirdMatrix();

    /**
     * Gets the internal representation of the bird's shape in Cinder. Used for testing.
     * @return 2D vector representing the bird's shape in Cinder
     */
    vector<vector<bool>> GetBirdMatrix();

    /**
     * Fills in the wing in the bird matrix based on wing configuration.
     */
    void ModifyMatrixByWingConfiguration();

    /**
     * Sets the bird's position.
     * @param position position to set the bird's position to
     */
    void SetPosition(vec2 position);

    /**
     * Gets whether the bird's wing is currently up.
     * @return whether the bird's wing is up
     */
    bool GetWingUp() const;

    /**
     * Sets whether the bird's wing is up.
     * @param wing_up value to set whether the bird's wing is up to
     */
    void SetWingUp(bool wing_up);

    /**
     * Gets the x-coordinate of the bird's left edge.
     * @return x-coordinate of bird's left edge
     */
    float GetLeftMostPoint();

    /**
     * Gets the x-coordinate of the bird's right edge.
     * @return x-coordinate of bird's right edge
     */
    float GetRightMostPoint();

    /**
     * Gets this the size with which each cell of the bird matrix is drawn in Cinder.
     * @return bird's square size
     */
    float GetSquareSize();

    /**
     * Gets vector of the geometrically lowest (numerically highest) values at which the bird matrix is filled in.
     * @return vector of lowest filled-in points
     */
    vector<int> GetLowestFilledInPoints();

    /**
     * Gets vector of the geometrically highest (numerically lowest) values at which the bird matrix is filled in.
     * @return vector of highest filled-in points
     */
    vector<int> GetHighestFilledInPoints();

    /**
     * Shifts the bird's position `horizontal_movement` to the right.
     * @param horizontal_movement distance by which to shift position
     */
    void MoveBird(float horizontal_movement);

    /**
     * Fills in the vectors of the geometrically lowest (numerically highest) and geometrically highest (numerically)
     * lowest) values at which the bird matrix is filled in.
     */
    void PopulateLowHighPoints();

    /**
     * Returns bottom y-coordinate of the bird at the given horizontal index in the bird matrix.
     * @param i horizontal index being examined
     * @return bottom y-coordinate at `i` units from the front of the bird
     */
    float LowestPointAtIndex(int i);

    /**
     * Returns top y-coordinate of the bird at the given horizontal index in the bird matrix.
     * @param i horizontal index being examined
     * @return top y-coordinate at `i` units from the front of the bird
     */
    float HighestPointAtIndex(int i);

private:
    /* Size of square representing each element in the bird matrix. */
    float square_size_;

    /* Whether the bird's wing is up. */
    bool wing_up_;

    /* Coordinates at which to draw bottom left corner of bird matrix. */
    vec2 position_;

    /* The matrix representing the image of the bird. */
    vector<vector<bool>> bird_matrix_;

    /* Vector of the geometrically lowest (numerically highest) values at which the bird matrix is filled in. */
    vector<int> lowest_filled_in_point_;

    /* Vector of the geometrically highest (numerically lowest) values at which the bird matrix is filled in. */
    vector<int> highest_filled_in_point_;

    /* Size of each internal vector in the bird matrix. */
    static const int kMatrixSizeX = 21;

    /* Size of external vector in the bird matrix. */
    static const int kMatrixSizeY = 18;
};

}
