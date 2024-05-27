#include "TextureManager.hpp"
#include "SDL2/SDL.h"
#include <vector>

//todo Passar a posição pelo construtor, o numero de retângulos; 
//// Lista de Retangulos
//// Carregar textura
//todo Atualizar Score passando um inteiro

class Score 
{
public: 
    Score(int pos_x, int pos_y, int num_rects);
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