#include "SDL2/SDL.h"

class Player 
{
public:
    Player(int pos_chao);
    void jump(float deltaTime);
    void draw(SDL_Renderer* m_renderer);
    SDL_Rect m_player_rect;
    bool isJumping;
    
    void setmyJumpForce (float curJumpForce);

    SDL_Rect getRect() const;
    SDL_Texture* getTexture (const char* filepath, SDL_Renderer* renderer);
    float getCurJumpForce() const;

    void setHeight(); 

private:
    float myGravity;
    float maxFallSpeed;
    float myJumpForce;
    float curJumpForce;
    float deltaTime; // (Time Between frames)

    SDL_Texture* m_playerTexture;
};