from TFE import *
import numpy as np
import random as rnd
import math
import time

MAX_CHILDREN = 2 * 4 * 16
DIR_KEY = {"u": 0, "d": 1, "l": 2, "r":3}
DIR_VAL = {v: k for k, v in DIR_KEY.iteritems()}

class Node:
    option = 0
    parent = None
    total_games = 0
    total_wins = 0
    UCB = 0
    children = np.array([])

    # Array to store what options have already been done.
    # Should be at most 128
    children_options = np.array([])

    # Each node must contain a move and new tile appearance option.
    # can also be done to save a snapshot of the grid, but for now, no need.
    def __init__(self, parent, option, tfe):
        self.option = option
        self.parent = parent
        # Generate options based off availability
        self.children_options = self.genOpt(tfe)
    
    # Returns a grid
    def optToTFE(self, opt, tfe):
        dir = DIR_VAL[opt % 16]
        loc = int((opt / 16) % 2)
        val = int(opt / (16 * 2))
        
        tfe.moveGrid(dir)
        tfe.grid[loc / 4, loc % 4] = val
        return tfe


    def genOpt(self, tfe):
        # Can save if necessary
        after_grid = tfe.availDir()

        # Move
        dir = [DIR_KEY[k] for k, v in after_grid.iteritems()]
        # Then generate
        res = []
        for k, v in after_grid.iteritems():
            v_f = v.flatten()
            # Multiply to have unique ID for each range.
            # Think of it as an unique array index for each config.
            res += [DIR_KEY[k] + 16 * (y + 2 * 0) for y in np.nditer(np.argwhere(v_f == 0), ["zerosize_ok"])]
            res += [DIR_KEY[k] + 16 * (y + 2 * 1) for y in np.nditer(np.argwhere(v_f == 0), ["zerosize_ok"])]
        
        return np.array(res)
        
    # Create a new child for the node, if possible.
    # Does a check to see if possible.
    # Returns false if cannot create child.
    # Mutates tfe
    def create_child(self, tfe):
        if self.children_options.size == 0:
            return False

        arg = rnd.randint(0, self.children_options.size - 1)
        opt = self.children_options[arg]

        # Delete the option.
        self.children_options = np.delete(self.children_options, arg)
        result = Node(self, opt, self.optToTFE(opt, tfe))
        self.children = np.append(self.children, result)
        print self.children_options.size
        return result

    def hasUCB(self):
        return self.total_games != 0

    def UCB(self):
        return float(self.total_wins) / self.total_games


class MCT:
    def __init__(self, tfe):
        self.tfe = tfe

    # Run the AI
    # Returns best direction to select next.
    def run(self, sec):
        grid_original = self.tfe.grid.copy()
        root = Node(None, -1, self.tfe)
        
        trav = []
        t_end = time.time() + 60 * sec
        # Monte Carlo loop
        while time.time() <= t_end:
            cur_node = root
            # Keep going until leaf node.
            while (not self.tfe.isLose()) and (not self.tfe.isWin()):
                # check time again in inner loop
                if time.time() > t_end:
                    break

                # check if we should go down children
                res = cur_node.create_child(self.tfe)
                if res == False:
                    # save snapshot
                    trav.append(cur_node)
                    # Go down the highest ucb.
                    print cur_node.children
                    cur_node = self.getHighestUCB(cur_node.children)
                else:
                    # otherwise, we have created a child
                    trav.append(res)
                    cur_node = res
            
            # End if time is ended
            if time.time() > t_end:
                break

            # Save the last node / leaf node
            trav.append(cur_node)
            if self.tfe.isWin():
                self.backPropagate(trav, 1)
            else:
                self.backPropagate(trav, 0)
            
        # restore tfe
        self.tfe.grid = grid_original
        # Select a result
        # Check makesure we have all children
        if root.children_options.size != 0:
            return None

        print root.children
        highest = self.getHighestUCB(root.children)
        return DIR_VAL[highest.option % 16]


    def backPropagate(self, trav, win):
        # Backpropagate
        while len(trav) != 0:
            n = trav.pop()
            n.total_games += 1
            n.total_wins += win
            # calculate ucb
            if n.parent != None:
                n.UCB  = 1.6 * math.sqrt(math.log(n.parent.total_games + 1) / n.total_games) 

    def getHighestUCB(self, children):
        # Check UCB, select highest UCB
        sel = None
        sel_val = -1
        for child in children:
            if sel_val < child.UCB:
                sel = child
                sel_val = child.UCB
        
        return sel