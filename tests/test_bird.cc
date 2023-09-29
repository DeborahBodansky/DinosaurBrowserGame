#include <catch2/catch.hpp>

#include <bird.h>

using dinosaurgame::Bird;

TEST_CASE("ResetBirdMatrix") {
    Bird bird = Bird();
    bird.ResetBirdMatrix();
    vector<vector<bool>> bird_matrix = bird.GetBirdMatrix();
    for (int i = 0; i < bird_matrix.size(); i++) {
        for (int j = 0; j < bird_matrix[i].size(); j++) {
            REQUIRE(bird_matrix[i][j] == false);
        }
    }
}

//   012345678901234567890
// 0
// 1
// 2
// 3     ##
// 4    ###
// 5   #####
// 6  ######
// 7 ##############
// 8       #########
// 9        ##############
// 0         ##########
// 1          ###########
// 2           #######
// 3
// 4
// 5
// 6
// 7

TEST_CASE("DrawBirdGeneral") {
    bool t = true;
    bool f = false;
    vector<vector<bool>> expected_matrix{
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 0
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 1
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 2
        vector<bool>{f, f, f, f, t, t, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 3
        vector<bool>{f, f, f, t, t, t, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 4
        vector<bool>{f, f, t, t, t, t, t, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 5
        vector<bool>{f, t, t, t, t, t, t, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 6
        vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
        vector<bool>{f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f}, // 8
        vector<bool>{f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t, t, t, t, t}, // 9
        vector<bool>{f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, f, f, f, f}, // 10
        vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t, f, f}, // 11
        vector<bool>{f, f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, f, f, f, f}, // 12
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 13
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 14
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 15
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 16
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}  // 17
    }; //            0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20

    Bird bird = Bird();
    bird.ResetBirdMatrix();
    bird.DrawBirdGeneral();

    vector<vector<bool>> actual_matrix = bird.GetBirdMatrix();
    for (int i = 0; i < expected_matrix.size(); i++) {
        for (int j = 0; j < expected_matrix[i].size(); j++) {
            REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
        }
    }
}

TEST_CASE("Modify matrix by wing configuration") {

    bool t = true;
    bool f = false;

    //   012345678901234567890
    // 0        #
    // 1        ##
    // 2        ###
    // 3     ##  ###
    // 4    ###  ####
    // 5   ##### #####
    // 6  ###### ######
    // 7 ##############
    // 8       #########
    // 9        ##############
    // 0         ##########
    // 1          ###########
    // 2           #######
    // 3
    // 4
    // 5
    // 6
    // 7
    SECTION("Wing up") {
        vector<vector<bool>> expected_matrix{
                vector<bool>{f, f, f, f, f, f, f, t, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 0
                vector<bool>{f, f, f, f, f, f, f, t, t, f, f, f, f, f, f, f, f, f, f, f, f}, // 1
                vector<bool>{f, f, f, f, f, f, f, t, t, t, f, f, f, f, f, f, f, f, f, f, f}, // 2
                vector<bool>{f, f, f, f, t, t, f, f, t, t, t, f, f, f, f, f, f, f, f, f, f}, // 3
                vector<bool>{f, f, f, t, t, t, f, f, t, t, t, t, f, f, f, f, f, f, f, f, f}, // 4
                vector<bool>{f, f, t, t, t, t, t, f, t, t, t, t, t, f, f, f, f, f, f, f, f}, // 5
                vector<bool>{f, t, t, t, t, t, t, f, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 6
                vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
                vector<bool>{f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f}, // 8
                vector<bool>{f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t, t, t, t, t}, // 9
                vector<bool>{f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, f, f, f, f}, // 10
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t, f, f}, // 11
                vector<bool>{f, f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, f, f, f, f}, // 12
                vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 13
                vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 14
                vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 15
                vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 16
                vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}  // 17
        }; //                0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20

        Bird bird = Bird();
        bird.ResetBirdMatrix();

        bird.SetWingUp(true);
        bird.DrawBirdGeneral();
        bird.ModifyMatrixByWingConfiguration();

        vector<vector<bool>> actual_matrix = bird.GetBirdMatrix();
        for (int i = 0; i < expected_matrix.size(); i++) {
            for (int j = 0; j < expected_matrix[i].size(); j++) {
                REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
            }
        }
    }

    //   012345678901234567890
    // 0
    // 1
    // 2
    // 3     ##
    // 4    ###
    // 5   #####
    // 6  ######
    // 7 ##############
    // 8       #########
    // 9        ##############
    // 0         ##########
    // 1         ############
    // 2         #########
    // 3         ####
    // 4         ###
    // 5         ##
    // 6         ##
    // 7         #
    SECTION("Wing down") {
        vector<vector<bool>> expected_matrix{
                vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 0
                vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 1
                vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 2
                vector<bool>{f, f, f, f, t, t, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 3
                vector<bool>{f, f, f, t, t, t, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 4
                vector<bool>{f, f, t, t, t, t, t, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 5
                vector<bool>{f, t, t, t, t, t, t, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 6
                vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
                vector<bool>{f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f}, // 8
                vector<bool>{f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t, t, t, t, t}, // 9
                vector<bool>{f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, f, f, f, f}, // 10
                vector<bool>{f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t, t, f, f}, // 11
                vector<bool>{f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, f, f, f, f}, // 12
                vector<bool>{f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f, f, f, f}, // 13
                vector<bool>{f, f, f, f, f, f, f, f, t, t, t, f, f, f, f, f, f, f, f, f, f}, // 14
                vector<bool>{f, f, f, f, f, f, f, f, t, t, f, f, f, f, f, f, f, f, f, f, f}, // 15
                vector<bool>{f, f, f, f, f, f, f, f, t, t, f, f, f, f, f, f, f, f, f, f, f}, // 16
                vector<bool>{f, f, f, f, f, f, f, f, t, f, f, f, f, f, f, f, f, f, f, f, f}  // 17
        }; //                0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20

        Bird bird = Bird();
        bird.ResetBirdMatrix();

        bird.SetWingUp(false);
        bird.DrawBirdGeneral();
        bird.ModifyMatrixByWingConfiguration();

        vector<vector<bool>> actual_matrix = bird.GetBirdMatrix();
        for (int i = 0; i < expected_matrix.size(); i++) {
            for (int j = 0; j < expected_matrix[i].size(); j++) {
                REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
            }
        }
    }
}

TEST_CASE("Bird: Populate low and high vectors") {

    Bird bird = Bird();

    SECTION("Wing up") {

        bird.ResetBirdMatrix();
        bird.SetWingUp(true);
        bird.DrawBirdGeneral();
        bird.ModifyMatrixByWingConfiguration();
        bird.PopulateLowHighPoints();

        SECTION("Lowest filled-in points") {
            vector<int> expected_lowest{7, 7, 7, 7, 7, 7, 8, 9, 10, 11, 12, 12, 12, 12, 12, 12, 12, 11, 11, 9, 9};

            vector<int> actual_lowest = bird.GetLowestFilledInPoints();
            for (int i = 0; i < expected_lowest.size(); i++) {
                REQUIRE(expected_lowest[i] == actual_lowest[i]);
            }
        }

        SECTION("Highest filled-in points") {
            vector<int> expected_highest{7, 6, 5, 4, 3, 3, 5, 0, 1, 2, 3, 4, 5, 6, 8, 9, 9, 9, 9, 9, 9};

            vector<int> actual_highest = bird.GetHighestFilledInPoints();
            for (int i = 0; i < expected_highest.size(); i++) {
                REQUIRE(expected_highest[i] == actual_highest[i]);
            }
        }
    }

    SECTION("Wing down") {

        bird.ResetBirdMatrix();
        bird.SetWingUp(false);
        bird.DrawBirdGeneral();
        bird.ModifyMatrixByWingConfiguration();
        bird.PopulateLowHighPoints();

        SECTION("Lowest filled-in points") {
            vector<int> expected_lowest{7, 7, 7, 7, 7, 7, 8, 9, 17, 16, 14, 13, 12, 12, 12, 12, 12, 11, 11, 9, 9};

            vector<int> actual_lowest = bird.GetLowestFilledInPoints();
            for (int i = 0; i < expected_lowest.size(); i++) {
                REQUIRE(expected_lowest[i] == actual_lowest[i]);
            }
        }

        SECTION("Highest filled-in points") {
            vector<int> expected_highest{7, 6, 5, 4, 3, 3, 5, 7, 7, 7, 7, 7, 7, 7, 8, 9, 9, 9, 9, 9, 9};

            vector<int> actual_highest = bird.GetHighestFilledInPoints();
            for (int i = 0; i < expected_highest.size(); i++) {
                REQUIRE(expected_highest[i] == actual_highest[i]);
            }
        }
    }
}

TEST_CASE("Coordinates") {

    Bird bird = Bird();
    bird.SetPosition(vec2(300, 300));

    SECTION("Leftmost point") {
        REQUIRE(300 == (int) bird.GetLeftMostPoint());
    }

    SECTION("Rightmost point") {
        REQUIRE(331.5 == (double) bird.GetRightMostPoint());
    }

    SECTION("Highest points") {
        SECTION("Wing up") {
            bird.ResetBirdMatrix();
            bird.SetWingUp(true);
            bird.DrawBirdGeneral();
            bird.ModifyMatrixByWingConfiguration();
            bird.PopulateLowHighPoints();

            vector<double> expected_highest{285, 283.5, 282, 280.5, 279, 279, 282, 274.5, 276, 277.5, 279, 280.5, 282,
                283.5, 286.5, 288, 288, 288, 288, 288, 288};
            for (int i = 0; i < expected_highest.size(); i++) {
                REQUIRE(expected_highest[i] == bird.HighestPointAtIndex(i));
            }
        }

        SECTION("Wing down") {
            bird.ResetBirdMatrix();
            bird.SetWingUp(false);
            bird.DrawBirdGeneral();
            bird.ModifyMatrixByWingConfiguration();
            bird.PopulateLowHighPoints();

            vector<double> expected_highest{285, 283.5, 282, 280.5, 279, 279, 282, 285, 285, 285, 285, 285, 285, 285,
                286.5, 288, 288, 288, 288, 288, 288};
            for (int i = 0; i < expected_highest.size(); i++) {
                REQUIRE(expected_highest[i] == bird.HighestPointAtIndex(i));
            }
        }
    }

    SECTION("Lowest points") {
        SECTION("Wing up") {
            bird.ResetBirdMatrix();
            bird.SetWingUp(true);
            bird.DrawBirdGeneral();
            bird.ModifyMatrixByWingConfiguration();
            bird.PopulateLowHighPoints();

            vector<double> expected_lowest{285, 285, 285, 285, 285, 285, 286.5, 288, 289.5, 291, 292.5, 292.5, 292.5,
                292.5, 292.5, 292.5, 292.5, 291, 291, 288, 288};
            for (int i = 0; i < expected_lowest.size(); i++) {
                REQUIRE(expected_lowest[i] == bird.LowestPointAtIndex(i));
            }
        }

        SECTION("Wing down") {
            bird.ResetBirdMatrix();
            bird.SetWingUp(false);
            bird.DrawBirdGeneral();
            bird.ModifyMatrixByWingConfiguration();
            bird.PopulateLowHighPoints();

            vector<double> expected_lowest{285, 285, 285, 285, 285, 285, 286.5, 288, 300, 298.5, 295.5, 294, 292.5,
                292.5, 292.5, 292.5, 292.5, 291, 291, 288, 288};
            for (int i = 0; i < expected_lowest.size(); i++) {
                REQUIRE(expected_lowest[i] == bird.LowestPointAtIndex(i));
            }
        }
    }
}

TEST_CASE("Movement") {
    Bird bird = Bird();
    bird.SetPosition(vec2(300, 300));
    bird.MoveBird(20);
    REQUIRE(270 == bird.GetLeftMostPoint());
}