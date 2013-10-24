from nose.tools import *

from entropy import shannon_entropy


class TestShannonEntropy(object):
    def assert_entropy(self, data, expected):
        assert_almost_equal(shannon_entropy(data), expected, places=3)

    def test_0(self):
        self.assert_entropy('\x00' * 1024, 0.0)

    def test_f(self):
        self.assert_entropy('\xff' * 1024, 0.0)

    def test_alternate_0f(self):
        self.assert_entropy('\x00\xff' * 512, 0.125)

    def test_alternate_f0(self):
        self.assert_entropy('\xff\x00' * 512, 0.125)

    def test_alternate_0cf(self):
        self.assert_entropy('\x00\xcc\xff' * 512, 0.198)

    def test_one(self):
        self.assert_entropy(''.join(chr(i) for i in xrange(256)), 1.0)
