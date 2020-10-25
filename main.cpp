#include "Engine.h"
#include "chapter_1/Chapter_1.h"

int main()
{
    Engine engine;
        engine.setScene(std::unique_ptr<Chapter_1>(new Chapter_1()));
    engine.run();

    return 0;
}
