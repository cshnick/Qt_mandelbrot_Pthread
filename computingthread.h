#ifndef COMPUTINGTHREAD_H
#define COMPUTINGTHREAD_H

#include "thread.h"
#include "sigslot.h"
#include <QSize>

#define FOREVER for(;;)
using namespace sigslot;

class QImage;


class MyThread: public pthr::Thread{
public:
  // Инициализируем в false флаг завершения в конструкторе
  MyThread() : __done(false) {}
  virtual void Execute() {
    // В процессе работы потока меняем флаг завершения на истину
    __done = true;
  }
  // Функция, возвращающая значение флага завершение
  bool done() const { return __done; }
private:
  bool __done;
};


class ComputingThread : public pthr::Thread
{

public:
    ComputingThread();
    ~ComputingThread();

    void render(double centerX, double centerY, double scaleFactor,
                QSize resultSize);

    void Execute();
    bool isRunning() {return started;}
    signal2<const QImage&, double> img;


private:
    uint rgbFromWaveLength(double wave);

    pthr::Mutex mutex;
    pthr::WaitCondition condition;
    double centerX;
    double centerY;
    double scaleFactor;
    QSize resultSize;
    bool restart;
    bool abort;
    bool started;

    enum { ColormapSize = 512 };
    uint colormap[ColormapSize];
};

#endif // COMPUTINGTHREAD_H
