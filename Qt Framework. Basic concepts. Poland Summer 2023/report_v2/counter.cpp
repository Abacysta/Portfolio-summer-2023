#include "counter.h"

Counter::Counter(int startValue) : m_count(startValue) {}

int Counter::Increment() {
    m_count++;
    emit incremented();
    return m_count;
}

int Counter::Decrement() {
    m_count--;
    emit decremented();
    return m_count;
}

int Counter::value() const {
    return m_count;
}

void Counter::onIncremented() {
    m_count++;
}

void Counter::onDecremented() {
    m_count--;
}
