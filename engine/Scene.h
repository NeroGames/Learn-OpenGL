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

    protected:
            //shader
        //void                        createShader();
        //void                        compileShader();
        //void                        linkShader();

    public:
        virtual void                init();
        virtual void                clear();
        virtual void                render();
        virtual void                destroy();
        virtual void                handleEvent(const sf::Event& event);

    private:

};

#endif // SCENE_H
