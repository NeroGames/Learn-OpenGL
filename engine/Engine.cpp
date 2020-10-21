////////////////////////////////////////////////////////////
// Learn OpenGL
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
///////////////////////////HEADERS//////////////////////////
#include "Engine.h"
////////////////////////////////////////////////////////////

Engine::Engine():
     m_OpenGlAvailable(true)
    ,m_EngineRunning(true)
{
    createWindow();
    initOpenGL();
}

Engine::~Engine()
{
    //dtor
}

void Engine::setScene(Scene::Ptr scene)
{
    m_Scene = std::move(scene);
}

void Engine::run()
{
    if(!m_OpenGlAvailable || !m_Scene) return;

    m_Scene->init();

    while(m_EngineRunning)
    {
        // handle events
        sf::Event event;
        while(m_RenderWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                // end the program
                m_EngineRunning = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }

            m_Scene->handleEvent(event);
        }

        // clear the buffers
        m_Scene->clear();
        // draw scene
        m_Scene->render();

        // end the current frame (internally swaps the front and back buffers)
        m_RenderWindow.display();
    }

    m_Scene->destroy();

}

void Engine::createWindow()
{
    // create the window
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 3;

    m_RenderWindow.create(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);
    m_RenderWindow.setVerticalSyncEnabled(true);

    // activate the window
    m_RenderWindow.setActive(true);
}

void Engine::initOpenGL()
{
    //Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        m_OpenGlAvailable = false;
    }
}
