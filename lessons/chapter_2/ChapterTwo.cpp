////////////////////////////////////////////////////////////
// Learn OpenGL
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
#include "chapter_2/ChapterTwo.h"
////////////////////////////////////////////////////////////

ChapterTwo::ChapterTwo()
{
    setSceneName("Chapter 2 - Shader and Texture");

    //Vertex shaper inputs are call vertex attributes
    //OpenGL guarantees there are always at least 16 4-component
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
}

ChapterTwo::~ChapterTwo()
{
    //empty
}

void ChapterTwo::init()
{
    //create shader program
    m_ShaderProgram     = createShaderProgram();
    m_ShaderProgramTwo  = createShaderProgramTwo();

    //build a triangle
    createTriangle(sf::Vector2f(200.f, 200.f), sf::Vector2f(50.f, 400.f), sf::Vector2f(350.f, 400.f));
    createTriangleTwo(sf::Vector2f(550.f, 200.f), sf::Vector2f(400.f, 400.f), sf::Vector2f(700.f, 400.f));
}

void ChapterTwo::render()
{
    drawTriangle();
    drawTriangleTwo();
}

void ChapterTwo::destroy()
{
    destroyTriangle();

    glDeleteProgram(m_ShaderProgram);
}

int ChapterTwo::createShaderProgram()
{
    const char *vertexShaderSource ="#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "uniform vec4 ourColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = ourColor;\n"
        "}\n\0";

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

void ChapterTwo::createTriangle(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, const sf::Vector2f& vertex3)
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

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);


    // bind the VAO (it was already bound, but just to demonstrate): seeing as we only have a single VAO we can
    // just bind it beforehand before rendering the respective triangle; this is another approach.
    glBindVertexArray(0);

}

void ChapterTwo::drawTriangle()
{

        // be sure to activate the shader before any calls to glUniform
        glUseProgram(m_ShaderProgram);

        // update shader uniform
        float timeValue = m_Clock.getElapsedTime().asSeconds();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(m_ShaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // render the triangle
        glBindVertexArray(m_Triangle.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ChapterTwo::destroyTriangle()
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_POINT, GL_LINE, and GL_FILL
    glDeleteVertexArrays(1, &m_Triangle.VAO);
    glDeleteBuffers(1, &m_Triangle.VBO);
    //glDeleteBuffers(1, &m_Triangle.EBO);
}

int ChapterTwo::createShaderProgramTwo()
{
    const char *vertexShaderSource ="#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "out vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos, 1.0);\n"
        "   ourColor = aColor;\n"
        "}\0";

    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(ourColor, 1.0f);\n"
        "}\n\0";

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

void ChapterTwo::createTriangleTwo(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, const sf::Vector2f& vertex3)
{
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
     float vertices[] =
     {
        // positions                                         // colors
        pixelToNDC(vertex1).x, pixelToNDC(vertex1).y, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        pixelToNDC(vertex2).x, pixelToNDC(vertex2).y, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        pixelToNDC(vertex3).x, pixelToNDC(vertex3).y, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };

    glGenVertexArrays(1, &m_TriangleTwo.VAO);
    glGenBuffers(1, &m_TriangleTwo.VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_TriangleTwo.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_TriangleTwo.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
     glBindVertexArray(0);
}

void ChapterTwo::drawTriangleTwo()
{
    glUseProgram(m_ShaderProgramTwo);
    // render the triangle
    glBindVertexArray(m_TriangleTwo.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void ChapterTwo::destroyTriangleTwo()
{
    glDeleteVertexArrays(1, &m_TriangleTwo.VAO);
    glDeleteBuffers(1, &m_TriangleTwo.VBO);
}
