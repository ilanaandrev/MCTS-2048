############################################
# Project: MCT-TFE
# File: main.py
# By: ProgrammingIncluded
# Website: ProgrammingIncluded.com
############################################

from TFE import *
from MCT import *
import time
import random as rnd

MONTE_CARLO_RUN = 10

def test_tfe():
    tfe = TFE()
    tfe.grid = np.array([2, 2, 8, 2, 0, 8, 32, 32, 0, 0,2, 4, 0, 0, 0, 2]).reshape((4,4))
    print tfe.grid
    tfe.moveGrid("d")
    print tfe.grid
    tfe.moveGrid("r")
    print tfe.grid

def main():
    tfe = TFE()
    # generate a new
    tfe.putNew()
    print "STARTING BOARD: "
    print tfe.grid
    print ""

    mct = MCT()
    while (not tfe.isWin()) and (not tfe.isLose()):

        start = time.clock() 

        old_grid = np.copy(tfe.grid)

        print "*********************"
        act = mct.run(tfe, MONTE_CARLO_RUN, True)

        if not np.array_equal(tfe.grid, old_grid):
            print "NOT EQUAL"
            print old_grid
            print tfe.grid
            exit()

            
        print "AI SELECT ACTION: " + act
        print "*********************"
        print "BEFORE: "
        print tfe.grid
        print ""

        print "*********************"
        print "AFTER: "

        # move grid
        tfe.moveGrid(act)

        # generate a new
        tfe.putNew()

        print tfe.grid
        print ""

        print "TIME TAKEN FOR STEP: " + str(time.clock() - start)
        print ""
    
    print "FINISHED: "
    print tfe.grid
    print ""

    print "IS WIN?: "
    print tfe.isWin()
    print ""
    
    print "IS LOSE?: "
    print tfe.isLose()
    print ""


if __name__ == '__main__':
    #test_tfe()
    main()