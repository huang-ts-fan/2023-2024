import torch
from torch import nn
import torch.nn.functional as F

class CNN(nn.Module):
    def __init__(self):
        super(CNN_linkedin, self).__init__()
 
        self.conv1 = nn.Conv2d(in_channels=1, out_channels=32, kernel_size=3, padding=1)
        self.bn1 = nn.BatchNorm2d(num_features=32)
        self.pool1 = nn.MaxPool2d(kernel_size=2, stride=2)
        self.dropout1 = nn.Dropout(0.25)
    
        self.conv2 = nn.Conv2d(in_channels=32, out_channels=64, kernel_size=3, padding=1)
        self.bn2 = nn.BatchNorm2d(num_features=64)
        self.pool2 = nn.MaxPool2d(kernel_size=2, stride=2)
        self.dropout2 = nn.Dropout(0.25)
     
        self.fc1 = nn.Linear(in_features=64 * 32 * 32, out_features=512)  
        self.dropout3 = nn.Dropout(0.5)
        self.fc2 = nn.Linear(in_features=512, out_features=1)

    def forward(self, x):
  
        x = self.dropout1(self.pool1(F.leaky_relu(self.bn1(self.conv1(x)))))
        x = self.dropout2(self.pool2(F.leaky_relu(self.bn2(self.conv2(x)))))
      
        x = x.view(x.size(0), -1)  
   
        x = F.leaky_relu(self.fc1(x))
        x = self.dropout3(x)
        x = self.fc2(x) 
        return x

