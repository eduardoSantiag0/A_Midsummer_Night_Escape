#include <iostream>
#include "Obstacles.hpp"
#include <cmath>
#include "TextureManager.hpp"


Obstacles::Obstacles(int posX, int posY, int tipo) : m_speed(25), m_obstacleTexture(nullptr), m_active(true), m_spawn_pos (posY), m_Tipo(tipo), m_time (0),
currentFrame(0), maxFrames(2), animationSpeed(300), lastFrameTime(0)
{
    // x, y, w, h
    
    switch (tipo)
    {
    case (1): // Fireball
        // m_obstacle = {posX, posY + 40, 40, 40};
        frameHeight = 40;
        frameWidth = 40;
        m_obstacle = {posX, posY - 40, frameWidth, frameHeight};
        spritePath = "src/images/sprites/fireballsheet.png";
        break;
    
    case (2): // Roseira
        // m_obstacle = {posX, posY + 20 + 60, 180, 60};
        frameHeight = 60;
        frameWidth = 210;
        // m_obstacle = {posX, posY - 60, frameHeight, frameWidth};
        m_obstacle = {posX, posY - 60, frameWidth, frameHeight};
        spritePath = "src/images/sprites/roseirasheet.png";
        break;
    case (3): // Cogumelo
        // m_obstacle = {posX, posY - 20, 100, 100};
        frameHeight = 100;
        frameWidth = 100;
        spritePath = "src/images/sprites/cogumelosheet.png";
        m_obstacle = {posX, posY - 100, frameWidth, frameHeight};
        break;
    default:
        break;
    }

    srcRect = {0, 0, frameWidth, frameHeight};

} 

void Obstacles::move() 
{
    if (m_Tipo == 1) {
        senoidalMovement();
    } else {
        m_obstacle.x -= m_speed;
    }

    if (m_obstacle.x + m_obstacle.w <= 0) 
        m_active = false;


} 

void Obstacles::draw (SDL_Renderer* m_renderer) 
{
    if (!m_obstacleTexture) { 
        m_obstacleTexture = TextureManager::LoadTexture(spritePath.c_str(), m_renderer);
        if (!m_obstacleTexture) {
            std::cerr << "Failed to load spaceship texture." << SDL_GetError() << std::endl;
            return;
        }
    }

    updateFrame();

    SDL_RenderCopy(m_renderer, m_obstacleTexture, &srcRect, &m_obstacle);
}

void Obstacles::updateFrame() 
{

    Uint32 currentTime = SDL_GetTicks();

    if (currentTime > lastFrameTime + animationSpeed) {
        currentFrame = (currentFrame + 1) % maxFrames;

        srcRect.x = currentFrame * frameWidth;

        lastFrameTime = currentTime;
    }
}



SDL_Rect Obstacles::getRect () const 
{
    return m_obstacle;
}

SDL_Texture* Obstacles::getTexture(const char* filepath, SDL_Renderer* renderer) {
    SDL_Texture* m_obstacleTexture = TextureManager::LoadTexture(filepath, renderer);

    return m_obstacleTexture;
}



void Obstacles::senoidalMovement()
{
    m_obstacle.x -= m_speed;
    
    m_time += 0.1;
    
    m_obstacle.y = (m_spawn_pos - 100) + 30 * std::sin(m_time);

}