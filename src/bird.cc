#include "bird.h"
#include "draw_square.h"
#include "cinder/gl/gl.h"

using glm::vec2;
using ci::geom::Rect;

namespace dinosaurgame {

Bird::Bird() : square_size_(1.5), wing_up_(true), position_(vec2(250, 250)),
    bird_matrix_(vector<vector<bool>>(kMatrixSizeY,vector<bool>(kMatrixSizeX, false))),
    lowest_filled_in_point_(vector<int>(kMatrixSizeX, 0)), highest_filled_in_point_(vector<int>(kMatrixSizeX,
    0)) {
    DrawBirdGeneral();
    ModifyMatrixByWingConfiguration();
    PopulateLowHighPoints();
}

Bird::Bird(float square_size, bool wing_up, vec2 position) : square_size_(square_size), wing_up_(wing_up),
    position_(position), bird_matrix_(vector<vector<bool>>(kMatrixSizeY, vector<bool>(kMatrixSizeX,
    false))) {
    DrawBirdGeneral();
    ModifyMatrixByWingConfiguration();
    PopulateLowHighPoints();
}

void Bird::Display() const {
    for (int i = 0; i < kMatrixSizeY; i++) {
        for (int j = 0; j < kMatrixSizeX; j++) {
            if (bird_matrix_[i][j]) {
                vec2 upper_left = position_ + (square_size_ * vec2(j, -1 * (kMatrixSizeY - i)));
                vec2 lower_right = position_ + (square_size_ * vec2(j + 1, -1 * (kMatrixSizeY - i - 1)));
                ci::gl::drawSolidRect(ci::Rectf(upper_left, lower_right));
            }
        }
    }
}

void Bird::Animate() {
    ResetBirdMatrix();
    DrawBirdGeneral();
    ModifyMatrixByWingConfiguration();
    PopulateLowHighPoints();
}

void Bird::DrawBirdGeneral() {
    // head
    for (int i = 3; i <= 7; i++) {
        for (int j = 7 - i; j <= 5; j++) {
            bird_matrix_[i][j] = true;
        }
    }
    bird_matrix_[5][6] = true;
    bird_matrix_[6][6] = true;

    // body
    for (int i = 7; i <= 12; i++) {
        for (int j = i - 2; j <= i + 6; j++) {
            bird_matrix_[i][j] = true;
        }
    }

    // tail modification
    for (int i = 16; i <= 20; i++) {
        bird_matrix_[9][i] = true;
    }

    bird_matrix_[11][18] = true;
    bird_matrix_[12][17] = false;
    bird_matrix_[12][18] = false;
}

void Bird::ResetBirdMatrix() {
    for (int i = 0; i < kMatrixSizeY; i++) {
        for (int j = 0; j < kMatrixSizeX; j++) {
            bird_matrix_[i][j] = false;
        }
    }
}

vector<vector<bool>> Bird::GetBirdMatrix() {
    return bird_matrix_;
}

void Bird::ModifyMatrixByWingConfiguration() {
    if (wing_up_) {
        for (int i = 0; i <= 2; i++) {
            for (int j = 7; j <= i + 7; j++) {
                bird_matrix_[i][j] = true;
            }
        }

        for (int i = 3; i <= 6; i++) {
            for (int j = 8; j <= i + 7; j++) {
                bird_matrix_[i][j] = true;
            }
        }
    } else {
        bird_matrix_[11][8] = true;
        bird_matrix_[12][8] = true;
        bird_matrix_[12][9] = true;

        for (int i = 13; i <= 14; i++) {
            for (int j = 8; j <= 11; j++) {
                bird_matrix_[i][j] = true;
            }
        }
        bird_matrix_[14][11] = false;

        for (int i = 15; i <= 16; i++) {
            for (int j = 8; j <= 9; j++) {
                bird_matrix_[i][j] = true;
            }
        }
        bird_matrix_[17][8] = true;
    }
}

void Bird::SetPosition(vec2 position) {
    position_ = position;
}

bool Bird::GetWingUp() const {
    return wing_up_;
}

void Bird::SetWingUp(bool wing_up) {
    wing_up_ = wing_up;
}

vector<int> Bird::GetLowestFilledInPoints() {
    return lowest_filled_in_point_;
}

vector<int> Bird::GetHighestFilledInPoints() {
    return highest_filled_in_point_;
}

void Bird::MoveBird(float horizontal_movement) {
    position_.x -= square_size_ * horizontal_movement;
}

float Bird::GetLeftMostPoint() {
    return position_.x;
}

float Bird::GetRightMostPoint() {
    return position_.x + (square_size_ * kMatrixSizeX);
}

float Bird::GetSquareSize() {
    return square_size_;
}

void Bird::PopulateLowHighPoints() {
    for (int i = 0; i < kMatrixSizeX; i++) {
        int j = 0;
        while (!bird_matrix_[j][i]) {
            j++;
        }
        highest_filled_in_point_[i] = j;

        j = kMatrixSizeY - 1;
        while (!bird_matrix_[j][i]) {
            j--;
        }
        lowest_filled_in_point_[i] = j;
    }
}

float Bird::LowestPointAtIndex(int i) {
    return position_.y - (square_size_ * (kMatrixSizeY - lowest_filled_in_point_[i] - 1));
}

float Bird::HighestPointAtIndex(int i) {
    return position_.y - (square_size_ * (kMatrixSizeY - highest_filled_in_point_[i] - 1));
}

}