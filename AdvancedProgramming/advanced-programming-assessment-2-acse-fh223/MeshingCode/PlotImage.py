import pandas as pd
import matplotlib.pyplot as plt

# Read csv files
ini_opt_errors = pd.read_csv('ini_opt_errors.csv')
search_times = pd.read_csv('search_times.csv')

# Create a figure and a set of subplots
fig, ax1 = plt.subplots(figsize=(10, 6))

# Set x-axis
x = ini_opt_errors['NodeCount']

# Draw errors on the first y-axis
ax1.plot(x, ini_opt_errors['iniTempError'], label='Initial Temp Error', color='tab:blue', marker='o')
ax1.plot(x, ini_opt_errors['optTempError'], label='Optimized Temp Error', color='tab:green', marker='x')
ax1.plot(x, ini_opt_errors['iniPressError'], label='Initial Press Error', color='tab:red', marker='^')
ax1.plot(x, ini_opt_errors['optPressError'], label='Optimized Press Error', color='tab:purple', marker='s')
ax1.set_xlabel('Node Count')
ax1.set_ylabel('Error', color='tab:blue')
ax1.tick_params(axis='y', labelcolor='tab:blue')
ax1.set_yscale('log')
ax1.legend(loc='upper left')

# Draw search times on the second y-axis
ax2 = ax1.twinx()
ax2.plot(x, search_times['DirectSearchTime'], label='Direct Search Time', color='tab:orange', marker='d')
ax2.plot(x, search_times['OctreeSearchTime'], label='Octree Search Time', color='tab:brown', marker='+')
ax2.set_ylabel('Time (ms)', color='tab:orange')
ax2.tick_params(axis='y', labelcolor='tab:orange')
ax2.set_yscale('log')
ax2.legend(loc='upper right')

# Show the plot
plt.title('Errors and Search Times vs. Node Count')
plt.show()
