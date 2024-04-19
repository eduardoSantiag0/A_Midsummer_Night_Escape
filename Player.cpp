#include "Player.hpp"
#include "TextureManager.hpp"
#include <iostream>

//// float myGravity = 0.2f;
//// float maxFallSpeed = -5.0f;
//// float myJumpForce = 5.0f;
//// float curJumpForce = 0.0f;
//// float deltaTime; (Time Between frames)

//// bool m_jumping = false;

//// if(press key){
////    m_jumping = true;
////    curJumpForce = myJumpForce;
//// }

// if(m_jumping){
//    player.y += curJumpForce * deltaTime;
   
//    if(curJumpForce > maxFallSpeed){
//       myJumpForce -= myGravity * deltaTime;
//    }else{
//       curJumpForce = maxFallSpeed;
//    }

////    if(Hit Ground){
////       m_jumping = false;
////    }
// }

Player::Player(int pos_chao) : m_playerTexture(nullptr), isJumping(false)
{
    float myGravity = 0.2f;
    float maxFallSpeed = -5.0f;
    float myJumpForce = 5.0f;
    float curJumpForce = 0.0f;
    float deltaTime; 
    m_player_rect = {300, pos_chao, 100, 170};
    std::cout << "Puck Criado!\n";
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

void Player::jump (float deltaTime) 
{  
    m_player_rect.y += curJumpForce * deltaTime;
   
    if(curJumpForce > maxFallSpeed){
       myJumpForce -= myGravity * deltaTime;
    }else{
       curJumpForce = maxFallSpeed;
    }

}

void Player::setHeight() 
{}



float Player::getCurJumpForce () const
{
    return curJumpForce;
}
void Player::setmyJumpForce (float curJumpForce) 
{
    myJumpForce = curJumpForce;
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