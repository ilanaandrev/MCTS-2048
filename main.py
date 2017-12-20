############################################
# Project: MCT-TFE
# File: main.py
# By: ProgrammingIncluded
# Website: ProgrammingIncluded.com
############################################

from TFE import *
from MCT import *
import random as rnd

def main():
    tfe = TFE()
    mct = MCT(tfe)
    print mct.run(1)

if __name__ == '__main__':
    main()