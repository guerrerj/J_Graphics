#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include <ctype.h>
#include <vector>
#include <algorithm>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

class Load
{
public:
    Load(){}
    GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
    bool LoadOBJ(std::string path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals);
    std::vector<float> Parser(std::string const& line, char const& div);
    bool is_near(float v1, float v2);

    struct PackedVertex{glm::vec3 PVposition;
                        glm::vec2 PVuv;
                        glm::vec3 PVnormal;
                        bool operator<(const PackedVertex that)const
                        {
                           return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)>0);
                        }
                        };

    bool getSimilarVertexIndex(PackedVertex& packed, std::map<PackedVertex,unsigned short>& VertexToOutIndex,
                               unsigned short& result);
    void indexVBO(std::vector<glm::vec3>& in_vertices,
                  std::vector<glm::vec2>& in_uvs,
                  std::vector<glm::vec3>& in_normals,
                  std::vector<unsigned short>& out_indices,
                  std::vector<glm::vec3>& out_vertices,
                  std::vector<glm::vec2>&out_uvs,
                  std::vector<glm::vec3>& out_normals);

    void indexVBO_TBN(std::vector<glm::vec3>& in_vertices,
                      std::vector<glm::vec2>& in_uvs,
                      std::vector<glm::vec3>& in_normals,
                      std::vector<glm::vec3>& in_tangents,
                      std::vector<glm::vec3>& in_bitangents,
                      std::vector<unsigned short>& out_indices,
                      std::vector<glm::vec3>& out_vertices,
                      std::vector<glm::vec2>& out_uvs,
                      std::vector<glm::vec3>& out_normals,
                      std::vector<glm::vec3>& out_tangents,
                      std::vector<glm::vec3>& out_bitangents);
    bool getSimilarVertexIndex(
                      glm::vec3 & in_vertex,
	                  glm::vec2 & in_uv,
	                  glm::vec3 & in_normal,
	                  std::vector<glm::vec3> & out_vertices,
	                  std::vector<glm::vec2> & out_uvs,
	                  std::vector<glm::vec3> & out_normals,
	                  unsigned short & result);

    ~Load(){}

private:
};

class Controls
{
public:
    Controls();
    void CUpdate(GLFWwindow* win, double lastTime);

    void CTransform(GLuint programID, float distance, float LightPower, float LightColor);

    virtual ~Controls(){}
protected:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;
    float horizontalAngle;
    float verticalAngle;
    float FoV;
    float speed; // three units per second
    float mouseSpeed;
};
