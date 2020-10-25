////////////////////////////////////////////////////////////
// Learn OpenGL
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#ifndef CHAPTETWO_H
#define CHAPTETWO_H
///////////////////////////HEADERS//////////////////////////
//SFML
#include <SFML/System/Clock.hpp>
//
#include "Scene.h"
////////////////////////////////////////////////////////////
class ChapterTwo : public Scene
{
    public:
                                            ChapterTwo();
        virtual                            ~ChapterTwo();

    public:
        virtual void                        init();
        virtual void                        render();
        virtual void                        destroy();

    private:

        int                                 createShaderProgram();
        int                                 createShaderProgramTwo();
        //triangle
        void                                createTriangle(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, const sf::Vector2f& vertex3);
        void                                drawTriangle();
        void                                destroyTriangle();
        //triangle 2
        void                                createTriangleTwo(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, const sf::Vector2f& vertex3);
        void                                drawTriangleTwo();
        void                                destroyTriangleTwo();



    private:
        int                                 m_ShaderProgram;
        int                                 m_ShaderProgramTwo;
        struct                              Triangle{unsigned int VBO, VAO, EBO;} m_Triangle;
        struct                              TriangleTwo{unsigned int VBO, VAO, EBO;} m_TriangleTwo;
        sf::Clock                           m_Clock;

};

#endif // CHAPTETWO_H
