#include "ParallaxBG.hpp"
#include "TextureManager.hpp"
#include <string>

ParallaxBG::ParallaxBG(int width, int height, int groundY, SDL_Renderer* renderer) 
    : m_WIDTH_WINDOW(width), m_HEIGHT_WINDOW(height), scrollSpeed(10), m_renderer(renderer), groundY(groundY)
{
    std::string pathTree0 = "src/images/sprites/arvore0.png";
    std::string pathTree1 = "src/images/sprites/arvore1.png";
    std::string pathTree2 = "src/images/sprites/arvore2.png";

    // Load textures
    m_treeTextures.push_back(TextureManager::LoadTexture(pathTree0.c_str(), m_renderer));
    m_treeTextures.push_back(TextureManager::LoadTexture(pathTree1.c_str(), m_renderer));
    m_treeTextures.push_back(TextureManager::LoadTexture(pathTree2.c_str(), m_renderer));

    // Initialize rectangles for each layer
    for (int i = 0; i < 3; i++) {
        SDL_Rect treeLayer1 = {0, 0, m_WIDTH_WINDOW, groundY}; // First rect
        SDL_Rect treeLayer2 = {m_WIDTH_WINDOW, 0, m_WIDTH_WINDOW, groundY}; // Second rect, starting after the first
        treeBackgrounds.push_back(treeLayer1);
        treeBackgrounds.push_back(treeLayer2); 
    }
}

void ParallaxBG::move()
{
    for (size_t i = 0; i < treeBackgrounds.size(); i++) {
        treeBackgrounds[i].x -= scrollSpeed; // Move background leftward

        // Check if the background is completely off-screen
        if (treeBackgrounds[i].x + treeBackgrounds[i].w < 0) {
            // If it is, move it to the end of the other backgrounds
            treeBackgrounds[i].x = m_WIDTH_WINDOW;
        }
    }
}

void ParallaxBG::draw()
{
    // Draw each tree layer
    for (size_t i = 0; i < m_treeTextures.size(); i++) {
        SDL_RenderCopy(m_renderer, m_treeTextures[i], NULL, &treeBackgrounds[i * 2]);     // First rectangle
        SDL_RenderCopy(m_renderer, m_treeTextures[i], NULL, &treeBackgrounds[i * 2 + 1]); // Second rectangle
    }
}
