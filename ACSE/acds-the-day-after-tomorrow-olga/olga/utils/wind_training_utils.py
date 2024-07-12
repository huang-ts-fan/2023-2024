import torch
from torch.utils.data import DataLoader
from tqdm import tqdm
from sklearn.metrics import mean_squared_error, mean_absolute_error
from livelossplot import PlotLosses
from torch.cuda.amp import GradScaler, autocast
import torch


class ModelTrainer:
    """
    A class to encapsulate training, validation, and evaluation processes.
    """
    
    def __init__(self, model, optimizer, criterion, device):
        """
        Initializes the ModelTrainer with the model, optimizer, criterion, and device.
        
        Parameters:
            model (torch.nn.Module): The neural network model to train.
            optimizer (torch.optim.Optimizer): The optimizer to use for training.
            criterion (callable): The loss function.
            device (torch.device): The device to train the model on.
        """
        self.model = model
        self.optimizer = optimizer
        self.criterion = criterion
        self.device = device

    def train(self, data_loader):
        """
        Trains the model for one epoch.
        
        Parameters:
            data_loader (DataLoader): The DataLoader for the training data.
        
        Returns:
            float: The average training loss for the epoch.
        """
        self.model.train()
        running_loss = 0.0
        for X, y in tqdm(data_loader, desc="Training", leave=False):
            X, y = X.to(self.device), y.to(self.device)
            self.optimizer.zero_grad()

            with torch.cuda.amp.autocast():
                outputs = self.model(X)
                loss = self.criterion(outputs, y)
            
            loss.backward()
            self.optimizer.step()

            running_loss += loss.item() * X.size(0)
        return running_loss / len(data_loader.dataset)

    def validate(self, data_loader):
        """
        Validates the model.
        
        Parameters:
            data_loader (DataLoader): The DataLoader for the validation data.
        
        Returns:
            float: The average validation loss.
        """
        self.model.eval()
        validation_loss = 0.0
        with torch.no_grad():
            for X, y in tqdm(data_loader, desc="Validation", leave=False):
                X, y = X.to(self.device), y.to(self.device)
                outputs = self.model(X)
                loss = self.criterion(outputs, y)
                validation_loss += loss.item() * X.size(0)
        return validation_loss / len(data_loader.dataset)
    


    def evaluate(self, data_loader):
        """
        Evaluates the model on the given dataset.

        Parameters:
            data_loader (DataLoader): DataLoader for the dataset to evaluate.

        Returns:
            tuple: A tuple containing lists of predictions and actual values, and the calculated MSE and MAE.
        """
        self.model.eval()
        predictions = []
        actuals = []
        with torch.no_grad():
            for X, y in data_loader:
                X, y = X.to(self.device), y.to(self.device)
                outputs = self.model(X)
                predictions.extend(outputs.view(-1).cpu().numpy())
                actuals.extend(y.view(-1).cpu().numpy())
        
        mse = mean_squared_error(actuals, predictions)
        mae = mean_absolute_error(actuals, predictions)
        return predictions, actuals, mse, mae
    

    def train_model(self, train_dataset, val_dataset, n_epochs, lr, batch_size):
        """
        Handles the complete training process including setup and execution of the training loop.
        
        Parameters:
            train_dataset (Dataset): The dataset to use for training.
            val_dataset (Dataset): The dataset to use for validation.
            n_epochs (int): The number of epochs to train the model.
            lr (float): Learning rate for the optimizer.
            batch_size (int): Batch size for training and validation.
        """
        # Create DataLoaders
        train_loader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
        val_loader = DataLoader(val_dataset, batch_size=batch_size, shuffle=False)

        # Setup optimizer if not already provided
        if self.optimizer is None:
            self.optimizer = torch.optim.Adam(self.model.parameters(), lr=lr)

        # Setup live plot
        liveloss = PlotLosses()

        for epoch in range(n_epochs):
            logs = {}
            train_loss = self.train(train_loader)
            val_loss = self.validate(val_loader)

            logs['loss'] = train_loss
            logs['val_loss'] = val_loss

            liveloss.update(logs)
            liveloss.send()

        print("Training completed.")


