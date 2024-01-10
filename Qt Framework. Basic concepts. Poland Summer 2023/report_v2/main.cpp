#include <iostream>
#include "counter.h"
#include <QCoreApplication>

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Create two counters with a different starting value
    Counter counter1(5);
    Counter counter2(10);

    // Connect signals and slots
    QObject::connect(&counter1, SIGNAL(incremented()), &counter2, SLOT(onIncremented()));
    QObject::connect(&counter2, SIGNAL(incremented()), &counter1, SLOT(onIncremented()));

    QObject::connect(&counter1, SIGNAL(decremented()), &counter2, SLOT(onDecremented()));
    QObject::connect(&counter2, SIGNAL(decremented()), &counter1, SLOT(onDecremented()));

    // Execute Increment() of the first counter
    counter1.Increment();
    // Display values of both counters
    std::cout << "Counter 1: " << counter1.value() << ", Counter 2: " << counter2.value() << std::endl;

    // Execute Increment() of the second counter
    counter2.Increment();
    // Display values of both counters
    std::cout << "Counter 1: " << counter1.value() << ", Counter 2: " << counter2.value() << std::endl;

    // Execute Decrement() of the first counter
    counter1.Decrement();
    // Display values of both counters
    std::cout << "Counter 1: " << counter1.value() << ", Counter 2: " << counter2.value() << std::endl;

    // Execute Decrement() of the second counter
    counter2.Decrement();
    // Display values of both counters
    std::cout << "Counter 1: " << counter1.value() << ", Counter 2: " << counter2.value() << std::endl;

    return 0;
}
