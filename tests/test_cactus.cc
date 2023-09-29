#include <catch2/catch.hpp>

#include <cactus.h>

using dinosaurgame::Cactus;

TEST_CASE("Cactus coordinates") {

    Cactus cactus = Cactus();
    cactus.SetBasePosition(vec2(300, 300));
    cactus.SetHeight(25);
    cactus.SetWidth(6);
    cactus.SetArmWidth(4);
    cactus.SetHorizontalArmLength(5);
    cactus.SetDistFromGroundLeft(10);
    cactus.SetArmHeightLeft(7);
    cactus.SetDistFromGroundRight(9);
    cactus.SetArmHeightRight(13);

    SECTION("Leftmost point") {
        REQUIRE(284 == cactus.GetLeftMostPoint());
    }

    SECTION("Rightmost point") {
        REQUIRE(316 == cactus.GetRightMostPoint());
    }

    SECTION("Width") {
        REQUIRE(12 == cactus.GetWidth());
    }

    SECTION("Arm width") {
        REQUIRE(8 == cactus.GetArmWidth());
    }

    SECTION("Topmost...") {
        SECTION("Left") {
            REQUIRE(266 == cactus.GetTopMostLeft());
        }

        SECTION("Right") {
            REQUIRE(256 == cactus.GetTopMostRight());
        }

        SECTION("Trunk") {
            REQUIRE(250 == cactus.GetTopMostTrunk());
        }
    }
}

TEST_CASE("Cactus movement") {
    Cactus cactus = Cactus();
    cactus.SetBasePosition(vec2(300, 300));
    cactus.MoveCactus(20);
    REQUIRE(260 == cactus.GetBasePosition().x);
}