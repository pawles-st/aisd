import numpy as np
import math
import matplotlib.pyplot as plt

data_begin = 10000                                          # beginning of data range
data_end = 100000                                           # end of data range (inclusive)
data_step = 10000                                           # data range step
data_range = np.arange(data_begin, data_end + 1, data_step) # array of data values
data_size = len(data_range)                                 # length of the data values array

tree_types = ["bst", "rbbst", "splay"]
#tree_types = ["bst", "rbbst"]

print(tree_types)

m = 20 # number of repeats for a single experiment

comparisons = np.zeros((len(tree_types), data_size), int)
read_ptr = np.zeros((len(tree_types), data_size), int)
write_ptr = np.zeros((len(tree_types), data_size), int)
height = np.zeros((len(tree_types), data_size), int)

for t in range(len(tree_types)): # tree type

    for n in data_range: # size of the input

        # read results and sum them

        data = open(f"results/{tree_types[t]}_{n}.txt", "r")
        print(data)
        for result in data.readlines():
            result_split = result.rstrip("\n").split(" ")
            result_split = [eval(i) for i in result_split]
            print(tree_types[t], n, result)
            comparisons[t][n // data_step - 1] += result_split[0]
            read_ptr[t][n // data_step - 1] += result_split[1]
            write_ptr[t][n // data_step - 1] += result_split[2]
            height[t][n // data_step - 1] += result_split[3]

    # take the average

    comparisons[t] = comparisons[t] / m
    read_ptr[t] = read_ptr[t] / m
    write_ptr[t] = write_ptr[t] / m
    height[t] = height[t] / m

# plot the averages

for t in range(0, len(tree_types)):
    plt.plot(data_range, comparisons[t], label=f"{tree_types[t]}")
    
plt.title("comparisons")
plt.legend()
plt.show()

for t in range(len(tree_types)):
    plt.plot(data_range, read_ptr[t], label=f"{tree_types[t]}")
    
plt.title("pointers read")
plt.legend()
plt.show()

for t in range(len(tree_types)):
    plt.plot(data_range, write_ptr[t], label=f"{tree_types[t]}")
    
plt.title("pointers written")
plt.legend()
plt.show()

for t in range(len(tree_types)):
    plt.plot(data_range, height[t], label=f"{tree_types[t]}")
    
plt.title("height")
plt.legend()
plt.show()

