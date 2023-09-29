//
// Created by Deborah Bodansky on 4/10/22.
//

#pragma once

#include "cinder/gl/gl.h"
#include "cactus.h"
#include "bird.h"

using glm::vec2;
using std::vector;

namespace dinosaurgame {

    /**
     * Enumerator class for all possible foot configurations the dinosaur can have.
     */
    enum FootConfig { BOTH_DOWN, RIGHT_UP, LEFT_UP };

    /**
     * Represents a dinosaur shape.
     */
    class Dinosaur {
    public:

        /**
         * Default constructor for the Dinosaur class.
         */
        Dinosaur();

        /**
         * Destructor for the Dinosaur class.
         */
        ~Dinosaur() = default;

        /**
         * Constructor for the Dinosaur class which sets all internal variables manually.
         * @param square_size size of each "square" - the smallest building block of this shape, represented by one cell
         * in the matrix
         * @param leg_lift how many squares to lift each leg by
         * @param foot_configuration current foot configuration (both down, right up, or left up)
         * @param is_dead whether the dinosaur is dead
         * @param is_blinking whether the dinosaur is blinking
         * @param position the dinosaur's position (bottom left corner of the matrix)
         * @param color color with which to draw dinosaur in Cinder
         */
        Dinosaur(float square_size, int leg_lift, FootConfig foot_configuration, bool is_dead, bool is_blinking,
            vec2 position);

        /**
         * Sets the dinosaur's position.
         * @param position position to set the dinosaur's position to
         */
        void SetPosition(vec2 position);

        /**
         * Sets the dinosaur's foot configuration.
         * @param foot_configuration foot configuration to set the dinosaur's foot configuration to
         */
        void SetFootConfiguration(FootConfig foot_configuration);

        /**
         * Sets whether the dinosaur is dead.
         * @param is_dead death status to set dinosaur's death status to
         */
        void SetIsDead(bool is_dead);

        /**
         * Sets whether the dinosaur is currently in the process of blinking.
         * @param is_blinking blinking status to set dinosaur's blinking status to
         */
        void SetIsBlinking(bool is_blinking);

        /**
         * Gets the matrix representing this dinosaur (true for squares to fill in).
         * @return a 2D boolean vector where each true value represents a square to draw.
         */
        vector<vector<bool>> GetDinosaurMatrix();

        /**
         * Gets the dinosaur's foot configuration.
         * @return the dinosaur's foot configuration
         */
        FootConfig GetFootConfiguration();

        /**
         * Gets the x-coordinate of the dinosaur's right edge.
         * @return x-coordinate of dinosaur's right edge
         */
        float GetRightMostPoint();

        /**
         * Draws the dinosaur in Cinder.
         */
        void Display() const;

        /**
         * Updates the dinosaur matrix based on current internal variables.
         */
        void Animate();

        /**
         * Populates the dinosaur matrix with the general outline of the dinosaur that aligns with all possible
         * configurations.
         */
        void DrawDinosaurGeneral();

        /**
         * Clears the dinosaur matrix by setting all values to false.
         */
        void ResetDinosaurMatrix();

        /**
         * Modifies the eye of the dinosaur and adds the lower jaw of the dinosaur based on whether it is dead.
         */
        void ModifyMatrixByDeathStatus();

        /**
         * Adds the dinosaur's feet to the matrix based on its foot configuration.
         */
        void ModifyMatrixByFootConfiguration();

        /**
         * Fills in the vectors of the geometrically lowest (numerically highest) and geometrically highest (numerically
         * lowest) values at which the dinosaur matrix is filled in.
         */
        void PopulateLowHighVectors();

        /**
         * Returns the vector of the geographically highest (numerically lowest) pixels at each dinosaur matrix index.
         * @return vector of highest filled-in pixels
         */
        vector<int> GetHighestFilledInPixels();

        /**
         * Returns the vector of the geographically lowest (numerically highest) pixels at each dinosaur matrix index.
         * @return vector of lowest filled-in pixels
         */
        vector<int> GetLowestFilledInPixels();

        /**
         * Determines whether the dinosaur is colliding with the passed-in cactus.
         * @param cactus cactus to determine if the dinosaur is colliding with
         * @return whether the dinosaur is colliding with the cactus
         */
        bool CollidingWith(Cactus cactus) const;

        /**
         * Determines whether the dinosaur is colliding with the passed-in bird.
         * @param bird bird to determine if the dinosaur is colliding with
         * @return whether the dinosaur is colliding with the bird
         */
        bool CollidingWith(Bird bird) const;

    private:

        /**
         * Determines whether the dinosaur is above `height` on an interval of [`left`, `right`].
         * @param height height (y-coordinate) that dinosaur is above
         * @param left left edge of range being examined
         * @param right right edge of range being examined
         * @return whether the dinosaur is above `height` on an interval of [`left`, `right`]
         */
        bool IsAbove(float height, float left, float right) const;

        /* Size of square to draw for each true value in the matrix. */
        float square_size_;

        /* Number of "pixels" to lift each dinosaur leg by. */
        int leg_lift_;

        /* The dinosaur's foot configuration. */
        FootConfig foot_configuration_;

        /* Whether the dinosaur is dead. */
        bool is_dead_;

        /* Whether the dinosaur is blinking. */
        bool is_blinking_;

        /* The coordinates of the dinosaur matrix's lower left corner. */
        vec2 position_;

        /* The matrix representing the image of the dinosaur. */
        vector<vector<bool>> dinosaur_matrix_;

        /* Vector of the geometrically lowest (numerically highest) values at which the dinosaur matrix is filled in. */
        vector<int> lowest_filled_in_pixel_;

        /* Vector of the geometrically highest (numerically lowest) values at which the dinosaur matrix is filled in. */
        vector<int> highest_filled_in_pixel_;

        /* The size of the (square) matrix. */
        static const int kMatrixSize = 19;
    };

}