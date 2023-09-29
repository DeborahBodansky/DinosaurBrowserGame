#include "dinosaur_game_app.h"

using ci::app::KeyEvent;

namespace dinosaurgame {

DinosaurGameApp::DinosaurGameApp() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);

//    if (GAME_DEMO) {
    game_window_ = GameWindow();
//    } else {
//        dinosaur_ = Dinosaur();
//        cactus_ = Cactus();
//        bird_ = Bird();
//    }
}

void DinosaurGameApp::draw() {
    // if (GAME_DEMO) {
    game_window_.Display();
//    } else {
//        ci::Color background_color("blue");
//        ci::gl::clear(background_color);
//        dinosaur_.Display();
//        cactus_.Display();
//        bird_.Display();
//    }
}
void DinosaurGameApp::update() {
    game_window_.AdvanceOneFrame();
}

void DinosaurGameApp::keyDown(KeyEvent event) {
//    if (event.getCode() == KeyEvent::KEY_SPACE) {
    game_window_.OnKeyPress();
}

}