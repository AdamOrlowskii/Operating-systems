#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <random>
#include <semaphore>

using namespace std;

int number_of_philosophers = 5; // 5 philosophers
mutex* forks;
counting_semaphore<>* table; // Semaphore

void philosopher(int id) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 5);

    while (true) {
        cout << "Philosopher " << id + 1 << " is thinking...\n";
        this_thread::sleep_for(chrono::seconds(dist(gen)));

        table->acquire(); // Taking a place on the table

        int left = id;
        int right = (id + 1) % number_of_philosophers;

        if (id % 2 == 0) {
            forks[left].lock();
            forks[right].lock();
        }
        else {
            forks[right].lock();
            forks[left].lock();
        }

        cout << "Philosopher " << id + 1 << " is eating...\n";
        this_thread::sleep_for(chrono::seconds(dist(gen)));

        forks[left].unlock();
        forks[right].unlock();

        table->release(); // Leaving the table

        cout << "Philosopher " << id + 1 << " finished eating and put down forks.\n";
    }
}

int main(int argc, char* argv[]) {

    if (argc > 1) {
        try {
            number_of_philosophers = stoi(argv[1]);
            if (number_of_philosophers < 2) {
                cerr << "Number of philosophers must be at least 2.\n";
                return 1;
            }
        }
        catch (...) {
            cerr << "Invalid argument. Please provide an integer.\n";
            return 1;
        }
    }

    // Dynamic allocation of the mutex and semaphore
    forks = new mutex[number_of_philosophers];
    table = new counting_semaphore<>(number_of_philosophers - 1);

    vector<thread> philosophers;
    for (int i = 0; i < number_of_philosophers; i++) {
        philosophers.emplace_back(philosopher, i);
    }

    for (auto& ph : philosophers) {
        ph.join();
    }

    delete[] forks;
    delete table;

    return 0;
}
