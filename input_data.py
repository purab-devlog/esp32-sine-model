import numpy as np
x_data = np.linspace(0, 2 * np.pi, 100).reshape(-1, 1)
np.savetxt('input_data.txt',x_data)
