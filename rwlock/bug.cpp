#include <cstdio>
#include <atomic>

class RWLock {
public:
  RWLock() = default;
  ~RWLock() = default;

  bool tryReadLock() {
    int locked = lock_.load();

    if(locked==1) {
      return false;
    }

    // BUG: if reached here, and a write lock set locked?
    int prev_read = read_num_.fetch_add(1);
    return true;
  }

  void readUnlock() {
    read_num_.fetch_sub(1);
  }

  bool tryWriteLock() {
    int locked = lock_.exchange(1);

    if(locked==1) {
      return false;
    }

    // BUG: before read lock set the read_num_
    // reader and writer all get lock
    int prev_read = read_num_.load();
    if(prev_read>0) {
      return false;
    }

    return true;
  }

  void writeUnlock() {
    lock_.store(0);
  }

private:
  std::atomic_int lock_;
  std::atomic_int read_num_;
};

int main (int argc, char *argv[]) {
  RWLock rwlock;
  printf("try read lock: %d\n", rwlock.tryReadLock());
  printf("try read lock: %d\n", rwlock.tryReadLock());
  printf("try read lock: %d\n", rwlock.tryReadLock());
  printf("try write lock: %d\n", rwlock.tryWriteLock());

  printf("read unlock\n");
  rwlock.readUnlock();
  printf("read unlock\n");
  rwlock.readUnlock();
  printf("read unlock\n");
  rwlock.readUnlock();

  printf("write unlock\n");
  rwlock.writeUnlock();

  printf("try write lock: %d\n", rwlock.tryWriteLock());
  return 0;
}
