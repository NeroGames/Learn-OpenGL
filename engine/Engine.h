////////////////////////////////////////////////////////////
// Learn OpenGL
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#ifndef ENGINE_H
#define ENGINE_H
///////////////////////////HEADERS//////////////////////////
//Glew
#include <GL/glew.h>
//SFML
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
//
#include "Scene.h"
////////////////////////////////////////////////////////////
class Engine
{
    public:
                            Engine(const unsigned int& windowWidth = 1080, const unsigned int& windowHeight = 720);
        virtual            ~Engine();
        void                run();
        void                setScene(Scene::Ptr scene);

    private:
        void                createWindow();
        void                initOpenGL();

    protected:
        sf::Window          m_RenderWindow;
        Scene::Ptr          m_Scene;
        bool                m_OpenGlAvailable;
        bool                m_EngineRunning;
        sf::Vector2f        m_WindowResolution;

};

#endif // ENGINE_H
