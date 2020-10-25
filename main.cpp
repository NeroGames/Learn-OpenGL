#include "Engine.h"
#include "chapter_2/ChapterTwo.h"

int main()
{
    Engine engine;
        engine.setScene(std::unique_ptr<ChapterTwo>(new ChapterTwo()));
    engine.run();

    return 0;
}
