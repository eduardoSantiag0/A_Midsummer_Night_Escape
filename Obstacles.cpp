#include <iostream>
#include "Obstacles.hpp"


Obstacles::Obstacles(int posX, int posY) : m_speed (10), m_obstacleTexture(nullptr), m_acive (true)
{
    // x, y, w, h
    std::cout << "\n";
    m_obstacle = {posX, posY, 40, 40};
    std::cout << "Obstaculo Criado!\n";

} 

void Obstacles::move() 
{
    m_obstacle.x -= m_speed;
    // std::cout << "Obstaculo Posicao X: " << m_obstacle.x << "\n";
    if (m_obstacle.x <= 0) 
        m_acive = false;

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