const test = require('tape')

const rand = require('../lib/prng')

test('xoroshiro128**: 64-bit pseudorandom number generator', t => {
  t.plan(7)

  const a = rand.xoroshiro128_ss().toString('hex')
  const b = rand.xoroshiro128_ss().toString('hex')

  t.equal(a.length, 16, 'test A should be 4 bytes long')
  t.notEqual(a, '0000000000000000', 'test A should not be trivial')
  t.notEqual(a, 'ffffffffffffffff', 'test A should not be trivial')

  t.equal(b.length, 16, 'test B should be 4 bytes long')
  t.notEqual(b, '0000000000000000', 'test B should not be trivial')
  t.notEqual(b, 'ffffffffffffffff', 'test B should not be trivial')

  t.notEqual(a, b, 'both test results should be different')
})

test('xoroshiro128+: 64-bit pseudorandom number generator', t => {
  t.plan(7)

  const a = rand.xoroshiro128_p().toString('hex')
  const b = rand.xoroshiro128_p().toString('hex')

  t.equal(a.length, 16, 'test A should be 8 bytes long')
  t.notEqual(a, '0000000000000000', 'test A should not be trivial')
  t.notEqual(a, 'ffffffffffffffff', 'test A should not be trivial')

  t.equal(b.length, 16, 'test B should be 8 bytes long')
  t.notEqual(b, '0000000000000000', 'test B should not be trivial')
  t.notEqual(b, 'ffffffffffffffff', 'test B should not be trivial')

  t.notEqual(a, b, 'both test results should be different')
})

test('xoroshiro128++: 64-bit pseudorandom number generator', t => {
  t.plan(7)

  const a = rand.xoroshiro128_pp().toString('hex')
  const b = rand.xoroshiro128_pp().toString('hex')

  t.equal(a.length, 16, 'test A should be 8 bytes long')
  t.notEqual(a, '0000000000000000', 'test A should not be trivial')
  t.notEqual(a, 'ffffffffffffffff', 'test A should not be trivial')

  t.equal(b.length, 16, 'test B should be 8 bytes long')
  t.notEqual(b, '0000000000000000', 'test B should not be trivial')
  t.notEqual(b, 'ffffffffffffffff', 'test B should not be trivial')

  t.notEqual(a, b, 'both test results should be different')
})
