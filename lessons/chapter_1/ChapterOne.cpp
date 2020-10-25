////////////////////////////////////////////////////////////
// Learn OpenGL
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
#include "chapter_1/ChapterOne.h"
////////////////////////////////////////////////////////////

ChapterOne::ChapterOne()
{
    setSceneName("Chapter 1 - Draw Simple Shapes");
}

ChapterOne::~ChapterOne()
{
    //empty
}

void ChapterOne::init()
{
    //create shader program
    m_ShaderProgram = createShaderProgram();

    //build a triangle
    createTriangle(sf::Vector2f(500.f, 10.f), sf::Vector2f(350.f, 200.f), sf::Vector2f(650.f, 200.f));
    //build a rectangle
    createRectangle(sf::Vector2f(10.f, 10.f), sf::Vector2f(300.f, 200.f));

    //

}

void ChapterOne::render()
{
    drawTriangle();
    drawRectangle();
}

void ChapterOne::destroy()
{
    destroyTriangle();
    destroyRectangle();

    glDeleteProgram(m_ShaderProgram);
}

int ChapterOne::createShaderProgram()
{
    const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

    // load resources, initialize the OpenGL states, ...
     // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void ChapterOne::createTriangle(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, const sf::Vector2f& vertex3)
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] =
    {
        pixelToNDC(vertex1).x, pixelToNDC(vertex1).y, 0.0f, // left
        pixelToNDC(vertex2).x, pixelToNDC(vertex2).y, 0.0f, // right
        pixelToNDC(vertex3).x, pixelToNDC(vertex3).y, 0.0f  // top
    };

    glGenVertexArrays(1, &m_Triangle.VAO);
    glGenBuffers(1, &m_Triangle.VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_Triangle.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_Triangle.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

void ChapterOne::drawTriangle()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glUseProgram(m_ShaderProgram);
    glBindVertexArray(m_Triangle.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ChapterOne::destroyTriangle()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_POINT, GL_LINE, and GL_FILL
    glDeleteVertexArrays(1, &m_Triangle.VAO);
    glDeleteBuffers(1, &m_Triangle.VBO);
    glDeleteBuffers(1, &m_Triangle.EBO);
}

void ChapterOne::createRectangle(const sf::Vector2f& origin, const sf::Vector2f& rectSize)
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] =
    {
        pixelToNDC(origin).x,  pixelToNDC(origin).y, 0.0f,                  // top left (origin)
        pixelToNDC(origin + rectSize).x, pixelToNDC(origin).y, 0.0f,           // top right
        pixelToNDC(origin + rectSize).x, pixelToNDC(origin + rectSize).y, 0.0f,  // bottom right
        pixelToNDC(origin).x,  pixelToNDC(origin + rectSize).y, 0.0f          // bottom left
    };

    unsigned int indices[] =
    {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &m_Rectangle.VAO);
    glGenBuffers(1, &m_Rectangle.VBO);
    glGenBuffers(1, &m_Rectangle.EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_Rectangle.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_Rectangle.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Rectangle.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

void ChapterOne::drawRectangle()
{
    // draw our first triangle
    glUseProgram(m_ShaderProgram);
    glBindVertexArray(m_Rectangle.VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glBindVertexArray(0); // no need to unbind it every time
}
void ChapterOne::destroyRectangle()
{
    glDeleteVertexArrays(1, &m_Rectangle.VAO);
    glDeleteBuffers(1, &m_Rectangle.VBO);
    glDeleteBuffers(1, &m_Rectangle.EBO);
}
