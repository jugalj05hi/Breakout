## Add any additional notes here

- You can change the language before the start of the game i.e. by the following command `./breakout french` or you can also toggle the language on-the-go while playing the game by pressing the 'L' key.

## Game Publicity

**Project Website**: https://jugalj05hi.github.io/Breakout/ (See part 3)

## Compilation Instructions

- The game supports two languages as of now. English and French. To start the game in either of the language, you have to pass an argument on the command line when executing the binary 'breakout'. Eg: `./breakout french` or `./breakout english`. 

## Project Hieararchy

In the future, other engineers may take on our project, so we have to keep it organized given the following requirements below. Forming some good organization habits now will help us later on when our project grows as well. This is the required project hierarchy you should have.

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
- GameBuild (Optional)
    - You may optionally put a .zip to you final deliverable. One should be able to copy and paste this directory, and only this directory onto another machine and be able to run the game. This is optional because for this course we will be building your projects from source. However, in the game industry it is useful to always have a build of a game ready for testers, thus a game project hieararchy would likely have this directory in a repo or other storage medium.
- ThirdParty
    - LTimer class -- I've used the class as given on the lazyfoo website and made some minor modifications in it to better suit my code and needs

**Additional Notes:** 

1. src and include should only contain ".cpp" or ".hpp" files. Why? It makes it very fast to do a backup of your game project as one example. Secondly, binary files that are generated often clutter up directories. I should not see any binaries in your repository, you may use a '.gitignore' file to help prevent this automatically. 
