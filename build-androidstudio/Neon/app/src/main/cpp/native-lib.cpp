#include <string>
#include <sstream>
#include <chrono> /* C++11 functionality */
#include <random>
#include <cstdlib>

#include <SDL.h>

/* Android OpenGL ES 3 headers */
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* Shader sources */
const GLchar* vertexSource =
        "#version 300 es\n"
                "precision mediump float;"
                "in vec2 aPosition;"
                "in vec3 aColor;"
                "out vec3 vColor;"
                "uniform mat4 uModel;"
                "uniform mat4 uLookAt;"
                "uniform mat4 uProjection;"
                "void main() {"
                "   vColor = aColor;"
                "   gl_Position = uProjection * uLookAt * uModel * vec4(aPosition, 0.0, 1.0);"
                "}";

const GLchar* fragmentSource =
        "#version 300 es\n"
                "precision mediump float;"
                "in vec3 vColor;"
                "out vec4 FragColor;"
                "void main() {"
                "   FragColor = vec4(vColor, 1.0);"
                "}";

/* Must use parameters here or else there will be an undefined reference to SDL_main */
int SDL_main(int argc, char** argv)
{
    /* Initialize SDL library */
    SDL_Window* sdlWindow = 0;
    SDL_GLContext sdlGL = 0;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to initalize SDL: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_DisplayMode mode;
    SDL_GetDisplayMode(0, 0, &mode);
    int width = mode.w;
    int height = mode.h;

    SDL_Log("Width = %d. Height = %d\n", width, height);

    sdlWindow = SDL_CreateWindow(nullptr, 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);

    if (sdlWindow == 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create the sdlWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    sdlGL = SDL_GL_CreateContext(sdlWindow);

    /* Query OpenGL device information */
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    std::stringstream ss;
    ss << "\n-------------------------------------------------------------\n";
    ss << "GL Vendor    : " << vendor;
    ss << "\nGL GLRenderer : " << renderer;
    ss << "\nGL Version   : " << version;
    ss << "\nGL Version   : " << major << "." << minor;
    ss << "\nGLSL Version : " << glslVersion;
    ss << "\n-------------------------------------------------------------\n";
    SDL_Log("%s", ss.str().c_str());

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CCW);
    //glCullFace(GL_BACK);

    /* Create OpenGL vertex data */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);

    GLfloat vertices[] = {
            -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, /* Bottom left */
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, /* Bottom right */
            -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, /* Top left  */
            0.5f,  0.5f, 1.0f, 0.0f, 1.0f  /* Top right */
    };

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    /* Index data */
    GLuint ebo;
    glGenBuffers(1, &ebo);

    GLuint elements[] = {
            0, 1, 2,
            1, 3, 2
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    /* Create and compile the vertex shader */
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);

    /* Create and compile the fragment shader */
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);

    /* Link the vertex and fragment shader into a shader program */
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Specify the layout of the vertex data
    GLint posAttrib = glGetAttribLocation(shaderProgram, "aPosition");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));

    GLint colAttrib = glGetAttribLocation(shaderProgram, "aColor");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(2 * sizeof(GLfloat)));

    GLint modelMatrixPos = glGetUniformLocation(shaderProgram, "uModel");
    GLint projMatrixPos = glGetUniformLocation(shaderProgram, "uProjection");
    GLint lookatMatrixPos = glGetUniformLocation(shaderProgram, "uLookAt");

    glm::mat4 perspective = glm::perspective(glm::radians(60.0f), static_cast<GLfloat>(width) / static_cast<GLfloat>(height), 0.1f, 100.0f);
    glUniformMatrix4fv(projMatrixPos, 1, GL_FALSE, glm::value_ptr(perspective));

    glm::mat4 lookat = glm::lookAt(glm::vec3(0.0f, 0.0f, 2.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    glUniformMatrix4fv(lookatMatrixPos, 1, GL_FALSE, glm::value_ptr(lookat));

    float mixCounter = 0.0001f;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist (90.0f, 180.0f);

    auto startTime = std::chrono::high_resolution_clock::now();

    bool done = false;
    while (!done)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = true;
            }
            else if (event.type == SDL_FINGERDOWN || event.type == SDL_FINGERMOTION || event.type == SDL_FINGERMOTION)
            {
                // no implementation right now
            }
        }

        auto nowTime = std::chrono::high_resolution_clock::now();
        float dt = std::chrono::duration_cast<std::chrono::duration<float>>(nowTime - startTime).count();

        mixCounter = (mixCounter > 1.0f) ? 0.0001f : mixCounter + 0.0001f;
        glm::vec3 colorMix = glm::mix(glm::vec3(0.0f), glm::vec3(1.0f), mixCounter);

        glClearColor(colorMix.x, colorMix.y, colorMix.z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1);
        model = glm::rotate(model, dt * glm::radians(dist(mt)), glm::vec3(0.0f, 0.0f, 1.0f));

        glUniformMatrix4fv(modelMatrixPos, 1, GL_FALSE, glm::value_ptr(model));

        /* Draw a rectangle from the vertex data using 6 indices */
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        /* Swap OpenGL render buffers */
        SDL_GL_SwapWindow(sdlWindow);
    } /* while !done */

    glDeleteProgram(shaderProgram);

    glDeleteBuffers(1, &ebo);
    glDeleteBuffers(1, &vbo);

    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
} /* main */
