# 1.1.35

SIDES = 6
NUM_DICE = 2

# populate number of rolls 
def build_distribution
  dist = Array.new(NUM_DICE * SIDES + 1, 0)
  (1..SIDES).each do |i|
    (1..SIDES).each do |j|
      dist[i+j] += 1
    end
  end

  # normalize to a probability
  (NUM_DICE..NUM_DICE * SIDES).each do |k|
    dist[k] = dist[k].to_f / 36.to_f
  end
  dist
end

def roll_one
  1 + rand(SIDES)
end

def roll
  3.times.select{|i| i}
  NUM_DICE.times.map { |i| roll_one }.inject {|sum, x| sum + x }
end

def simulate(n=10)
  simulation = Array.new(NUM_DICE * SIDES + 1, 0)
  n.times do
    simulation[roll] += 1
  end
  
  (NUM_DICE..NUM_DICE * SIDES).each do |k|
    simulation[k] = simulation[k].to_f / n
  end
  
  simulation
end

def compare(expected, actual)
  expected_mult = expected.map {|e| (e * 1000).to_i }
  actual_mult = actual.map { |e| (e * 1000).to_i }
  
  expected_mult.zip(actual_mult) do |e, a|
    puts "#{e} -- #{a}"
  end
  
  puts actual_mult.sort == expected_mult.sort
end

compare(build_distribution, simulate(4000000))