#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

class Counter : public QObject {
    Q_OBJECT

public:
    Counter(int startValue);

    int Increment();
    int Decrement();
    int value() const;

signals:
    void incremented();
    void decremented();

public slots:
    void onIncremented();
    void onDecremented();

private:
    int m_count;
};

#endif // COUNTER_H
