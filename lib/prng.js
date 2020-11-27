const addon = require('bindings')('prng')

module.exports = {
  xorshift32() {
    return addon.xorshift32()
  },
  xorshift64() {
    return addon.xorshift64()
  },
  xoroshiro128_p() {
    return addon.xoroshiro128_p()
  },
  xoroshiro128_pp() {
    return addon.xoroshiro128_pp()
  },
  xoroshiro128_ss() {
    return addon.xoroshiro128_ss()
  },
  xoshiro256_p() {
    return addon.xoshiro256_p()
  },
  xoshiro256_pp() {
    return addon.xoshiro256_pp()
  },
  xoshiro256_ss() {
    return addon.xoshiro256_ss()
  },
}
