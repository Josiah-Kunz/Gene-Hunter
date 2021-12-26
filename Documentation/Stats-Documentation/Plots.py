import matplotlib.pyplot as plt
import numpy as np
from Table import *
from si_prefix import si_format

# Classes
# =======

class BaseStat:
    
    fullname=""
    shortname=""
    description=""
    
    def __init__(self, fullname, shortname, description=""):
        self.fullname = fullname
        self.shortname = shortname
        self.description = description
        
        
class BaseStatColor:
    
    value = 0
    color = None
    description = ""
    
    def __init__(self, value, color, description):
        self.value = value
        self.color = color
        self.description = description
        
class Mutation:
    
    name = ""
    pro = ""
    con = ""
    
    def __init__(self, name, pro, con):
        self.name = name
        self.pro = pro
        self.con = con
        
# Constants
# =========

BASE_STAT_NAMES = [
                    BaseStat("HP",                  "HP",   "Health"),
                    BaseStat("Physical Attack",     "PhA",  "Physical offensive ability,\nsuch as strength"),
                    BaseStat("Physical Defense",    "PhD",  "Physical defensive ability,\nsuch as toughness"),
                    BaseStat("Special Attack",      "SpA",  "Noncorporeal offensive ability,\n such as mentality"),
                    BaseStat("Special Defense",     "SpD",  "Noncorporeal defensive ability,\nsuch as willpower"),
                    BaseStat("Haste",               "Hst",  "Reduces cast and\ncooldown time"),
                    BaseStat("Critical Hit",        "Crt",  "Chance to increase damage")

       ]

BASE_STAT_COLORS = [
                BaseStatColor(0,    "red",          "Minimum"),
                BaseStatColor(50,   "orange",       "Bad"),
                BaseStatColor(100,  "gold",         "Average"),
                BaseStatColor(120,  "lawngreen",    "Good"),
                BaseStatColor(150,  "cyan",         "Specialist"),
                BaseStatColor(200,  "violet",       "Boss")
        ]

MUTATIONS = [
         Mutation("$\it{None}$", "—", "—"),
         Mutation("Berserker Gene", "$+$15% PhA", "$-$10% PhD\n$-$10% SpD"),
         Mutation("Gigantism", "Max height, weight", "—"),
]
        
CELL_WIDTH = 1.3
CELL_HEIGHT = 0.3

HEADER_FONT_SIZE=16
HEADER_COLOR="lightgrey"

BODY_FONT_SIZE=12
DESCRIPTION_FONT_SIZE=8
NEUTRAL_CELL_COLOR = "honeydew"

GAP_LINE_THICKNESS = 0.025

DPI = 300
SILENT = True

def Main():
    
    # Delete lingering
    plt.close("all")
    
    # Keys
    MakeStatKey(silent=SILENT)
    MakeColorKey(silent=SILENT)
    
    # Base pair analysis
    #PlotBasePairContribution()
    PlotBasePairVsAtk()
    MutationsTable()

    # Standard stats
    for basePair in [1, 50, 100]:
        
        Plot(
             "[Standard Stat]", StandardStat, basePair,
            savefilename="Standard-stat-overview-" + str(basePair),
            silent=SILENT
        )

        #Plot(
        #     "[Standard Stat]", StandardStat, basePair,
        #     savefilename="Standard-stat-low-levels-" + str(basePair), 
        #     notedLevels=[1, 9, 10, 19, 20],
        #     silent=SILENT
        # )
        
        #HP
        Plot("HP", HP, basePair, 
             savefilename="HP-overview-" + str(basePair), 
             silent=SILENT
        )
        #Plot("HP", HP, savefilename="HP-low-levels", notedLevels=[1, 9, 10, 19, 20], silent=SILENT)
        
        # Percentage-based stats
        Plot("Haste", Haste, basePair, 
             ylabel="Haste (%)", 
             savefilename="Haste-overview-" + str(basePair), 
             silent=SILENT)
        #Plot("Haste", Haste, 0, ylabel="Haste (%)", savefilename="Haste-low-levels", notedLevels=[1, 9, 10, 19, 20], silent=SILENT)
        HasteCDRTable(silent=SILENT)
        Plot("Crit", Crit, basePair, 
             ylabel="Crit (%)", 
             savefilename="Crit-overview-" + str(basePair), 
             silent=SILENT
        )
        #Plot("Crit", Crit, ylabel="Crit (%)", savefilename="Crit-low-levels", notedLevels=[1, 9, 10, 19, 20], silent=SILENT)
    
