# 1.2.16

def gcd(p, q)
  return p if q == 0
  gcd(q, p % q)
end

class Rational
  
  def initialize(numerator, denominator)
    g = gcd(numerator, denominator)
    
    self.numerator = numerator / g
    self.denominator = denominator / g
  end
  
  attr_accessor :numerator
  attr_accessor :denominator
  
  def plus(rational)
    n = (self.numerator * rational.denominator) + (self.denominator * rational.numerator)
    d = self.denominator * rational.denominator
    Rational.new(n, d)
  end
  
  def minus(rational)
    n = (self.numerator * rational.denominator) - (self.denominator * rational.numerator)
    d = self.denominator * rational.denominator
    Rational.new(n, d)
  end
  
  def times(rational)
    n = self.numerator * rational.numerator
    d = self.denominator * rational.denominator
    Rational.new(n, d)
  end
  
  def divide(rational)
    n = (self.numerator * rational.denominator)
    d = (self.denominator * rational.numerator)
    Rational.new(n, d)
  end
  
  def equals?(that)
    that.numerator == self.numerator && 
    that.denominator == self.denominator
  end
  
  def to_s
    "#{numerator}/#{denominator}"
  end
  
end

a = Rational.new(1,4)
b = Rational.new(1,4)
c = Rational.new(1,2)

puts a
puts b
puts a.equals?(b)

puts "#{a} + #{b} = #{a.plus(b)}"
puts "#{c} - #{a} = #{c.minus(a)}"
puts "#{a} . #{b} = #{a.times(b)}"
puts "#{a} / #{b} = #{a.divide(b)}"
