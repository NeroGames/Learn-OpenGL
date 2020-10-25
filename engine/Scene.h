////////////////////////////////////////////////////////////
// Learn OpenGL
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#ifndef SCENE_H
#define SCENE_H
///////////////////////////HEADERS//////////////////////////
//Glew
#include <GL/glew.h>
//SFML
#include <SFML/OpenGL.hpp>
#include <SFML/Window/Event.hpp>
//CPP
#include <iostream>
#include <memory>
////////////////////////////////////////////////////////////
class Scene
{
    public:
        typedef std::unique_ptr<Scene> Ptr;

    public:
                                    Scene();
        virtual                    ~Scene();
        std::string                 getSceneName();
        sf::Vector2f                getResolution();

    protected:
            //shader
        //void                        createShader();
        //void                        compileShader();
        //void                        linkShader();
        void                        setSceneName(const std::string& name);
        sf::Vector2f                pixelToNDC(const sf::Vector2f& vertex);

    public:
        virtual void                init();
        virtual void                clear();
        virtual void                render();
        virtual void                destroy();
        virtual void                handleEvent(const sf::Event& event);

    private:
        friend class                Engine;
        std::string                 m_SceneName;
        sf::Vector2f                m_Resolution;

};

#endif // SCENE_H
