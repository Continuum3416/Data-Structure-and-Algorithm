import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import font_manager as fm

# Load the font for the plot
font_path = 'fonts/computer-modern/cmunrm.ttf'
prop = fm.FontProperties(fname=font_path)
plt.rcParams['font.family'] = prop.get_name()

# Load the data from the files
file_names = ['python/timing_data1.txt', 'python/timing_data2.txt', 'python/timing_data3.txt'] # , 'timing_data2.txt', 'timing_data3.txt'
data_frames = [pd.read_csv(file) for file in file_names]

# Prepare a list of colors for each dataset
colors = ['red', 'green', 'blue']

# Plot the cleaned data for each file
plt.figure(figsize=(6, 6))
plt.grid(True, linestyle='--')
font_size = 14

for i, data in enumerate(data_frames):
    # Calculate IQR for the current dataset
    Q1 = data[['n', 'time_ms']].quantile(0.25)
    Q3 = data[['n', 'time_ms']].quantile(0.75)
    IQR = Q3 - Q1
    
    # Define outlier thresholds
    outlier_factor = 1.0
    lower_bound = (Q1 - outlier_factor * IQR).to_dict()
    upper_bound = (Q3 + outlier_factor * IQR).to_dict()
    
    # Filter out outliers
    data_clean = data[~((data[['n', 'time_ms']] < lower_bound) | (data[['n', 'time_ms']] > upper_bound)).any(axis=1)]
    
    # Sort data_clean by 'n' to connect the points in order
    data_clean = data_clean.sort_values('n')
    
    # Fit a linear model
    coefficients = np.polyfit(data_clean['n'], data_clean['time_ms'], i + 1)
    linear_fit = np.poly1d(coefficients)
    
    # Plot data points and linear fit
    plt.plot(data_clean['n'], data_clean['time_ms'], marker='o', linestyle='None', color=colors[i], markersize=3, label=f'maximumSummation{i+1}')
    # plt.plot(data_clean['n'], linear_fit(data_clean['n']), color=colors[i], linestyle='-', label=f'maximumSummation{i+1}')

# Set plot labels and title
plt.xlabel('n (Number of Elements)', fontsize=font_size)
plt.ylabel('Time (milliseconds)', fontsize=font_size)
plt.title('n vs Time (milliseconds)', fontsize=font_size)
plt.legend()

plt.show()
