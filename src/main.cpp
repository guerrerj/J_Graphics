/*#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <algorithm>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>
class Display
{
public:

    Display(int width, int height, std::string const& title)
    {
        this->width = width; //uniform initialization did not work.
        this->height = height;
        this->title = title;

        SDL_Init(SDL_INIT_EVERYTHING);

        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


        m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
        m_glContext = SDL_GL_CreateContext(m_window);

        GLenum status = glewInit();

        if(status != GLEW_OK)
        {
            std::cerr << " Glew failed to initialize" << std::endl;
        }

        m_isClosed = false;
    }

    void Update()
    {
        SDL_GL_SwapWindow(m_window);
        SDL_Event e;

        while(SDL_PollEvent(&e))
        {
            if(e.type == 2)
            {
                m_isClosed = true;
            }
        }
    }

    bool IsClosed()
    {
        return m_isClosed;
    }

    void Clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

    }

    virtual ~Display() { SDL_GL_DeleteContext(m_glContext); SDL_DestroyWindow(m_window);SDL_Quit(); }
private:
    int width;
    int height;
    std::string title;

    SDL_Window* m_window;
    SDL_GLContext m_glContext;

    bool m_isClosed;

};


int main()
{
    std::cout << "Welcome mi amigo to the Jose Christmas Special!!" << std::endl;

    Display display(800, 600, "Christmas Special");

    while(!display.IsClosed())
    {
        display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
        display.Update();
    }
    return true;
}
*/
