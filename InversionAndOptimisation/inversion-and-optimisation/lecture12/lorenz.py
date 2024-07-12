# start by building a model
import numpy as np
from scipy.integrate import odeint

rho = 28
sigma = 10
beta = 8/3

def f(X, t):
    """Right Hand Side for the 3 variable Lorenz attractor ODE system"""
    
    x = X.reshape(3, len(X)//3)
    
    y = np.empty(x.shape)
    
    y[0, :] = sigma*(x[1, :]-x[0, :])
    y[1, :] = -x[0, :]*x[2, :] + rho*x[0, :]-x[1, :]
    y[2, :] = x[0, :]*x[1, :] - beta*x[2, :]
    
    return y.ravel()

def lorenz_model(x0, t):
    t = np.asarray(t)
    return odeint(f, x0, t).reshape(t.shape[0], 3)

def ensemble_lorenz_model(x0, t):
    x0 = np.asarray(x0)
    t = np.asarray(t)
    return odeint(f, x0.ravel(), t).reshape(t.shape[0], 3, x0.shape[1])
