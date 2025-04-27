#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void CheckShaderCompile(GLuint shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "Shader Compile Error: " << infoLog << std::endl;
    }
}

GLuint CreateSimpleShader()
{
    const char* vertexShaderSource = R"(#version 330 core
    layout (location = 0) in vec3 aPos;
    uniform mat4 uProj;
    uniform mat4 uModel;
    void main()
    {
        gl_Position = uProj * uModel * vec4(aPos, 1.0);
    })";

    const char* fragmentShaderSource = R"(#version 330 core
    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(0.2, 0.7, 0.9, 1.0);
    })";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    CheckShaderCompile(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    CheckShaderCompile(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint CreateSimpleTextShader()
{
    const char* vertexShaderSource = R"(#version 330 core
    layout (location = 0) in vec2 aPos;
    layout (location = 1) in vec2 aTex;
    out vec2 TexCoord;
    uniform mat4 uProj;
    void main()
    {
        gl_Position = uProj * vec4(aPos, 0.0, 1.0);
        TexCoord = aTex;
    })";

    const char* fragmentShaderSource = R"(#version 330 core
    in vec2 TexCoord;
    out vec4 FragColor;
    uniform sampler2D textTexture;
    void main()
    {
        FragColor = texture(textTexture, TexCoord);
    })";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    CheckShaderCompile(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    CheckShaderCompile(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint CreateTextureFromSurface(SDL_Surface* surface)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    GLenum format;
    switch (surface->format)
    {
    case SDL_PIXELFORMAT_RGBA32:
        format = GL_RGBA;
        break;
    case SDL_PIXELFORMAT_BGRA32:
        format = GL_BGRA;
        break;
    case SDL_PIXELFORMAT_RGB24:
        format = GL_RGB;
        break;
    case SDL_PIXELFORMAT_BGR24:
        format = GL_BGR;
        break;
    default:
        std::cerr << "Unsupported pixel format!" << std::endl;
        return 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0,
        GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;
}

int main(int argc, char** argv)
{
    const int framerate = 120; // FPS
    const int framelength = 1000 / framerate; // ms

    Uint32 frameStart;
    int frameTime;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("OpenGL Text + 3D", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint triangleShader = CreateSimpleShader();
    GLuint textShader = CreateSimpleTextShader();

    // Triangle Data
    float triangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    GLuint triangleVAO, triangleVBO;
    glGenVertexArrays(1, &triangleVAO);
    glGenBuffers(1, &triangleVBO);

    glBindVertexArray(triangleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Text
    TTF_Font* font = TTF_OpenFont("segoeui.ttf", 48);
    SDL_Color white = { 255, 255, 255, 255 };
    char msg[] = "HELLO WORLD";
    SDL_Surface* surface = TTF_RenderText_Blended(font, msg, sizeof(msg)/sizeof(char), white);
    GLuint textTexture = CreateTextureFromSurface(surface);
    int textW = surface->w;
    int textH = surface->h;
    SDL_DestroySurface(surface);

    float textVertices[] = {
        // positions        // tex coords
        0.0f, 0.0f,         0.0f, 0.0f,
        textW, 0.0f,        textW, 0.0f,
        textW, textH,       textW, textH,
        0.0f, textH,        0.0f, textH,
    };
    unsigned int textIndices[] = {
        0, 1, 2,
        2, 3, 0
    };
    GLuint textVAO, textVBO, textEBO;
    glGenVertexArrays(1, &textVAO);
    glGenBuffers(1, &textVBO);
    glGenBuffers(1, &textEBO);

    glBindVertexArray(textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, textVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(textVertices), textVertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, textEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(textIndices), textIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Matrices
    glm::mat4 perspective = glm::perspective(glm::radians(45.0f), 1280.f / 720.f, 0.1f, 100.0f);
    glm::mat4 ortho = glm::ortho(0.0f, 1280.f, 720.f, 0.0f, -1.0f, 1.0f);

    bool running = true;
    float angle = 0.0f;

    while (running)
    {
        frameStart = SDL_GetTicks();

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
                running = false;
        }

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // --- Draw Triangle ---
        glEnable(GL_DEPTH_TEST);
        glUseProgram(triangleShader);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0., 0., -3.));
        model = glm::rotate(model, glm::radians(angle), glm::vec3(0., 1., 0.));

        glUniformMatrix4fv(glGetUniformLocation(triangleShader, "uProj"), 1, GL_FALSE, glm::value_ptr(perspective));
        glUniformMatrix4fv(glGetUniformLocation(triangleShader, "uModel"), 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // --- Draw Text ---
        /*glDisable(GL_DEPTH_TEST);
        glUseProgram(textShader);

        glUniformMatrix4fv(glGetUniformLocation(textShader, "uProj"), 1, GL_FALSE, glm::value_ptr(ortho));
        glBindTexture(GL_TEXTURE_2D, textTexture);

        glBindVertexArray(textVAO);
        glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);*/

        SDL_GL_SwapWindow(window);

        angle += 1.0f;

        frameTime = SDL_GetTicks() - frameStart;
        if (framelength > frameTime) {
            SDL_Delay(framelength - frameTime);
        }
    }

    // Cleanup
    glDeleteProgram(triangleShader);
    glDeleteProgram(textShader);
    glDeleteTextures(1, &textTexture);
    glDeleteVertexArrays(1, &triangleVAO);
    glDeleteVertexArrays(1, &textVAO);
    glDeleteBuffers(1, &triangleVBO);
    glDeleteBuffers(1, &textVBO);
    glDeleteBuffers(1, &textEBO);

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
