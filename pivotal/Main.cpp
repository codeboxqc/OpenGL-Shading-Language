#include <SDL.h>
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

extern std::string loadFile(const std::string& path);

// Compile a shader
GLuint compileShader(GLenum type, const std::string& src) {
    GLuint shader = glCreateShader(type);
    const char* csrc = src.c_str();
    glShaderSource(shader, 1, &csrc, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cerr << "Shader compile error: " << info << std::endl;
    }
    return shader;
}

// Create a program from a fragment shader file
GLuint createProgramFromFile(const std::string& fragPath) {
    std::string fragSrc = loadFile(fragPath);

    // Simple vertex shader for fullscreen quad
    std::string vertSrc =
        "#version 330 core\n"
        "layout(location = 0) in vec2 aPos;\n"
        "void main() { gl_Position = vec4(aPos, 0.0, 1.0); }";

    GLuint vs = compileShader(GL_VERTEX_SHADER, vertSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragSrc);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    glDeleteShader(vs);
    glDeleteShader(fs);

    GLint success;
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        char info[512];
        glGetProgramInfoLog(prog, 512, nullptr, info);
        std::cerr << "Program link error: " << info << std::endl;
    }

    return prog;
}

int main(int argc, char* argv[]) {
    // SDL init
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* win = SDL_CreateWindow("Shader Switcher",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, SDL_WINDOW_OPENGL);
    SDL_GLContext ctx = SDL_GL_CreateContext(win);
    glewInit();

    // Fullscreen quad setup
    float vertices[] = { -1,-1,  1,-1, -1,1,  -1,1, 1,-1, 1,1 };
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Shader list
    std::vector<std::string> shaders = {
        "sh1.frag","sh2.frag","sh3.frag","sh4.frag","sh5.frag",
        "sh6.frag","sh7.frag","sh8.frag","sh9.frag","sh10.frag",
        "sh11.frag","sh12.frag","sh13.frag","sh14.frag","sh15.frag",
        "sh16.frag","sh17.frag","sh18.frag",

        "sh19.frag","sh20.frag","sh21.frag","sh22.frag",
        "sh23.frag","sh24.frag","sh25.frag","sh26.frag","sh27.frag",
        "sh28.frag","sh29.frag","sh30.frag","sh31.frag","sh32.frag",
        "sh33.frag" 
    };
    int currentShader = 0;

    GLuint program = createProgramFromFile(shaders[currentShader]);
    glUseProgram(program);

    GLint resLoc = glGetUniformLocation(program, "iResolution");
    GLint timeLoc = glGetUniformLocation(program, "iTime");

    bool running = true;
    Uint64 start = SDL_GetPerformanceCounter();

    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    currentShader = (currentShader + 1) % shaders.size();
                    glDeleteProgram(program);
                    program = createProgramFromFile(shaders[currentShader]);
                    glUseProgram(program);
                    resLoc = glGetUniformLocation(program, "iResolution");
                    timeLoc = glGetUniformLocation(program, "iTime");
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                    currentShader = (currentShader - 1 + shaders.size()) % shaders.size();
                    glDeleteProgram(program);
                    program = createProgramFromFile(shaders[currentShader]);
                    glUseProgram(program);
                    resLoc = glGetUniformLocation(program, "iResolution");
                    timeLoc = glGetUniformLocation(program, "iTime");
                }

               
                    if (e.key.keysym.sym == SDLK_SPACE) {
                        currentShader = (currentShader + 1) % shaders.size();
                        glDeleteProgram(program);
                        program = createProgramFromFile(shaders[currentShader]);
                        glUseProgram(program);
                        resLoc = glGetUniformLocation(program, "iResolution");
                        timeLoc = glGetUniformLocation(program, "iTime");
                    }
            }
        }

        float time = (SDL_GetPerformanceCounter() - start) /
            (float)SDL_GetPerformanceFrequency();

        glUniform2f(resLoc, 800.0f, 600.0f);
        glUniform1f(timeLoc, time);

        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        SDL_GL_SwapWindow(win);
    }

    glDeleteProgram(program);
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
