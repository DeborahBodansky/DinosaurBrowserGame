#include "game_window.h"
#include "cinder/gl/gl.h"
#include "cinder/Font.h"

using glm::vec2;

namespace dinosaurgame {

GameWindow::GameWindow() : background_color_(ci::Color("blue")),
    elements_color_(ci::Color("orange")), game_status_(GameStatus::GAME_READY), frames_since_landing_(0),
    frames_since_game_start_(0), dinosaur_(Dinosaur()), cacti_(vector<Cactus>()), birds_(vector<Bird>()),
    ground_coordinates_(450), dinosaur_position_(vec2(kLeftCoordinate + kLeftMargin, ground_coordinates_
    + kGroundMargin)), vertical_velocity_(0), time_until_next_blink_(kBlinkIntervalTime * kFrameInterval),
    time_blink_remaining_(kBlinkTime * kFrameInterval), dinosaur_is_jumping_(false), is_day_(true),
    next_cacti_time_(kTimeCactiFirstAppearance), bird_altitude_(90), next_bird_time_(kTimeBirdsFirstAppearance),
    game_over_altitude_(270), text_font_("LucidaGrande-Bold"), game_over_size_(50), score_altitude_(300),
    score_size_(30) {
    dinosaur_.SetPosition(dinosaur_position_);
}

void GameWindow::Display() const {
    if (is_day_) {
        ci::gl::clear(background_color_);
        ci::gl::color(elements_color_);
        DisplayText(elements_color_);
    } else {
        ci::gl::clear(elements_color_);
        ci::gl::color(background_color_);
        DisplayText(background_color_);
    }

    ci::gl::drawLine(vec2(kLeftCoordinate, ground_coordinates_), vec2(kRightCoordinate,
        ground_coordinates_));

    for (const Cactus &c : cacti_) {
        c.Display();
    }

    for (const Bird &b : birds_) {
        b.Display();
    }

    dinosaur_.Display();

    // add "wings" on both sides of the game "window" behind which cacti and birds can disappear smoothly
    if (is_day_) {
        ci::gl::color(background_color_);
    } else {
        ci::gl::color(elements_color_);
    }
    ci::gl::drawSolidRect(ci::Rectf(vec2(kRightCoordinate, ground_coordinates_ - 200),
        vec2(kRightCoordinate + 50, ground_coordinates_ + 10)));
    ci::gl::drawSolidRect(ci::Rectf(vec2(0, ground_coordinates_ - 200), vec2(kLeftCoordinate,
        ground_coordinates_ + 10)));
}

void GameWindow::AdvanceOneFrame() {
    if (game_status_ == GameStatus::GAME_READY) {
        WaitForStartGame();
    } else if (game_status_ == GameStatus::GAME_IN_PROGRESS) {
        PlayGame();
    }

    // actually update dinosaur matrix
    dinosaur_.Animate();

    // end game if dinosaur is colliding with any cacti
    CheckForCactiCollisions();

    // end game if dinosaur is colliding with any birds
    CheckForBirdCollisions();
}

void GameWindow::OnKeyPress() {
    if (game_status_ == GameStatus::GAME_READY) {
        game_status_ = GameStatus::GAME_IN_PROGRESS;
        dinosaur_.SetIsBlinking(false); // dinosaur should not blink while game is in session
    }

    if (!dinosaur_is_jumping_) {
        dinosaur_is_jumping_ = true;
        dinosaur_.SetFootConfiguration(FootConfig::BOTH_DOWN);
        vertical_velocity_ = kInitialVerticalVelocity;
    }
}

void GameWindow::DinosaurJump() {
    // if the dinosaur has returned to the ground, his jump is over
    if (dinosaur_position_.y > ground_coordinates_ + 5) {
        dinosaur_position_.y = ground_coordinates_ + 5;
        dinosaur_.SetPosition(dinosaur_position_);
        dinosaur_is_jumping_ = false;
        vertical_velocity_ = 0;
        frames_since_landing_ = 0;
        dinosaur_.SetFootConfiguration(FootConfig::LEFT_UP);
    } else {
        // otherwise, update position based on velocity and (vertical) velocity based on acceleration
        dinosaur_position_.y -= vertical_velocity_;
        dinosaur_.SetPosition(dinosaur_position_);
        vertical_velocity_ -= kDownwardAcceleration;
    }
}

void GameWindow::GenerateCacti(int num_cacti) {
    for (int i = 0; i < num_cacti; i++) {
        // each cactus gets a different random seed, so that even cacti in clusters are all different
        srand(frames_since_game_start_ + i);
        Cactus cactus = Cactus();
        cactus.SetBasePosition(vec2(kRightCoordinate + kLeftMargin, ground_coordinates_
            + kGroundMargin));
        cacti_.push_back(cactus);
    }

    srand(time(0));
    next_cacti_time_ = rand() % kTimeCactiFirstAppearance + 50;
}

void GameWindow::MoveCacti() {
    // do nothing if there are no cacti
    if (cacti_.size() == 0) {
        return;
    }

    // move each cactus ONLY if the cactus before it does not overlap with it
    for (int i = cacti_.size(); i >= 0; i--) {
        if (i == 0 || (i > 0 && cacti_[i].GetLeftMostPoint() > cacti_[i - 1].GetRightMostPoint())) {
            cacti_[i].MoveCactus(kCactusSpeed);
        }
    }

    // once first cactus is off the grid, delete it
    if (cacti_[0].GetRightMostPoint() < kLeftCoordinate) {
        cacti_.erase(cacti_.begin());
    }
}

void GameWindow::MoveBirds() {
    // do nothing if there are no birds
    if (birds_.size() == 0) {
        return;
    }

    // move each bird
    for (int i = birds_.size() - 1; i >= 0; i--) {
        birds_[i].MoveBird(kBirdSpeed);

        // every `kFrameInterval` frames, switch wing from up to down and vice versa
        if (frames_since_game_start_ % kFrameInterval == 0) {
            if (birds_[i].GetWingUp()) {
                birds_[i].SetWingUp(false);
            } else {
                birds_[i].SetWingUp(true);
            }
        }

        birds_[i].Animate();
    }

    // once first bird is off the grid, delete it
    if (birds_[0].GetRightMostPoint() < kLeftCoordinate) {
        birds_.erase(birds_.begin());
    }
}

void GameWindow::WaitForStartGame() {
    // if it's time for dinosaur to blink -- and not yet time for dinosaur to finish blinking
    if (time_until_next_blink_ == 0 && time_blink_remaining_ > 0) {
        // if we've just started blinking
        if (time_blink_remaining_ == kBlinkTime * kFrameInterval) {
            dinosaur_.SetIsBlinking(true);
        }
        time_blink_remaining_--;
    } else if (time_until_next_blink_ == 0) {

        // finished blinking: reset variables, begin countdown again
        dinosaur_.SetIsBlinking(false);
        time_blink_remaining_ = kBlinkTime * kFrameInterval;
        time_until_next_blink_ = kBlinkIntervalTime * kFrameInterval;
    } else {
        time_until_next_blink_--;
    }
}

void GameWindow::PlayGame() {
    frames_since_game_start_++;
    next_cacti_time_--;
    next_bird_time_--;

    // change from day to night every once in a while
    if (frames_since_game_start_ % (kDayLength * kFrameInterval) == 0) {
        if (is_day_) {
            is_day_ = false;
        } else {
            is_day_ = true;
        }
    }

    UpdateCacti();
    UpdateBirds();

    if (dinosaur_is_jumping_) {
        // if dinosaur is jumping, he should always have both feet down
        DinosaurJump();
    } else {
        frames_since_landing_++;
        if (frames_since_landing_ % kFrameInterval == 0) {
            if (dinosaur_.GetFootConfiguration() == FootConfig::LEFT_UP) {
                dinosaur_.SetFootConfiguration(FootConfig::RIGHT_UP);
            } else if (dinosaur_.GetFootConfiguration() == FootConfig::RIGHT_UP) {
                dinosaur_.SetFootConfiguration(FootConfig::LEFT_UP);
            }
        }
    }
}

void GameWindow::UpdateCacti() {
    if (next_cacti_time_ * kFrameInterval == 0) {
        srand(time(0));
        int cacti_cluster_size = rand() % 3 + 1;
        GenerateCacti(cacti_cluster_size);
    }

    MoveCacti();
}

void GameWindow::UpdateBirds() {
    if (next_bird_time_ * kFrameInterval == 0) {
        Bird bird = Bird();
        bird.SetPosition(vec2(kRightCoordinate + kLeftMargin, ground_coordinates_ - bird_altitude_));
        birds_.push_back(bird);
        srand(time(0));
        next_bird_time_ = rand() % kTimeBirdsFirstAppearance + 80;
    }

    MoveBirds();
}

void GameWindow::CheckForCactiCollisions() {
    if (game_status_ == GameStatus::GAME_IN_PROGRESS) {
        int i = 0;
        while (i < cacti_.size() && cacti_[i].GetLeftMostPoint() <= dinosaur_.GetRightMostPoint()) {
            if (dinosaur_.CollidingWith(cacti_[i])) {
                game_status_ = GameStatus::GAME_OVER;
                dinosaur_.SetIsDead(true);
                break;
            }
            i++;
        }
    }
}

void GameWindow::CheckForBirdCollisions() {
    if (game_status_ == GameStatus::GAME_IN_PROGRESS) {
        int i = 0;
        while (i < birds_.size() && birds_[i].GetLeftMostPoint() <= dinosaur_.GetRightMostPoint()) {
            if (dinosaur_.CollidingWith(birds_[i])) {
                game_status_ = GameStatus::GAME_OVER;
                dinosaur_.SetIsDead(true);
                break;
            }
            i++;
        }
    }
}

void GameWindow::DisplayText(ci::Color color) const {
    int score = floor(frames_since_game_start_ / kFrameInterval);
    if (game_status_ == GameStatus::GAME_IN_PROGRESS) {
        ci::gl::drawStringRight("Score: " + std::to_string(score), vec2(kRightCoordinate,
            score_altitude_), color);
    } else if (game_status_ == GameStatus::GAME_OVER) {
        ci::gl::drawStringCentered("GAME OVER", vec2(kLeftCoordinate + ((kRightCoordinate - kLeftCoordinate)
            / 2), game_over_altitude_), color, ci::Font(text_font_,game_over_size_));
        ci::gl::drawStringCentered("Score: " + std::to_string(score), vec2(kLeftCoordinate +
            ((kRightCoordinate - kLeftCoordinate) / 2), game_over_altitude_ + score_size_ + 20), color,
            ci::Font(text_font_, score_size_));
    }
}

}

