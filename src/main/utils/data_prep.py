import string

import numpy as np
import pandas as pd
import warnings
from sklearn.metrics import mean_absolute_error
from matplotlib import pyplot as plt

BASIC_DATA_PATH: string = '../../data/stock_prices_sample.csv'


def mean_absolute_percentage_error(y_true, y_pred):  # useless for now
    return np.mean(np.abs((y_true - y_pred) / y_true)) * 100


def get_data(data_path: string):
    warnings.filterwarnings('ignore')
    return pd.read_csv(data_path, index_col=['DATE'], parse_dates=['DATE'])


def convert_row_data():
    data = get_data(BASIC_DATA_PATH)
    data = data[data.TICKER != 'GEF']
    data = data[data.TYPE != 'Intraday']
    drop_cols = ['SPLIT_RATIO', 'EX_DIVIDEND', 'ADJ_FACTOR', 'ADJ_VOLUME', 'ADJ_CLOSE', 'ADJ_LOW', 'ADJ_HIGH',
                 'ADJ_OPEN',
                 'VOLUME', 'FREQUENCY', 'TYPE', 'FIGI']
    data.drop(drop_cols, axis=1, inplace=True)
    return data


def plot_data(data):
    plt.figure(figsize=(17, 8))
    plt.plot(data.CLOSE)
    plt.title('Closing price of New Germany Fund Inc (GF)')
    plt.ylabel('Closing price ($)')
    plt.xlabel('Trading day')
    plt.grid(False)
    plt.show()


def plot_moving_average(series, window, plot_intervals=False, scale=1.96):
    rolling_mean = series.rolling(window=window).mean()

    plt.figure(figsize=(17, 8))
    plt.title('Moving average\n window size = {}'.format(window))
    plt.plot(rolling_mean, 'g', label='Rolling mean trend')

    # Plot confidence intervals for smoothed values
    if plot_intervals:
        mae = mean_absolute_error(series[window:], rolling_mean[window:])
        deviation = np.std(series[window:] - rolling_mean[window:])
        lower_bound = rolling_mean - (mae + scale * deviation)
        upper_bound = rolling_mean + (mae + scale * deviation)
        plt.plot(upper_bound, 'r--', label='Upper bound / Lower bound')
        plt.plot(lower_bound, 'r--')

    plt.plot(series[window:], label='Actual values')
    plt.legend(loc='best')
    plt.grid(True)
    plt.show()

