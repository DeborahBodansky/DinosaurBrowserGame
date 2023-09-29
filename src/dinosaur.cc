#include "dinosaur.h"
#include "draw_square.h"
#include "cinder/gl/gl.h"

using glm::vec2;
using ci::geom::Rect;

namespace dinosaurgame {

Dinosaur::Dinosaur() : square_size_(2), leg_lift_(2), foot_configuration_(FootConfig::BOTH_DOWN), is_dead_(false),
    is_blinking_(false), position_(vec2(300, 300)), dinosaur_matrix_(vector<vector<bool>>(kMatrixSize,
    vector<bool>(kMatrixSize, false))), lowest_filled_in_pixel_(vector<int>(kMatrixSize, 0)),
    highest_filled_in_pixel_(vector<int>(kMatrixSize, 0)) {
    DrawDinosaurGeneral();
    ModifyMatrixByDeathStatus();
    ModifyMatrixByFootConfiguration();
    PopulateLowHighVectors();
}

Dinosaur::Dinosaur(float square_size, int leg_lift, FootConfig foot_configuration, bool is_dead, bool is_blinking,
    vec2 position) : square_size_(square_size), leg_lift_(2), foot_configuration_(foot_configuration),
    is_dead_(is_dead), is_blinking_(is_blinking), position_(position),
    dinosaur_matrix_(vector<vector<bool>>(kMatrixSize, vector<bool>(kMatrixSize, false))),
    lowest_filled_in_pixel_(vector<int>(kMatrixSize, 0)), highest_filled_in_pixel_(vector<int>(kMatrixSize,
    0)) {
    DrawDinosaurGeneral();
    ModifyMatrixByDeathStatus();
    ModifyMatrixByFootConfiguration();
}

void Dinosaur::SetPosition(vec2 position) {
    position_ = position;
}

void Dinosaur::SetFootConfiguration(FootConfig foot_configuration) {
    foot_configuration_ = foot_configuration;
}

void Dinosaur::SetIsDead(bool is_dead) {
    is_dead_ = is_dead;
}

void Dinosaur::SetIsBlinking(bool is_blinking) {
    is_blinking_ = is_blinking;
}

vector<vector<bool>> Dinosaur::GetDinosaurMatrix() {
    return dinosaur_matrix_;
}

FootConfig Dinosaur::GetFootConfiguration() {
    return foot_configuration_;
}

float Dinosaur::GetRightMostPoint() {
    return position_.x + (square_size_ * kMatrixSize);
}

void Dinosaur::Display() const {

    for (int i = 0; i < kMatrixSize; i++) {
        for (int j = 0; j < kMatrixSize; j++) {
            if (dinosaur_matrix_[i][j]) {
                vec2 upper_left = position_ + (square_size_ * vec2(j, -1 * (kMatrixSize - i)));
                vec2 lower_right = position_ + (square_size_ * vec2(j + 1, -1 * (kMatrixSize - i - 1)));
                ci::gl::drawSolidRect(ci::Rectf(upper_left, lower_right));
            }
        }
    }
}

void Dinosaur::Animate() {
    ResetDinosaurMatrix();
    DrawDinosaurGeneral();
    ModifyMatrixByDeathStatus();
    ModifyMatrixByFootConfiguration();
    PopulateLowHighVectors();
}

void Dinosaur::DrawDinosaurGeneral() {
    // head
    for (int i = 0; i <= 3; i++) {
        for (int j = 9; j <= 18; j++) {
            if (i == 0 && (j == 9 || j == 18)) {
                continue;
            }
            dinosaur_matrix_[i][j] = true;
        }
    }

    // neck
    for (int i = 4; i <= 5; i++) {
        for (int j = 9; j <= 12; j++) {
            dinosaur_matrix_[i][j] = true;
        }
    }

    // upper torso
    for (int i = 6; i <= 9; i++) {
        for (int j = 14 - i; j <= 11; j++) {
            dinosaur_matrix_[i][j] = true;
        }
    }

    // tail
    dinosaur_matrix_[6][0] = true;
    for (int i = 7; i <= 9; i++) {
        for (int j = 0; j <= i - 7; j++) {
            dinosaur_matrix_[i][j] = true;
        }
    }


    // arm
    dinosaur_matrix_[8][12] = true;
    dinosaur_matrix_[8][13] = true;
    dinosaur_matrix_[9][13] = true;

    // lower torso
    for (int i = 10; i <= 11; i++) {
        for (int j = 0; j <= 11; j++) {
            dinosaur_matrix_[i][j] = true;
        }
    }
    for (int i = 12; i <= 14; i++) {
        for (int j = i - 11; j <= i - ((i - 12) * 2) - 1; j++) {
            dinosaur_matrix_[i][j] = true;
        }
    }
}

void Dinosaur::ResetDinosaurMatrix() {
    for (int i = 0; i < kMatrixSize; i++) {
        for (int j = 0; j < kMatrixSize; j++) {
            dinosaur_matrix_[i][j] = false;
        }
    }
}

void Dinosaur::ModifyMatrixByDeathStatus() {
    if (!is_dead_) {
        for (int i = 13; i <= 16; i++) {
            dinosaur_matrix_[5][i] = true;
        }
        if (!is_blinking_) {
            dinosaur_matrix_[1][11] = false;
        }
    } else {
        for (int i = 13; i <= 16; i++) {
            dinosaur_matrix_[4][i] = true;
        }
        for (int i = 1; i <= 3; i++) {
            for (int j = 11; j <= 13; j++) {
                dinosaur_matrix_[i][j] = false;
            }
        }
        dinosaur_matrix_[2][12] = true;
        foot_configuration_ = FootConfig::BOTH_DOWN;
    }
}

void Dinosaur::ModifyMatrixByFootConfiguration() {
    int left_foot = 0;
    int right_foot = 0;
    if (foot_configuration_ == FootConfig::LEFT_UP) {
        left_foot = leg_lift_;
    }
    if (foot_configuration_ == FootConfig::RIGHT_UP) {
        right_foot = leg_lift_;
    }

    // left foot
    dinosaur_matrix_[15 - left_foot][4] = true;
    dinosaur_matrix_[15 - left_foot][5] = true;
    dinosaur_matrix_[15 - left_foot][6] = true;
    dinosaur_matrix_[16 - left_foot][4] = true;
    dinosaur_matrix_[16 - left_foot][5] = true;
    dinosaur_matrix_[17 - left_foot][4] = true;
    dinosaur_matrix_[18 - left_foot][4] = true;
    dinosaur_matrix_[18 - left_foot][5] = true;

    // right foot
    dinosaur_matrix_[15 - right_foot][8] = true;
    dinosaur_matrix_[15 - right_foot][9] = true;
    dinosaur_matrix_[16 - right_foot][9] = true;
    dinosaur_matrix_[17 - right_foot][9] = true;
    dinosaur_matrix_[18 - right_foot][9] = true;
    dinosaur_matrix_[18 - right_foot][10] = true;
}

void Dinosaur::PopulateLowHighVectors() {
    for (int i = 0; i < kMatrixSize; i++) {
        int j = 0;
        while (!dinosaur_matrix_[j][i]) {
            j++;
        }
        highest_filled_in_pixel_[i] = j;

        j = kMatrixSize - 1;
        while (!dinosaur_matrix_[j][i]) {
            j--;
        }
        lowest_filled_in_pixel_[i] = j;
    }
}

vector<int> Dinosaur::GetHighestFilledInPixels() {
    return highest_filled_in_pixel_;
}

vector<int> Dinosaur::GetLowestFilledInPixels() {
    return lowest_filled_in_pixel_;
}

bool Dinosaur::CollidingWith(Cactus cactus) const {

    // check if dinosaur is above left arm of cactus
    float height = cactus.GetTopMostLeft();
    float left = cactus.GetLeftMostPoint();
    float right = left + cactus.GetArmWidth();
    if (!IsAbove(height, left, right)) {
        return true;
    }

    // check if dinosaur is above trunk of cactus
    height = cactus.GetTopMostTrunk();
    left = cactus.GetBasePosition().x - (cactus.GetWidth() / 2);
    right = cactus.GetBasePosition().x + (cactus.GetWidth() / 2);
    if (!IsAbove(height, left, right)) {
        return true;
    }

    // check if dinosaur is above right arm of cactus
    height = cactus.GetTopMostRight();
    right = cactus.GetRightMostPoint();
    left = right - cactus.GetArmWidth();
    if (!IsAbove(height, left, right)) {
        return true;
    }

    return false;
}

bool Dinosaur::CollidingWith(Bird bird) const {
    float dinosaur_right_edge = position_.x + square_size_ * kMatrixSize;

    float bird_square_size = bird.GetSquareSize();
    float bird_left_edge = bird.GetLeftMostPoint();

    // check if dinosaur is either entirely above or entirely below every index in the bird matrix
    for (int i = 0; i < 21; i++) {
        float left = bird_left_edge + (bird_square_size * i);
        float right = left + bird_square_size;

        // there's a chance of collision only if the dinosaur and this index of the bird overlap horizontally
        if ((left >= position_.x && left <= dinosaur_right_edge) || (right >= position_.x && right <=
            dinosaur_right_edge)) {
            float horiz_diff_left = (left - position_.x) / square_size_;
            float horiz_diff_right = (right - position_.x) / square_size_;

            for (int j = std::max((float) 0, floor(horiz_diff_left)); j <= std::min((float) kMatrixSize - 1,
                horiz_diff_right); j++) {
                // if highest point of dinosaur is higher than lowest point of bird AND lowest point of dinosaur is
                // lower than highest point of bird
                if (position_.y - (square_size_ * (kMatrixSize - highest_filled_in_pixel_[j] - 1)) <=
                    bird.LowestPointAtIndex(i) && !IsAbove(bird.HighestPointAtIndex(i), left, right)) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Dinosaur::IsAbove(float height, float left, float right) const {
    float dinosaur_right_edge = position_.x + square_size_ * kMatrixSize;

    // there's a chance of collision only if the dinosaur is within the [left, right] range
    if ((left >= position_.x && left <= dinosaur_right_edge) || (right >= position_.x && right <= dinosaur_right_edge))
        {
        float horiz_diff_left = (left - position_.x) / square_size_;
        float horiz_diff_right = (right - position_.x) / square_size_;

        for (int i = std::max((float) 0, floor(horiz_diff_left)); i <= std::min((float) kMatrixSize - 1,
            horiz_diff_right); i++) {
            // if lowest point of dinosaur is lower than height
            if (position_.y - (square_size_ * (kMatrixSize - lowest_filled_in_pixel_[i] - 1)) >= height) {
                return false;
            }
        }
    }

    return true;
}

}