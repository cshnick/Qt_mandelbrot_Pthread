#ifndef COMPUTINGTHREAD_H
#define COMPUTINGTHREAD_H

#include "thread.h"
#include <QSize>

#define FOREVER for(;;)

class QImage;




class ComputingThread : public pthr::Thread
{

public:
    ComputingThread();
    ~ComputingThread();

    void render(double centerX, double centerY, double scaleFactor,
                QSize resultSize);

    void Execute();
    bool isRunning() {return started;}

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
