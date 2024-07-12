<p align="center">
  <img src="https://github.com/ese-msc-2023/advanced-programming-group-depth-first-search/assets/143221118/308a0f58-114b-4096-8eaf-e33c182383f1" alt="mip-nofilter" width="200"/>
  <img src="https://github.com/ese-msc-2023/advanced-programming-group-depth-first-search/assets/143221118/7f1a5b79-e35f-42e8-874b-91c165f27d98" alt="minip-median_3x3x3"width="200" height="250"/>
  <img src="https://github.com/ese-msc-2023/advanced-programming-group-depth-first-search/assets/143221118/f4167e28-6d33-4a4a-a8e4-db2ec86431e9" alt="gracehopper" width="200"/>
  <img src="https://github.com/ese-msc-2023/advanced-programming-group-depth-first-search/assets/143221118/d423dfcf-5f9e-42b6-b4af-8f1d231aa100" alt="stinkbug_80" width="200"/>
</p>

# Advanced Programming Group Project
Advanced Programming course group project assessment. Build a C++ program to apply a range of image filters and orthographic projections to an input 2D image or 3D data volume.

# CT Scans
Download CT Scan datasets here:
https://imperiallondon-my.sharepoint.com/:u:/g/personal/tmd02_ic_ac_uk/EafXMuNsbcNGnRpa8K62FjkBvIKvCswl1riz7hPDHpHdSQ

# How to access documentation

In terminal, in the project directory, run:

`open documentation/html/index.html`

# Getting Started

### Prerequisites

1. C++ Compiler (C++17 or later recommended)
2. `stb_image.h` and `stb_image_write.h` for image loading and saving.

# Installation

1. Clone the repository:

`git clone https://github.com/ese-msc-2023/advanced-programming-group-depth-first-search.git`

2. Ensure `stb_image.h` and `stb_image_write.h` are placed in the project's include path.
3. If the user uses CMake, please refer to `CMakeLists.txt`.

## Usage

Run `main.cpp` to start the user interface, which allows you to choose between processing 2D images or 3D volume data.

### 2D Image Processing

After selecting 2D processing:

1. **Enter the path to the image file.**

2. **Choose your processing option:**

#### Color Correction
- **Grayscale**: Converts the image to grayscale.
- **Brightness**: Adjusts brightness (value range: -255 to 255, or auto).
- **Histogram Equalization**: For grayscale or RGB (via HSV/HSL conversion).
- **Threshold**: Sets pixels below a threshold to black, above to white.
- **Salt and Pepper Noise**: Adds specified percentage of noise to the image.

#### Image Blur
- **Median Blur**: Applies a median blur.
- **Box Blur**: Applies a box blur.
- **Gaussian Blur**: Applies a Gaussian blur.

#### Edge Detection
- **Sobel**, **Prewitt**, **Scharr**, **Roberts**: Applies the selected edge detection filter.

### 3D Volume Processing

After selecting 3D processing:

1. **Enter the path to the volume directory.**
2. **Specify the start index and number of images (0 for all images).**

#### Choose your processing option:

#### Apply Projection
- **MIP (Maximum Intensity Projection)**
- **MinIP (Minimum Intensity Projection)**
- **AIP (Average Intensity Projection)**
- Optionally apply a blur filter with a selected kernel size.

#### Apply Slice
- Choose orientation (`X`, `Y`, `Z`) and index for the slice.

#### Apply Blur
- **Median Blur** or **Gaussian Blur**: Choose the type of blur to apply.

### Saving Processed Images

- You will have the option to save the processed image or volume slice to a specified path.

### References
- https://chat.openai.com/share/16a33ddc-ed93-45d9-92c5-ee5c29f51936
- https://chat.openai.com/share/c92ad6fb-c139-429c-9c03-2aa19f9300c1
- https://chat.openai.com/share/3377765f-e925-4ccc-93bc-e7c51d02fd4e
- https://chat.openai.com/share/59ab2706-c695-4639-845d-fd93bf677590
- https://chat.openai.com/share/fbd814b6-d079-4eba-b756-22415d657859
- https://chat.openai.com/share/30085de1-caa8-4c9e-a360-c8c6728d8740

*PS: The stinkbug at the top is thankfully a literal bug, and not a code bug.*
 
