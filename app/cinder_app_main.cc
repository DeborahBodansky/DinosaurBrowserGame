#include "dinosaur_game_app.h"
#include "cinder/app/RendererGl.h"

using dinosaurgame::DinosaurGameApp;

void prepareSettings(DinosaurGameApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(DinosaurGameApp, ci::app::RendererGl, prepareSettings);