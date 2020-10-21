#ifndef CHAPTER_1_H
#define CHAPTER_1_H

#include "Scene.h"


class Chapter_1 : public Scene
{
    public:
        /** Default constructor */
        Chapter_1();
        /** Default destructor */
        virtual ~Chapter_1();

    public:
        virtual void                init();
        virtual void                render();
        virtual void                destroy();

    protected:

    private:
        int shaderProgram;
        unsigned int VBO, VAO, EBO;
};

#endif // CHAPTER_1_H
