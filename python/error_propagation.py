import numpy as np
from scipy import integrate as i
from pylab import *

t = np.arange(0,100,1)
acc = np.empty(100); acc.fill(10)
acc_error = acc + 1
dist = i.cumtrapz(acc, t)
dist_error = i.cumtrapz(acc_error, t)

acc_diff = acc_error - acc
dist_diff = dist_error - dist

plt.figure(1)
plt.plot(acc)
plt.plot(acc_error)
plt.axis([0, 100, 0, 12])
plt.xlabel('t')
plt.ylabel('acceleration')
plt.title('acceleration with error')
plt.legend(['acc', 'acc+error'], loc = 'lower right')
plt.savefig('acc.pdf')

plt.figure(2)
plt.plot(dist)
plt.plot(dist_error)
plt.axis([0, 100, 0, 1200])
plt.xlabel('t')
plt.ylabel('distance')
plt.title('distance with error')
plt.legend(['dist', 'dist+error'], loc = 'lower right')
plt.savefig('dist.pdf')

plt.figure(3)
plt.plot(acc_diff)
plt.plot(dist_diff)
plt.axis([0, 100, 0, 100])
plt.xlabel('t')
plt.ylabel('difference')
plt.title('difference between INS and real position')
plt.legend(['diff of acc', 'diff of pos'], loc = 'lower right')
plt.savefig('diff.pdf')
