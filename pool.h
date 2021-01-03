#pragma once
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include <vector>
#include <functional>

struct vec2 {
    int x;
    int y;
    vec2() {
        x = 0;
        y = 0;
    }
    vec2(int _x, int _y) {
        x = _x;
        y = _y;
    }
};

class World {

private:
    static World* instance;
    
    static std::vector<vec2> Data;
    static std::vector<std::thread> Threads;
    static std::vector<std::pair<std::function<void(vec2)>, vec2>> Jobs;
    static std::mutex Mutex;
    static std::atomic<bool> Run;
    static void RunThreads();
    static void Test1(vec2 val);
    static void Test2(vec2 val);
    World() {};
public:
    World(World& object) = delete;
    void operator=(const World&) = delete;
    static World* GetInstance();
    static void StartThreads();
    static void StopThreads();
    static void AddJob(vec2 val,int test);
};