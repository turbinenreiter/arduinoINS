import numpy as np
import pylab


data = np.loadtxt('log.csv', delimiter=',')

ax = data[:,0]
ay = data[:,1]
az = data[:,2]

zero = []
k = 0
while k < 1024:
    if ax[k] < 300 and ay[k] < 300 and az[k] < 300:
        zero.append(0)
        k=k+1
    else:
        zero.append(1)
        k=k+1

#pylab.plot(ax)
#pylab.plot(ay)
#pylab.plot(az)
pylab.plot(zero)

pylab.show()
