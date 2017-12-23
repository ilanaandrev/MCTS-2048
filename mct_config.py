############################################
# Project: MCT-TFE
# File: mct_config.py
# By: ProgrammingIncluded
# Website: ProgrammingIncluded.com
############################################

from TFE import *
import numpy as np


# Number of 0's minimum before starting non-greedy approach
GREEDY_THRESH = 16
# Allow greedy algorithm for the first few squares.
GREEDY_CONTROL = True
GREEDY_INIT_ONLY = True

MONTE_CARLO_RUN = 10

# TODO: Value Heuristic
VAL_H = True
# Directions of corners to check, across.
V_DIR = 4

# Branch Weight
LEAF_WIN_WEIGHT = 7000

# Max children for each turn. 4 directions, 16 available, 2 possible gen values.
MAX_CHILDREN = 2 * 4 * 16

# Keys for direction
DIR_KEY = {"u": 0, "d": 1, "l": 2, "r":3}
DIR_VAL = {v: k for k, v in DIR_KEY.iteritems()}

# Heuristic filter used for weighting corners. n^2 weighted.
VFB = np.array([[64, 18, 4, 1], [18, 18, 4, 1], [18, 18, 18, 1], [1, 1, 1, 1]]).reshape((4,4))
FILTERS = [VFB, np.rot90(VFB, 1), np.rot90(VFB, 3), np.rot90(VFB, 2), np.rot90(VFB, 4)]

# Used for simulation
SIM = TFE()