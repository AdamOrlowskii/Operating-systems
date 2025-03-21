#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

const int number_of_philosophers = 5; // 5 philosophers
mutex forks[number_of_philosophers]; // 5 forks

void philosopher(int id) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000);

    while (true) {

        // thinking
        cout << "Philosopher " << id << " is thinking...\n";
        this_thread::sleep_for(chrono::milliseconds(dist(gen)));

        // picking up forks
        int left = id;
        int right = (id + 1) % number_of_philosophers;




    }

}

int main()
{

}
