import numpy as np
from pylab import *

acc = []

with open('data.txt') as f:
    data = f.readlines()

for value in data:
    value_acc = ((int(value))-128)/30.0
    acc.append(value_acc)

plt.figure(1)
plt.plot(acc)
#plt.axis([0, 100, 0, 100])
plt.xlabel('t[s]')
plt.ylabel('acc [g]')
plt.title('acceleration in x-direction')
plt.legend(['acc'], loc = 'lower right')
plt.savefig('acc_sens.png')
