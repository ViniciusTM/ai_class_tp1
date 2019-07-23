import numpy as np
import sys

if __name__ == "__main__":
	np.random.seed(8787)

	n = int(sys.argv[1])
	m = int(sys.argv[2])

	baseConfig = [i for i in range(1, n**2)] + [-1]
	array = np.array([np.random.permutation(baseConfig) for i in range(m)])
	np.savetxt("instancias/{:d}-{:d}.txt".format(n, m), array, "%d", " ")
