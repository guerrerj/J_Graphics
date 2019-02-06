#ifndef GAME_H
#define GAME_H
#include "Utils.h"


class Game
{
    public:
        Game();
        Game(int width,int height,int buffw,int buffh);
        void framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH);
        GLFWwindow* PSetup(std::string const& title);
        void Game::PDraw(std::vector<glm::vec3> const& indexed_vertices, std::vector<glm::vec2> const& indexed_uvs, std::vector<glm::vec3> const& indexed_normals, std::vector<glm::vec3> const& normals,std::vector<unsigned int>const& indices);
        void PBMP_Loader(const char* imagepath);

        virtual ~Game();

    protected:
        int W_WIDTH;
        int W_HEIGHT;
        int framebufferHeight;
        int framebufferWidth;
        int m_width;
        int m_height;
        unsigned char* data;
        GLFWwindow* window;

    private:
};

#endif // GAME_H
