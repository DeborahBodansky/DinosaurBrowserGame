#include "cinder/gl/gl.h"
#include "draw_square.h"

using glm::vec2;
using ci::geom::Rect;

namespace dinosaurgame {

void DrawSquare(vec2 upper_left, vec2 upper_right, vec2 lower_left, vec2 lower_right) {
    Rect square;
    square.texCoords(upper_left, upper_right, lower_right, lower_left);
    ci::gl::draw(square);
}

}

