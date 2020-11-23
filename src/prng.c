// Xorshift algorithm for ultra-fast pseudorandom number generator
// https://en.wikipedia.org/wiki/Xorshift
// require NodeJS 12.11.0 or up for NAPI_VERSION 5

#define NAPI_VERSION 5

#include <node_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

static inline uint64_t rotl(const uint64_t x, int k) {
  return (x << k) | (x >> (64 - k));
}

static uint64_t x; /* The state can be seeded with any value. */

static inline uint64_t splitmix64() {
	uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

#define napi_fn(x) napi_value x(napi_env env, napi_callback_info info)

napi_fn(xorshift32);
napi_fn(xorshift64);
napi_fn(xoroshiro128_p);
napi_fn(xoroshiro128_pp);
napi_fn(xoroshiro128_ss);

static uint32_t _seed32;
static uint64_t _seed64;

static uint64_t ss[2];
static uint64_t pp[2];
static uint64_t p[2];

napi_value xorshift32(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  unsigned char *buf;
  unsigned char *out;

  // xorshift32 algorithm
  uint32_t n = _seed32;

  n ^= n << 13;
  n ^= n >> 17;
  n ^= n << 5;

  _seed32 = n;

  buf = (unsigned char*) &n;

  status = napi_create_buffer_copy(env, 4, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;

}

napi_value xorshift64(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  unsigned char *buf;
  unsigned char *out;

  // xorshift64 algorithm
  uint64_t n = _seed64;

  n ^= n << 13;
  n ^= n >> 7;
  n ^= n << 17;

  _seed64 = n;

  buf = (unsigned char*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}

static inline uint64_t xoroshiro128_ss_next(void) {
  const uint64_t s0 = ss[0];
  uint64_t s1 = ss[1];
  const uint64_t result = rotl(s0 * 5, 7) * 9;

  s1 ^= s0;
  ss[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
  ss[1] = rotl(s1, 37); // c

  return result;
}

napi_value xoroshiro128_ss(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  unsigned char *buf;
  unsigned char *out;

  uint64_t n = xoroshiro128_ss_next();
  buf = (unsigned char*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}

static inline uint64_t xoroshiro128_p_next(void) {
  const uint64_t s0 = p[0];
  uint64_t s1 = p[1];
  const uint64_t result = s0 + s1;

  s1 ^= s0;
  p[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
  p[1] = rotl(s1, 37); // c

  return result;
}

napi_value xoroshiro128_p(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  unsigned char *buf;
  unsigned char *out;

  uint64_t n = xoroshiro128_p_next();
  buf = (unsigned char*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}

static inline uint64_t xoroshiro128_pp_next(void) {
  const uint64_t s0 = pp[0];
  uint64_t s1 = pp[1];
  const uint64_t result = rotl(s0 + s1, 17) + s0;

  s1 ^= s0;
  pp[0] = rotl(s0, 49) ^ s1 ^ (s1 << 21); // a, b
  pp[1] = rotl(s1, 28); // c

  return result;
}

napi_value xoroshiro128_pp(napi_env env, napi_callback_info info) {
  napi_status status;
  napi_value retval;
  unsigned char *buf;
  unsigned char *out;

  uint64_t n = xoroshiro128_pp_next();
  buf = (unsigned char*) &n;

  status = napi_create_buffer_copy(env, 8, buf, &out, &retval);
  if (status != napi_ok) {
    return NULL;
  }

  return retval;
}

napi_value init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  time_t _t;

  srand((unsigned) time(&_t));

  x = (int) rand();

  _seed32 = (uint32_t)splitmix64();
  _seed64 = splitmix64();
  p[0] = splitmix64();
  p[1] = splitmix64();
  pp[0] = splitmix64();
  pp[1] = splitmix64();
  ss[0] = splitmix64();
  ss[1] = splitmix64();

  // create xorshift32 function
  status = napi_create_function(env, NULL, 0, xorshift32, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xorshift32", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xorshift64 function
  status = napi_create_function(env, NULL, 0, xorshift64, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xorshift64", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xoroshiro128+ function
  status = napi_create_function(env, NULL, 0, xoroshiro128_p, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xoroshiro128_p", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xoroshiro128++ function
  status = napi_create_function(env, NULL, 0, xoroshiro128_pp, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xoroshiro128_pp", fn);
  if (status != napi_ok) {
    return NULL;
  }

  // create xoroshiro128** function
  status = napi_create_function(env, NULL, 0, xoroshiro128_ss, NULL, &fn);
  if (status != napi_ok) {
    return NULL;
  }

  status = napi_set_named_property(env, exports, "xoroshiro128_ss", fn);
  if (status != napi_ok) {
    return NULL;
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)
