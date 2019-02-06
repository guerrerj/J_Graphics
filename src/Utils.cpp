#include "../include/Utils.h"
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

GLuint Load::LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
    {
        //Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        //Read the vertex shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
        if(VertexShaderStream.is_open())
        {
            std::stringstream sstr;
            sstr << VertexShaderStream.rdbuf();
            VertexShaderCode= sstr.str();
            VertexShaderStream.close();
        }else
        {
            std::cout << "Unable to open the Vertex Shader" << std::endl;
        }
        //Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
        if(FragmentShaderStream.is_open())
        {
            std::stringstream sstr;
            sstr << FragmentShaderStream.rdbuf();
            FragmentShaderCode = sstr.str();
            FragmentShaderStream.close();
        }
        GLint Result = GL_FALSE;
        int InfoLogLength;

        //compile the Vertex Shader
        std::cout << "Compiling the Shader " << vertex_file_path << std::endl;
        char const* VertexSourcePointer= VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
        glCompileShader(VertexShaderID);

        //check vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if(InfoLogLength > 0)
        {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            std::cout << &VertexShaderErrorMessage[0] << std::endl;
        }

        //Compile Fragment Shader
        std::cout << fragment_file_path << std::endl;
        char const * FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            std::cout <<  &FragmentShaderErrorMessage[0] << std::endl;
        }
        //Link the program
        std::cout << "Linking the program " << std::endl;
        GLuint ProgramID = glCreateProgram();
        glAttachShader(ProgramID, VertexShaderID);
        glAttachShader(ProgramID, FragmentShaderID);
        glLinkProgram(ProgramID);
        //check the program
        glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if ( InfoLogLength > 0 ){
            std::vector<char> ProgramErrorMessage(InfoLogLength+1);
            glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            std::cout << &ProgramErrorMessage[0] << std::endl;
        }
        glDetachShader(ProgramID, VertexShaderID);
        glDetachShader(ProgramID, FragmentShaderID);

        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);

        return ProgramID;

    }
std::vector<float> Load::Parser(std::string const& line, char const& div)
{
      std::vector<float> result;
      std::string temp;
      bool space{true};
      if(div == ' ')
     {
          for(int i = 0; i < line.length(); i++)
          {
              if((line.at(i) == 'v') || (line.at(i) == 't') || (line.at(i)== 'n'))
                continue;
              if(line.at(i) != ' ' && !space)
              {
                  temp.push_back(line.at(i));

              }
              if(line.at(i) == ' ' && !space)
              {
                  result.push_back(std::stof(temp, nullptr));
                  temp.clear();
              }
              if(i == line.length()-1)
              {
                    result.push_back(std::stof(temp, nullptr));
                  temp.clear();
              }

              space = false;

        }

      }
      if(div == '/')
        {
            for(int i = 0; i < line.length(); i++)
          {
              if((line.at(i) == 'f'))
                continue;
              if(line.at(i) != ' ' && !space && line.at(i) != '/')
              {
                  temp.push_back(line.at(i));

              }
              if(line.at(i) == ' ' && !space)
              {
                  result.push_back(std::stof(temp, nullptr));
                  temp.clear();
              }
              if(line.at(i) == '/' && !space)
              {
                  result.push_back(std::stof(temp, nullptr));
                  temp.clear();
              }
              if(i == line.length()-1)
              {
                  result.push_back(std::stof(temp, nullptr));
                  temp.clear();
              }

              space = false;
        }
    }
      return result;
}
bool Load::LoadOBJ(std::string path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    std::ifstream myfile;
    myfile.open(path);
    std::string line;
    if(myfile.is_open())
    {
        while(std::getline(myfile, line))
        {
            std::string check;
            for(auto ch: line)
            {
                if(ch != ' ')
                    check.push_back(ch);
                if(ch == ' ')
                    break;
            }
            try{
            if(check == "v")
            {
                glm::vec3 vertex;
                std::vector<float> temp = Parser(line, ' ');
                vertex.x = temp.at(0);
                vertex.y = temp.at(1);
                vertex.z = temp.at(2);
                temp_vertices.push_back(vertex);
            }
            if(check == "vt")
            {
                glm::vec2 uv;
                std::vector<float> temp = Parser(line, ' ');
                uv.x = temp.at(0);
                uv.y = temp.at(1);
                temp_uvs.push_back(uv);
            }
            if(check == "vn")
            {
                glm::vec3 normal;
                std::vector<float> temp = Parser(line, ' ');
                normal.x = temp.at(0);
                normal.y = temp.at(1);
                normal.z = temp.at(2);
                temp_normals.push_back(normal);
            }
            if(check == "f")
            {
                std::vector<float> temp = Parser(line, '/');
                vertexIndices.push_back(temp.at(0));
                vertexIndices.push_back(temp.at(3));
                vertexIndices.push_back(temp.at(6));
                uvIndices.push_back(temp.at(1));
                uvIndices.push_back(temp.at(4));
                uvIndices.push_back(temp.at(7));
                normalIndices.push_back(temp.at(2));
                normalIndices.push_back(temp.at(5));
                normalIndices.push_back(temp.at(8));
            }
            }catch(std::exception& e)
            {
                std::cout << e.what() << std::endl;
            }
        }
    }else {std::cout << " Unable to open the File" << std::endl;}






        for(unsigned int i = 0;i<vertexIndices.size(); i++)
        {
            unsigned int vertexIndex = vertexIndices[i];
            glm::vec3 vertex = temp_vertices[vertexIndex-1];
            out_vertices.push_back(vertex);
        }
        for(unsigned int i = 0;i<uvIndices.size(); i++)
        {
            unsigned int uvIndex = uvIndices[i];
            glm::vec2 uvs = temp_uvs[uvIndex-1];
            out_uvs.push_back(uvs);
        }
        for(unsigned int i = 0;i<normalIndices.size(); i++)
        {
            unsigned int normalIndex = normalIndices[i];
            glm::vec3 normal = temp_normals[normalIndex-1];
            out_normals.push_back(normal);
        }

        return true;


}

