# -*- coding: cp1251 -*-
from math import fabs
import time

import matplotlib.pyplot as plt
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter,
                               AutoMinorLocator)
import numpy as np
import csv

#time.sleep(5);

mas = []
mas1 = []
mas2 = []
x = []
y = []
size = 0
coordCount = 0

with open('../example.csv', 'r') as f:
    content = csv.reader(f, delimiter= ';')
    counter = 0
    for row in content:
      
      if(counter == coordCount):
          if(counter!=0):
            mas.append(mas1.copy())
            mas1.clear()
          counter = 0
          coordCount = float(row[0])
      else:
          mas2.append(float(row[0]))
          mas2.append(float(row[1]))
          mas1.append(mas2.copy())
          mas2.clear()
          counter+=1

mas.append(mas1.copy())
mas1.clear()

fig, ax = plt.subplots(figsize=(8, 6))


ax.set_xlabel("x")
ax.set_ylabel("y")
ax.grid(which="major", linewidth=1.2)
ax.grid(which="minor", linestyle="--", color="gray", linewidth=0.5)

maxX = []
maxY = []
minX = []
minY = []

labels = [ " ??????? ???????", "????????????", "?????????????"]
colorList = ["b", "r", "g", "m"]

for i in range(len(mas)):
    x=[]
    y=[]
    for j in range(len(mas[i])):
        x.append(mas[i][j][0])
        y.append(mas[i][j][1])
    if(i == 0):
        ax.plot(x, y, "r", linestyle="-", label = labels[i % len(labels)])
        maxX.append(max(x))
        maxY.append(max(y))
        minX.append(min(x))
        minY.append(min(y))
    else:
        ax.scatter(x, y, color = colorList[i%len(colorList)])

       
ax.legend()

minx = min(minX)
miny = min(minY)

maxx = max(maxX)
maxy = max(maxY)

ax.set_ylim([miny - fabs((maxy - miny)/10), maxy + fabs((maxy - miny)/10)])
ax.set_xlim([minx - fabs((maxx - minx)/10), maxx + fabs((maxx - minx)/10)])
#ax.legend()


ax.xaxis.set_minor_locator(AutoMinorLocator())
ax.yaxis.set_minor_locator(AutoMinorLocator())
ax.tick_params(which='major', length=10, width=2)
ax.tick_params(which='minor', length=5, width=1)

plt.show()