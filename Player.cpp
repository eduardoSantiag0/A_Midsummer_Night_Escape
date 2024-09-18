#include "Player.hpp"
#include "TextureManager.hpp"
#include <iostream>

// jumpVelocity: Controla a velocidade do salto.
// gravity: Aceleração constante aplicada para simular a gravidade.
// maxJumpHeight: Define a altura máxima que o jogador pode alcançar (não usada diretamente no cálculo neste exemplo, mas pode ser útil para ajustes futuros).


Player::Player(int pos_chao) : m_playerTexture(nullptr), isJumping(false), m_GoDown(false), jumpVelocity(0.0f), gravityUp(1.1f), gravityDown(1.5f), isAlive(true)
{

    int relative_ground = pos_chao - 160;

    m_player_rect = {300, pos_chao, 100, 160};

    m_pos_chao = relative_ground;

    std::cout << "Puck Criado!\n";
    maxJumpHeight = m_pos_chao - (m_player_rect.h - 100);

    std::cout << "Max Jump Height: " << maxJumpHeight << std::endl;
}

void Player::draw(SDL_Renderer* m_renderer) 
{
    //* Animation
    //* Base
    //* Jump
    //* Death

    if (m_playerTexture) {
        SDL_DestroyTexture(m_playerTexture); 
    }

    std::string spritePath = "";
    
    if (!isAlive) {
        spritePath = "src/images/sprites/puckdeath.png";
    } else if (isJumping) {
        spritePath = "src/images/sprites/puckjump.png";
    } else {
        spritePath = "src/images/sprites/puckbase.png";
    }

    m_playerTexture = getTexture(spritePath.c_str(), m_renderer);
    if (!m_playerTexture) {
        std::cerr << "Failed to load player texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_RenderCopy(m_renderer, m_playerTexture, nullptr, &m_player_rect);
}

void Player::jump (bool spacePressed) 
{ 
    if (m_GoDown) {
        //* Posição Y vai aumentando, ou seja, indo para baixo
        jumpVelocity += gravityDown;
    } else {
        //* Velocidade diminuindo conforme vai subindo, tendendo a zero 
        jumpVelocity -= gravityUp;
        
        //* Ao chegar em zero, ele começa a descer
        if (m_player_rect.y <= maxJumpHeight || !spacePressed) {
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

void Player::startJump()
{
    if (!isJumping)
    {
        isJumping = true;
        m_GoDown = false;
        jumpVelocity = -15.0f; //* Controla a altura do pulo
    }
}

void Player::endJump()
{
    m_GoDown = true;
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

void Player::resetPosition() 
{
    m_player_rect.x = 300;
    m_player_rect.y = m_pos_chao;
    isAlive = true;
}

void Player::isDead() 
{
    isAlive = false;
}