#include "Player.hpp"
#include "TextureManager.hpp"
#include <iostream>

Player::Player(int pos_chao) : m_playerTexture(nullptr), isJumping(false)
{
    
    float m_gravity = 0.2f;

    m_player_rect = {300, pos_chao, 100, 170};

    m_pos_chao = pos_chao;

    std::cout << "Puck Criado!\n";
    maxJumpHeight = m_pos_chao - m_player_rect.h;

}

void Player::draw (SDL_Renderer* m_renderer) 
{
    SDL_SetRenderDrawColor(m_renderer, 250, 32, 15, 255); // Vermelho
    SDL_RenderFillRect (m_renderer, &m_player_rect);

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

void Player::jump () 
{  
    std::cout << "Jump!\n";

    if (isJumping) {

        if (m_GoDown) {
            m_player_rect.y += 10;
        } else {
            m_player_rect.y -= 10;
        } 

        // 610 - 170 == 440
        if (m_player_rect.y <= maxJumpHeight) {
            m_GoDown = true;
        }

        if (m_player_rect.y >= m_pos_chao) {
            isJumping = false;
            m_GoDown = false;

        }

    }
}



SDL_Rect Player::getRect() const 
{
    return m_player_rect;
}

SDL_Texture* Player::getTexture(const char* filepath, SDL_Renderer* renderer) 
{
    SDL_Texture* playerTex = TextureManager::LoadTexture(filepath, renderer);

    return playerTex;
}