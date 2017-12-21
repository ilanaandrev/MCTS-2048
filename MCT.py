from TFE import *
import numpy as np
import random as rnd
import math
import time

# Number of 0's minimum before starting non-greedy approach
GREEDY_THRESH = 15
# Allow greedy algorithm for the first few squares.
GREEDY_CONTROL = True

MAX_CHILDREN = 2 * 4 * 16

DIR_KEY = {"u": 0, "d": 1, "l": 2, "r":3}
DIR_VAL = {v: k for k, v in DIR_KEY.iteritems()}

SIM = TFE()

class Node:
    option = 0
    parent = None
    total_games = 0
    total_wins = 0
    UCB = 0
    grid = None
    children = np.array([])

    # Array to store what options have already been done.
    # Should be at most 128
    children_options = np.array([])

    # Each node must contain a move and new tile appearance option.
    # can also be done to save a snapshot of the grid, but for now, no need.
    def __init__(self, parent, option, grid):
        self.option = option
        self.parent = parent
        # Generate options based off availability
        self.children_options = self.genOpt(grid)
        self.grid = np.copy(grid)
    
    # Returns a grid
    def optToGrid(self, opt):
        val = int(opt / (4 * 16))
        opt -= val * 4 * 16
        loc = opt / 4
        dir = DIR_VAL[opt % 4]
            
        SIM.grid = np.copy(self.grid)
        SIM.moveGrid(dir)
        res = SIM.grid
        if val == 0:
            res[loc / 4, loc % 4] = 2
        else:
            res[loc / 4, loc % 4] = 4
    
        return res


    # given current grid, generate some options
    def genOpt(self, grid):
        # Can save if necessary
        SIM.grid = np.copy(grid)
        after_grid = SIM.availDir()

        # Move
        dir = [DIR_KEY[k] for k, v in after_grid.iteritems()]
        # Then generate
        res = []
        for k, v in after_grid.iteritems():
            v_f = v.flatten("K")
            # Multiply to have unique ID for each range.
            # Think of it as an unique array index for each config.
            res += [DIR_KEY[k] + 4 * (y[0] + 16 * 0) for y in np.argwhere(v_f == 0).tolist()]
            res += [DIR_KEY[k] + 4 * (y[0] + 16 * 1) for y in np.argwhere(v_f == 0).tolist()]

        return np.array(res)
        
    # Create a new child for the node, if possible.
    # Does a check to see if possible.
    # Returns false if cannot create child.
    # Mutates tfe
    def create_child(self):
        if self.children_options.size == 0:
            return False

        arg = rnd.randint(0, self.children_options.size - 1)
        opt = self.children_options[arg]

        # Delete the option.
        self.children_options = np.delete(self.children_options, arg)
        result = Node(self, opt, self.optToGrid(opt))
        self.children = np.append(self.children, result)
        return result

    def hasUCB(self):
        return self.total_games != 0

    def UCB(self):
        return self.UCB


class MCT:
    # Greedy algorithm for faster approach
    # Select the direction with highest direct yield
    def greedy(self, tfe):
        res = tfe.availDir()
        scores = []
        dir_save = []
        for k, v in res.iteritems():
            v = v.flatten("K")
            res = [0 if x==0 else math.log(x, 2) for x in v]
            scores.append(sum(res))
            dir_save.append(k)
        
        arg = np.argmax(scores)
        return dir_save[arg]

    # Run the AI
    # Returns best direction to select next.
    def run(self, tfe, sec, noNone = False):
        if GREEDY_CONTROL and np.argwhere(tfe.grid.flatten() == 0).size > GREEDY_THRESH:
            return self.greedy(tfe)
    
        root = Node(None, -1, tfe.grid)
        print "\nBRANCHES: " + str(root.children_options.size)
        
        trav = []
        t_end = time.time() + sec
        # Monte Carlo loop
        while time.time() <= t_end or noNone:
            cur_node = root
            SIM.grid = cur_node.grid
            # Keep going until leaf node.
            while (not SIM.isLose()) and (not SIM.isWin()):
                # check time again in inner loop
                if time.time() > t_end and (not noNone):
                    break

                res = cur_node.create_child()
                if res == False:
                    noNone = False
                    # save snapshot
                    trav.append(cur_node)
                    # Go down the highest ucb.
                    cur_node = self.getHighestUCB(cur_node.children)
                else:
                    # otherwise, we have created a child
                    trav.append(res)
                    cur_node = res
                SIM.grid = cur_node.grid
                #print cur_node.grid
            
            # End if time is ended
            if time.time() > t_end and (not noNone):
                break

            # Save the last node / leaf node
            trav.append(cur_node)

            if tfe.isWin():
                self.backPropagate(trav, 1)
            else:
                self.backPropagate(trav, 0)
        # Select a result
        # Check makesure we have all children
        if root.children_options.size != 0:
            return None

        highest = self.getHighestUCB(root.children)
        opt = highest.option
        z = int(opt) / (4 *  16)
        opt -= z * 4 * 16
        return DIR_VAL[opt % 4]


    def backPropagate(self, trav, win):
        # Backpropagate
        while len(trav) != 0:
            n = trav.pop()
            n.total_games += 1
            n.total_wins += win
            # calculate ucb
            if n.parent != None:
                n.UCB  = (n.total_wins /n.total_games) + 1.6 * math.sqrt(math.log(n.parent.total_games + 1) / n.total_games) 
                # update siblings as well
                for s in n.parent.children:
                    s.UCB = (s.total_wins /s.total_games) + 1.6 * math.sqrt(math.log(s.parent.total_games + 1) / s.total_games)


    def getHighestUCB(self, children):
        # Check UCB, select highest UCB
        sel = None
        sel_val = -1
        for child in children:
            if sel_val < child.UCB:
                sel = child
                sel_val = child.UCB
        
        return sel