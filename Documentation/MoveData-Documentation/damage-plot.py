# -*- coding: utf-8 -*-
"""
Created on Thu Aug 15 21:13:48 2024

@author: Josiah D. Kunz
"""

# Class definitions
from class_definitions import *

# Settings
NOTED_LEVELS = [20, 50, 100]
BASE_STAT_COLORS = [
                BaseStatColor(0,    "red",          "Minimum"),
                BaseStatColor(50,   "orange",       "Bad"),
                BaseStatColor(100,  "gold",         "Average"),
                BaseStatColor(120,  "lawngreen",    "Good"),
                BaseStatColor(150,  "cyan",         "Specialist"),
                BaseStatColor(200,  "violet",       "Boss")
        ]
DPI = 300
SILENT = True # closes plots automatically, etc.


# Main execution
def Main():
    
    # Various plots
    PlotDamage([100], 
               [100], 
               [5, 10, 50, 75, 100], 
               "bp")
    PlotDamage([100], 
               [100], 
               [5, 10, 50, 75, 100], 
               "bp", True)
    PlotDamage([50, 100, 120, 150, 200], 
               [100], 
               [50], 
               "batk")
    PlotDamage([100], 
               [50, 100, 120, 150, 200], 
               [50], 
               "bdef")
    PlotEndgameDamage([5, 10, 50, 75, 100])
    


# The damage equation
def Damage(level, base_power, attack, defense, crit_multiplier, rand_fluct,
           stab_mult, type_adv_mult):
    return ((0.4*level+2)*base_power/50*attack/defense + 2) \
        * crit_multiplier * rand_fluct * stab_mult * type_adv_mult \
        * 3**np.floor(level/10)

        
# The healing equation
def Healing(level, base_power, attack, defense, crit_multiplier, rand_fluct,
           stab_mult, type_adv_mult):
    return ((0.4*level+2)*base_power/50*attack/100 + 2) \
        * crit_multiplier * rand_fluct * stab_mult \
        * 3**np.floor(level/10)


# Packages
import matplotlib.pyplot as plt
import numpy as np

def PlotDamage(base_atk_range, base_def_range, bp_range
               , variation="bp" # bp, batk, bdef
               , norm_by_hp = False
               ):
    
    # Clear lingering
    plt.cla()
    
    # Establish level range
    levels = np.linspace(0, max(NOTED_LEVELS), max(NOTED_LEVELS)+1)
    
    # Do we need to normalize by anything?
    norm_value = 1
    if norm_by_hp:
        norm_value = HP(levels, 100, 100)/100
    
    
    # Need this to determine if it's a log scale or not
    ymax = 0
    
    # Iterate through variables
    for bp in bp_range:
        for attack in base_atk_range:
            for defense in base_def_range:
    
                # Do the plot
                y = Damage(levels, bp, 
                           StandardStat(levels, attack, 100),  
                           StandardStat(levels, defense, 100), 
                           1, 1, 1, 1)/norm_value
                
                # Update the max
                ymax = max(ymax, max(y))
                
                # Legend setup
                if variation=="bp":
                    label=f"Base Power: {bp:.0f}"
                elif variation=="batk":
                    label=f"Base Atk: {attack:.0f}"
                else:
                    label=f"Base Def: {defense:.0f}"
                plt.plot(levels, y, label=label)
                    
    
    # Should this be a log scale?
    if (ymax > 10000):
        plt.yscale("log")                
    
    # Gussy it up
    plt.grid(True)
    plt.xlabel("Level")
    plt.legend(loc='best')
    
    # y label depends on if we're normalizing
    plt.ylabel("Damage")
    if norm_by_hp:
        plt.ylabel("% Health")
        
    # Title
    title="Damage"
    if norm_by_hp:
        title += " by % Health"
    title += ":\n"
    if variation=="bp":
        title += "Base Power"
    elif variation=="batk":
        title += "Base Attack"
    else:
        title += "Base Defense"
    title += " Variation"
    plt.title(title)
        
    # Get best name for save file
    filename = "base-power"
    if variation=="batk":
        filename="base-attack"
    elif variation=="bdef":
        filename="base-defense"
    filename += "-variation"
    
    # Normalized by HP or no?
    if norm_by_hp:
        filename += "-normed"
    
    # Add extension
    "-plot.png"
    
    # Save figure
    plt.savefig(filename, 
                #transparent=True, 
                dpi=DPI)
    if SILENT:
        plt.close("all")

def StandardStat(level, baseStat, basePair):
    return np.floor(2*baseStat*BasePairContribution(basePair)*level/100 + 5)*3**np.floor(level/10)

def HP(level, baseStat, basePair):
    return np.floor(2*baseStat*BasePairContribution(basePair)*level/100 + 10)*3**np.floor(level/10)

def BasePairContribution(basePair):
    return (basePair/100)**0.25

def PlotEndgameDamage(bp_range):
    
    # Define endgame
    levels = np.linspace(90, 100, 11)
    
    # Get the max health @ lv. 100
    max_hp = HP(100, 100, 100)
    norm_value = max_hp/100 # since percentage
    
    # Constants
    attack=100
    defense=100
    
    # Again, log or no? IDK!
    ymax = 0
    
    # Iterate over base power variation
    for bp in bp_range:
    
        # Do the plot
        y = Damage(levels, bp, 
                   StandardStat(levels, attack, 100),  
                   StandardStat(levels, defense, 100), 
                   1, 1, 1, 1)/norm_value
        
        # Update the max
        ymax = max(ymax, max(y))
        
        # Legend setup
        label=f"Base Power: {bp:.0f}"
        plt.plot(levels, y, label=label)
    
    # Should this be a log scale?
    if (ymax > 10000):
        plt.yscale("log")                
    
    # Gussy it up
    plt.grid(True)
    plt.xlabel("Level")
    plt.legend(loc='best')
    plt.ylabel("% Health")
    plt.title("Damage vs Lv. 100:\n" + "Base Power Variation")
    
    # Save figure
    plt.savefig("endgame-damage-plot.png", 
                #transparent=True, 
                dpi=DPI)
    if SILENT:
        plt.close("all")
    
    
    
    

"""
# Initialize table
table = Table(DPI)
x=0
y=0

# Title
table.AddCells(Cell(
                   x, x+(len(NOTED_LEVELS) + 1)*CELL_WIDTH, y, y-CELL_HEIGHT,
                    content=ylabel,
                    fontsize=HEADER_FONT_SIZE,
                    color="white",
                    lineColor="white"
                ),
                Cell(
                   x, x+(len(NOTED_LEVELS) + 1)*CELL_WIDTH, y, y-2*CELL_HEIGHT,
                    content="",
                    color="white",
                    lineColor="white"
                )
        )
y -= CELL_HEIGHT

# "Level" header
table.AddCell(Cell(
                   x+CELL_WIDTH + GAP_LINE_THICKNESS/2, x+CELL_WIDTH+len(NOTED_LEVELS)*CELL_WIDTH, y, y-CELL_HEIGHT,
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
for level in NOTED_LEVELS:
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
    for level in NOTED_LEVELS:
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
"""

if __name__ == "__main__":
    Main()