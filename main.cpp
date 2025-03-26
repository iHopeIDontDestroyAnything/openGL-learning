#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include "renderer.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexArray.h"
#include "vertexBufferLayout.h"


static std::tuple<std::string,std::string> ParseShader(const std::string& filepath)
{
  std::ifstream stream(filepath);
  std::string line;
  std::stringstream ss[2];
  enum class ShaderType 
  {
    NONE = -1, VERTEX = 0, FRAGMENT = 1
  };

  ShaderType type = ShaderType::NONE;
  while (std::getline(stream, line))
  {
    if (line.find("#shader") != std::string::npos)
    {
      if(line.find("vertex") != std::string::npos)
      {
        type = ShaderType::VERTEX;
      }
      else if (line.find("fragment") != std::string::npos)
      {
        type = ShaderType::FRAGMENT;
      }
    }
    else
    {
      ss[(int)type] << line << '\n';
    }
  }

  std::string vs = ss[0].str();
  std::string fs = ss[1].str();
  
  return std::tuple<std::string,std::string>(vs,fs);
}

static unsigned int CompileShader(unsigned int type,const std::string& src)
{
  unsigned int id = glCreateShader(type);
  const char *source = src.c_str(); 
  glShaderSource(id,1,&source, NULL);
  glCompileShader(id);


  int result;
  glGetShaderiv(id,GL_COMPILE_STATUS,&result);
  if(result == GL_FALSE) 
  {
    int lenght;
    glGetShaderiv(id,GL_INFO_LOG_LENGTH,&lenght);
    char* message = (char*)alloca(lenght * sizeof(char));
    glGetShaderInfoLog(id,lenght,&lenght,message);
    std::cout << "Failed to compile "<< (
      type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<" shader\n";
    std::cout <<message <<"\n";
    glDeleteShader(id);
    return 0;
  }

  return id; 
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

  glAttachShader(program,vs);
  glAttachShader(program,fs);
  glLinkProgram(program);

  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);
  return program;
}


int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    GLCall(glfwMakeContextCurrent(window));

    GLCall(glfwSwapInterval(1));

    GLCall(glewInit());

    float rectangle[]
    {
      -0.5f,-0.5f,
      -0.5f,0.5f,
       0.5f,0.5f,
       0.5f,-0.5f
    };
    unsigned int indRect[]
    {
      0,1,2,
      2,3,4
    };

    float positions[]{
       0.5f, 0.5f,
       0.0f, 0.5f,
       0.3f, 0.0f,
    };

    unsigned int indicies[]{
      0,1,2, 
    };

    float positions2[]{
       0.0f,-0.5f,
       0.5f,-0.5f,
       0.5f, 0.0f,
    };

    unsigned int indicies2[]{
      0,1,2, 
    };

    {
    vertexBuffer rect(rectangle,4*2*sizeof(float)); 
    vertexBuffer vb(positions,3*2*sizeof(float));
    vertexBuffer vb2(positions2,3*2*sizeof(float));
    vertexBufferLayout layout;
    layout.push<float>(2);
    vertexArray va;
    vertexArray va2;
    vertexArray obdlznik;
    va.addBuffer(vb,layout);
    va2.addBuffer(vb2,layout);
    obdlznik.addBuffer(rect,layout);

    indexBuffer ib(indicies, 3);
    indexBuffer ib2(indicies2,3);
    indexBuffer irect(indRect,6);
  

    auto sources = ParseShader("../res/shaders/basic.shader");
    std::string VertexShader = std::get<0>(sources);
    std::string FragmentShader = std::get<1>(sources);
    unsigned int shader = CreateShader(VertexShader,FragmentShader);
    GLCall(glUseProgram(shader));

    GLCall(int location = glGetUniformLocation(shader, "u_Color"));
    ASSERT(location != -1);
    GLCall(glUniform4f(location,0.8,0.1,0.8,1.0));

    GLCall(glUseProgram(0));
    GLCall(__glewBindVertexArray(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));

    float r = 0.0f;
    float increment = 0.05f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
          
        GLCall(glUseProgram(shader));
        GLCall(glUniform4f(location,r,0.2,0.8,1.0));
        if(r > 1.0f || r < 0.0f) increment = -increment; 
        r += increment;
        
        // GLCall(va.Bind());
        // GLCall(ib.Bind());
        // GLCall(glDrawElements(GL_TRIANGLES,3,GL_UNSIGNED_INT,NULL));
        // GLCall(va.Unbind()); 
        // GLCall(ib.UnBind());
        // GLCall(ib2.Bind());
        // GLCall(va2.Bind()); 

        GLCall(obdlznik.Bind()); 
        GLCall(irect.Bind()); 
        GLCall(glDrawElements(GL_TRIANGLES,4,GL_UNSIGNED_INT,NULL));
        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(window));

        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }
    }
    glfwTerminate();
    return 0;
}
