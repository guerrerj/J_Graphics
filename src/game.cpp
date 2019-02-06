#include "../include/game.h"


Game::Game(int width,int height,int buffw,int buffh):
        W_WIDTH{width}, W_HEIGHT{height}, framebufferHeight{buffh}, framebufferWidth{buffw}
    {
        glfwInit();
        //create a window

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    }


void Game::framebuffer_resize_callback(GLFWwindow* window, int fbW, int fbH)
    {
        glViewport(0, 0, fbW, fbH);
    }


GLFWwindow* Game::PSetup(std::string const& title)
    {
         window = glfwCreateWindow(W_WIDTH, W_HEIGHT, title.c_str(), NULL, NULL);
        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE; // INIt glew(needs window and opengl context);
        //error
        if(glewInit()!= GLEW_OK)
        {
            std::cout << "Error: Main.cpp :: glew init failed " << std::endl;
            glfwTerminate();
        }
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);


        return window;
    }

void Game::PDraw(std::vector<glm::vec3> const& indexed_vertices, std::vector<glm::vec2> indexed_uvs, std::vector<glm::vec3> indexed_normals, std::vector<glm::vec3> const& normals,std::vector<unsigned int>const& indices)
    {
        GLuint vertexbuffer;
        glGenBuffers(1, &vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() *sizeof(glm::vec3), &indexed_uvs[0], GL_STATIC_DRAW);

        GLuint uvbuffer;
        glGenBuffers(1, &uvbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

        GLuint normalbuffer;
        glGenBuffers(1, &normalbuffer);
        glBindBuffer(GL_ARRAY_BUFFER,normalbuffer);
        glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

        GLuint elementbuffer;
        glGenBuffers(1,&elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()* sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        //Vertex Color


        static const GLfloat g_uv_buffer_data[] = {
        0.000059f, 0.000004f,
        0.000103f, 0.336048f,
        0.335973f, 0.335903f,
        1.000023f, 0.000013f,
        0.667979f, 0.335851f,
        0.999958f, 0.336064f,
        0.667979f, 0.335851f,
        0.336024f, 0.671877f,
        0.667969f, 0.671889f,
        1.000023f, 0.000013f,
        0.668104f, 0.000013f,
        0.667979f, 0.335851f,
        0.000059f, 0.000004f,
        0.335973f, 0.335903f,
        0.336098f, 0.000071f,
        0.667979f, 0.335851f,
        0.335973f, 0.335903f,
        0.336024f, 0.671877f,
        1.000004f, 0.671847f,
        0.999958f, 0.336064f,
        0.667979f, 0.335851f,
        0.668104f, 0.000013f,
        0.335973f, 0.335903f,
        0.667979f, 0.335851f,
        0.335973f, 0.335903f,
        0.668104f, 0.000013f,
        0.336098f, 0.000071f,
        0.000103f, 0.336048f,
        0.000004f, 0.671870f,
        0.336024f, 0.671877f,
        0.000103f, 0.336048f,
        0.336024f, 0.671877f,
        0.335973f, 0.335903f,
        0.667969f, 0.671889f,
        1.000004f, 0.671847f,
        0.667979f, 0.335851f
    };


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        // Generate mipmaps, by the way.
        glGenerateMipmap(GL_TEXTURE_2D);


        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
        0, //attribute 0
        3, //size
        GL_FLOAT, //type
        GL_FALSE, //normalized
        0, //stride
        (void*)0 //array buffer offset
        );



        /*GLuint colorbuffer;
        glGenBuffers(1,&colorbuffer);
        glBindBuffer(GL_ARRAY_BUFFER,colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data,GL_STATIC_DRAW);*/

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);



        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);

        //Enable depth test
        glEnable(GL_DEPTH_TEST);
        //Accept fragment if it is closer to the camera than the former one
        glDepthFunc(GL_LESS);
        //Cull triangles which normal is not towards the camera
        glEnable(GL_CULL_FACE);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
        glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_SHORT, (void*)0);
        glDisableVertexAttribArray(0);
    }

 void Game::PBMP_Loader(const char* imagepath)
    {
        unsigned char header[54]; //each bmp file begins with a header
        unsigned int dataPos;

        unsigned int imageSize;
         // actual RGB data

        FILE * file = fopen(imagepath,"rb");
        if(!file){std::cout << "Image could not be opened"<< std::endl;}
        if(fread(header,1,54,file)!=54)
        {
            std::cout << "Not correct bmp file" << std::endl;

        }
        if(header[0]!='B'|| header[1]!='M')
        {
            std::cout << "Not a correct BMP file" << std::endl;
        }
        dataPos = *(int*)&(header[0x0A]);
        imageSize = *(int*)&(header[0x22]);
        m_width = *(int*)&(header[0x12]);
        m_height = *(int*)&(header[0x16]);

        //make up data if it is missing
        if (imageSize ==0) imageSize = m_width*m_height*3;//one byte for rgb
        if(dataPos == 0) dataPos = 54;
        data = new unsigned char [imageSize];
        fread(data,1,imageSize, file);
        fclose(file);


        GLuint textureID;
        glGenTextures(1, &textureID);
        //Bind the newly created texture
        glBindTexture(GL_TEXTURE_2D, textureID);

        //give the image to Opengl
        glTexImage2D(GL_TEXTURE_2D,0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE,data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glGenerateMipmap(GL_TEXTURE_2D);
        std::cout << "Loaded the Image" << std::endl;

    }


Game::~Game()
{
     glfwTerminate();
}

