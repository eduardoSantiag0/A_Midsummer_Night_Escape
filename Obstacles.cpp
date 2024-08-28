#include <iostream>
#include "Obstacles.hpp"
#include <cmath>

Obstacles::Obstacles(int posX, int posY, int tipo) : m_speed(25), m_obstacleTexture(nullptr), m_active(true), m_spawn_pos (posY), m_Tipo(tipo), m_time (0)
{
    // x, y, w, h
    
    switch (tipo)
    {
    case (1): // Generico / Bloco Pequeno
        m_obstacle = {posX, posY, 40, 40};
        break;
    
    case (2): // Cobra 
        m_obstacle = {posX, posY + 20, 210, 60};
        break;
    case (3): // Bloco Grande
        m_obstacle = {posX, posY - 20, 100, 80 + 20};
        break;

    default:
        break;
    }

    // std::cout << "\nObstaculo Criado!\n";
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
    SDL_SetRenderDrawColor(m_renderer, 240, 15, 94, 255); // Verde
    SDL_RenderFillRect (m_renderer, &m_obstacle);

    //! Quando tiver sprites
    // if (!m_playerTexture) { 
    //     m_playerTexture = getTexture("src/images/sprites/spaceship/spaceship_teste_2.png", m_renderer);
    //     if (!m_playerTexture) {
    //         std::cerr << "Failed to load spaceship texture." << SDL_GetError() << std::endl;
    //         return;
    //     }
    // }
    // SDL_RenderCopy(m_renderer, m_playerTexture, NULL, &m_player_rect);
}


SDL_Rect Obstacles::getRect () const 
{
    return m_obstacle;
}

// SDL_Texture* Obstacles::getTexture(const char* filepath, SDL_Renderer* renderer) {
//     SDL_Texture* m_obstacleTexture = TextureManager::LoadTexture(filepath, renderer);

//     return m_obstacleTexture;
// }



void Obstacles::senoidalMovement()
{
    m_obstacle.x -= m_speed;
    
    m_time += 0.1;
    
    // Calculate the new vertical position using sine wave
    m_obstacle.y = m_spawn_pos + 30 * std::sin(m_time);

}