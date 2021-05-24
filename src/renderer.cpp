#include "renderer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

const int number_add = 20;

    int add_shader(std::string fileName, GLuint shaderProgram, GLenum shaderType)
    {
        char* src; int32_t size;

        //Читаем файл с кодом шейдера
        std::ifstream t;
        std::string fileContent;

        t.open(fileName);
        if(t.is_open())
        {
            std::stringstream buffer;
            buffer << t.rdbuf();
            fileContent = buffer.str();
        }
        else std::cout<<"File "<<fileName<<" opening failed"<<std::endl;
        t.close();
        size = fileContent.length();  //Set the Size

        std::string result = fileContent;
        src = const_cast<char*>(result.c_str());

        int shaderID = glCreateShader(shaderType);
        glShaderSource(shaderID, 1, &src, &size);
        
        //компилируем шейдер
        glCompileShader(shaderID);
        int success;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if(success) 
        {
            glAttachShader(shaderProgram, shaderID);
        }
        else 
        {
            //печатаем информацию об ошибках компиляции
            int m;
            glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &m);
            char* l = new char[m];
            if(t) glGetShaderInfoLog(shaderID, m, &m, l);
            std::cout<<"Compiler Error: "<<l<<std::endl;
            delete[] l;
        }
        return shaderID;
    }
    void add_shader_program(GLuint &shaderProgram, const std::string vs, const std::string fs)
    {
        //компилируем шейдеры и связываем их с программой
        shaderProgram = glCreateProgram(); 
        int vs_code = add_shader(vs,shaderProgram, GL_VERTEX_SHADER);
        int fs_code = add_shader(fs,shaderProgram, GL_FRAGMENT_SHADER);
        glLinkProgram(shaderProgram);

        //печатаем ошибки линковки
        int success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) 
        {
            int m;
            glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &m);
            char* l = new char[m];
            glGetProgramInfoLog(shaderProgram, m, &m, l);
            std::cout<<"Linker Error: "<<l<<std::endl;
            delete[] l;
        }
        glDeleteShader(vs_code);
        glDeleteShader(fs_code);
    }
    void add_point_vertices(GLfloat* vertices, int number_add)
    {
        float shift = 0.1/float(number_add+1);
        for(int i=0; i<=number_add+1; i++)
        {
            //Верхние точки
            vertices[5*(2*i)]   = -0.05f + float(i)*shift;
            vertices[5*(2*i)+1] =  0.07f;
            vertices[5*(2*i)+2] =  0.0f;
            vertices[5*(2*i)+3] =  0.0f + float(i)*shift*10;
            vertices[5*(2*i)+4] =  0.0f;
            //Нижние точки
            vertices[5*(2*i+1)]   = -0.05f + float(i)*shift;
            vertices[5*(2*i+1)+1] = -0.07f;
            vertices[5*(2*i+1)+2] =  0.0f;
            vertices[5*(2*i+1)+3] =  0.0f + float(i)*shift*10;
            vertices[5*(2*i+1)+4] =  1.0f;
            std::cout << i << '\n';

        }
        std::cout << "end for" << '\n';
        std::cout << sizeof(vertices) << '\n';
        std::cout << 5*(4+number_add*2) << '\n';
        for(int i=0; i<5*(4+number_add*2); i++)
        {
            std::cout <<  vertices[i] << ','<< '\n';
        }
        std::cout << vertices << '\n';
    }

    void add_point_indices(GLuint* indices, int number_add)
    {
        
        for(int i=0; i<=number_add; i++)
        {
            //Первый треугольник
            indices[3*(2*i)+0] = 2*i+0; //Верхняя левая
            indices[3*(2*i)+1] = 2*i+1; //Нижняя левая
            indices[3*(2*i)+2] = 2*i+2; //Верхняя правая
            //Второй треугольник 
            indices[3*(2*i+1)+0] = 2*i+1; //Нижняя левая
            indices[3*(2*i+1)+1] = 2*i+2; //Верхняя правая
            indices[3*(2*i+1)+2] = 2*i+3; //Нижняя правая
        }
        std::cout <<  "indices" << '\n';
        for(int i=0; i<3*2*(number_add+1); i++)
        {
            std::cout <<  indices[i]<< ',' << '\n';
        }
        
    }
    
    void Renderer::Init(SDL_Window *_window, int w, int h)
    {
        window = _window;
        width = w;
        height = h;

        GLfloat vertices[5*(4+number_add*2)];
        add_point_vertices(vertices, number_add);
        
        GLuint indices[3*2*(number_add+1)];
        add_point_indices(indices, number_add);
        
        std::cout << sizeof(indices)<<' '<< sizeof(indices) << '\n';
        std::cout <<  "indices" << '\n';
        for(int i=0; i<3*2*(number_add+1); i++)
        {
            std::cout <<  indices[i]<< ',' << '\n';
        } 
                                                   
    
    // 1. Создаем буферы
        glGenBuffers(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
    // 2. Копируем наши вершины в буфер для OpenGL
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 3. Копируем наши индексы в в буфер для OpenGL
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 3. Устанавливаем указатели на вершинные атрибуты
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);    
    // 4. Отвязываем VAO (НЕ EBO)
    glBindVertexArray(0);

    add_shader_program(shaderProgram,"shaders/simple.vert","shaders/simple.frag");
    }
    void Renderer::Render(unsigned char *data, int width, int height, float time=0)
    {
        // Texture 

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        // Устанавливаем параметры наложения и фильтрации текстур (для текущего связанного объекта текстуры)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        // Загрузка и генерация текстуры
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        glUseProgram(shaderProgram);
        glUniform1f(glGetUniformLocation(shaderProgram, "GlobalTime"), time);
        //glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3*2*(number_add + 1), GL_UNSIGNED_INT, 0);//3*2*(number_add+1)
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    void Renderer::Close()
    {
        glDeleteBuffers(1,&VAO);
        glDeleteBuffers(1,&VBO);
        glDeleteBuffers(1,&EBO);
        glDeleteProgram(shaderProgram);
    }