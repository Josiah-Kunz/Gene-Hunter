"""

This is such a mess. The curve_fit does worse than my guess (probably because it's a 2D problem).

"""


# Import packages
# ===============
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import numpy as np

def CurveFit(statName, *args):
    """
    *args: A list of [baseStat, level, stat] contraints
    """
    
    # Set up guesses
    baseCoefficient = 0.00002
    baseExponent = 2
    levelCoefficient = 0.13
    levelExponent = 2
    p0 = [baseCoefficient, baseExponent, levelCoefficient, levelExponent]
    #p0 = [baseCoefficient, levelCoefficient]
    #p0 = [baseExponent, levelExponent]
    
    # Catch sillyness
    if len(p0) > len(args):
        print("\n")
        print("="*30)
        print("Error!\n" + "Number of fitted points (", len(args),
        ") must be greater than or equal to number of fitted parameters (", len(p0),")!")
        print("="*30)
        print("\n")
    
    # Set up data
    baseLevel = np.array([])
    stat = np.array([])
    for pair in args:
        baseLevel = np.append(baseLevel, [pair[0], pair[1]])
        stat = np.append(stat, pair[2])
        
    # Run the curve fit
    coeff, cov = curve_fit(FullFunction, baseLevel, stat, p0=p0)
    
    # Get a dict of <base stat, levels>
    baseLevelDict = {}
    baseStatDict = {}
    for i in range(len(args)):
        baseStat = args[i][0]
        level = args[i][1]
        stat = args[i][2]
        if not baseStat in baseLevelDict:
            baseLevelDict[baseStat] = np.array([])
            baseStatDict[baseStat] = np.array([])
        baseLevelDict[baseStat] = np.append(baseLevelDict[baseStat], level)
        baseStatDict[baseStat] = np.append(baseStatDict[baseStat], stat)
        
    
    # Plot the constraints
    plt.cla()
    for baseStat in baseLevelDict:
        plt.scatter(baseLevelDict[baseStat], baseStatDict[baseStat], color="red")
    
    # Plot the fitted data  
    levels = np.linspace(0, 100, 101)
    for baseStat in baseLevelDict:
        plt.plot(levels, FullFunction([baseStat, levels], *coeff), label=baseStat)
        #plt.plot(levels, FullFunction([baseStat, levels], *p0), label=baseStat)
    plt.legend(loc='best')
    
    # Show
    plt.savefig("tmp.png")
    print(*coeff)
    print(cov)
    
def FullFunction(baseLevel, baseCoefficient, baseExponent, levelCoefficient, levelExponent):
    baseStat = baseLevel[0]
    level = baseLevel[1]
    return level * (baseCoefficient * baseStat ** baseExponent + np.floor(level/10) * levelCoefficient ** levelExponent)
    
def FunctionWithoutExponents(baseLevel, baseCoefficient, levelCoefficient):
    baseStat = baseLevel[0]
    level = baseLevel[1]
    return level * (baseCoefficient * baseStat ** 2 + np.floor(level/10) * levelCoefficient ** 2)
    
def FunctionWithoutCoefficients(baseLevel, baseExponent, levelExponent):
    baseStat = baseLevel[0]
    level = baseLevel[1]
    return level * (0.00002 * baseStat ** baseExponent + np.floor(level/10) * 0.13 ** levelExponent)
    
    
def Test():
    x = np.array((1e-4, 0.9, 0.95, 0.98, 0.99, 0.99))
    y = np.array((250, 1000, 2500, 5000, 7500, 10000))
    p0 = [1, 0]
    p1, cov = curve_fit(Func, x, y, p0=p0)
    print("m =", p1[0])
    print("b =", p1[1])
    
def Func(x, m, b):
    return m*x+b
    
# Main execution
# ==============
if __name__ == "__main__":
    CurveFit("Haste", 
                 [50, 100, 25],
                 #[50, 50, 12],
                 
                 [100, 100, 33.333333],
                 #[100, 50, 20],
                 
                 [150, 100, 60],
                 #[150, 50, 33.333],
                 
                 #[200, 50, 50],
                 [200, 100, 100]
             )
    
    
    
    
    
    
    
    
    
    
    
    
    