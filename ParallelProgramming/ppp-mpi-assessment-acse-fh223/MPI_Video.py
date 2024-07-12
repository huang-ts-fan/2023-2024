import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os

# set the data file path, number of processes (default 4), and number of steps (default 301)
# declare boundary conditions (neu or periodic)
num_procs = 4
num_steps = 301
boundary = "periodic"
file_dir = f"MPI_out_{boundary}/"

# which concentration to plot C1 or C2
concentration = 1

# file name format is output_C1_<process id>_<time step>.dat for MPI code generated data
def combine_files(step, num_procs, file_dir):
    combined_data = []
    for proc_id in range(num_procs):
        file_path = os.path.join(file_dir, f"output_C{concentration}_{proc_id}_{step}.dat")
        with open(file_path, 'r') as f:
            data = [list(map(float, line.strip().split())) for line in f if line.strip()]
            combined_data.append(data)
    return np.vstack(combined_data)  # combine data from all processes

# initialize a list to store all time step data
all_steps_data = []

# for each time step, read the data
for step in range(num_steps):
    all_steps_data.append(combine_files(step, num_procs, file_dir))

# visualization and animation function
def update(frame, all_steps_data):
    plt.clf()
    plt.imshow(all_steps_data[frame], cmap='viridis', aspect='auto')
    plt.colorbar(label='Concentration')
    plt.title(f'Chemical Concentration C{concentration} at Time Step {frame}')
    plt.xlabel('X Axis')
    plt.ylabel('Y Axis')

# create animation
fig, ax = plt.subplots()
ani = FuncAnimation(fig, update, frames=range(num_steps), fargs=(all_steps_data,), repeat=False)

# save the animation as an MP4 file
ani.save(f'Videos/MPI_concentration_C{concentration}_{boundary}.mp4', writer='ffmpeg', fps=10)

print(f"Store in Videos/MPI_concentration_C{concentration}_{boundary}.mp4")
