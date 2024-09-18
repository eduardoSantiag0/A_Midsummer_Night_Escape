#include "Game.hpp"
#include <iostream>
#include "SDL2/SDL.h"
#include <time.h>
#include <algorithm>
#include <string>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#define SCREEN_FPS 30

Game::Game ()
    : 
    background_texture(nullptr),
    m_player(160),
    m_score_player(0),
    spawnTimeInterval(1300), 
    m_startScreen (true), m_gameOverScreen(false),
    m_textTexture(nullptr), m_font(nullptr), 
    scoreDisplay (1920, 20, 6),
    m_HighestScores(0), 
    themeSong(nullptr), 
    treeTexture(nullptr), 
    groundTexture(nullptr)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return;
    }


    m_window = SDL_CreateWindow("A Midsummer Night's Escape", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_WIDTH_WINDOW, m_HEIGHT_WINDOW, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (m_window == nullptr) {
        std::cout << "Nao foi  possivel abrir a janela\n";
        return;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer == nullptr) {
        std::cout << "Nao foi  possivel abrir o render \n";
        return;
    }

    m_WIDTH_WINDOW = SDL_GetWindowSurface(m_window)->w;
    m_HEIGHT_WINDOW = SDL_GetWindowSurface(m_window)->h;

    //* ÍCONE
    SDL_Surface* icon = SDL_LoadBMP("./src/images/references/A-Midsummer-Night_s-Escape_Colored.bmp");
    if (icon == nullptr) {
        std::cout << "Nao foi possivel abrir o icone\n";
        return;
    }
    SDL_SetWindowIcon(m_window, icon);
    SDL_FreeSurface(icon);

    //* MÚSICA
    //todo Descomentar
    // if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    //     std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
    //     return;
    // }
 
    // themeSong = Mix_LoadMUS("src/music/Midsummer's Night Escape Master 16-06-24.wav");
    // if (!themeSong) {
    //     std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
    // }

    // //todo ERROR
    // if (!Mix_PlayMusic(themeSong, -1)) {
    //     std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
    // }


    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    groundY = (m_HEIGHT_WINDOW * 2) / 3;
    m_groundHeight = m_HEIGHT_WINDOW - groundY; 

    m_background = {0, 0, m_WIDTH_WINDOW, m_HEIGHT_WINDOW};
    treeBackground = {0, 0, m_WIDTH_WINDOW, groundY};
    
    //todo Arrumar Chão
    m_ground = {0, m_groundHeight - 150, m_WIDTH_WINDOW, m_HEIGHT_WINDOW};

    m_player = Player(groundY);
    scoreDisplay  = Score(m_WIDTH_WINDOW, 20, 6);


    std::vector<Obstacles> vetorObstacles;

    srand(time(0));

    m_font = TTF_OpenFont("src/fonts/light-arial.ttf", 42);
    if (m_font == nullptr) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
    }
    textColor = {255, 255, 255, 255};

    loadHighestScore();

}


