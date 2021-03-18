# Welcome to Breakout

This is my attempt to remake the famous retro game Breakout with notably good FPS to suit modern day monitors. 

# Technology Stack Used
- C++17
- SDL2

# Code Architecture 
The following docs below are generated through 'Doxygen' and gives you an overview of the game code base and architecture
[Architecture Docs](docs/html/index.html)

# Target Systems 
- MacOS BigSur x64 architecture. 

# How to Run the game 

### Building the game 
- Install the following frameworks 
    - [SDL2](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/mac/index.php) 
    - [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/)
    - [SDL2_mixer](https://www.libsdl.org/projects/SDL_mixer/)
    - [SDL2_images](https://www.libsdl.org/projects/SDL_image/)
- Download and Extra the following ZIP file to a folder. 
    - [Game.zip](Installation/Game.zip)
- After Extracting open the terminal and run the following command inside of the Game folder
    ``` python build.py ```
- The above steps would result in binary file being created in the name of 'breakout'

### Running the game 
- If you want to run the game in English, then type the following on the terminal ```./breakout english```
- If you want to run the game in French, then type the following on the terminal ``` ./breakout french```
    - Further, you can toggle the language on-the-go by pressing the 'L' key while in the game

### Editing levels
- If you want to edit levels as per user's liking, it can be done in the config file. Inside of config folders you'll find serveral level.txt files.
- Inside of those text files is an array of the brick map. '1' represents brick and '0' represents empty space. 
- Feel free to play around with the levels. 
# Game Trailer 
[![Breakout](https://res.cloudinary.com/marcomontalbano/image/upload/v1616032648/video_to_markdown/images/youtube--ZvIxED4Fa7E-c05b58ac6eb4c4700831b2b3070cd403.jpg)](https://youtu.be/ZvIxED4Fa7E "Breakout")

# Game Screenshots 
![Image](docs/media/screenshots/1.png)
![Image](docs/media/screenshots/2.png)
![Image](docs/media/screenshots/3.png)

# Post Mortem
- The codebase could be abstracted even more to make it look clean and optimize it. For instance, the methods in Breakout.cpp could be abstracted with the help of inheritance. The same goes for various entities of the game including paddle, ball and bricks. All of them could inherit from a parent class that has some common function like collide, hasIntersection and etc. 
 - Gameplay wise, one could add more fun elements such as powerups and extra lives. Having said that, one could also add support for chosing different lenght of paddles. The bigger paddles move slowly while the shorter paddles have faster movement speed. This could add some level of complexity and decision making in the game. 
 - Aesthetically, one could also add theme features. Such as  space theme, wildwest theme and etc. Having different themes to chosse from could spice up things for the user. 

