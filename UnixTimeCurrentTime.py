# Reading Unix time/ POSIX time/Epoch time and converting it into current time 


import time
timestamp = int(time.time()) 
print timestamp #This is the Unix time in a string format like "1482823748"
local_time = time.localtime(timestamp) # This is the local time in a format like (tm_year=2016, tm_mon=12, tm_mday=26, tm_hour=23, tm_min=29, tm_sec=8, tm_wday=0, tm_yday=361, tm_isdst=0
print(time.strftime("%Y-%m-%d %H:%M:%S", local_time))  #Formating the local time to make it readable
