#include "pool.h"

World* World::instance = nullptr;
std::vector<vec2> World::Data;
std::vector<std::thread> World::Threads;
std::vector<std::pair<std::function<void(vec2)>, vec2>> World::Jobs;
std::mutex World::Mutex;
std::atomic<bool> World::Run = true;

void World::StartThreads()
{
	for (int i = 0; i < 5; i++) {
		Threads.push_back(std::thread(RunThreads));
	}
}

void World::StopThreads()
{
	for (auto& thread : Threads)
		thread.join();
}

World* World::GetInstance()
{
	if (instance == nullptr)
		instance = new World();
	return instance;
}

void World::RunThreads() {
	while (Run) {
		Mutex.lock();
		if (Jobs.size() > 0) {
			std::cout << "Jobs to do!" << std::endl;
			auto tmp = Jobs.back();
			Jobs.pop_back();
			Mutex.unlock();
			tmp.first(tmp.second);
			continue;
		} else {
			Mutex.unlock();
		}
	}
}

void World::Test1(vec2 vec) {
	Mutex.lock();
	Data.push_back(vec);
	Mutex.unlock();
}
void World::Test2(vec2 vec) {
	vec.x *= 2;
	vec.y *= 8;
	Mutex.lock();
	Data.push_back(vec);
	Mutex.unlock();
}

void World::AddJob(vec2 val,int test) {
	Mutex.lock();
	std::function<void(vec2)> func;
	switch (test)
	{
	case 1: 
		func = &Test1;
		break;
	default:
		func = &Test2;
		break;
	}
	auto tmp = std::make_pair(func, val);
	Jobs.push_back(tmp);
	Mutex.unlock();
}

