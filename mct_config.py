############################################
# Project: MCT-TFE
# File: mct_config.py
# By: ProgrammingIncluded
# Website: ProgrammingIncluded.com
############################################

from TFE import *
import numpy as np

VFB = np.array([[4, 3, 2, 1], [3, 3, 2, 1], [2, 2, 2, 1], [1, 1, 1, 1]]).reshape((4,4))
FILTERS = [VFB, np.rot90(VFB, 1), np.rot90(VFB, 2), np.rot90(VFB, 3), np.rot90(VFB, 4)]

# Number of 0's minimum before starting non-greedy approach
GREEDY_THRESH = 15
# Allow greedy algorithm for the first few squares.
GREEDY_CONTROL = True

MONTE_CARLO_RUN = 0

# Value Heuristic
VAL_H = True
# Directions of corners to check
V_DIR = 4

MAX_CHILDREN = 2 * 4 * 16

DIR_KEY = {"u": 0, "d": 1, "l": 2, "r":3}
DIR_VAL = {v: k for k, v in DIR_KEY.iteritems()}

# Used for simulation
SIM = TFE()