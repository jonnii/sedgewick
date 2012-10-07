1.1.14
======
write a static method lg() that takes an int value N as argument and returns 
the large int not larger than teh base-2 logarithm of N. Do not use Math.

The log base 2 of an integer is the same as the position of the highest bit set 
or most significant bit set, MSB.

unsigned int v; // 32-bit word to find the log base 2 of
unsigned int r = 0; // r will be lg(v)

while (v >>= 1) // unroll for more speed...
{
  r++;
}

more here: http://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious

1.1.25
======
Use mathematical induction to prove that Euclid's algorithm computes the
greatest common divisor of any pair of non-negative integers p and q.

http://calculus.nipissingu.ca/tutorials/induction.html
http://www.cut-the-knot.org/blue/Euclid.shtml
