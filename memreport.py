#!/usr/bin/env python3

import matplotlib.pyplot as plt

report_file = open("memstat.data", "rt")

size = []
resident = []
shared =[]
text = []
data = []

for line in report_file.readlines():
    fileds = line.strip().split(" ")
    size.append(int(fileds[0]))
    resident.append(int(fileds[1]))
    shared.append(int(fileds[2]))
    text.append(int(fileds[3]))
    data.append(int(fileds[5]))

time = list(range(len(size)))

plt.plot(time, size, label="Total virtual memory")
plt.plot(time, resident, label="Estimated physical memory")
plt.plot(time, shared, label="Shared pages")
plt.plot(time, text, label="Text section")
plt.plot(time, data, label="Data section")
plt.legend()
plt.show()
