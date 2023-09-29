# Dinosaur Game: Illini Style

## What is it?

You know that dinosaur game that you can play on a Google Chrome browser when there's no internet? Have you ever wanted to have it available on your computer so that you can play it whenever you want? You're in luck! This is exactly what this project does. It allows you to play a slightly simplified version of this game, where your dinosaur figurine runs, jumps, and gracefully evades obstacles in the forms of cacti (by jumping over them) and birds (by ducking under them).  All you need to do is clone this repo and start it up, and you can play the game from anywhere that you can bring your laptop to. For added school spirit, the game is all in Illini colors (orange and blue!).

## How do I do that?

This project is built in Cinder, a C++ library, and compiled using CMake. It also uses Catch2 for testing, and the `CMakeLists.txt` file will import this library for you if you choose to build `dinosaur-test`. This won't be important to you if all you want to do is play the game. Doing so is a simple process:

* Download Cinder. You cannot play this game without it. Then clone this repository inside your Cinder folder. From here, you should theoretically be able to run this game from whatever IDE your prefer; please note, however, that it has only been tested and run in CLion.
* Run the `dinosaur-game` target. If you use CLion, you can do this by selecting "dinosaur-game | Debug" from the target menu and clicking the green go button. Alternatively, you can select "Run" on the CLion toolbar and select `Run 'dinosaur game'`, which should be the first option. This will build the target and run it for you.
* A separate window will appear, showing a dinosaur standing on a stretch of ground. Navigate to this window and click inside it, once. If you don't do this, the game will not respond to any further clicks and you will not actually be able to start playing.
* Pressing the space bar will start the game. You can also make the dinosaur jump with the space bar.
* Once you are done playing, you can exit the game by clicking the red stop button next to the target menu in CLion, or by clicking "Run" in the CLion toolbar and selecting `Stop`.

Hope you enjoy!
