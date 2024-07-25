#include "Score.hpp"
// #include "TextureManager.hpp"
#include <string>
#include <iostream>


Score::Score(int pos_x, int pos_y, int num_rects)
    : m_textureScore(nullptr), m_pos_x(pos_x), m_pos_y(pos_y), m_num_rects(num_rects) {

    int digitWidth = 30; 
    int digitHeight = 30; 
    int gap = 10; 

    for (int i = 0; i < num_rects; ++i) {
        SDL_Rect rect = { pos_x + i * (digitWidth + gap), pos_y, digitWidth, digitHeight };
        vetorScores.push_back(rect);
    }
}


Score::~Score() {
    if (m_textureScore) {
        SDL_DestroyTexture(m_textureScore);
    }
}

SDL_Texture* Score::getTexture(const char* filepath, SDL_Renderer* renderer) {
    SDL_Texture* scoreTex = TextureManager::LoadTexture(filepath, renderer);
    if (!scoreTex) {
        std::cerr << "Failed to load score texture: " << SDL_GetError() << std::endl;
    }
    return scoreTex;
}


void Score::extractDigitos(SDL_Renderer* renderer, int digit, SDL_Rect& vetorScore) {

    SDL_Rect src_rect;

    int col;
    const int linha = 8 * 3;

    switch (digit) {
        case 0:
            col = 0;
            break;
        case 1:
            col = 8;
            break;
        case 2:
            col = 16;
            break;
        case 3:
            col = 24;
            break;
        case 4:
            col = 32;
            break;
        case 5:
            col = 40;
            break;
        case 6:
            col = 48;
            break;
        case 7:
            col = 56;
            break;
        case 8:
            col = 64;
            break;
        case 9:
            col = 72;
            break;
        default:
            col = 0; 
            break;
    }


    src_rect.x = col;
    src_rect.y = linha;
    src_rect.w = 8;
    src_rect.h = 8;

    SDL_RenderCopy(renderer, m_textureScore, &src_rect, &vetorScore);
}


void Score::draw(SDL_Renderer* renderer, int player_score) {
    if (!m_textureScore) {
        m_textureScore = getTexture("src/fonts/score_font.png", renderer);
    }


    std::string score_str = std::to_string(player_score);
    int len = score_str.length(); 

    int digitWidth = 30; 
    int gap = 10; 
    int totalWidth = len * digitWidth + (len - 1) * gap; 
    int startX = (1920 - totalWidth) / 2; 

    for (int i = 0; i < len; ++i) {
        int digit = score_str[i] - '0'; 
        SDL_Rect dst_rect = { startX + i * (digitWidth + gap), 50, digitWidth, digitWidth }; 
        extractDigitos(renderer, digit, dst_rect);
    }
}