#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <SDL2/SDL.h>

class Renderer
{
public:
    void Init(SDL_Window *window, int w, int h);
    void Render(unsigned char * Texture, int wTexture, int hTexture, float);
    void Close();
private:
    GLfloat translations[200];
    glm::mat4 model, view, projection;
    GLuint VAO, VBO, EBO;
    GLuint shaderProgram;
    SDL_Window *window;
    int width,height;
};
