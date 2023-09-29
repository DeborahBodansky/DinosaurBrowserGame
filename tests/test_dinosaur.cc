

#include <catch2/catch.hpp>

#include <dinosaur.h>

using dinosaurgame::Dinosaur;
using dinosaurgame::FootConfig;
using dinosaurgame::Cactus;
using dinosaurgame::Bird;

TEST_CASE("ResetDinosaurMatrix") {
    Dinosaur dinosaur = Dinosaur();
    dinosaur.ResetDinosaurMatrix();
    vector<vector<bool>> dino_matrix = dinosaur.GetDinosaurMatrix();
    for (int i = 0; i < dino_matrix.size(); i++) {
        for (int j = 0; j < dino_matrix[i].size(); j++) {
            REQUIRE(dino_matrix[i][j] == false);
        }
    }
}

//   0123456789012345678
// 0           ########
// 1          ##########
// 2          ##########
// 3          ##########
// 4          ####
// 5          ####
// 6 #       ####
// 7 #      #####
// 8 ##    ########
// 9 ###  ####### #
// 0 ############
// 1 ############
// 2  ###########
// 3   #########
// 4    #######
// 5
// 6
// 7
// 8

TEST_CASE("DrawDinosaurGeneral") {
    bool t = true;
    bool f = false;
    vector<vector<bool>> expected_matrix{
        vector<bool>{f, f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f}, // 0
        vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 1
        vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 2
        vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 3
        vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 4
        vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 5
        vector<bool>{t, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f, f}, // 6
        vector<bool>{t, f, f, f, f, f, f, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
        vector<bool>{t, t, f, f, f, f, t, t, t, t, t, t, t, t, f, f, f, f, f}, // 8
        vector<bool>{t, t, t, f, f, t, t, t, t, t, t, t, f, t, f, f, f, f, f}, // 9
        vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 10
        vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 11
        vector<bool>{f, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 12
        vector<bool>{f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f}, // 13
        vector<bool>{f, f, f, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f, f}, // 14
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 15
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 16
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 17
        vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}  // 18
        //           0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18
    };
    Dinosaur dinosaur = Dinosaur();
    dinosaur.ResetDinosaurMatrix();
    dinosaur.DrawDinosaurGeneral();

    vector<vector<bool>> actual_matrix = dinosaur.GetDinosaurMatrix();
    for (int i = 0; i < expected_matrix.size(); i++) {
        for (int j = 0; j < expected_matrix[i].size(); j++) {
            REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
        }
    }
}

TEST_CASE("ModifyMatrixByDeathStatus") {
    bool t = true;
    bool f = false;
    SECTION("Dinosaur is alive") {
        //   0123456789012345678
        // 0           ########
        // 1          ##########
        // 2          ##########
        // 3          ##########
        // 4          ####
        // 5          ########
        // 6 #       ####
        // 7 #      #####
        // 8 ##    ########
        // 9 ###  ####### #
        // 0 ############
        // 1 ############
        // 2  ###########
        // 3   #########
        // 4    #######
        // 5
        // 6
        // 7
        // 8
        SECTION("Dinosaur is blinking") {
            vector<vector<bool>> expected_matrix{
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f}, // 0
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 1
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 2
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 3
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 4
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f, f}, // 5
                    vector<bool>{t, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f, f}, // 6
                    vector<bool>{t, f, f, f, f, f, f, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
                    vector<bool>{t, t, f, f, f, f, t, t, t, t, t, t, t, t, f, f, f, f, f}, // 8
                    vector<bool>{t, t, t, f, f, t, t, t, t, t, t, t, f, t, f, f, f, f, f}, // 9
                    vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 10
                    vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 11
                    vector<bool>{f, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 12
                    vector<bool>{f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f}, // 13
                    vector<bool>{f, f, f, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f, f}, // 14
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 15
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 16
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 17
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}  // 18
                    //           0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18
            };
            Dinosaur dinosaur = Dinosaur();
            dinosaur.ResetDinosaurMatrix();

            dinosaur.SetIsDead(false);
            dinosaur.SetIsBlinking(true);
            dinosaur.DrawDinosaurGeneral();
            dinosaur.ModifyMatrixByDeathStatus();

            vector<vector<bool>> actual_matrix = dinosaur.GetDinosaurMatrix();
            for (int i = 0; i < expected_matrix.size(); i++) {
                for (int j = 0; j < expected_matrix[i].size(); j++) {
                    REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
                }
            }
        }

        //   0123456789012345678
        // 0           ########
        // 1          ## #######
        // 2          ##########
        // 3          ##########
        // 4          ####
        // 5          ########
        // 6 #       ####
        // 7 #      #####
        // 8 ##    ########
        // 9 ###  ####### #
        // 0 ############
        // 1 ############
        // 2  ###########
        // 3   #########
        // 4    #######
        // 5
        // 6
        // 7
        // 8
        SECTION("Dinosaur is not blinking") {
            vector<vector<bool>> expected_matrix{
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f}, // 0
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, f, t, t, t, t, t, t, t}, // 1
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 2
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 3
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 4
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f, f}, // 5
                    vector<bool>{t, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f, f}, // 6
                    vector<bool>{t, f, f, f, f, f, f, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
                    vector<bool>{t, t, f, f, f, f, t, t, t, t, t, t, t, t, f, f, f, f, f}, // 8
                    vector<bool>{t, t, t, f, f, t, t, t, t, t, t, t, f, t, f, f, f, f, f}, // 9
                    vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 10
                    vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 11
                    vector<bool>{f, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 12
                    vector<bool>{f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f}, // 13
                    vector<bool>{f, f, f, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f, f}, // 14
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 15
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 16
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 17
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}  // 18
                    //           0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18
            };
            Dinosaur dinosaur = Dinosaur();
            dinosaur.ResetDinosaurMatrix();

            dinosaur.SetIsDead(false);
            dinosaur.SetIsBlinking(false);
            dinosaur.DrawDinosaurGeneral();
            dinosaur.ModifyMatrixByDeathStatus();

            vector<vector<bool>> actual_matrix = dinosaur.GetDinosaurMatrix();
            for (int i = 0; i < expected_matrix.size(); i++) {
                for (int j = 0; j < expected_matrix[i].size(); j++) {
                    REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
                }
            }
        }
    }

    //   0123456789012345678
    // 0           ########
    // 1          ##   #####
    // 2          ## # #####
    // 3          ##   #####
    // 4          ########
    // 5          ####
    // 6 #       ####
    // 7 #      #####
    // 8 ##    ########
    // 9 ###  ####### #
    // 0 ############
    // 1 ############
    // 2  ###########
    // 3   #########
    // 4    #######
    // 5
    // 6
    // 7
    // 8
    SECTION("Dinosaur is dead") {
        Dinosaur dinosaur = Dinosaur();
        dinosaur.ResetDinosaurMatrix();

        dinosaur.SetFootConfiguration(FootConfig::LEFT_UP);
        dinosaur.SetIsDead(true);

        dinosaur.DrawDinosaurGeneral();
        dinosaur.ModifyMatrixByDeathStatus();
        SECTION("General") {
            vector<vector<bool>> expected_matrix{
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f}, // 0
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, f, f, f, t, t, t, t, t}, // 1
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, f, t, f, t, t, t, t, t}, // 2
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, f, f, f, t, t, t, t, t}, // 3
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f, f}, // 4
                    vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 5
                    vector<bool>{t, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f, f}, // 6
                    vector<bool>{t, f, f, f, f, f, f, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
                    vector<bool>{t, t, f, f, f, f, t, t, t, t, t, t, t, t, f, f, f, f, f}, // 8
                    vector<bool>{t, t, t, f, f, t, t, t, t, t, t, t, f, t, f, f, f, f, f}, // 9
                    vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 10
                    vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 11
                    vector<bool>{f, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 12
                    vector<bool>{f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f}, // 13
                    vector<bool>{f, f, f, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f, f}, // 14
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 15
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 16
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 17
                    vector<bool>{f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f, f}  // 18
                    //           0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18
            };
            vector<vector<bool>> actual_matrix = dinosaur.GetDinosaurMatrix();
            for (int i = 0; i < expected_matrix.size(); i++) {
                for (int j = 0; j < expected_matrix[i].size(); j++) {
                    REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
                }
            }
        }

        SECTION("Foot configuration == BOTH_DOWN") {
            REQUIRE(dinosaurgame::FootConfig::BOTH_DOWN == dinosaur.GetFootConfiguration());
        }
    }
}

