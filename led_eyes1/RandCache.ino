#include "RandCache.h"

void RandCache::setup()
{
  debug = 0;
  reset();
}

void RandCache::reset()
{
  for( int i=0; i<RANDCACHE_MAX; i++ ) {
    cache[i].key = -1;
    cache[i].expiresAt= 0ul;
    cache[i].min = 0;
    cache[i].max = 0;
    cache[i].value = 0;
  }
}

void RandCache::loop()
{

}

void RandCache::setDebug(bool _debug)
{
  debug = _debug;
}
void RandCache::dumpCache()
{
  for ( int i=0; i<RANDCACHE_MAX; i++) {
    Serial.print(i);Serial.print(F(":\t"));Serial.print(cache[i].key);Serial.print(F("\t"));
    Serial.print(cache[i].min);Serial.print(F("/"));Serial.print(cache[i].max);Serial.print(F("\t"));
    Serial.print(cache[i].value);Serial.print(F("\t"));Serial.println(cache[i].expiresAt);
    //delay(500);
  }
  Serial.println(F("------------------------"));
}
/**
 * random - get a random number, given a cache key and a min/max value
 *   key ....... non-negative integer, used to identify a cached random number
 * 
 * When requesting a random number between two values, return the cached value if
 *  the key, min, and max match and the exxpiration is in the future 
 */
int RandCache::getRandom(int key, int min, int max)
{
  if ( debug ) {
    Serial.print(F("key=") );Serial.print(key);Serial.print(F(" min="));Serial.print(min);
    Serial.print(F(" max="));Serial.print(max);Serial.print(F(" millis="));Serial.println(millis());
  }    
  for ( int i=0;i<RANDCACHE_MAX;i++ ) {

    // Check if this entry matches the given key
    if ( cache[i].key == key ) {

      // Check for cache hit
      if( cache[i].min==min && cache[i].max==max && cache[i].expiresAt > millis() ) {
        if ( debug ) {
          Serial.print(F("Cache hit slot "));Serial.print(i);Serial.print(F(" on key "));Serial.println(key);
        }
        cache[i].expiresAt = millis() + RANDCACHE_TTL;
        return cache[i].value;
      } else {
        // the key exists, but other params are wrong, so fix this entry 
        if ( debug ) {
          Serial.print(F("Updating entry "));Serial.print(i);Serial.print(F(" for key "));Serial.println(key);
          Serial.print(F("WAS: min="));Serial.print(cache[i].min);Serial.print(F(" max="));Serial.print(cache[i].max);
          Serial.print(F(" expiresAt="));Serial.print(cache[i].expiresAt);Serial.print(F("/"));Serial.println(millis());
        }
        cache[i].min = min;
        cache[i].max = max;
        cache[i].value = random(min,max);
        cache[i].expiresAt = millis() + RANDCACHE_TTL;
        return cache[i].value;
      }
    }
  }

  // if here, did not find the given key in the cache, find an unused or expired slot
  for ( int i=0; i<RANDCACHE_MAX; i++ ) {
    if ( cache[i].key < 0 || millis() > cache[i].expiresAt ) {
      cache[i].key = key;
      cache[i].min = min;
      cache[i].max = max;
      cache[i].expiresAt = millis() + RANDCACHE_TTL;
      cache[i].value = random(min,max);
      if ( debug ) {
        Serial.print(F("Adding new entry "));Serial.print(i);Serial.print(F(" for key "));Serial.print(key);Serial.print(F(" value "));Serial.println(cache[i].value);
      }
      return cache[i].value;
    }
  }
  // if get here, no cache slots available, might fix itself once a slot expires
  // but increase RANDCACHE_MAX 
  Serial.println(F("No randcache slots available"));
  return random(min,max);
}
