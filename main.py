############################################
# Project: MCT-TFE
# File: main.py
# By: ProgrammingIncluded
# Website: ProgrammingIncluded.com
############################################

from TFE import *
import random as rnd

def main():
    tfe = TFE()
    tfe.putNew()
    print tfe.grid

    while (not tfe.isLose()) or tfe.isWin():
        select = rnd.randint(0, 3)
        tfe.moveGrid(MOV_OPT[select])
        tfe.putNew()
        print tfe.grid

if __name__ == '__main__':
    main()