Game::~Game() 
{
    TTF_Quit();
    Mix_FreeMusic(themeSong);
    Mix_CloseAudio();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void Game::loadHighestScore() 
{
    m_FileHighestScore.open("highest_score.txt", std::ios::in);
    if (m_FileHighestScore.is_open()) {
        std::string file_Content;
        while (getline(m_FileHighestScore, file_Content)) {
            if (!file_Content.empty()) {
                try {
                    m_HighestScores = std::stoi(file_Content);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error parsing highest score: " << e.what() << std::endl;
                    m_HighestScores = 0;

                } catch (const std::out_of_range& e) {
                    std::cerr << "Error parsing highest score (out of range): " << e.what() << std::endl;
                    m_HighestScores = 0;

                }
            }
        }
        m_FileHighestScore.close(); 
    } else {
        m_FileHighestScore.open("highest_score.txt", std::ios::out);
        if (m_FileHighestScore.is_open()) {
            m_FileHighestScore << m_HighestScores;
        }
        m_FileHighestScore.close();
    }
}

void Game::loadDisplayHighestScore ()
{
    std::string highestScoreMessage = "TOP SCORE: " + std::to_string(m_HighestScores);
    // SDL_Color textColor = {255, 255, 255, 255};
    renderText(highestScoreMessage.c_str(), 150, 65, 1.15, textColor);
}

void Game::run() 
{
    const int targetFrameTime = 1000 / SCREEN_FPS;
    Uint32 frameStart;
    int frameTime;
    Uint32 currentSpawnTime;

    const int chaoPlayer =  (m_HEIGHT_WINDOW - m_groundHeight) - m_player.getRect().h;
    bool m_isRunning = true;

    bool spacePressed = false; 

    while (m_isRunning)
    {

        frameStart = SDL_GetTicks();

        loadHighestScore();
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
                        m_player.resetPosition();
                        m_startScreen = false;
                        m_score_player = 0;
                        spawnControllerDiminish = 0;
                        lastTimeSpawned = SDL_GetTicks();
                    } else if (m_gameOverScreen) {
                        m_player.resetPosition();
                        m_gameOverScreen = false;
                        m_score_player = 0;
                        spawnControllerDiminish = 0;
                        lastTimeSpawned = SDL_GetTicks();
                        vetorObstacles.clear();
                        if (m_score_player > m_HighestScores) 
                            updateHighestScore();
                    } else if (!spacePressed) {
                        spacePressed = true;
                        m_player.startJump();
                    } 
                    if (!m_player.getEscaping()) {
                        m_player.startEscaping();
                    } 

                    break;
                
                case SDLK_ESCAPE:
                    m_isRunning = false;
                    break;
                default:
                    break;
                }
                break;
            case SDL_KEYUP: 
                if (e.key.keysym.sym == SDLK_SPACE) {
                    spacePressed = false; 
                    m_player.endJump();
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
                m_player.jump(spacePressed); 


            currentSpawnTime = SDL_GetTicks() - lastTimeSpawned;
            if (currentSpawnTime > spawnTimeInterval && m_startScreen == false) 
            {
                int tipoObstacle = randomIntGenerator(1, 3);
                // Obstacles i (m_WIDTH_WINDOW, 700, tipoObstacle);
                Obstacles i (m_WIDTH_WINDOW, groundY, tipoObstacle);
                vetorObstacles.push_back(i);
                lastTimeSpawned = SDL_GetTicks();
                currentSpawnTime = 0;
                spawnTimeInterval = spawnTimeGenerator();
            }


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

    SDL_RenderClear(m_render);
    
    // SDL_SetRenderDrawColor(m_renderer, 44, 220, 250, 255); 
    // SDL_RenderFillRect (m_renderer, &m_background);

    loadBackground(background_texture, "src/images/sprites/ceulua.png", m_render, m_background);
    loadBackground(treeTexture, "src/images/sprites/arvore2.png", m_render, treeBackground);
    loadBackground(groundTexture, "src/images/sprites/chao2.png", m_render, m_ground);
    // loadGround(m_render);

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
    loadDisplayHighestScore();

    SDL_RenderPresent(m_render);

}


void Game::loadBackground(SDL_Texture*& texture, const char* filepath, SDL_Renderer* renderer, SDL_Rect srcRect) 
{
    if (!texture) {
        texture = TextureManager::LoadTexture(filepath, renderer);
        if (!texture) {
            std::cerr << "Failed to load background texture" << SDL_GetError() << std::endl;
            return;
        }
    }
    // SDL_RenderCopy(renderer, texture, nullptr, &srcRect);
    if (SDL_RenderCopy(renderer, texture, nullptr, &srcRect) < 0) {
        std::cerr << "Failed to render background texture: " << SDL_GetError() << std::endl;
    }
}


void Game::loadGround (SDL_Renderer* m_render) 
{
    // SDL_SetRenderDrawColor(m_renderer, 17, 24, 64, 0);
    // SDL_SetRenderDrawColor(m_renderer, 40, 64, 34, 0);
    SDL_SetRenderDrawColor(m_renderer, 14, 20, 38, 0);
    SDL_RenderFillRect (m_renderer, &m_ground);
}

void Game::verColisoes() 
{
    auto it = vetorObstacles.begin();

    while (it != vetorObstacles.end())
    {
        if (checkColisao(it->getRect(), m_player.getRect())) {
            m_gameOverScreen = true;
            m_player.isDead();
            return;
        }
        if (it->getRect().x == 0) {
            it = vetorObstacles.erase(it);
        } else {
            ++it;
        }
    }
}

bool Game::checkColisao(SDL_Rect a, SDL_Rect b) 
{
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
    if( bottomA <= topB || topA >= bottomB || rightA <= leftB ||  leftA >= rightB ) {
        return false;
    }


    //* Tem colisao
    // Nenhum dos lados de A estão fora de B;
    return true;
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

    const char* startMessage = "Press SPACE to Start";

    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, startMessage, textColor);
    if (!textSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
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

    SDL_DestroyTexture(m_textTexture); 
    SDL_FreeSurface(textSurface);    
}


void Game::gameOverScreen() 
{
    if (m_font == nullptr) {
        std::cerr << "Font not loaded properly, cannot render game over screen text." << std::endl;
        return;
    }

    const char* lines[] = {
        "Game Over!",
        "SPACE to Restart",
        "ESC to Quit"
    };

    if (m_score_player > m_HighestScores) {
        updateHighestScore();
    }


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

        SDL_FreeSurface(textSurface);
    }
}

void Game::updateHighestScore()
{
    m_FileHighestScore.open("highest_score.txt", std::ios::out);
    if (m_FileHighestScore.is_open()) {
        m_FileHighestScore << m_score_player;
        m_FileHighestScore.close();
    } else {
        std::cerr << "Falha ao abrir highest_score.txt" << std::endl;            
    }
}

void Game::renderText(const char* message, int x, int y, float scale, SDL_Color color) 
{
    if (!m_font) {
        std::cerr << "Font not loaded properly, cannot render text." << std::endl;
        return;
    }

    SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, message, color);
    if (!textSurface) {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Failed to create text texture: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect textRect = {
        x - static_cast<int>(textSurface->w * scale / 2), 
        y - static_cast<int>(textSurface->h * scale / 2), 
        static_cast<int>(textSurface->w * scale),
        static_cast<int>(textSurface->h * scale)
    };

    SDL_RenderCopy(m_renderer, textTexture, nullptr, &textRect);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}