TEST_CASE("ModifyMatrixByFootConfiguration") {
    bool t = true;
    bool f = false;

    //   0123456789012345678
    // 0           ########
    // 1          ##########
    // 2          ##########
    // 3          ##########
    // 4          ####
    // 5          ####
    // 6 #       ####
    // 7 #      #####
    // 8 ##    ########
    // 9 ###  ####### #
    // 0 ############
    // 1 ############
    // 2  ###########
    // 3   #########
    // 4    #######
    // 5     ### ##
    // 6     ##   #
    // 7     #    #
    // 8     ##   ##
    SECTION("BOTH_DOWN") {
        vector<vector<bool>> expected_matrix{
                vector<bool>{f, f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f}, // 0
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 1
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 2
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 3
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 4
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 5
                vector<bool>{t, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f, f}, // 6
                vector<bool>{t, f, f, f, f, f, f, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
                vector<bool>{t, t, f, f, f, f, t, t, t, t, t, t, t, t, f, f, f, f, f}, // 8
                vector<bool>{t, t, t, f, f, t, t, t, t, t, t, t, f, t, f, f, f, f, f}, // 9
                vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 10
                vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 11
                vector<bool>{f, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 12
                vector<bool>{f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f}, // 13
                vector<bool>{f, f, f, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f, f}, // 14
                vector<bool>{f, f, f, f, t, t, t, f, t, t, f, f, f, f, f, f, f, f, f}, // 15
                vector<bool>{f, f, f, f, t, t, f, f, f, t, f, f, f, f, f, f, f, f, f}, // 16
                vector<bool>{f, f, f, f, t, f, f, f, f, t, f, f, f, f, f, f, f, f, f}, // 17
                vector<bool>{f, f, f, f, t, t, f, f, f, t, t, f, f, f, f, f, f, f, f}  // 18
                //           0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18
        };
        Dinosaur dinosaur = Dinosaur();
        dinosaur.ResetDinosaurMatrix();

        dinosaur.SetFootConfiguration(FootConfig::BOTH_DOWN);
        dinosaur.DrawDinosaurGeneral();
        dinosaur.ModifyMatrixByFootConfiguration();

        vector<vector<bool>> actual_matrix = dinosaur.GetDinosaurMatrix();
        for (int i = 0; i < expected_matrix.size(); i++) {
            for (int j = 0; j < expected_matrix[i].size(); j++) {
                REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
            }
        }
    }

    //   0123456789012345678
    // 0           ########
    // 1          ##########
    // 2          ##########
    // 3          ##########
    // 4          ####
    // 5          ####
    // 6 #       ####
    // 7 #      #####
    // 8 ##    ########
    // 9 ###  ####### #
    // 0 ############
    // 1 ############
    // 2  ###########
    // 3   #########
    // 4    #######
    // 5     #   ##
    // 6     ##   #
    // 7          #
    // 8          ##
    SECTION("LEFT_UP") {
        vector<vector<bool>> expected_matrix{
                vector<bool>{f, f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f}, // 0
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 1
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 2
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 3
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 4
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 5
                vector<bool>{t, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f, f}, // 6
                vector<bool>{t, f, f, f, f, f, f, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
                vector<bool>{t, t, f, f, f, f, t, t, t, t, t, t, t, t, f, f, f, f, f}, // 8
                vector<bool>{t, t, t, f, f, t, t, t, t, t, t, t, f, t, f, f, f, f, f}, // 9
                vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 10
                vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 11
                vector<bool>{f, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 12
                vector<bool>{f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f}, // 13
                vector<bool>{f, f, f, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f, f}, // 14
                vector<bool>{f, f, f, f, t, f, f, f, t, t, f, f, f, f, f, f, f, f, f}, // 15
                vector<bool>{f, f, f, f, t, t, f, f, f, t, f, f, f, f, f, f, f, f, f}, // 16
                vector<bool>{f, f, f, f, f, f, f, f, f, t, f, f, f, f, f, f, f, f, f}, // 17
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, f, f, f, f, f, f, f, f}  // 18
                //           0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18
        };
        Dinosaur dinosaur = Dinosaur();
        dinosaur.ResetDinosaurMatrix();

        dinosaur.SetFootConfiguration(FootConfig::LEFT_UP);
        dinosaur.DrawDinosaurGeneral();
        dinosaur.ModifyMatrixByFootConfiguration();

        vector<vector<bool>> actual_matrix = dinosaur.GetDinosaurMatrix();
        for (int i = 0; i < expected_matrix.size(); i++) {
            for (int j = 0; j < expected_matrix[i].size(); j++) {
                REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
            }
        }
    }

    //   0123456789012345678
    // 0           ########
    // 1          ##########
    // 2          ##########
    // 3          ##########
    // 4          ####
    // 5          ####
    // 6 #       ####
    // 7 #      #####
    // 8 ##    ########
    // 9 ###  ####### #
    // 0 ############
    // 1 ############
    // 2  ###########
    // 3   #########
    // 4    #######
    // 5     ###  #
    // 6     ##   ##
    // 7     #
    // 8     ##
    SECTION("RIGHT_UP") {
        vector<vector<bool>> expected_matrix{
                vector<bool>{f, f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f}, // 0
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 1
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 2
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 3
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 4
                vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 5
                vector<bool>{t, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f, f}, // 6
                vector<bool>{t, f, f, f, f, f, f, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
                vector<bool>{t, t, f, f, f, f, t, t, t, t, t, t, t, t, f, f, f, f, f}, // 8
                vector<bool>{t, t, t, f, f, t, t, t, t, t, t, t, f, t, f, f, f, f, f}, // 9
                vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 10
                vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 11
                vector<bool>{f, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 12
                vector<bool>{f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f}, // 13
                vector<bool>{f, f, f, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f, f}, // 14
                vector<bool>{f, f, f, f, t, t, t, f, f, t, f, f, f, f, f, f, f, f, f}, // 15
                vector<bool>{f, f, f, f, t, t, f, f, f, t, t, f, f, f, f, f, f, f, f}, // 16
                vector<bool>{f, f, f, f, t, f, f, f, f, f, f, f, f, f, f, f, f, f, f}, // 17
                vector<bool>{f, f, f, f, t, t, f, f, f, f, f, f, f, f, f, f, f, f, f}  // 18
                //           0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18
        };
        Dinosaur dinosaur = Dinosaur();
        dinosaur.ResetDinosaurMatrix();

        dinosaur.SetFootConfiguration(FootConfig::RIGHT_UP);
        dinosaur.DrawDinosaurGeneral();
        dinosaur.ModifyMatrixByFootConfiguration();

        vector<vector<bool>> actual_matrix = dinosaur.GetDinosaurMatrix();
        for (int i = 0; i < expected_matrix.size(); i++) {
            for (int j = 0; j < expected_matrix[i].size(); j++) {
                REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
            }
        }
    }
}

//   0123456789012345678
// 0           ########
// 1          ## #######
// 2          ##########
// 3          ##########
// 4          ####
// 5          ########
// 6 #       ####
// 7 #      #####
// 8 ##    ########
// 9 ###  ####### #
// 0 ############
// 1 ############
// 2  ###########
// 3   #########
// 4    #######
// 5     ### ##
// 6     ##   #
// 7     #    #
// 8     ##   ##
TEST_CASE("Animate") {
    bool t = true;
    bool f = false;

    vector<vector<bool>> expected_matrix{
            vector<bool>{f, f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f}, // 0
            vector<bool>{f, f, f, f, f, f, f, f, f, t, t, f, t, t, t, t, t, t, t}, // 1
            vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 2
            vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, t, t}, // 3
            vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f}, // 4
            vector<bool>{f, f, f, f, f, f, f, f, f, t, t, t, t, t, t, t, t, f, f}, // 5
            vector<bool>{t, f, f, f, f, f, f, f, t, t, t, t, f, f, f, f, f, f, f}, // 6
            vector<bool>{t, f, f, f, f, f, f, t, t, t, t, t, f, f, f, f, f, f, f}, // 7
            vector<bool>{t, t, f, f, f, f, t, t, t, t, t, t, t, t, f, f, f, f, f}, // 8
            vector<bool>{t, t, t, f, f, t, t, t, t, t, t, t, f, t, f, f, f, f, f}, // 9
            vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 10
            vector<bool>{t, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 11
            vector<bool>{f, t, t, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f}, // 12
            vector<bool>{f, f, t, t, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f}, // 13
            vector<bool>{f, f, f, t, t, t, t, t, t, t, f, f, f, f, f, f, f, f, f}, // 14
            vector<bool>{f, f, f, f, t, t, t, f, t, t, f, f, f, f, f, f, f, f, f}, // 15
            vector<bool>{f, f, f, f, t, t, f, f, f, t, f, f, f, f, f, f, f, f, f}, // 16
            vector<bool>{f, f, f, f, t, f, f, f, f, t, f, f, f, f, f, f, f, f, f}, // 17
            vector<bool>{f, f, f, f, t, t, f, f, f, t, t, f, f, f, f, f, f, f, f}  // 18
            //           0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18
    };

    Dinosaur dinosaur = Dinosaur();
    dinosaur.ResetDinosaurMatrix();
    dinosaur.Animate();
    vector<vector<bool>> actual_matrix = dinosaur.GetDinosaurMatrix();
    for (int i = 0; i < expected_matrix.size(); i++) {
        for (int j = 0; j < expected_matrix[i].size(); j++) {
            REQUIRE(expected_matrix[i][j] == actual_matrix[i][j]);
        }
    }
}

TEST_CASE("Get rightmost point") {
    Dinosaur dinosaur = Dinosaur();
    dinosaur.SetPosition(vec2(300, 300));
    REQUIRE(338 == (int) dinosaur.GetRightMostPoint());
}

//   0123456789012345678
// 0           ########
// 1          ## #######
// 2          ##########
// 3          ##########
// 4          ####
// 5          ########
// 6 #       ####
// 7 #      #####
// 8 ##    ########
// 9 ###  ####### #
// 0 ############
// 1 ############
// 2  ###########
// 3   #########
// 4    #######
// 5     ### ##
// 6     ##   #
// 7     #    #
// 8     ##   ##

TEST_CASE("Dinosaur: Populate low and high vectors") {
    SECTION("Populate highest vector") {
        vector<int> expected_highest{6, 8, 9, 10, 10, 9, 8, 7, 6, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1};

        Dinosaur dinosaur = Dinosaur();
        dinosaur.ResetDinosaurMatrix();
        dinosaur.DrawDinosaurGeneral();
        dinosaur.ModifyMatrixByDeathStatus();
        dinosaur.ModifyMatrixByFootConfiguration();
        dinosaur.PopulateLowHighVectors();

        vector<int> actual_highest = dinosaur.GetHighestFilledInPixels();
        for (int i = 0; i < expected_highest.size(); i++) {
            REQUIRE(expected_highest[i] == actual_highest[i]);
        }
    }

    SECTION("Populate lowest vector") {
        SECTION("Dinosaur alive") {
            SECTION("Both feet down") {
                vector<int> expected_lowest{11, 12, 13, 14, 18, 18, 15, 14, 15, 18, 18, 12, 8, 9, 5, 5, 5, 3, 3};

                Dinosaur dinosaur = Dinosaur();
                dinosaur.ResetDinosaurMatrix();
                dinosaur.DrawDinosaurGeneral();
                dinosaur.ModifyMatrixByDeathStatus();
                dinosaur.ModifyMatrixByFootConfiguration();
                dinosaur.PopulateLowHighVectors();

                vector<int> actual_lowest = dinosaur.GetLowestFilledInPixels();
                for (int i = 0; i < expected_lowest.size(); i++) {
                    REQUIRE(expected_lowest[i] == actual_lowest[i]);
                }
            }

            SECTION("Left foot up") {
                vector<int> expected_lowest{11, 12, 13, 14, 16, 16, 14, 14, 15, 18, 18, 12, 8, 9, 5, 5, 5, 3, 3};

                Dinosaur dinosaur = Dinosaur();
                dinosaur.ResetDinosaurMatrix();
                dinosaur.SetFootConfiguration(FootConfig::LEFT_UP);
                dinosaur.DrawDinosaurGeneral();
                dinosaur.ModifyMatrixByDeathStatus();
                dinosaur.ModifyMatrixByFootConfiguration();
                dinosaur.PopulateLowHighVectors();

                vector<int> actual_lowest = dinosaur.GetLowestFilledInPixels();
                for (int i = 0; i < expected_lowest.size(); i++) {
                    REQUIRE(expected_lowest[i] == actual_lowest[i]);
                }
            }

            SECTION("Right foot up") {
                vector<int> expected_lowest{11, 12, 13, 14, 18, 18, 15, 14, 14, 16, 16, 12, 8, 9, 5, 5, 5, 3, 3};

                Dinosaur dinosaur = Dinosaur();
                dinosaur.ResetDinosaurMatrix();
                dinosaur.SetFootConfiguration(FootConfig::RIGHT_UP);
                dinosaur.DrawDinosaurGeneral();
                dinosaur.ModifyMatrixByDeathStatus();
                dinosaur.ModifyMatrixByFootConfiguration();
                dinosaur.PopulateLowHighVectors();

                vector<int> actual_lowest = dinosaur.GetLowestFilledInPixels();
                for (int i = 0; i < expected_lowest.size(); i++) {
                    REQUIRE(expected_lowest[i] == actual_lowest[i]);
                }
            }
        }

        SECTION("Dinosaur dead") {
            vector<int> expected_lowest{11, 12, 13, 14, 18, 18, 15, 14, 15, 18, 18, 12, 8, 9, 4, 4, 4, 3, 3};
            Dinosaur dinosaur = Dinosaur();
            dinosaur.ResetDinosaurMatrix();
            dinosaur.SetIsDead(true);
            dinosaur.DrawDinosaurGeneral();
            dinosaur.ModifyMatrixByDeathStatus();
            dinosaur.ModifyMatrixByFootConfiguration();
            dinosaur.PopulateLowHighVectors();

            vector<int> actual_lowest = dinosaur.GetLowestFilledInPixels();
            for (int i = 0; i < expected_lowest.size(); i++) {
                REQUIRE(expected_lowest[i] == actual_lowest[i]);
            }
        }
    }
}

//   0123456789012345678
// 0           ########
// 1          ##   #####
// 2          ## # #####
// 3          ##   #####
// 4          ########
// 5          ####
// 6 #       ####
// 7 #      #####
// 8 ##    ########
// 9 ###  ####### #
// 0 ############
// 1 ############
// 2  ###########
// 3   #########
// 4    #######
// 5     ### ##
// 6     ##   #
// 7     #    #
// 8     ##   ##

TEST_CASE("Checking for collisions") {

    Dinosaur dinosaur = Dinosaur();

    SECTION("Cactus collisions") {

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

        SECTION("Out of range") {
            SECTION("Dinosaur on left") {
                dinosaur.SetPosition(vec2(244, 300));
                REQUIRE(dinosaur.CollidingWith(cactus) == false);
            }

            SECTION("Dinosaur on right") {
                dinosaur.SetPosition(vec2(318, 300));
                REQUIRE(dinosaur.CollidingWith(cactus) == false);
            }
        }

        SECTION("In range") {
            SECTION("Cactus left arm") {
                SECTION("Colliding") {
                    dinosaur.SetPosition(vec2(247, 298));
                    REQUIRE(dinosaur.CollidingWith(cactus) == true);
                }

                SECTION("Not colliding") {
                    dinosaur.SetPosition(vec2(247, 290));
                    REQUIRE(dinosaur.CollidingWith(cactus) == false);
                }
            }

            SECTION("Cactus trunk") {
                SECTION("Colliding") {
                    dinosaur.SetPosition(vec2(285, 252));
                    REQUIRE(dinosaur.CollidingWith(cactus) == true);
                }

                SECTION("Not colliding") {
                    SECTION("Because too high") {
                        dinosaur.SetPosition(vec2(285, 246));
                        REQUIRE(dinosaur.CollidingWith(cactus) == false);
                    }

                    SECTION("Because no horizontal overlap") {
                        SECTION("Dinosaur behind cactus") {
                            dinosaur.SetPosition(vec2(270, 252));
                            REQUIRE(dinosaur.CollidingWith(cactus) == false);
                        }

                        SECTION("Dinosaur in front of cactus") {
                            dinosaur.SetPosition(vec2(303, 252));
                            REQUIRE(dinosaur.CollidingWith(cactus) == false);
                        }
                    }
                }
            }

            SECTION("Cactus right arm") {
                SECTION("Colliding") {
                    dinosaur.SetPosition(vec2(312, 271));
                    REQUIRE(dinosaur.CollidingWith(cactus) == true);
                }

                SECTION("Not colliding") {
                    dinosaur.SetPosition(vec2(312, 264));
                    REQUIRE(dinosaur.CollidingWith(cactus) == false);
                }
            }
        }
    }

    SECTION("Bird collisions") {

        Bird bird = Bird();
        bird.SetPosition(vec2(300, 300));

        SECTION("Out of range") {
            SECTION("Dinosaur at left") {
                dinosaur.SetPosition(vec2(260, 300));
                REQUIRE(dinosaur.CollidingWith(bird) == false);
            }

            SECTION("Dinosaur at right") {
                dinosaur.SetPosition(vec2(332, 300));
                REQUIRE(dinosaur.CollidingWith(bird) == false);
            }
        }

        SECTION("In range") {
            SECTION("Dinosaur above") {
                SECTION("No collision") {
                    SECTION("Wing up") {
                        bird.ResetBirdMatrix();
                        bird.SetWingUp(true);
                        bird.DrawBirdGeneral();
                        bird.ModifyMatrixByWingConfiguration();
                        bird.PopulateLowHighPoints();

                        dinosaur.SetPosition(vec2(300, 270));
                        REQUIRE(dinosaur.CollidingWith(bird) == false);
                    }

                    SECTION("Wing down") {
                        bird.ResetBirdMatrix();
                        bird.SetWingUp(false);
                        bird.DrawBirdGeneral();
                        bird.ModifyMatrixByWingConfiguration();
                        bird.PopulateLowHighPoints();

                        dinosaur.SetPosition(vec2(300, 274));
                        REQUIRE(dinosaur.CollidingWith(bird) == false);
                    }
                }

                SECTION("Kissing") {
                    dinosaur.SetPosition(vec2(266, 313.5));
                    REQUIRE(dinosaur.CollidingWith(bird) == true);
                }

                SECTION("Stepping on") {
                    SECTION("Wing up") {
                        bird.ResetBirdMatrix();
                        bird.SetWingUp(true);
                        bird.DrawBirdGeneral();
                        bird.ModifyMatrixByWingConfiguration();
                        bird.PopulateLowHighPoints();

                        dinosaur.SetPosition(vec2(301.5, 275));
                        REQUIRE(dinosaur.CollidingWith(bird) == true);
                    }

                    SECTION("Wing down") {
                        bird.ResetBirdMatrix();
                        bird.SetWingUp(false);
                        bird.DrawBirdGeneral();
                        bird.ModifyMatrixByWingConfiguration();
                        bird.PopulateLowHighPoints();

                        dinosaur.SetPosition(vec2(301.5, 286));
                        REQUIRE(dinosaur.CollidingWith(bird) == true);
                    }
                }

                SECTION("Rubbing butts") {
                    dinosaur.SetPosition(vec2(331, 303));
                    REQUIRE(dinosaur.CollidingWith(bird) == true);
                }
            }

            SECTION("Dinosaur below") {
                SECTION("No collision") {
                    SECTION("Wing up") {
                        bird.ResetBirdMatrix();
                        bird.SetWingUp(true);
                        bird.DrawBirdGeneral();
                        bird.ModifyMatrixByWingConfiguration();
                        bird.PopulateLowHighPoints();

                        dinosaur.SetPosition(vec2(300, 332.5));
                        REQUIRE(dinosaur.CollidingWith(bird) == false);
                    }

                    SECTION("Wing down") {
                        bird.ResetBirdMatrix();
                        bird.SetWingUp(false);
                        bird.DrawBirdGeneral();
                        bird.ModifyMatrixByWingConfiguration();
                        bird.PopulateLowHighPoints();

                        dinosaur.SetPosition(vec2(300, 340));
                        REQUIRE(dinosaur.CollidingWith(bird) == false);
                    }
                }

                SECTION("Kissing") {
                    dinosaur.SetPosition(vec2(266, 321));
                    REQUIRE(dinosaur.CollidingWith(bird) == true);
                }

                SECTION("Headbutting") {
                    SECTION("Wing up") {
                        bird.ResetBirdMatrix();
                        bird.SetWingUp(true);
                        bird.DrawBirdGeneral();
                        bird.ModifyMatrixByWingConfiguration();
                        bird.PopulateLowHighPoints();

                        dinosaur.SetPosition(vec2(279.5, 314));
                        REQUIRE(dinosaur.CollidingWith(bird) == true);
                    }

                    SECTION("Wing down") {
                        bird.ResetBirdMatrix();
                        bird.SetWingUp(true);
                        bird.DrawBirdGeneral();
                        bird.ModifyMatrixByWingConfiguration();
                        bird.PopulateLowHighPoints();

                        dinosaur.SetPosition(vec2(279.5, 328));
                        REQUIRE(dinosaur.CollidingWith(bird) == true);
                    }
                }

                SECTION("Head hits tail") {
                    dinosaur.SetPosition(vec2(309.5, 325));
                    REQUIRE(dinosaur.CollidingWith(bird) == true);
                }
            }
        }
    }
}
