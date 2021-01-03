#include "pool.h"


int main()
{
    World* world = World::GetInstance();
    for (int i = 0; i < 1000; i++) {
        world->AddJob(vec2(i, (int)i / 2), i % 2);
    }
    world->StartThreads();
    world->StopThreads();
    return 0;
}
