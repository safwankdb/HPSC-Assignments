import numpy as np
from matplotlib import pylab as plt
import seaborn as sns

cuda = []
cuda_thread = []
omp = []
mpi = []
timings = [100, 400, 800, 1000, 2000, 4000, 6000, 8000, 10000]
threads = [1, 4, 8, 16, 32, 64, 256, 512, 1024]
with open('output.txt') as f:
    for arr in [cuda]:
        for _ in timings:
            f.readline()
            s = f.readline().replace('ms', '')
            arr.append(float(s.strip()))
    for arr in [cuda_thread]:
        for _ in threads:
            f.readline()
            s = f.readline().replace('ms', '')
            arr.append(float(s.strip()))

with open('../A2/output.txt') as f:
    for arr in [omp, mpi]:
        for _ in timings:
            f.readline()
            s = f.readline().replace('ms', '').split(',')
            arr.append([float(s[0].strip()), float(s[1].strip())])

cuda = np.array(cuda)
cuda_thread = np.array(cuda_thread)
omp = np.array(omp)
mpi = np.array(mpi)

sns.set_theme()
plt.figure(figsize=(8, 6))
plt.title('Matrix Multiplication')
plt.plot(timings, cuda/1000, color='#76b900', label='CUDA')
plt.plot(timings, omp[:, 0]/1000, color='r', label='OMP')
plt.plot(timings, mpi[:, 0]/1000, color='b', label='MPI')
# plt.xscale('log')
# plt.yscale('log')
plt.legend()
plt.ylabel("Time in sec")
plt.xlabel("Size of Matrix N")
plt.tight_layout()
plt.savefig('report/1.png')
# plt.show()

plt.figure(figsize=(8, 6))
plt.title('Matrix Multiplication')
plt.plot(timings, cuda, color='#76b900', label='CUDA')
plt.plot(timings, omp[:, 0], color='r', label='OMP')
plt.plot(timings, mpi[:, 0], color='b', label='MPI')
# plt.xscale('log')
plt.yscale('log')
plt.legend()
plt.ylabel("Time in ms")
plt.xlabel("Size of Matrix N")
plt.tight_layout()
plt.savefig('report/2.png')

plt.figure(figsize=(8, 6))
plt.title('CUDA for N=2500')
plt.plot(threads, cuda_thread/1000, color='#76b900', label="Matrix Multiplication")
plt.xscale('log')
plt.ylabel("Time in sec")
plt.xlabel("Threads per Block")
plt.tight_layout()
plt.savefig('report/3.png')

