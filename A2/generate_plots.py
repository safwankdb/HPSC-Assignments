import numpy as np
from matplotlib import pylab as plt
import seaborn as sns

omp = []
mpi = []
mpi_thread = []
omp_thread = []
timings = [100, 400, 800, 1000, 2000, 4000, 6000, 8000, 10000]
threads = list(range(2, 9))
with open('output.txt') as f:
    for arr in [omp, mpi]:
        for _ in timings:
            f.readline()
            s = f.readline().replace('ms', '').split(',')
            arr.append([float(s[0].strip()), float(s[1].strip())])
    for arr in [mpi_thread, omp_thread]:
        for _ in threads:
            f.readline()
            s = f.readline().replace('ms', '').split(',')
            arr.append([float(s[0].strip()), float(s[1].strip())])

omp = np.array(omp)
mpi = np.array(mpi)
mpi_thread = np.array(mpi_thread)
omp_thread = np.array(omp_thread)

sns.set_theme()
plt.figure(figsize=(12, 6))
plt.subplot(121)
plt.title('Matrix Multiplication')
plt.plot(timings, omp[:, 0], color='r', label='OMP')
plt.plot(timings, mpi[:, 0], color='b', label='MPI')
# plt.xscale('log')
plt.yscale('log')
plt.legend()
plt.ylabel("Time in ms")
plt.xlabel("Size of Matrix N")

plt.subplot(122)
plt.title('Gaussian Elimination')
plt.plot(timings, omp[:, 1], color='r', label='OMP')
plt.plot(timings, mpi[:, 1], color='b', label='MPI')
# plt.xscale('log')
plt.yscale('log')
plt.legend()
plt.ylabel("Time in ms")
plt.xlabel("Size of Matrix N")
plt.tight_layout()
plt.savefig('report/1.png')
# plt.show()

plt.figure(figsize=(12, 6))
plt.subplot(122)
plt.title('MPI for N=2500')
plt.plot(threads, mpi_thread[:, 0], color='r', label="Matrix Multiplication")
plt.plot(threads, mpi_thread[:, 1], color='b', label="Gaussian Elimination")
plt.legend()
plt.ylabel("Time in ms")
plt.xlabel("Number of Processors")

plt.subplot(121)
plt.title('OMP for N=2500')
plt.plot(threads, omp_thread[:, 0], color='r', label="Matrix Multiplication")
plt.plot(threads, omp_thread[:, 1], color='b', label="Gaussian Elimination")
plt.legend()
plt.ylabel("Time in ms")
plt.xlabel("Number of Processors")
plt.tight_layout()
plt.savefig('report/2.png')
# plt.show()
