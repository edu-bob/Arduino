#ifndef RAND_CACHE_H
#define RAND_CACHE_H

#define RANDCACHE_TTL 20ul
#define RANDCACHE_WINDOW 20ul
#define RANDCACHE_MAX 6

typedef struct {
  int key;
  int min;
  int max;
  unsigned long expiresAt;
  unsigned long lastUsed;
  int value;
} randcache_t;

class RandCache {
  public:
    void setup(void);
    void loop(void);
    int getRandom(int, int, int);
    void dumpCache(void);
    void setDebug(bool);
    void reset(void);

  private:
    bool debug;
    randcache_t cache[RANDCACHE_MAX];
};

#endif
