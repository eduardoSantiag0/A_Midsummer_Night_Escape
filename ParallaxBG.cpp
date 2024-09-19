#include "ParallaxBG.hpp"
#include "TextureManager.hpp"
#include <string>

ParallaxBG::ParallaxBG(int width, int height, int groundY, SDL_Renderer* renderer, int speed) 
    : m_WIDTH_WINDOW(width), m_HEIGHT_WINDOW(height), scrollSpeed(speed), m_renderer(renderer), groundY(groundY)
{
    std::string pathTree0 = "src/images/sprites/arvore0_edited.png";
    std::string pathTree1 = "src/images/sprites/arvore1_edited.png";
    std::string pathTree2 = "src/images/sprites/arvore2_edited.png";

    m_treeTextures.push_back(TextureManager::LoadTexture(pathTree0.c_str(), m_renderer));
    m_treeTextures.push_back(TextureManager::LoadTexture(pathTree1.c_str(), m_renderer));
    m_treeTextures.push_back(TextureManager::LoadTexture(pathTree2.c_str(), m_renderer));

    for (int i = 0; i < 3; i++) {
        SDL_Rect treeLayer1 = {0, 0, m_WIDTH_WINDOW, groundY + 50};
        SDL_Rect treeLayer2 = {m_WIDTH_WINDOW, 0, m_WIDTH_WINDOW, groundY + 50}; 
        treeBackgrounds.push_back(treeLayer1);
        treeBackgrounds.push_back(treeLayer2); 
    }
}

void ParallaxBG::move()
{
    for (size_t i = 0; i < treeBackgrounds.size(); i++) {
        treeBackgrounds[i].x -= scrollSpeed; // Move esquerda

        // Background saiu de tela
        if (treeBackgrounds[i].x + treeBackgrounds[i].w < 0) {
            // Vai para o final do outro sprite
            treeBackgrounds[i].x = m_WIDTH_WINDOW;
        }
    }
}

void ParallaxBG::draw()
{
    for (size_t i = 0; i < m_treeTextures.size(); i++) {
        SDL_RenderCopy(m_renderer, m_treeTextures[i], NULL, &treeBackgrounds[i * 2]);     
        SDL_RenderCopy(m_renderer, m_treeTextures[i], NULL, &treeBackgrounds[i * 2 + 1]); 
    }
}
