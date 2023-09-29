//
// Created by Deborah Bodansky on 4/13/22.
//
#pragma once

#include "cinder/app/App.h"
#include "cinder/gl/gl.h"
#include "dinosaur.h"
#include "cactus.h"
#include "bird.h"
#include "game_window.h"

namespace dinosaurgame {

class DinosaurGameApp : public ci::app::App {
public:
    bool GAME_DEMO = true;

    DinosaurGameApp();

    void draw() override;
    void update() override;
    void keyDown(ci::app::KeyEvent event) override;

    const int kWindowSize = 875;
    const int kMargin = 100;

private:
//    Dinosaur dinosaur_;
//    Cactus cactus_;
//    Bird bird_;

    GameWindow game_window_;
};

}
