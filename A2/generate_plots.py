import numpy as np
from matplotlib import pylab as plt

omp = []
mpi = []
timings = [100,400,1000,2000,5000,10000]
with open('output.txt') as f:
    for arr in [omp, mpi]:
        for _ in timings:
            f.readline()
            s = f.readline().replace('ms', '').split(',')
            arr.append([float(s[0].strip()), float(s[1].strip())])
omp = np.array(omp)
mpi = np.array(mpi)
# print(omp)
# print(mpi)

plt.plot(timings, omp[:,0], label='OMP Matrix Multiplication')
plt.plot(timings, omp[:,1], label='OMP Gaussian Elimination')
plt.plot(timings, mpi[:,0], label='MPI Matrix Multiplication')
plt.plot(timings, mpi[:,1], label='MPI Gaussian Elimination')
# plt.xscale('log')
# plt.yscale('log')
plt.legend()
plt.grid()
plt.show()
