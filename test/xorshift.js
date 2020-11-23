const test = require('tape')

const rand = require('../lib/prng')

test('Xorshift32: 32-bit pseudorandom number generator', t => {
  t.plan(7)

  const a = rand.xorshift32().toString('hex')
  const b = rand.xorshift32().toString('hex')

  t.equal(a.length, 8, 'test A should be 4 bytes long')
  t.notEqual(a, '0000000000000000', 'test A should not be trivial')
  t.notEqual(a, 'ffffffffffffffff', 'test A should not be trivial')

  t.equal(b.length, 8, 'test B should be 4 bytes long')
  t.notEqual(b, '0000000000000000', 'test B should not be trivial')
  t.notEqual(b, 'ffffffffffffffff', 'test B should not be trivial')

  t.notEqual(a, b, 'both test results should be different')
})

test('Xorshift64: 64-bit pseudorandom number generator', t => {
  t.plan(7)

  const a = rand.xorshift64().toString('hex')
  const b = rand.xorshift64().toString('hex')

  t.equal(a.length, 16, 'test A should be 8 bytes long')
  t.notEqual(a, '0000000000000000', 'test A should not be trivial')
  t.notEqual(a, 'ffffffffffffffff', 'test A should not be trivial')

  t.equal(b.length, 16, 'test B should be 8 bytes long')
  t.notEqual(b, '0000000000000000', 'test B should not be trivial')
  t.notEqual(b, 'ffffffffffffffff', 'test B should not be trivial')

  t.notEqual(a, b, 'both test results should be different')
})