def MakeStatKey(silent=False):
    
    # Delete lingering
    plt.cla()
    
    # Initialize table
    statKey = Table(DPI)
    x=0
    y=0
    
    # Title
    statKey.AddCells(Cell(
                       x, x+3*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Stat Types",
                        fontsize=HEADER_FONT_SIZE,
                        color="white",
                        lineColor="white"
                    ),
                    Cell(
                        x, x+3*CELL_WIDTH, y, y-2*CELL_HEIGHT,
                        content="",
                        color="white",
                        lineColor="white"
                    )
            )
    y -= CELL_HEIGHT
    
    # Headers
    statKey.AddCells(
                   Cell(
                        x, x+CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Full Name",
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
                    ),
                    Cell(
                        x + CELL_WIDTH, x+2*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Short Name",
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
                    ),
                    Cell(
                        x + 2*CELL_WIDTH, x+3*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Description",
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
                    )
                         
    )
    y -= CELL_HEIGHT
   
    # Cells
    for baseStatName in BASE_STAT_NAMES:
       statKey.AddCells(
                   Cell(
                        x, x+CELL_WIDTH, y, y-CELL_HEIGHT,
                        content=baseStatName.fullname,
                        fontsize=BODY_FONT_SIZE,
                        color=NEUTRAL_CELL_COLOR
                    ),
                    Cell(
                        x + CELL_WIDTH, x+2*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content=baseStatName.shortname,
                        fontsize=BODY_FONT_SIZE,
                        color=NEUTRAL_CELL_COLOR
                    ),
                    Cell(
                        x + 2*CELL_WIDTH, x+3*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content=baseStatName.description,
                        fontsize=DESCRIPTION_FONT_SIZE,
                        color=NEUTRAL_CELL_COLOR
                    )
       )
       y -= CELL_HEIGHT

    # Render and save
    statKey.Save("stat-key.png", silent=silent)
    

def MakeColorKey(silent=False):
    
    # Delete lingering
    plt.cla()
    
    # Initialize table
    colorKey = Table(DPI)
    x=0
    y=0
    
    # Title
    colorKey.AddCells(Cell(
                       x, x+2*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Stat Quality",
                        fontsize=HEADER_FONT_SIZE,
                        color="white",
                        lineColor="white"
                    ),
                    Cell(
                        x, x+2*CELL_WIDTH, y, y-2*CELL_HEIGHT,
                        content="",
                        color="white",
                        lineColor="white"
                    )
            )
    y -= CELL_HEIGHT
    
    # Headers
    colorKey.AddCells(
                   Cell(
                        x, x+CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Base Stat",
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
                    ),
                    Cell(
                        x + CELL_WIDTH, x+2*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Description",
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
                    )
    )
    y -= CELL_HEIGHT
   
    # Cells
    for baseStatColor in BASE_STAT_COLORS:
       colorKey.AddCells(
                   Cell(
                        x, x+CELL_WIDTH, y, y-CELL_HEIGHT,
                        content=Format(baseStatColor.value, True),
                        fontsize=BODY_FONT_SIZE,
                        color=baseStatColor.color
                    ),
                    Cell(
                        x + CELL_WIDTH, x+2*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content=baseStatColor.description,
                        fontsize=BODY_FONT_SIZE,
                        color=baseStatColor.color
                    )
       )
       y -= CELL_HEIGHT

    # Render and save
    colorKey.Save("color-key.png", silent=silent)
    

