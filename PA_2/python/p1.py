import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import font_manager as fm
from matplotlib import rc

font_path = 'fonts/computer-modern/cmunrm.ttf'
prop = fm.FontProperties(fname=font_path)
plt.rcParams['font.family'] = prop.get_name()

# rc('font', **{'family': 'serif', 'serif': ['Computer Modern']})
# rc('text', usetex=True)


# Load the data from the file
data = pd.read_csv('timing_data.txt')

# Plot the data
plt.figure(figsize=(6, 6))
plt.grid(True, linestyle='--')
plt.plot(data['n'], data['time_ms'], marker='o', linestyle='None', color='red', markersize=3)

# Set plot labels and title
plt.xlabel('n (Number of Elements)')
plt.ylabel('Time (ms)')
plt.title('n vs Time (ms)')


# Show grid
plt.grid(True)

# Display the plot
plt.show()
