import numpy as np
import matplotlib.pyplot as plt

#cpp = np.genfromtxt("noisysim.csv", delimiter=",").T
pyt = np.genfromtxt("simdata.csv", delimiter=",").T

#cpp_timings = cpp[0]
pyt_timings = pyt[0]

#cpp_phases = cpp[1:]
pyt_phases = pyt[1:]

plt.ion()
#axes_cpp = [plt.subplot2grid((5, 2), (i, 0)) for i in range(5)]
axes_pyt = [plt.subplot2grid((5, 2), (i, 1)) for i in range(5)]


def adjust_x(min, max):
    global axes_pyt #, axes_cpp
    for i in range(5):
        #axes_cpp[i].axis([min, max, 0, 1])
        axes_pyt[i].axis([min, max, 0, 1])

    plt.draw()

for i in range(5):
    #axes_cpp[i].plot(cpp_timings, cpp_phases[i])
    axes_pyt[i].plot(pyt_timings, pyt_phases[i])

plt.draw()
