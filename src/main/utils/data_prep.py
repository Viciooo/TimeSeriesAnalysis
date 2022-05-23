import string

import numpy as np
import pandas as pd
import warnings

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


def exponential_smoothing(series, alpha):
    result = [series[0]]  # first value is same as series
    for n in range(1, len(series)):
        result.append(alpha * series[n] + (1 - alpha) * result[n - 1])
    return result


def double_exponential_smoothing(series, alpha, beta):
    result = [series[0]]
    for n in range(1, len(series) + 1):
        if n == 1:
            level, trend = series[0], series[1] - series[0]
        if n >= len(series):  # forecasting
            value = result[-1]
        else:
            value = series[n]
        last_level, level = level, alpha * value + (1 - alpha) * (level + trend)
        trend = beta * (level - last_level) + (1 - beta) * trend
        result.append(level + trend)
    return result
