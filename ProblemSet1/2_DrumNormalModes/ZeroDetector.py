#Script for finding sing change in the plot data of a function
import pandas as pd
from math import copysign
colnames =  ["x", "y"] #name of columns
df = pd.read_csv("datosb.dat", sep="\t", header=None, names=colnames )
x = df["x"]
y = df["y"]
# to store the interval (a,b) in which the zeros live
zeros = {"a":[], "b":[], } #type: dict

n = len(y)-1
for k in range(n):
    a, b = x[k] , x[k+1]
    fa, fb = y[k], y[k+1]
    if copysign(1, fa) != copysign(1, fb):
        zeros["a"].append(a)
        zeros["b"].append(b)
zeros_df = pd.DataFrame(zeros)
#save to txt
zeros_df.to_csv("zeros.dat", sep="\t", index=False)
print(zeros_df)
