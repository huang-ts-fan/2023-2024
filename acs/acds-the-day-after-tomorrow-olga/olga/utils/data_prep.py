import json
import os
import pandas as pd
from PIL import Image
from torchvision import transforms
from torch.utils.data import Dataset
from torch import stack
import numpy as np
import torch


class StormImageDatasetLoader:
    """
    A class for loading storm images and their labels for both training/validation and test datasets
    from specified directories and CSV files.
    
    Attributes:
        base_path (str): The base path to the directory containing the images and CSV files.
        train_csv_file (str): The name of the CSV file containing the metadata for training/validation images.
        test_csv_file (str): The name of the CSV file containing the metadata for test images.
        train_dataset (list): A list where each element is a tuple containing an image array and its label for training/validation.
        test_dataset (list): A list where each element is a tuple containing an image array and its label for testing.
    """

    def __init__(self, base_path, train_csv_file='tst_fulldata.csv', test_csv_file='tst_testdata (1).csv'):
        """
        Initializes the StormImageDatasetLoader with base path and CSV file names.
        
        Parameters:
            base_path (str): The base directory path where images and CSV are located.
            train_csv_file (str): The CSV file name for training/validation dataset.
            test_csv_file (str): The CSV file name for test dataset.
        """
        self.base_path = base_path
        self.train_csv_file = train_csv_file
        self.test_csv_file = test_csv_file
        self.train_dataset = []
        self.test_dataset = []

    def load_dataset(self, dataset_type='train'):
        """
        Loads the specified dataset from the directory and CSV file, converting images to RGB if necessary.
        
        Parameters:
            dataset_type (str): The type of dataset to load ('train' for training/validation or 'test' for testing).
        """
        csv_file = self.train_csv_file if dataset_type == 'train' else self.test_csv_file
        csv_path = os.path.join(self.base_path, csv_file)
        data = pd.read_csv(csv_path)

        dataset = self.train_dataset if dataset_type == 'train' else self.test_dataset

        for _, row in data.iterrows():
            image_path = os.path.join(self.base_path, row['image'])
            img = Image.open(image_path)
            img_array = np.array(img)

            if len(img_array.shape) == 2:  
                rgb_img_array = np.repeat(img_array[:, :, np.newaxis], 3, axis=2)
            else:
                rgb_img_array = img_array

            wind_speed = row['wind_speed']
            dataset.append((rgb_img_array, wind_speed))

    def get_dataset(self, dataset_type='train'):
        """
        Returns the specified dataset.
        
        Parameters:
            dataset_type (str): The type of dataset to retrieve ('train' for training/validation or 'test' for testing).
        
        Returns:
            list: The requested dataset containing tuples of image arrays and their labels.
        """
        return self.train_dataset if dataset_type == 'train' else self.test_dataset







class CustomDataset(Dataset):
    """
    A custom dataset class for handling image data with optional transformations and augmentations.
    
    Attributes:
        data (list): A list of tuples where each tuple represents an (image, label) pair.
        transform (callable, optional): A function/transform that takes in an image and returns a transformed version.
        augmentation (callable, optional): A function/transform that applies data augmentation to an image.
    """
    def __init__(self, data, transform=None, augmentation=None):
        """
        Initializes the CustomDataset with data, optional transformations, and augmentations.
        
        Parameters:
            data (list): The dataset, a list of (image, label) tuples.
            transform (callable, optional): Optional transform to be applied on a sample.
            augmentation (callable, optional): Optional augmentation to be applied on a sample.
        """
        self.data = data
        self.transform = transform
        self.augmentation = augmentation

    def __len__(self):
        """Returns the size of the dataset."""
        return len(self.data)

    def __getitem__(self, idx):
        """
        Retrieves an item from the dataset at the specified index.
        
        Parameters:
            idx (int): The index of the item to retrieve.
        
        Returns:
            tuple: A tuple containing the transformed and/or augmented image and its label.
        """
        image, label = self.data[idx]

        if image.ndim == 4:
            image = image[0]  

        if self.augmentation:
            image = self.augmentation(image)

        if self.transform:
            image = self.transform(image)

        label = torch.tensor([label], dtype=torch.float32)
        return image, label



def prep_image_gen(image_list):
    output = stack(image_list).unsqueeze(0)
    return output





