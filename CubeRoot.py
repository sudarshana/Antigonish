# Calculating cube root
# Seemed like a good idea at the time
# Months later... no idea how this works

x = int(input ('Can I has an integar please: '))
ans = 0
while ans ** 3 < abs (x):
    ans=ans + 1
if ans ** 3 < abs (x):
    ans = ans + 1
if ans ** 3 != abs (x):
    print (x, ' is not perfect cube. Duh!')
else:
    if x < 0:
        ans = -ans
    print ('Cube root be-eth', x, 'is', ans)
