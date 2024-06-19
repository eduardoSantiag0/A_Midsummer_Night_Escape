#include "Game.hpp"
#include <iostream>
#include "SDL2/SDL.h"
// #include "TextureManager.hpp"
#include <time.h>
#include <algorithm>

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>


#define SCREEN_FPS 30
//Chão == (HEIGHT_WINDOW - m_groundHeight) -  Altura do Player

Game::Game () 
    : m_WIDTH_WINDOW(1920), m_HEIGHT_WINDOW(1080), 
    background_texture(nullptr), m_groundHeight(300), 
    m_player(780 - 170), m_score_player(0),
    spawnTimeInterval(1300), 
    m_startScreen (true), m_gameOverScreen(false),
    m_textTexture(nullptr), m_font(nullptr), 
    scoreDisplay (1920, 20, 6)
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

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return;
    }


    m_background = {0, 0, m_WIDTH_WINDOW, m_HEIGHT_WINDOW};
    m_ground = {0, m_HEIGHT_WINDOW - m_groundHeight, m_WIDTH_WINDOW, m_groundHeight};
    // maxJumpHeight = m_player.getRect().h * 2;

    std::vector<Obstacles> vetorObstacles;

    srand(time(0));

    m_font = TTF_OpenFont("src/fonts/light-arial.ttf", 42);
    if (m_font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }

}

Game::~Game() {
    TTF_Quit();
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
    bool m_isRunning = true;


    while (m_isRunning)
    {
        frameStart = SDL_GetTicks();

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_SPACE:
                    if (m_startScreen) {
                        m_startScreen = false;
                        m_score_player = 0;
                        spawnControllerDiminish = 0;
                        lastTimeSpawned = SDL_GetTicks();
                    } else if (m_gameOverScreen) {
                        m_gameOverScreen = false;
                        m_score_player = 0;
                        spawnControllerDiminish = 0;
                        lastTimeSpawned = SDL_GetTicks();
                        vetorObstacles.clear();
                    }
                    m_player.startJump();
                    break;
                
                case SDLK_ESCAPE:
                    m_isRunning = false;
                    break;
                default:
                    break;
                }
                break;
            case SDL_QUIT: 
                m_isRunning = false;
                break;
            default:
                break;
            }
        }


        if (!m_gameOverScreen) {
            draw(m_renderer);

            if (m_player.isJumping) 
                m_player.jump();


            currentSpawnTime = SDL_GetTicks() - lastTimeSpawned;
            if (currentSpawnTime > spawnTimeInterval && m_startScreen == false) 
            {
                int tipoObstacle = randomIntGenerator(1, 3);
                Obstacles i (m_WIDTH_WINDOW, 700, tipoObstacle);
                vetorObstacles.push_back(i);
                lastTimeSpawned = SDL_GetTicks();
                currentSpawnTime = 0;
                spawnTimeInterval = spawnTimeGenerator();
            }

            std::cout << "Score: " << m_score_player << "\n";

            for (auto &obstacle : vetorObstacles)
            {
                obstacle.move();
            }

            verColisoes();

        } else {
            draw(m_renderer);
        }

        SDL_RenderPresent(m_renderer);
        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < targetFrameTime) {
            SDL_Delay(targetFrameTime - frameTime);
            if (!m_startScreen && !m_gameOverScreen)
                m_score_player += 2;
        }
        
        
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

    if (m_startScreen)
        startScreen();
    else if (m_gameOverScreen)
        gameOverScreen();


    m_player.draw(m_render);
    
    for (auto &obstacle : vetorObstacles)
    {
        obstacle.draw(m_render);
    }

    scoreDisplay.draw(m_render, m_score_player);

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


void Game::loadGround (SDL_Renderer* m_render) 
{
    SDL_SetRenderDrawColor(m_renderer, 250, 255, 255, 255);
    SDL_RenderFillRect (m_renderer, &m_ground);
}



void Game::verColisoes() 
{
    auto it = vetorObstacles.begin();

    while (it != vetorObstacles.end())
    {
        if (checkColisao(it->getRect(), m_player.getRect())) {
            m_gameOverScreen = true;
            return;
        }
        if (it->getRect().x == 0) {
            it = vetorObstacles.erase(it);
        } else {
            ++it;
        }
    }
}

Uint32 Game::spawnTimeGenerator() 
{
    Uint32 randomTime = rand() % 1900;
    Uint32 minSpawnTime = 1100;

    spawnControllerDiminish += 40;
    randomTime = (randomTime - spawnControllerDiminish) + minSpawnTime;

    return randomTime; 
}

int Game::randomIntGenerator (int min, int max) 
{
    return rand() % (max - min + 1) + min;
}

void Game::startScreen() 
{
    if (m_font == nullptr) {
        std::cerr << "Font not loaded properly, cannot render start screen text." << std::endl;
        return;
    }

    SDL_Color textColor = {0, 0, 0, 0};

    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, "Press SPACE to Start", textColor);
    if (textSurface == nullptr) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        TTF_CloseFont(m_font);
        return;
    }

    m_textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

    SDL_Rect textRect = {
        m_WIDTH_WINDOW / 2 - (textSurface->w / 2 * 3),
        m_HEIGHT_WINDOW / 2 - (textSurface->h / 2 * 3),
        textSurface->w * 3,
        textSurface->h * 3
    };

    SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &textRect);

    //todo Liberando recursos
    // SDL_DestroyTexture(textTexture);
    // SDL_FreeSurface(textSurface);
    // TTF_CloseFont(font);

}


void Game::gameOverScreen() 
{
    if (m_font == nullptr) {
        std::cerr << "Font not loaded properly, cannot render game over screen text." << std::endl;
        return;
    }

    SDL_Color textColor = {0, 0, 0, 255};

    const char* lines[] = {
        "Game Over!",
        "SPACE to Restart",
        "ESC to Quit"
    };


    // Calcula o número de linhas
    int numLines = sizeof(lines) / sizeof(lines[0]);
    int lineHeight = 0;

    // Loop pelo vetor do texto e renderiza elas
    for (int i = 0; i < numLines; ++i) {
        SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, lines[i], textColor);
        if (textSurface == nullptr) {
            std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
            continue;
        }

        if (m_textTexture != nullptr) {
            SDL_DestroyTexture(m_textTexture);
        }

        m_textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);

        SDL_Rect textRect = {
            m_WIDTH_WINDOW / 2 - textSurface->w / 2,
            m_HEIGHT_WINDOW / 2 - (numLines * textSurface->h / 2) + (i * textSurface->h),
            textSurface->w,
            textSurface->h
        };

        SDL_RenderCopy(m_renderer, m_textTexture, nullptr, &textRect);

        // Guarda a altura do texto
        lineHeight = textSurface->h;
        
        SDL_FreeSurface(textSurface);
    }
}