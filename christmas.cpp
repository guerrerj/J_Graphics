
#include "./include/game.h"


int main()
{
   Game Pyrus(800, 600, 0, 0);

   std::cout << "Christmas Game Verison Toi" << std::endl;

   GLFWwindow* window = Pyrus.PSetup("Christmas Special");


   Load Pload;
   Pyrus.PBMP_Loader("back.bmp");
   GLuint programID = Pload.LoadShaders("vertex.glsl", "fragment.glsl" );
   std::vector<glm::vec3> vertices;
   std::vector<glm::vec2> uvs;
   std::vector<glm::vec3> normals;
   std::vector<unsigned int> indices;
   std::vector<glm::vec3> indexed_vertices;
   std::vector<glm::vec2> indexed_uvs;
   std::vector<glm::vec3> indexed_normals;


   bool Res = Pload.LoadOBJ("cube.obj", vertices, uvs, normals);
   Pload.indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
   Controls Con;
   double lastTime;


   while(!glfwWindowShouldClose(window))
    {
        //update input
    glClearColor(0.2f, 0.15f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    lastTime = glfwGetTime();

    glfwPollEvents();

      //draw

    Con.CTransform(programID, 2.0f, 3.0f, 2.0f);
    glUseProgram(programID);
    Pyrus.PDraw( normals, indices);

    Con.CUpdate(window, lastTime);

    //end draw
    glfwSwapBuffers(window);
    glFlush();


    }
    return true;
}


