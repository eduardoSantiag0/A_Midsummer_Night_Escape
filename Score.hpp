#include "TextureManager.hpp"
#include "SDL2/SDL.h"
#include <vector>

class Score 
{
public: 
    Score(int pos_x, int pos_y, int num_rects);
    // Score(int pos_x, int pos_y, int num_rects, int screenWidth, int screenHeight);
    ~Score();

    void draw(SDL_Renderer* renderer, int player_score);

private: 
    SDL_Texture* getTexture (const char* filepath, SDL_Renderer* renderer);
    void extractDigitos (SDL_Renderer* renderer, int digit, SDL_Rect& vetorScores);

    SDL_Texture* m_textureScore; 
    int m_pos_x;
    int m_pos_y;
    int m_num_rects;
    std::vector<SDL_Rect> vetorScores;

};