def Plot(statName, function, *args, 
         ylabel="", 
         savefilename="", 
         notedLevels=[20, 50, 100],
         silent=False):
    """
        function: any function that accepts the first two arguments as independent variables
        args: any constants that should be passed to function
    """

    # Variables
    if ylabel=="":
        ylabel = statName
    if savefilename=="":
        savefilename = statName
        
    # Delete lingering
    plt.cla()
    
    # New figure
    fig, ax = plt.subplots()

    # Do the plot
    levels = np.linspace(0, max(notedLevels), max(notedLevels)+1)
    ymax = 0
    for baseStatColor in BASE_STAT_COLORS:
        y = function(levels, baseStatColor.value, *args)
        for yi in y:
            ymax = max(ymax, yi)
        plt.plot(levels, y, color=baseStatColor.color, label=baseStatColor.value)
        
        
    # Gussy it up
    plt.grid(True)
    #plt.title(statName)
    plt.xlabel("Level")
    plt.ylabel(ylabel)
    
    # Should this be a log scale?
    if (ymax > 10000):
        plt.yscale("log")
    
    # Save figure
    plt.legend(loc='best')
    plt.savefig(savefilename + "-plot.png", transparent=True, dpi=DPI)
    if silent:
        plt.close("all")
    
    # Initialize table
    table = Table(DPI)
    x=0
    y=0
    
    # Title
    table.AddCells(Cell(
                       x, x+(len(notedLevels) + 1)*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content=ylabel,
                        fontsize=HEADER_FONT_SIZE,
                        color="white",
                        lineColor="white"
                    ),
                    Cell(
                       x, x+(len(notedLevels) + 1)*CELL_WIDTH, y, y-2*CELL_HEIGHT,
                        content="",
                        color="white",
                        lineColor="white"
                    )
            )
    y -= CELL_HEIGHT
    
    # "Level" header
    table.AddCell(Cell(
                       x+CELL_WIDTH + GAP_LINE_THICKNESS/2, x+CELL_WIDTH+len(notedLevels)*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Level",
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
           ))
    y -= CELL_HEIGHT
    
    # Construct column labels
    x0 = x
    table.AddCell(Cell(
                       x, x+CELL_WIDTH, y, y-CELL_HEIGHT,
                       content="Base Stat",
                       fontsize=HEADER_FONT_SIZE,
                       color=HEADER_COLOR
           ))
    x += CELL_WIDTH
    for level in notedLevels:
        table.AddCell(Cell(
                           x, x+CELL_WIDTH, y, y-CELL_HEIGHT,
                           content=level,
                           fontsize=HEADER_FONT_SIZE,
                           color=HEADER_COLOR
               ))
        x += CELL_WIDTH
    x = x0
    y -= CELL_HEIGHT
    y0 = y
    
    #Construct table body
    x0=x
    for baseStatColor in BASE_STAT_COLORS:
        x = x0
        table.AddCell(Cell(
                       x, x+CELL_WIDTH, y, y-CELL_HEIGHT,
                       color=baseStatColor.color,
                        content=Format(baseStatColor.value, True),
                        fontsize=BODY_FONT_SIZE
           ))
        x += CELL_WIDTH
        for level in notedLevels:
            statValue = function(level, baseStatColor.value, *args)
            table.AddCell(Cell(
                                   x, x+CELL_WIDTH, y, y-CELL_HEIGHT, 
                                   color=baseStatColor.color,
                                    content=Format(statValue),
                                    fontsize=BODY_FONT_SIZE
            ))
            x += CELL_WIDTH
        y -= CELL_HEIGHT
        
    # Extra line separating base stat labels from actual base stat values
    table.AddCell(Cell(
                       CELL_WIDTH, CELL_WIDTH + GAP_LINE_THICKNESS, y0 + CELL_HEIGHT, y0-len(BASE_STAT_COLORS)*CELL_HEIGHT,
                        color="black"
           ))
 
    # Render and save
    table.Save(savefilename + "-table.png", silent=silent)
    
