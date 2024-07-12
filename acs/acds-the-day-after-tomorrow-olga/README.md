# The Day After Tomorrow

### Predicting tropical storm behaviour through Deep Learning
**Gourp: Olga <br><br>**
<img src="https://github.com/ese-msc-2023/acds-the-day-after-tomorrow-olga/blob/main/media/logo.png?raw=true" width="300" height="300">

## Motivation

The **FEMA** (**F**ederal **E**mergency **M**anagement **A**gency) in the US have released an open competition to improve their emergency protocols under hurricane threats.

Hurricanes can cause upwards of 1,000 deaths and $50 billion in damages in a single event and have been responsible for well over 160,000 deaths globally in recent history. During a tropical cyclone, humanitarian response efforts hinge on accurate risk approximation models that can help predict optimal emergency strategic decisions.

In this project, we are responsible for predicting the tropical storm image and also the wind speed. And in this case of study, we have used the CNN-LSTM for image predicting and CNN model for wind speed for the coming surprise storm


## Repository Structure
This section mainly describe the content of the whole repository

• In the folder **notebooks**: contains two intergrated notebooks presenting the working flow and model details of predicting image and wind speed two parts, showcasing the design and implementation of the image and wind-speed prediction networks

• In the folder **olga**: contain the python files required for the project package

• The file **Pipeline.ipynb** is the merged version of the final notebook showing workflow applied to the surprise storm, containing results and justification

• The file **olga_windpredictions.csv** is the output csv file for the wind speed prediction

• The folder **olga_generatedimages** contains the final three prediction images for the surprise storm

## Working Process

For the two tasks, we have mainly splited into two groups, the general working flow and the methods are listed as below:

### Image Prediction (LSTM & CNN-LSTM)
#### LSTM:
1. Data normalization:(min-max)​
2. PCA(with components of 200)​
3. Customized dataset using five images as a sequence like a moving window​
4. LSTM model training with 400 epochs on the surprise storm dataset
#### CNN-LSTM:
1. ConvLSTM Cell receive two inputs at each time step,the current input image and the previous time step's hidden states.​
2. Convolution operations within its gating mechanisms (forget gate, input gate, output gate) instead of fully connected operations, allowing it to preserve the spatial structure of input images. ​
3. ConvLSTM updates its hidden states through a series of convolutional layers, providing information for the next time step. ​
4. We explored the possibility of using both MSE and SSIM as loss functions. These functions focus on pixel-level errors and perceptual image quality, respectively. By combining these two, we aim to optimize the model for generating high-quality image predictions. ​
5. We use the Adam optimizer to adjust the model's parameters, minimizing the loss function. ​

### Wind Speed Prediction (CNN)
1. Data Selection:
   
    • Analysis of image data from 30 storms indicates that the same speed corresponds to different image features across different storms.
   
    • To enhance the generalization ability of the model, training should be conducted on the data from these 30 storms.
   
    • To improve prediction accuracy for individual storms, further specialized training could be performed on specific test storms based on this data.
   
2. Image Processing:

    • Feature details can be enhanced and noise reduced by superimposing grayscale images as RGB images.
   
    • A time window approach was considered for analyzing image sequences, but it's important to note that LSTM may overlook special effects in certain images, resulting in less pronounced features.
   
3. Model Selection:

    • After consideration, ResNet, LSTM, and CNN were selected as potential model candidates.
   
    • We have decided to try several methods by choosing a standalone ResNet, CNN, and a combination of CNN with LSTM.
   
4. Predicting Results:
   
    • By combining generated images, we can provide a general trend and reference for changes in storm speeds.
   
    • The data shows a trend of progressively decreasing speeds, which could be very useful for predicting and understanding storm dynamics. 


## Library Used
```
livelossplot
matplotlib
numpy
pandas
scikit-learn
statsmodels
torch
torchvision
```
## Installation

To install the the library or the package, firstly clone this repository in your local file

```
git clone https://github.com/ese-msc-2023/acds-the-day-after-tomorrow-olga.git
```
To install the project requirement and library run the following command in your local virtual environment:
```
pip install -r requirements.txt

```
When all the installation of the requirements are done, the package should be installed by running:
```
pip install -e .
```
## License

The project is an open source and licensed under MIT LICENSE


