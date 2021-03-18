#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <cstdint>
#include <SDL2/SDL_mixer.h>
#include "Ball.h"
#include "Paddle.h"
#include "Contact.h"
#include "PlayerScore.h"
#include "Brick.h"
#include "LTimer.h"
#include <string>
#include <glad/glad.h>
#include "ResourceManager.h"
#include <iostream>
#include <fstream>
/**
 *The Width of the game window
 */
const int WINDOW_WIDTH = 1920;
/**
 *The Height of the game window
 */
const int WINDOW_HEIGHT = 1080;
/**
 *The target FPS we are aiming for
 */
const int FPS = 60;

/**
 * The 2D array for initializing the bricks
*/
int levelArray[10][26];
/**
 * The 2D array of brick object
*/
Brick bricks[10][26];
/**
 * The counter to keep track of number of bricks on screen
*/
int brickCounter;

enum Buttons
{
    PaddleOneUp = 0,
    PaddleOneDown,
    PaddleTwoUp,
    PaddleTwoDown,
};
bool init(){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        return false;
    }
    return true;
}

int frameCount, timerFPS, lastFrame, fps;

/**
 * Method to load the level from the scripts
 * @param level the level to be loaded
*/
void loadLevel(int level) {
    std::string filePath;
    switch (level) {
    case 1: filePath = "./config/level1.txt";break;
    case 2: filePath = "./config/level2.txt";break;
    case 3: filePath = "./config/level3.txt";break;
    default: SDL_Log("Cannot find the path");break;
    }
    std::ifstream levelFile(filePath);
    if (levelFile) {


        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 26; j++) {
                //     if (!(level >> levelArray[i][j])) {
                //         std::cout << "Bad value" << std::endl;
                //    }
                levelFile >> levelArray[i][j];
                // std::cout << levelArray[j][i];
                // level >> levelArray[i][j];
            }

        }
    }
}
/**
 * The method to set bricks
 * @param level The level to be loaded
 * @param renderer The renderer of the game loop
*/
void setBricks(int level, SDL_Renderer* renderer) {
    loadLevel(level);
    float sum = 0;
    float yColumn = 100;
    constexpr int xoffset = 75;
    constexpr int yoffset = 50;
    for (int i = 0; i < 10; ++i) {
        sum = 0;
        for (int j = 0; j < 26; ++j) {
            if (levelArray[i][j] == 1) {


                bricks[i][j].init(sum, yColumn, renderer, i);
                bricks[i][j].setSelected();
                brickCounter += 1;
            }
            sum += xoffset;

        }
        yColumn += yoffset;
    }
    
}
/**
 * The main function i.e. Entry point to the program
*/
int main(int argc, char* argv[]) {
    
    
    if (!init()) std::cout << "Failed at SDL_Init()" << std::endl;
    if(argc<2){
        std::cout << "Please pass in the language arugment i.e. ./breakout french or ./breakout english" << std::endl;
        return 0;
    }
    else {
        
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
        TTF_Init();
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        SDL_Window* window = SDL_CreateWindow("Breakout", 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        ResourceManager resourceManager = ResourceManager::getInstance();
        resourceManager.loadWords();
        TTF_Font* scoreFont = resourceManager.loadFont("./assets/fonts/DejaVuSansMono.ttf");
        Mix_Chunk* wallHitSound = resourceManager.loadWAV("./assets/sound/WallHit.wav");
        Mix_Chunk* paddleHitSound = resourceManager.loadWAV("./assets/sound/PaddleHit.wav");
        Mix_Music* backgroundMusic = resourceManager.loadMusic("./assets/sound/Background.MP3");
        Mix_Chunk* brickBreak = resourceManager.loadWAV("./assets/sound/BrickBreak.MP3");
        Mix_Chunk* gameOver = resourceManager.loadWAV("./assets/sound/GameOver.wav");
        
        PlayerScore heart(Vec2(10, 20), renderer, scoreFont);
        PlayerScore lives(Vec2(70, 20), renderer, scoreFont);
        PlayerScore flag(Vec2(100, 20), renderer, scoreFont);
        PlayerScore score(Vec2(WINDOW_WIDTH - 150, 20), renderer, scoreFont);
        PlayerScore star(Vec2(WINDOW_WIDTH - 200, 20), renderer, scoreFont);
        PlayerScore levelText(Vec2(WINDOW_WIDTH - 500, 20), renderer, scoreFont);
        PlayerScore levelDisplay(Vec2(WINDOW_WIDTH - 350, 20), renderer, scoreFont);
        PlayerScore message(Vec2(WINDOW_WIDTH - 1300, 20), renderer, scoreFont);
        


        // PlayerScore playerTwoScoreText(Vec2(3 * WINDOW_WIDTH / 4, 20), renderer, scoreFont);

        //Create the ball
        Ball ball(Vec2(WINDOW_WIDTH / 2.0f, (WINDOW_HEIGHT - 100)), Vec2(0.001f, -BALL_SPEED), WINDOW_HEIGHT, WINDOW_WIDTH, renderer);

        //Create the paddles
        Paddle paddleOne(
            Vec2(((WINDOW_WIDTH / 2.0f) - (PADDLE_WIDTH / 2.0f)), (WINDOW_HEIGHT - 60)), Vec2(0.0f, 0.0f), renderer);

        Mix_PlayMusic(backgroundMusic, -1);
        
        int level = 1;

        setBricks(level, renderer);
        
        bool running = true;
        bool buttons[4] = {};
        float dt = 0.0f;
        int livesCounter = 3;
        int scoreCounter = 0;
        static uint32_t lastTime = 0;
        int language = 1;
        if (strcmp(argv[1], "french") == 0 || strcmp(argv[1], "French") == 0 || strcmp(argv[1], "FRENCH") == 0)
            language = 0;
        bool gameEnd = false;
        bool pause = false;
        LTimer capTimer;
        heart.SetHeart();
        star.SetStar();
        resourceManager.setLanguage(language);
        /**
        * The game loop
        */
        while (running) {
            
            auto startTime = std::chrono::high_resolution_clock::now();
            lastFrame = capTimer.getSDLTicks();
            if (lastFrame >= (lastTime + 1000)) {
                lastTime = lastFrame;
                fps = frameCount;
                frameCount = 0;
            }

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        running = false;
                    }
                    else if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
                    {
                        buttons[Buttons::PaddleOneUp] = true;
                    }
                    else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
                    {
                        buttons[Buttons::PaddleOneDown] = true;
                    }
                    else if (event.key.keysym.sym == SDLK_l) {
                        if(language == 0) {
                            resourceManager.setLanguage(1);
                            language = 1;
                        }
                        else if (language == 1) {
                            resourceManager.setLanguage(0);
                            language = 0;
                        }
                    }

                }
                else if (event.type == SDL_KEYUP)
                {
                    if (event.key.keysym.sym == SDLK_a || event.key.keysym.sym == SDLK_LEFT)
                    {
                        buttons[Buttons::PaddleOneUp] = false;
                    }
                    else if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_RIGHT)
                    {
                        buttons[Buttons::PaddleOneDown] = false;
                    }
                }
            }
                if (buttons[Buttons::PaddleOneUp])
                {
                    paddleOne.velocity.x = -PADDLE_SPEED;
                }
                else if (buttons[Buttons::PaddleOneDown])
                {
                    paddleOne.velocity.x = PADDLE_SPEED;
                }
                else
                {
                    paddleOne.velocity.x = 0.0f;
                }

        
            paddleOne.Update(dt, WINDOW_WIDTH);   
            lives.SetScore(livesCounter);
            levelText.SetText(resourceManager.getWords("Level"));
            levelDisplay.SetScore(level);
            score.SetScore(scoreCounter);
            flag.setFlag(language);
            
            // playerTwoScoreText.SetScore(playerTwoScore);
            
            if (Contact contact = paddleOne.checkCollision(ball);
                contact.type != CollisionType::None)
            {
                ball.CollideWithPaddle(contact);
                Mix_PlayChannel(-1, paddleHitSound, 0);
            }
            else if (contact = ball.CheckWallCollision(); 
                contact.type != CollisionType::None)
            {
                ball.CollideWithWall(contact);
                if (contact.type == CollisionType::Bottom) {
                    livesCounter -= 1;
                    if (livesCounter < 0) {
                        livesCounter = 0;
                        message.SetText(resourceManager.getWords("Game Over :("));
                        
                        gameEnd = true;
                        Mix_PauseMusic();
                        Mix_PlayChannel(-1, gameOver, 0);
                    }
                    lives.SetScore(livesCounter);
                    ball.Reset();
                    paddleOne.Reset();
                    SDL_Delay(1000);
                }
                else if (contact.type == CollisionType::Right || contact.type == CollisionType::Left || contact.type == CollisionType::Top) {
                    Mix_PlayChannel(-1, wallHitSound, 0);
                }
                
            }
            
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    if (bricks[i][j].CollisionWithBall(ball, dt)) {

                        Mix_PlayChannel(-1, brickBreak, 0);
                        scoreCounter += 100;
                        brickCounter--;
                       
                        switch (scoreCounter) {
                        case 0 ... 1500: message.SetText(resourceManager.getWords("Good Luck!")); break;
                        case 1600 ... 5000: message.SetText(resourceManager.getWords("Good going!")); break;
                        case 5100 ... 7000: message.SetText(resourceManager.getWords("You got it, Champ!")); break;
                        case 7100 ... 10000: message.SetText(resourceManager.getWords("Way to go!")); break;
                        }
                        if (brickCounter == 0) {
                            
                            message.SetText(resourceManager.getWords("You won! Onto Next Level"));
                            ++level;
                            ball.Reset();
                            paddleOne.Reset();
                            gameEnd = true;
                        }
                        score.SetScore(scoreCounter);
                    }
                }
            }
            ball.Update(dt);
            
            
            SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xFF);
            SDL_RenderClear(renderer);
            
            // Drawing the net
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

            //Drawing the ball
           
            
            //Drawing the Paddles
            paddleOne.Draw();
            
            //Drawing the score board
            heart.Draw();
            lives.Draw();
            flag.Draw();
            message.Draw();
            levelText.Draw();
            levelDisplay.Draw();
            star.Draw();
            score.Draw();
            // playerTwoScoreText.Draw();
            
            ball.Draw();

            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 26; ++j) {
                    bricks[i][j].draw(renderer);
                }
            }


           
            frameCount++;
            timerFPS = capTimer.getSDLTicks() - lastFrame;
            if (timerFPS < (1000 / FPS)) {
                SDL_Delay((1000 / FPS) - timerFPS);
            }
            std::cout << "FPS: " << fps << std::endl;
            
            SDL_RenderPresent(renderer);
           
            
            auto stopTime = std::chrono::high_resolution_clock::now();
            dt = std::chrono::duration<float, std::chrono::milliseconds::period>(stopTime - startTime).count();
            

            if (gameEnd) {
                gameEnd = false;
                SDL_Delay(4000);
                setBricks(level, renderer);
                livesCounter = 3;
                Mix_ResumeMusic();
            }

        }
        Mix_FreeChunk(wallHitSound);
        Mix_FreeChunk(paddleHitSound);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_CloseFont(scoreFont);
        Mix_Quit();
        TTF_Quit();
        SDL_Quit();
    }
    return 0;
}