def HasteCDRTable(baseCD=10, notedLevel=100, basePair=100, silent=False):
    
    # Initialize table
    table = Table(DPI)
    x=0
    y=0
    
    
    # Title
    table.AddCell(Cell(
                       x, x+2*CELL_WIDTH, y, y-2*CELL_HEIGHT,
                        content="Haste CD Reduction" + "\n" + "Base CD: " + Format(baseCD) + "s",
                        fontsize=HEADER_FONT_SIZE,
                        color="white",
                        lineColor="white"
           ))
    y -= 2*CELL_HEIGHT
    
    # Headers
    table.AddCells(
                   Cell(
                        x, x+CELL_WIDTH, y, y-2*CELL_HEIGHT,
                        content="Base Stat" + "\n" + "at Lv. {:.0f}".format(notedLevel, True),
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
                    ),
                    Cell(
                        x+CELL_WIDTH, x+2*CELL_WIDTH, y, y-2*CELL_HEIGHT,
                        content="New" + "\n" + "Cooldown",
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
                    )
       )
    y -= 2*CELL_HEIGHT
    
    # Cells
    x0 = x
    for baseStatColor in BASE_STAT_COLORS:
        x = x0
        table.AddCells(
                       Cell(
                            x, x+CELL_WIDTH, y, y-CELL_HEIGHT,
                            content=baseStatColor.value,
                            fontsize=BODY_FONT_SIZE,
                            color=baseStatColor.color
                        ),
                        Cell(
                             x+CELL_WIDTH, x+2*CELL_WIDTH, y, y-CELL_HEIGHT,
                             content=Format(baseCD/(1+Haste(notedLevel, baseStatColor.value, basePair)/100)),
                             color=NEUTRAL_CELL_COLOR
                         )
           )
        y -= CELL_HEIGHT
                    
    # Render and save
    table.Save("Haste-CD-reduction-table.png", silent=SILENT)
    
def Format(number, integer=False):
    if integer:
        return "{:.0f}".format(number)
    if -100 < number and number<100:
        return "{:.1f}".format(number).replace(".0", "")
    return si_format(number).replace(".0", "")
    
def Haste(level, baseStat, basePair):
    return level * (\
            0.00002*(baseStat)**2 * BasePairContribution(basePair) \
            + 0.017 * np.floor(level/10) \
    )
    
def Crit(level, baseStat, basePair):
    prevLevel = 10*np.floor((level+0.1)/10)
    nextLevel = 10*np.ceil((level+0.1)/10)
    prevStat = CritBaseStat(prevLevel, baseStat, basePair)
    nextStat = CritBaseStat(nextLevel, baseStat, basePair)
    ret = (nextStat-prevStat)*0.8*(level-prevLevel)/(nextLevel-prevLevel) + prevStat
    if hasattr(ret, "__len__"):
        for i in range(len(ret)):
            if ret[i]<0:
                ret[i]=0
    else:
        if ret < 0:
            ret = 0
    return ret
                       
    
def CritBaseStat(level, baseStat, basePair):
    return np.ceil(level/10)*0.0000000036*(baseStat)**4.2 * BasePairContribution(basePair) + 0.625*np.floor(level/10)
    
def HP(level, baseStat, basePair):
    return np.floor(2*baseStat*BasePairContribution(basePair)*level/100 + 10)*3**np.floor(level/10)
    
def StandardStat(level, baseStat, basePair):
    return np.floor(2*baseStat*BasePairContribution(basePair)*level/100 + 5)*3**np.floor(level/10)
    
def BasePairContribution(basePair):
    return (basePair/100)**0.25

