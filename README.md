# Breakout
Remake of the famous retro game by Atari

## Notes

- You can change the language before the start of the game i.e. by the following command `./breakout french` or you can also toggle the language on-the-go while playing the game by pressing the 'L' key.

## Game Publicity

**Project Website**: https://jugalj05hi.github.io/Breakout/ 

## Compilation Instructions

- Download SDL2, SDL_Mixer, SDL_2_ttf, SDL2_Images. Instructions at https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php
- Clone this repo and in the root folder you will find a build.py file that will the build and compile the game. 
- From the terminal type `python build.py`
- The game supports two languages as of now. English and French. To start the game in either of the language, you have to pass an argument on the command line when executing the binary 'breakout'. Eg: `./breakout french` or `./breakout english`. 


### ./Game Directory Organization

- Docs 
    - Source Code Documentation
- Assets
    - Art assets (With the Sub directories music, sound, images, and anything else)
- src
    - source code(.cpp files) The make file or any build scripts that automate the building of your project should reside here.
- include
    - header files(.h and .hpp files)
- lib
    - libraries (.so, .dll, .a, .dylib files). Note this is a good place to put SDL
- bin
    - This is the directory where your built executable(.exe for windows, .app for Mac, or a.out for Linux) and any additional generated files are put after each build.

### Additional Citation  
- LTimer class -- Using this class from Lazyfoo. Made some minor adjustments in it. https://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php


