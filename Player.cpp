#include "Player.hpp"
#include "TextureManager.hpp"
#include <iostream>

// jumpVelocity: Controla a velocidade do salto.
// gravity: Aceleração constante aplicada para simular a gravidade.
// maxJumpHeight: Define a altura máxima que o jogador pode alcançar (não usada diretamente no cálculo neste exemplo, mas pode ser útil para ajustes futuros).

Player::Player(int pos_chao) : m_playerTexture(nullptr), isJumping(false), m_GoDown(false), jumpVelocity(0.0f), gravityUp(1.1f), gravityDown(1.0f), m_limiar_pulo (30)
{    

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

    if (isJumping)
    {
        if (m_GoDown) {
            //* Posição Y vai aumentando, ou seja, indo para baixo
            jumpVelocity += gravityDown;
        }
        else {
            //* Velocidade diminuindo conforme vai subindo, tendendo a zero 
            jumpVelocity -= gravityUp;
            
            //* Ao chegar em zero, ele começa a descer
            if (jumpVelocity <= 0) {
                m_GoDown = true;
            }
        }

        //* Transforma o jumpVelocity em posição
        m_player_rect.y += static_cast<int>(jumpVelocity);

        //* Não passa do chão
        if (m_player_rect.y >= m_pos_chao)
        {
            m_player_rect.y = m_pos_chao;
            isJumping = false;
            m_GoDown = false;
            jumpVelocity = 0.0f;
        }
    }
}

void Player::startJump()
{
// m_pos_chao - m_limiar_pulo == m_player_rect.y
    if (!isJumping || m_player_rect.y >= m_pos_chao - m_limiar_pulo)
    {
        isJumping = true;
        m_GoDown = false;
        jumpVelocity = -15.0f; //* Controla a altura do pulo
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