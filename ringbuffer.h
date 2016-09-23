#ifndef RINGBUFFER_H
#define RINGBUFFER_H

/*Insert in end of deque
 * take from front of deque
 */

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QMutexLocker>
#include <deque>

template <typename T>
class RingBuffer
{
    int size;
    std::deque<T>* buffer;
    int currentElement;
    QMutex* mutex;
public:
    explicit RingBuffer(int sz);
    ~RingBuffer();
    bool insertElement(const T &newElem);
    T& popElement(T &elem);

};


template <typename T>
RingBuffer<T>::RingBuffer(int sz)
{
    size = sz > 0 ? sz : 100;
    buffer = new std::deque<T>;
    currentElement = -1; //empty buffer
    mutex = new QMutex;
}

template <typename T>
RingBuffer<T>::~RingBuffer()
{
    qDebug() << "deleted buffer";
    buffer->clear();
    delete buffer;
    delete mutex;
}

//return false if buffer is full
template <typename T>
bool RingBuffer<T>::insertElement(const T &newElem)
{
    QMutexLocker locker(mutex);
    Q_UNUSED(locker)
    if (currentElement==size-1){ //full buffer
        return false;
    }
    ++currentElement;
    buffer->push_back(newElem);
    return true;
}

template <typename T>
T& RingBuffer<T>::popElement(T &elem)
{
    QMutexLocker locker(mutex);
    Q_UNUSED(locker)
    if (currentElement == -1) {
        return elem;
    }
    --currentElement;
    elem = buffer->front();
    buffer->pop_front();
    return elem;
}

#endif // RINGBUFFER_H
