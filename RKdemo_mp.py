import numpy as np
import matplotlib.pyplot as plt

def RK1Solve(f, y0, nsteps, x0, xmax):
    h = (xmax - x0) / nsteps  # step size
    x = x0                     # independent variable
    y = y0                     # dependent variable to plot vs x
    points = [(x0, y0)]        # store points for plotting

    for i in range(nsteps - 1):
        k1 = h * f(x, y)
        y = y + k1
        x += h
        points.append((x, y))
    return np.array(points)

def RK2Solve(f, y0, nsteps, x0, xmax):
    h = (xmax - x0) / nsteps  # step size
    x = x0                     # independent variable
    y = y0                     # dependent variable to plot vs x
    points = [(x0, y0)]        # store points for plotting

    for i in range(nsteps - 1):
        k1 = h * f(x, y)
        k2 = h * f(x + h / 2, y + k1 / 2)
        y = y + k2
        x += h
        points.append((x, y))
    return np.array(points)

# The differential equation to be solved
def fun1(x, y):
    return -2 * y  # f = y'(x,y) = -2 * y(x)  
                    # solution: y(x) = 3 * exp(-2*x); with initial condition y(0)=3

# Solve our DEQ using RK1 or RK2 methods!
tg1 = RK1Solve(fun1, 3, 30, 0, 3)  # initial condition y(0)=3
tg2 = RK2Solve(fun1, 3, 30, 0, 3)
x_exact = np.linspace(0, 3, 300)
y_exact = 3 * np.exp(-2 * x_exact)  # exact solution

# Plot the results
plt.figure(figsize=(10, 6))
plt.plot(tg1[:, 0], tg1[:, 1], 'r^', markersize=8, label='RK1 Solution')
plt.plot(tg2[:, 0], tg2[:, 1], 'g^', markersize=8, label='RK2 Solution')
plt.plot(x_exact, y_exact, 'k--', label='Exact Solution')

plt.title("ODE demo")
plt.xlabel("x")
plt.ylabel("y")
plt.legend()
plt.grid()
plt.savefig("ODE_py.png")
plt.show()