Controls::Controls():position{glm::vec3(0,1,5)}, horizontalAngle{3.14f}, verticalAngle{0.0f}, FoV{45.0f}, speed{3.0f}, mouseSpeed{0.01f}
    {

    }

void Controls::CUpdate(GLFWwindow* win, double lastTime)
    {


        double xpos, ypos;
        int height, width;

        //get the mouse posi
        glfwGetCursorPos(win, &xpos, &ypos);
        //Reset hte mouse position for the next frame
        glfwGetWindowSize(win, &width, &height);
        /*if(xpos >= width || ypos >= height){
            glfwSetCursorPos(win, width/2, height/2);
        }*/

        //timing
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);
        //Compute the new orientation
        horizontalAngle += mouseSpeed*deltaTime* float(width/2-xpos);
        verticalAngle  +=  mouseSpeed *deltaTime *float(height/2-ypos);
       //Direction:Spherical Coordinates to cartesian Coordinates of where we are looking at
       direction = glm::vec3(cos(verticalAngle)*sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle)*cos(horizontalAngle));
       right = glm::vec3(sin(horizontalAngle-3.14f/2),0, cos(horizontalAngle-3.14f/2.0f));
       up= glm::cross(right, direction);

       //Move Forward
       if(glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
       {
           position += direction *deltaTime*10.0f*speed;
       }
       if(glfwGetKey(win,GLFW_KEY_S) == GLFW_PRESS)
       {
           position -= direction *deltaTime*10.0f*speed;
       }
       if(glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
       {
           position += right *deltaTime*10.0f*speed;
       }
       if(glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
       {
           position -= right *deltaTime*10.0f*speed;
       }

    }
void Controls::CTransform(GLuint programID, float distance, float LightPower, float LightColor)
     {

        glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(FoV),4.0f/3.0f, 0.1f, 100.0f);;
        glm::mat4 ViewMatrix = glm::lookAt(position, position+direction, up);
        glm::mat4 ModelMatrix = glm::mat4(1.0f);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix*ModelMatrix;


        GLuint MatrixID = glGetUniformLocation(programID, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

        GLuint MID = glGetUniformLocation(programID,"M");
        glUniformMatrix4fv(MID,1,GL_FALSE, &ModelMatrix[0][0]);

        GLuint VID = glGetUniformLocation(programID,"V");
        glUniformMatrix4fv(VID,1,GL_FALSE, &ViewMatrix[0][0]);

        GLuint DID = glGetUniformLocation(programID, "D");
        glUniform1f(DID, distance);

        GLuint LPID = glGetUniformLocation(programID, "LP");
        glUniform1f(LPID, LightPower);

        GLuint LCID = glGetUniformLocation(programID, "LC");
        glUniform1f(LCID, LightColor);



    }
//Returns true if v1 can be considered to be equal to v2
bool Load::is_near(float v1, float v2)
{
    return fabs(v1-v2) < 0.01f;
}

bool Load::getSimilarVertexIndex(PackedVertex& packed, std::map<PackedVertex, unsigned short>& VertexToOutIndex,
                                 unsigned short& result)
                                 {
                                     std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
                                     if(it == VertexToOutIndex.end())
                                     {
                                         return false;
                                     }else{result = it->second; return true;}
                                 }

void Load::indexVBO(std::vector<glm::vec3>& in_vertices,
                    std::vector<glm::vec2>& in_uvs,
                    std::vector<glm::vec3>& in_normals,
                    std::vector<unsigned short>& out_indices,
                    std::vector<glm::vec3>& out_vertices,
                    std::vector<glm::vec2>& out_uvs,
                    std::vector<glm::vec3>& out_normals
                    )
                    {
                        std::map<PackedVertex, unsigned short> VertexToOutIndex;
                        for (unsigned int i = 0; i< in_vertices.size(); i++)
                        {
                            PackedVertex packed = {in_vertices[i], in_uvs[i], in_normals[i]};

                            //Try to find a similar vertex in out
                            unsigned short index;
                            bool found = getSimilarVertexIndex(packed, VertexToOutIndex, index);

                            if(found)
                            {
                                out_indices.push_back(index);
                            }else
                            {
                                out_vertices.push_back(in_vertices[i]);
                                out_uvs.push_back(in_uvs[i]);
                                out_normals.push_back(in_normals[i]);
                                unsigned short newindex = (unsigned short)out_vertices.size() - 1;
                                out_indices.push_back(newindex);
                                VertexToOutIndex[packed] = newindex;
                            }
                        }
                    }

bool Load::getSimilarVertexIndex(
	glm::vec3 & in_vertex,
	glm::vec2 & in_uv,
	glm::vec3 & in_normal,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	unsigned short & result
){
	// Lame linear search
	for ( unsigned int i=0; i<out_vertices.size(); i++ ){
		if (
			is_near( in_vertex.x , out_vertices[i].x ) &&
			is_near( in_vertex.y , out_vertices[i].y ) &&
			is_near( in_vertex.z , out_vertices[i].z ) &&
			is_near( in_uv.x     , out_uvs     [i].x ) &&
			is_near( in_uv.y     , out_uvs     [i].y ) &&
			is_near( in_normal.x , out_normals [i].x ) &&
			is_near( in_normal.y , out_normals [i].y ) &&
			is_near( in_normal.z , out_normals [i].z )
		){
			result = i;
			return true;
		}
	}
	// No other vertex could be used instead.
	// Looks like we'll have to add it to the VBO.
	return false;
}


void Load::indexVBO_TBN(
	std::vector<glm::vec3> & in_vertices,
	std::vector<glm::vec2> & in_uvs,
	std::vector<glm::vec3> & in_normals,
	std::vector<glm::vec3> & in_tangents,
	std::vector<glm::vec3> & in_bitangents,

	std::vector<unsigned short> & out_indices,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals,
	std::vector<glm::vec3> & out_tangents,
	std::vector<glm::vec3> & out_bitangents
){
	// For each input vertex
	for ( unsigned int i=0; i<in_vertices.size(); i++ ){

		// Try to find a similar vertex in out_XXXX
		unsigned short index;
		bool found = getSimilarVertexIndex(in_vertices[i], in_uvs[i], in_normals[i],     out_vertices, out_uvs, out_normals, index);

		if ( found ){ // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back( index );

			// Average the tangents and the bitangents
			out_tangents[index] += in_tangents[i];
			out_bitangents[index] += in_bitangents[i];
		}else{ // If not, it needs to be added in the output data.
			out_vertices.push_back( in_vertices[i]);
			out_uvs     .push_back( in_uvs[i]);
			out_normals .push_back( in_normals[i]);
			out_tangents .push_back( in_tangents[i]);
			out_bitangents .push_back( in_bitangents[i]);
			out_indices .push_back( (unsigned short)out_vertices.size() - 1 );
		}
	}
}
