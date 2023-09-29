#include "cactus.h"
#include "draw_square.h"
#include "cinder/gl/gl.h"

using glm::vec2;
using ci::geom::Rect;

namespace dinosaurgame {

Cactus::Cactus() : square_size_(2), base_position_(vec2(150, 150)), horizontal_arm_length_(4) {

    height_ = rand() % (kMaxHeight - kMinHeight) + kMinHeight;
    width_ = ceil(height_ / 4);
    dist_from_ground_left_ = rand() % (int) (height_ / 2) + 1;
    dist_from_ground_right_ = rand() % (int) (height_ / 2) + 1;

    arm_width_ = ceil(width_ / 2);
    arm_height_left_ = rand() % (height_ - dist_from_ground_left_) + arm_width_;
    arm_height_right_ = rand() % (height_ - dist_from_ground_right_) + arm_width_;
}

Cactus::Cactus(float square_size, int height, int width, vec2 base_position, int horizontal_arm_length,
    int dist_from_ground_left, int dist_from_ground_right, int arm_height_left, int arm_height_right, int arm_width)
    : square_size_(square_size), height_(height), width_(width), base_position_(base_position),
    horizontal_arm_length_(horizontal_arm_length), dist_from_ground_left_(dist_from_ground_left),
    dist_from_ground_right_(dist_from_ground_right), arm_height_left_(arm_height_left),
    arm_height_right_(arm_height_right), arm_width_(arm_width) { }

void Cactus::SetBasePosition(vec2 base_position) {
    base_position_ = base_position;
}

vec2 Cactus::GetBasePosition() const {
    return base_position_;
}

void Cactus::SetHeight(int height) {
    height_ = height;
}

void Cactus::SetWidth(int width) {
    width_ = width;
}

void Cactus::SetHorizontalArmLength(int horizontal_arm_length) {
    horizontal_arm_length_ = horizontal_arm_length;
}

void Cactus::SetDistFromGroundLeft(int dist_from_ground_left) {
    dist_from_ground_left_ = dist_from_ground_left;
}

void Cactus::SetDistFromGroundRight(int dist_from_ground_right) {
    dist_from_ground_right_ = dist_from_ground_right;
}

void Cactus::SetArmHeightLeft(int arm_height_left) {
    arm_height_left_ = arm_height_left;
}

void Cactus::SetArmHeightRight(int arm_height_right) {
    arm_height_right_ = arm_height_right;
}

void Cactus::SetArmWidth(int arm_width) {
    arm_width_ = arm_width;
}

void Cactus::Display() const {

    // cactus body
    vec2 upper_left = base_position_ - (square_size_ * vec2(width_ / 2, height_));
    vec2 lower_right = base_position_ + (square_size_ * vec2(width_ / 2, 0));
    ci::gl::drawSolidRect(ci::Rectf(upper_left, lower_right));

    // left arm: horizontal
    upper_left = base_position_ - (square_size_ * vec2((width_ / 2) + horizontal_arm_length_,
      dist_from_ground_left_ + arm_width_));
    lower_right = base_position_ - (square_size_ * vec2(width_ / 2, dist_from_ground_left_));
    ci::gl::drawSolidRect(ci::Rectf(upper_left, lower_right));

    // left arm: vertical
    upper_left = base_position_ - (square_size_ * vec2((width_ / 2) + horizontal_arm_length_,
      dist_from_ground_left_ + arm_height_left_));
    lower_right = base_position_ - (square_size_ * vec2((width_ / 2) + horizontal_arm_length_ - arm_width_,
      dist_from_ground_left_));
    ci::gl::drawSolidRect(ci::Rectf(upper_left, lower_right));

    // right arm: horizontal
    upper_left = base_position_ + (square_size_ * vec2(width_ / 2,
      -1 * (dist_from_ground_right_ + arm_width_)));
    lower_right = base_position_ + (square_size_ * vec2((width_ / 2) + horizontal_arm_length_,
      -1 * dist_from_ground_right_));
    ci::gl::drawSolidRect(ci::Rectf(upper_left, lower_right));

    // right arm: vertical
    upper_left = base_position_ + (square_size_ * vec2((width_ / 2) + horizontal_arm_length_ - arm_width_,
      -1 * (dist_from_ground_right_ + arm_height_right_)));
    ci::gl::drawSolidRect(ci::Rectf(upper_left, lower_right));
}

float Cactus::GetLeftMostPoint() const {
    return base_position_.x - (square_size_ * ((width_ / 2) + horizontal_arm_length_));
}

float Cactus::GetRightMostPoint() const {
    return base_position_.x + (square_size_ * ((width_ / 2) + horizontal_arm_length_));
}

int Cactus::GetWidth() const {
    return square_size_ * width_;
}

int Cactus::GetArmWidth() const {
    return square_size_ * arm_width_;
}

int Cactus::GetTopMostLeft() const {
    return base_position_.y - (square_size_ * (dist_from_ground_left_ + arm_height_left_));
}

int Cactus::GetTopMostRight() const {
    return base_position_.y - (square_size_ * (dist_from_ground_right_ + arm_height_right_));
}

int Cactus::GetTopMostTrunk() const {
    return base_position_.y - (square_size_ * height_);
}

void Cactus::MoveCactus(float horizontal_movement) {
    base_position_.x -= square_size_ * horizontal_movement;
}

}