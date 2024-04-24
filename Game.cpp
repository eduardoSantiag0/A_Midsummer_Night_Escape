#include "Game.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include "TextureManager.hpp"


#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>


#define SCREEN_FPS 30
//Chão == (HEIGHT_WINDOW - m_groundHeight) -  Altura do Player

Game::Game () 
    : m_WIDTH_WINDOW(1920), m_HEIGHT_WINDOW(1080), background_texture(nullptr), m_groundHeight(300), m_player(780 - 170), spawnTimeInterval(1200)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
    }

    m_window = SDL_CreateWindow("A Midsummer Night's Escape", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_WIDTH_WINDOW, m_HEIGHT_WINDOW, 0);
    if (m_window == nullptr) {
        std::cout << "Nao foi  possivel abrir a janela\n";
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == nullptr) {
        std::cout << "Nao foi  possivel abrir o render \n";
        return;
    }

    
    SDL_Surface* icon = SDL_LoadBMP("./src/images/references/A-Midsummer-Night_s-Escape_Colored.bmp");
    if (icon == nullptr) {
        std::cout << "Nao foi possivel abrir o icone\n";
        return;
    }
    SDL_SetWindowIcon(m_window, icon);
    SDL_FreeSurface(icon);

    m_background = {0, 0, m_WIDTH_WINDOW, m_HEIGHT_WINDOW};
    
    m_ground = {0, m_HEIGHT_WINDOW - m_groundHeight, m_WIDTH_WINDOW, m_groundHeight};

    lastDeltaJump = 0.0;

    maxJumpHeight = m_player.getRect().h * 2;

    std::vector<Obstacles> vetorObstacles;

}

Game::~Game() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


void Game::run() {
    const int targetFrameTime = 1000 / SCREEN_FPS;
    Uint32 frameStart;
    int frameTime;
    Uint32 currentSpawnTime;


    const int chaoPlayer =  (m_HEIGHT_WINDOW - m_groundHeight) - m_player.getRect().h;
    // std::cout << "RECEBA CHAO: " << chaoPlayer;

    bool isRunning = true;


    lastTimeSpawned = SDL_GetTicks();
    while (isRunning)
    {
        frameStart = SDL_GetTicks();

        currentDeltaJump = SDL_GetTicks();
        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_SPACE:
                    m_player.isJumping = true;
                    // if (currentDeltaJump - lastDeltaJump >= jumpInterval 
                        // && m_player.isJumping == false) 
                        // {
                            // m_player.isJumping = true;
                            // std::cout << "Jump Activated\n";
                            // lastDeltaJump = SDL_GetTicks();
                        // }
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT: 
                isRunning = false;
                break;
            default:
                break;
            }
        }


        draw(m_renderer);

        if (m_player.isJumping) 
            m_player.jump();


        currentSpawnTime = SDL_GetTicks() - lastTimeSpawned;
        if (currentSpawnTime > spawnTimeInterval) 
        {
            std::cout << "Criado!";
            Obstacles i (m_WIDTH_WINDOW, 700);
            vetorObstacles.push_back(i);
            lastTimeSpawned = SDL_GetTicks();
            currentSpawnTime = 0;
        }

        std::cout << "Tempo currentSpawn" << currentDeltaJump << "\n";

        for (auto &obstacle : vetorObstacles)
        {
            obstacle.move();
        }

        verColisoes();
        SDL_RenderPresent(m_renderer);
        frameTime = SDL_GetTicks() - frameStart;

        // std::cout << "\nPosicao do quadrado: " << m_player.getRect().y << "\n";
        if (frameTime < targetFrameTime) 
            SDL_Delay(targetFrameTime - frameTime);
        
        
    }

}

void Game::draw(SDL_Renderer* m_render) 
{
    // Chao -> Branco
    // Fundo -> Azul
    // Player -> Vermelho
    // Obstáculos -> Verde
    // 

    SDL_RenderClear(m_render);
    
    SDL_SetRenderDrawColor(m_renderer, 44, 220, 250, 255); 
    SDL_RenderFillRect (m_renderer, &m_background);


    loadGround(m_render);


    m_player.draw(m_render);

    // Draw obstacles
    for (auto &obstacle : vetorObstacles)
    {
        obstacle.draw(m_render);
    }

}


bool Game::checkColisao(SDL_Rect a, SDL_Rect b) {
    int leftA, leftB, rightA, rightB, topA, topB, bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //* Cenário em que não tem colisão 
    // Um dos lados de A estão fora de B
    // 
    if( bottomA <= topB || topA >= bottomB || rightA <= leftB ||  leftA >= rightB ) {
        return false;
    }


    //* Tem colisao
    // Nenhum dos lados de A estão fora de B;
    //
    return true;
}


SDL_Texture* Game::loadBackground(const char* filepath, SDL_Renderer* renderer) 
{
    SDL_Texture* tex = TextureManager::LoadTexture(filepath, renderer);
    return tex;
}


void Game::GameOver() 
{
    m_isRuning = false;
}


void Game::loadGround (SDL_Renderer* m_render) 
{
    SDL_SetRenderDrawColor(m_renderer, 250, 255, 255, 255);
    SDL_RenderFillRect (m_renderer, &m_ground);
}

void Game::verColisoes() 
{
    // Create an iterator to iterate through the vector
    auto it = vetorObstacles.begin();

    // Iterate through the vector
    while (it != vetorObstacles.end())
    {
        // Check collision between obstacle and player
        if (checkColisao(it->getRect(), m_player.getRect())) 
        {
            // Erase the obstacle if collision is detected
            it = vetorObstacles.erase(it);
        }
        else 
        {
            // Move to the next obstacle
            ++it;
        }
    }
}