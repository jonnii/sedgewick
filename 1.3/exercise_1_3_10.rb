# 1.3.10

# this is kinda shitty, doesn't handle whitespace or numbers larger than 9

def infix_to_postfix(k)
  stack = []
  operators = []
  k.each_char do |c|
    next if c == ' '
    
    if ['+', '-', '*'].include?(c)
      operators.push c
      next
    end
    
    if c == ')'
      raise 'no operator' if operators.length == 0
      stack.push operators.pop
    end
    
    stack.push c
  end
  stack.join('')
end

puts infix_to_postfix('(1 + 2)')
puts infix_to_postfix('((1 + 2) + (4 * 5))')