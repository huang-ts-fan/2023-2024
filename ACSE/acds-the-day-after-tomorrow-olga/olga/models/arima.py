import pandas as pd
from statsmodels.tsa.arima.model import ARIMA

class WindSpeedARIMAModel:
    def __init__(self, data, order=(2,1,2)):
        """
        Initializes the ARIMA model for wind speed prediction.
        
        Parameters:
            data (pd.Series): A Pandas Series containing the wind speed data.
            order (tuple): The order (p,d,q) of the ARIMA model.
        """
        self.data = data
        self.order = order
        self.model_fit = None

    def fit(self):
        """
        Fits the ARIMA model to the wind speed data.
        """
        model = ARIMA(self.data, order=self.order)
        self.model_fit = model.fit()

    def forecast(self, steps=3):
        """
        Forecasts future wind speed values.
        
        Parameters:
            steps (int): The number of future steps to forecast.
            
        Returns:
            pd.Series: A Pandas Series containing the forecasted values.
        """
        if self.model_fit is None:
            raise ValueError("Model must be fit before forecasting.")
        forecast = self.model_fit.forecast(steps=steps)
        return forecast