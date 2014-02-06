#include "thread.h"

namespace pthr {

static void ThreadCallback(Thread* who) {
  int old_thread_type;
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old_thread_type);
  who->Execute();
}

Thread::~Thread() {
}

//extern "C"
typedef void *(*pthread_callback)(void *);

void Thread::Start() {
  pthread_create(
    &__handle, 0,
    reinterpret_cast<pthread_callback>(ThreadCallback),
    this
  );
}

void Thread::Join() {
  pthread_join(__handle, 0);
}

void Thread::Kill() {
  pthread_cancel(__handle);
}

} // namespace pthr
