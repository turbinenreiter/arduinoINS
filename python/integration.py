import os
import numpy as np
from scipy import integrate as spi
from pylab import *

acc = []
t=arange(0, 10.24, 0.01)

fn = os.path.join(os.path.dirname(os.path.realpath(__file__)), 'data')
print fn
with open(fn) as f:
    data = f.readlines()

for value in data:
    value_acc = ((int(value)-128)/30.0)*9.81 #calibration
    acc.append(value_acc)

dist = spi.cumtrapz(acc, t)

plt.figure(1)
plt.plot(acc)
plt.plot(dist)
#plt.xlabel('t[s]')
#plt.ylabel('acc [g]')
#plt.title('acceleration in x-direction')
#plt.legend(['acc'], loc = 'lower right')
plt.show()