def PlotBasePairContribution(notedPoints=[1, 50, 80, 90, 95], color="blue"):
    
    # The data
    x = np.linspace(1, 100, 100)
    y = BasePairContribution(x)
    
    # Plot line
    plt.plot(x, y, color=color)
    
    # Noted points
    y = []
    ax = plt.gca()
    yannotate = BasePairContribution(notedPoints[0]) - 0.1
    for i in range(len(notedPoints)):
        y.append(BasePairContribution(notedPoints[i]))
        plt.annotate("(" + "{:.0f}".format(notedPoints[i]) + ", " + "{:.2f}".format(y[i]) + ")",
                      xy=(notedPoints[i], y[i] + (-0.02 if yannotate < y[i] else 0.02) ),
                      xytext=(notedPoints[i], yannotate),
                      arrowprops=dict(facecolor='black', arrowstyle="->"),
                      ha="center"
          )
        yannotate += 0.21
    plt.scatter(notedPoints, y, color=color)
    
    # Gussy up
    plt.grid(True)
    plt.xlabel("Number of Base Pairs")
    plt.ylabel("Multiplier")
    
    # Save
    plt.savefig("base-pairs-plot.png", transparent=True, dpi=DPI)
    if SILENT:
        plt.close("all")

def PlotBasePairVsAtk(notedPoints=[1, 50, 70, 80, 90, 95, 100], baseStat=100, level=100, color=(0.4, 0.545, 1)):
    
    # The data
    x = np.linspace(1, 100, 100)
    y = StandardStat(level, baseStat, x)
    
    # Plot line
    plt.plot(x, y, color=color)
    
    # Noted points
    yrange = max(y)-min(y)
    y = []
    ax = plt.gca()
    texty = StandardStat(level, baseStat, notedPoints[0]) - 0.1*yrange
    for i in range(len(notedPoints)):
        y.append(StandardStat(level, baseStat, notedPoints[i]))
        plt.annotate("(" + "{:.0f}".format(notedPoints[i]) + ", " + Format(y[i]) + ")",
                      xy=(notedPoints[i], y[i] + (-0.02 if texty < y[i] else 0.02) * yrange ),
                      xytext=(notedPoints[i], texty),
                      arrowprops=dict(facecolor='black', arrowstyle="->"),
                      ha="center"
          )
        texty += yrange/len(notedPoints)
    plt.scatter(notedPoints, y, color=color)
    
    # Gussy up
    plt.grid(True)
    plt.xlabel("Number of Base Pairs")
    plt.ylabel("Attack")
    
    # Save
    plt.savefig("base-pairs-vs-attack-plot.png", transparent=True, dpi=DPI)
    if SILENT:
        plt.close("all")
        
def MutationsTable():
    
    # Initialize table
    table = Table(DPI)
    x=0
    y=0
    
    
    # Title
    table.AddCell(Cell(
                       x, x+3*CELL_WIDTH, y, y-2*CELL_HEIGHT,
                        content="Mutations List",
                        fontsize=HEADER_FONT_SIZE,
                        color="white",
                        lineColor="white"
           ))
    y -= 2*CELL_HEIGHT
    
    # Headers
    table.AddCells(
                   Cell(
                        x, x+CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Mutation",
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
                    ),
                    Cell(
                        x+CELL_WIDTH, x+2*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Pro",
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
                    ),
                    Cell(
                        x+2*CELL_WIDTH, x+3*CELL_WIDTH, y, y-CELL_HEIGHT,
                        content="Con",
                        fontsize=HEADER_FONT_SIZE,
                        color=HEADER_COLOR
                    )
       )
    y -= CELL_HEIGHT
    
    # Cells
    x0 = x
    for mutation in MUTATIONS:
        x = x0
        table.AddCells(
                       Cell(
                            x, x+CELL_WIDTH, y, y-CELL_HEIGHT,
                            content=mutation.name,
                            fontsize=BODY_FONT_SIZE,
                            color=NEUTRAL_CELL_COLOR
                        ),
                        Cell(
                             x+CELL_WIDTH, x+2*CELL_WIDTH, y, y-CELL_HEIGHT,
                             content=mutation.pro,
                             color=NEUTRAL_CELL_COLOR
                        ),
                        Cell(
                             x+2*CELL_WIDTH, x+3*CELL_WIDTH, y, y-CELL_HEIGHT,
                             content=mutation.con,
                             color=NEUTRAL_CELL_COLOR
                        )
           )
        y -= CELL_HEIGHT
                    
    # Render and save
    table.Save("mutations-table.png", silent=SILENT)
        
# Main execution
# ==============
if __name__ == "__main__":
    Main()