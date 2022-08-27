import pandas as pd
import matplotlib.pyplot as plt
#Import data
Data_File_Name = "data.dat"
df = pd.read_csv("data.dat", sep="\t", header=None, names=["x", "y"])

#plotting  stuff
title = "Orbit of the planet"
xlabel = r"$x$"
ylabel = r"$y$"
Plot_File_Name = "OrbitPlot.pdf"

plt.grid()
plt.plot(df["x"], df["y"])
plt.title(title)
plt.xlabel(xlabel)
plt.ylabel(ylabel)
plt.savefig(Plot_File_Name)
