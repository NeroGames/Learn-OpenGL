////////////////////////////////////////////////////////////
// Learn OpenGL
// Copyright (c) 2020 sk-landry
////////////////////////////////////////////////////////////
#ifndef CHAPTERONE_H
#define CHAPTERONE_H
///////////////////////////HEADERS//////////////////////////
#include "Scene.h"
////////////////////////////////////////////////////////////
class ChapterOne : public Scene
{
    public:
                                            ChapterOne();
        virtual                            ~ChapterOne();

    public:
        virtual void                        init();
        virtual void                        render();
        virtual void                        destroy();

    private:

        int                                 createShaderProgram();
        //triangle
        void                                createTriangle(const sf::Vector2f& vertex1, const sf::Vector2f& vertex2, const sf::Vector2f& vertex3);
        void                                drawTriangle();
        void                                destroyTriangle();
        //rectangle
        void                                createRectangle(const sf::Vector2f& origin, const sf::Vector2f& rectSize);
        void                                drawRectangle();
        void                                destroyRectangle();


    private:
        int                                 m_ShaderProgram;
        struct                              Triangle{unsigned int VBO, VAO, EBO;} m_Triangle;
        struct                              Rectangle{unsigned int VBO, VAO, EBO;} m_Rectangle;

};

#endif // CHAPTERONE_H
