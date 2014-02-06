#ifndef THREAD_H
#define THREAD_H

#include "pthread.h"

namespace pthr {

typedef pthread_t ThreadType;

class Mutex {
    typedef pthread_mutex_t mutex_t;

public:
    Mutex() {pthread_mutex_init(__handle, NULL);}
    ~Mutex() {pthread_mutex_destroy(__handle);}

    void lock() {pthread_mutex_lock(__handle);}
    void unlock() {pthread_mutex_unlock(__handle);}

private:
    mutex_t *__handle;
    friend class WaitCondition;
};

class WaitCondition {
public:
    typedef pthread_cond_t cond_t;
    WaitCondition() {pthread_cond_init(__handle, NULL);}
    ~WaitCondition() {pthread_cond_destroy(__handle);}

    void wakeOne() {pthread_cond_signal(__handle);}
    void wakeAll() {pthread_cond_broadcast(__handle);}
    int wait(Mutex *p_mutex) {return pthread_cond_wait(__handle, p_mutex->__handle);}

private:
    cond_t *__handle;
};

class Thread {

public:
  Thread() {}
  virtual ~Thread();
  void Start();
  virtual void Execute() = 0;
  void Join();
  void Kill();

private:
  ThreadType __handle;

  Thread(const Thread&);
  void operator=(const Thread&);
};

} // namespace pthr {

#endif // THREAD_H
