import numpy as np
import matplotlib.pyplot as plt
from scipy import stats


f = open("count_of_numbers.txt")

numbers = []
for line in f:
    numbers.append(int(line))

f.close()

f = open("expected_numbers.txt")

expected_numbers = []
for line in f:
    expected_numbers.append(float(line))

f.close()

chi2_statistic, p_value = stats.chisquare(numbers, expected_numbers)
print(f"Chi-square statistics: {chi2_statistic}")
print(f"P: {p_value}")

x = np.arange(1, len(numbers)+1)
y = np.array(expected_numbers)

plt.bar(x, numbers)
plt.plot(x, y, color="red")
plt.title(f"P = {p_value}")
plt.show()