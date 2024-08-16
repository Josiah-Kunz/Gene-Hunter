# -*- coding: utf-8 -*-
"""
Created on Thu Aug 15 21:19:51 2024

@author: Josiah D. Kunz
"""

class BaseStatColor:
    
    value = 0
    color = None
    description = ""
    
    def __init__(self, value, color, description):
        self.value = value
        self.color = color
        self.description = description