from frechet_distance_module import compute_single_threshold as similarity

c1 = [(0,0), (1,1)]
c2 = [(1,0), (2,1)] # c1 translated to the right.
distance = 1

assert(similarity(c1, c2, distance)      == True)
assert(similarity(c1, c2, distance-0.01) == False)
