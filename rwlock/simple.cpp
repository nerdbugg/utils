/* borrowed code from https://eli.thegreenplace.net/2019/implementing-reader-writer-locks/ */

#include <cstdio>
#include <mutex>

class RWLock {
public:
  RWLock() {
    read_num_ = 0;
  }
  ~RWLock() = default;

  // NOTE: reader is prefered
  void readLock() {
    lock_.lock();
    read_num_++;
    lock_.unlock();
  }

  // blocked version
  void readUnlock() {
    lock_.lock();
    read_num_--;
    lock_.unlock();
  }

  // NOTE: during writer waiting, reader could grab lock
  // the lock is reader-prefered
  void writeLock() {
    lock_.lock();
    while (read_num_>0) {
      lock_.unlock();
    }

    // read_num_==0, no reader and lock is setted
  }

  void writeUnlock() {
    lock_.unlock();
  }

private:
  std::mutex lock_;
  int read_num_;
};

int main (int argc, char *argv[]) {
  RWLock rwlock;
  printf("read lock: \n");
  rwlock.readLock();
  printf("read lock: \n");
  rwlock.readLock();
  printf("read lock: \n");
  rwlock.readLock();

  printf("read unlock\n");
  rwlock.readUnlock();
  printf("read unlock\n");
  rwlock.readUnlock();
  printf("read unlock\n");
  rwlock.readUnlock();

  printf("write lock: \n");
  rwlock.writeLock();

  printf("write unlock\n");
  rwlock.writeUnlock();

  printf("write lock: \n");
  rwlock.writeLock();

  printf("write unlock\n");
  rwlock.writeUnlock();
  return 0;
}
