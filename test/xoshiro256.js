const test = require('tape')

const rand = require('../lib/prng')

test('xoshiro256**: 64-bit pseudorandom number generator', t => {
  t.plan(7)

  const a = rand.xoshiro256_ss().toString('hex')
  const b = rand.xoshiro256_ss().toString('hex')

  t.equal(a.length, 16, 'test A should be 4 bytes long')
  t.notEqual(a, '0000000000000000', 'test A should not be trivial')
  t.notEqual(a, 'ffffffffffffffff', 'test A should not be trivial')

  t.equal(b.length, 16, 'test B should be 4 bytes long')
  t.notEqual(b, '0000000000000000', 'test B should not be trivial')
  t.notEqual(b, 'ffffffffffffffff', 'test B should not be trivial')

  t.notEqual(a, b, 'both test results should be different')
})

test('xoshiro256+: 64-bit pseudorandom number generator', t => {
  t.plan(7)

  const a = rand.xoshiro256_p().toString('hex')
  const b = rand.xoshiro256_p().toString('hex')

  t.equal(a.length, 16, 'test A should be 8 bytes long')
  t.notEqual(a, '0000000000000000', 'test A should not be trivial')
  t.notEqual(a, 'ffffffffffffffff', 'test A should not be trivial')

  t.equal(b.length, 16, 'test B should be 8 bytes long')
  t.notEqual(b, '0000000000000000', 'test B should not be trivial')
  t.notEqual(b, 'ffffffffffffffff', 'test B should not be trivial')

  t.notEqual(a, b, 'both test results should be different')
})

test('xoshiro256++: 64-bit pseudorandom number generator', t => {
  t.plan(7)

  const a = rand.xoshiro256_pp().toString('hex')
  const b = rand.xoshiro256_pp().toString('hex')

  t.equal(a.length, 16, 'test A should be 8 bytes long')
  t.notEqual(a, '0000000000000000', 'test A should not be trivial')
  t.notEqual(a, 'ffffffffffffffff', 'test A should not be trivial')

  t.equal(b.length, 16, 'test B should be 8 bytes long')
  t.notEqual(b, '0000000000000000', 'test B should not be trivial')
  t.notEqual(b, 'ffffffffffffffff', 'test B should not be trivial')

  t.notEqual(a, b, 'both test results should be different')
})
