import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import os

# set the data file path and number of steps
# declare boundary conditions (neu or periodic)
num_steps = 301
boundary = "periodic"
file_dir = f"serial_out_{boundary}/"

# which concentration to plot C1 or C2
concentration = 1

# file name format is output_C1_<time step>.dat for serial code generated data
def read_data(step, file_dir):
    file_path = os.path.join(file_dir, f"output_C{concentration}_{step}.dat")
    with open(file_path, 'r') as f:
        data = [list(map(float, line.strip().split())) for line in f if line.strip()]
    return np.array(data)

# initialize a list to store all time step data
all_steps_data = []

# for each time step, read the data
for step in range(num_steps):
    all_steps_data.append(read_data(step, file_dir))

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
ani.save(f'Videos/serial_concentration_C{concentration}_{boundary}.mp4', writer='ffmpeg', fps=10)

print(f"Store in Videos/serial_concentration_C{concentration}_{boundary}.mp4")
