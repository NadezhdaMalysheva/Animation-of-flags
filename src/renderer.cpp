#include "renderer.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

const int number_add = 15;

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
            vertices[5*(2*i)+1] =  0.06f;
            vertices[5*(2*i)+2] =  0.0f;
            vertices[5*(2*i)+3] =  0.0f + float(i)*shift*10;
            vertices[5*(2*i)+4] =  0.0f;
            //Нижние точки
            vertices[5*(2*i+1)]   = -0.05f + float(i)*shift;
            vertices[5*(2*i+1)+1] = -0.06f;
            vertices[5*(2*i+1)+2] =  0.0f;
            vertices[5*(2*i+1)+3] =  0.0f + float(i)*shift*10;
            vertices[5*(2*i+1)+4] =  1.0f;

        }
        // Добавляем флагшток
        
        //Слева
        //Верхние точки
        vertices[5*(4+number_add*2)]   = -0.055f;
        vertices[5*(4+number_add*2)+1] =  0.06f;
        vertices[5*(4+number_add*2)+2] =  0.0f;
        vertices[5*(4+number_add*2)+3] =  2.0f;
        vertices[5*(4+number_add*2)+4] =  2.0f;
        //Нижние точки
        vertices[5*(4+number_add*2+1)]   = -0.055f;
        vertices[5*(4+number_add*2+1)+1] = -0.12f;
        vertices[5*(4+number_add*2+1)+2] =  0.0f;
        vertices[5*(4+number_add*2+1)+3] =  2.0f;
        vertices[5*(4+number_add*2+1)+4] =  2.0f;
        
        //Справа
        //Верхние точки
        vertices[5*(4+number_add*2+2)]   = -0.05f;
        vertices[5*(4+number_add*2+2)+1] =  0.06f;
        vertices[5*(4+number_add*2+2)+2] =  0.0f;
        vertices[5*(4+number_add*2+2)+3] =  2.0f;
        vertices[5*(4+number_add*2+2)+4] =  2.0f;
        //Нижние точки
        vertices[5*(4+number_add*2+3)]   = -0.05f;
        vertices[5*(4+number_add*2+3)+1] = -0.12f;
        vertices[5*(4+number_add*2+3)+2] =  0.0f;
        vertices[5*(4+number_add*2+3)+3] =  2.0f;
        vertices[5*(4+number_add*2+3)+4] =  2.0f;

        // Добавляем плоскость
        
        //Слева
        //Верхние точки
        vertices[5*(8+number_add*2)]   = -0.1f;
        vertices[5*(8+number_add*2)+1] = -0.12f;
        vertices[5*(8+number_add*2)+2] = -0.5f;
        vertices[5*(8+number_add*2)+3] =  3.0f;
        vertices[5*(8+number_add*2)+4] =  3.0f;
        //Нижние точки
        vertices[5*(8+number_add*2+1)]   = -0.1f;
        vertices[5*(8+number_add*2+1)+1] = -0.12f;
        vertices[5*(8+number_add*2+1)+2] =  0.5f;
        vertices[5*(8+number_add*2+1)+3] =  3.0f;
        vertices[5*(8+number_add*2+1)+4] =  3.0f;
        
        //Справа
        //Верхние точки
        vertices[5*(8+number_add*2+2)]   =  0.1f;
        vertices[5*(8+number_add*2+2)+1] = -0.12f;
        vertices[5*(8+number_add*2+2)+2] = -0.5f;
        vertices[5*(8+number_add*2+2)+3] =  3.0f;
        vertices[5*(8+number_add*2+2)+4] =  3.0f;
        //Нижние точки
        vertices[5*(8+number_add*2+3)]   =  0.1f;
        vertices[5*(8+number_add*2+3)+1] = -0.12f;
        vertices[5*(8+number_add*2+3)+2] =  0.5f;
        vertices[5*(8+number_add*2+3)+3] =  3.0f;
        vertices[5*(8+number_add*2+3)+4] =  3.0f;

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
        // Флагшток

        //Первый треугольник
        indices[3*2*(number_add+1)+0] = (4+number_add*2)+0; //Верхняя левая
        indices[3*2*(number_add+1)+1] = (4+number_add*2)+1; //Нижняя левая
        indices[3*2*(number_add+1)+2] = (4+number_add*2)+2; //Верхняя правая
        //Второй треугольник 
        indices[3*2*(number_add+1)+3] = (4+number_add*2)+1; //Нижняя левая
        indices[3*2*(number_add+1)+4] = (4+number_add*2)+2; //Верхняя правая
        indices[3*2*(number_add+1)+5] = (4+number_add*2)+3; //Нижняя правая

        // Плоскость

        //Первый треугольник
        indices[3*2*(number_add+2)+0] = (8+number_add*2)+0; //Верхняя левая
        indices[3*2*(number_add+2)+1] = (8+number_add*2)+1; //Нижняя левая
        indices[3*2*(number_add+2)+2] = (8+number_add*2)+2; //Верхняя правая
        //Второй треугольник 
        indices[3*2*(number_add+2)+3] = (8+number_add*2)+1; //Нижняя левая
        indices[3*2*(number_add+2)+4] = (8+number_add*2)+2; //Верхняя правая
        indices[3*2*(number_add+2)+5] = (8+number_add*2)+3; //Нижняя правая
        
    }
    
    void Renderer::Init(SDL_Window *_window, int w, int h)
    {
        window = _window;
        width = w;
        height = h;

        GLfloat vertices[5*(4+number_add*2) + 5*8];
        add_point_vertices(vertices, number_add);
               
        
        GLuint indices[3*2*(number_add+1) + 3*4];
        add_point_indices(indices, number_add);
        
         

        int index = 0;
        float offset = 0.1f;
        for(int y = -10; y < 10; y += 2)
        {
            for(int x = -10; x < 10; x += 2)
            {
                translations[index++] = (float)x / 10.0f + offset;
                translations[index++] = (float(y) + 0.5) / 11.0f + offset;
            }
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

    // Создаем матрицы преобразований 

    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.3f, -2.0f));
    projection = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.1f, 100.0f);
    
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
        glUniform1fv(glGetUniformLocation(shaderProgram, "Offsets"), 200, translations);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        //glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElementsInstanced(GL_TRIANGLES, 3*2*(number_add + 3), GL_UNSIGNED_INT,0, 100);//3*2*(number_add+1)
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