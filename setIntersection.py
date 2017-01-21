'''
Python includes a data type for sets. Set objects  upport mathematical operations like union, intersection, difference, and symmetric difference.
https://docs.python.org/3/tutorial/datastructures.html 
'''


import sets
cheese = sets.Set('mild cheddar')
burger = sets.Set('chicken') 
print ''.join(cheese & burger) # set intersection