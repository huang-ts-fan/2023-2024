import numpy as np
import pandas as pd
from sklearn.pipeline import Pipeline
from sklearn.model_selection import train_test_split
from sklearn.compose import ColumnTransformer
from sklearn.preprocessing import StandardScaler, OneHotEncoder
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import f1_score
# Add any other imports that you need here

# If you created custom transformers or helper functions, you can also add them to this file.

class LithoEstimator:
    '''Used to predict lithology in IODP wells. The signature (method name, argument and return types) for the strict minimum number of methods needed are already written for you below.
    Simply complete the methods following your own notebook results. You can also add more methods than provided below in order to keep your code clean.'''

    def __init__(self, path:str='data/log_data.csv') -> None:
        '''The path is a path to the training file. The default is the file I gave you.
        You want to create an X_train, X_test, y_train and y_test following the same principle as in your
        notebook. You also want to define and train your estimator as soon as you create it.
        
        I recommend creatubg the following instance variables in your __init__ method:
        self.X_train, self.X_test, self.y_train, self.y_test
        self.encoder - the label encoder for your categories
        self.model - the entire trained model pipeline

        Note that this class should not handle hyperparameter searching or feature selection - if you did those in your Part B 
        simply use your best estimators.
        
        '''

        # Load and prepare the data
        df = pd.read_csv(path)
        df = df.drop_duplicates()
        df[['color_hue', 'color_value', 'color_chroma']] = df['munsel_color'].str.split(expand=True)
        df[['color_value', 'color_chroma']] = df[['color_value', 'color_chroma']].apply(pd.to_numeric, errors='coerce')
        df = df.drop(columns=['munsel_color'])
        X = df.drop('lithology', axis=1)
        y = df['lithology']
        self.X_train, self.X_test, self.y_train, self.y_test = train_test_split(X, y, test_size=0.3, random_state=42)

        # Set up the pipeline
        numerical_features = self.X_train.select_dtypes(include=['float64', 'int']).columns
        numerical_transformer = StandardScaler()
        categorical_features = ['color_hue']
        categorical_transformer = OneHotEncoder(handle_unknown='ignore')
        preprocessor = ColumnTransformer(
            transformers=[
                ('num', numerical_transformer, numerical_features),
                ('cat', categorical_transformer, categorical_features)
            ])
        self.model = Pipeline(steps=[
            ('preprocessor', preprocessor),
            ('classifier', LogisticRegression(C=100, random_state=42, max_iter=1000))  # Use the hyperparameters from the best model
        ])

        # Train the model
        self.model.fit(self.X_train, self.y_train)

    def x_test_score(self) -> np.float:
        '''Returns the F1 macro score of the X_test. This should be of type float.'''

        y_pred_test = self.model.predict(self.X_test)
        return f1_score(self.y_test, y_pred_test, average='macro')

    def get_Xs(self) -> (pd.DataFrame, pd.DataFrame):
        '''Returns the X_train and X_test. This method is already written for you.'''

        return self.X_train, self.X_test
    
    def get_ys(self) -> (pd.DataFrame, pd.DataFrame):
        '''Returns the y_train and y_test. This method is already written for you.'''

        return self.y_train, self.y_test

    def predict(self, path_to_new_file:str='data/new_data.csv') -> np.array:
        '''Uses the trained algorithm to predict and return the predicted labels on an unseen file.
        The default file is the unknown_data.csv file in your data folder.
        
        Return a numpy array (the default for the "predict()" function of sklearn estimator)'''

        new_data = pd.read_csv(path_to_new_file)
        new_data[['color_hue', 'color_value', 'color_chroma']] = new_data['munsel_color'].str.split(expand=True)
        new_data[['color_value', 'color_chroma']] = new_data[['color_value', 'color_chroma']].apply(pd.to_numeric, errors='coerce')
        new_data = new_data.drop(columns=['munsel_color'])
        return self.model.predict(new_data)

    def get_model(self) -> Pipeline:
        '''returns the entire trained pipeline, i.e. your model. 
        This will include the data preprocessor and the final estimator.'''

        return self.model