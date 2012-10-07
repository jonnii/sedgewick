# 1.3.4

def balanced(parentheses)
  stack = []
  parentheses.each_char do |p|
    if ['[', '{', '('].include?(p)
      stack.push p
    elsif stack.length == 0
      return false
    elsif p == ')' && stack.pop != '('
      return false
    elsif p == ']' && stack.pop != '['
      return false
    elsif p == '}' && stack.pop != '{'
      return false
    end
  end
  true
end

puts balanced("[()]{}{[()()]}")
puts balanced("[(])")
puts balanced(")")