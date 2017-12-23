# Monte Carlo Tree Search for 2048
## General Description
This is a MCTS AI implementation in order to play 2048.
Includes a basic 2048 logic. Implementations of MCTS and 2048 Game are not optimal, this is a proof of concept project that is not funded. This was done as a Winter Break 2017 project as a MS-CSE students at UCSD with emphasis in AI/ML (more info about author on bottom).

2048 has been shown to be NP-HARD.

## Heuristic Methodologies
1. Greedy

   Greedily find the next direction that yields the most merges. No consideration to newly appeared values and their probabilities. Greedy threshold, if used as terminology, means the minimum amount of zeroes allowed before naive or corner MCTS kicks in.

2. Naive MCTS

   Run Monte Carlo Tree Search without any value function. Just run as many simulations as possible.

3. Corner Weighted

   Weight configurations where larger number tiles are valued more when near the corners. There are three version, 1, 2, and 4 corner versions. Where we check for only top-left corner; top-left, bottom-right; and all four corners. There can be three if needed by editing code.

## Discoveries
### Greedy
Greedy does not work well, at all. No seriously. This was used mainly for debugging at first and to save some runtime for 60 to 120 second runs per move. This will lead to about tile 128 to 64 with enough luck. Mainly good for remove the first few choices. So setting threshold to 12 is a good way to kick start a search because the first 3-4 tiles or so do not really play a big role.

### Naive MCTS
In theory this is enough to solve the problem. Due to the implementaiton of this project in Python, Naive MCTS is far too slow to be effective. However, with this result on vanilla Python can go tiles from 64 to 256.

Interesting observation to note is that the algorithm through tree search can detect that the weighted tiles should be clumped together. Furthermore, a priority should be given that maximizes space towards end-game.

### Corner Weighted
ASAP approach (one branch sample per children of root) takes us in the range of 128 to 512. This heuristic takes advantage of the fact that space should be maximized by clumping things in corners and that heavy nodes should be clumped together.

### Future Research
Checkered patterns are bad in 2048. Checkered patterns mean more directional movement is required to break up the parity. A future heuristic check on these parity can be done. The parity's resolution should be proportional to the space allowed. The theory is the allow detection of these parity's will allow MCTS to find the optimal resolution.

## Requirements
Python 2.x and Numpy

## Python Files
| File Name | Description |
| ---------------- |:-------------:|
| main.py | Main file to start an instance of MCTS and 2048. |
| MCT.py | File housing Monte Carlo Tree Search. |
| MCTNode.py | File to hold node implementation for MCTree. |
| TFE.py | File to hold 2048 program. |
| mct_config.py | File containing configurations for the program. |

## Naive Greedy Output
> output_t_g_m.txt

t: Time minimum per move.

g: Greedy algorithm that will run until g nodes exist.

m: Output id for (t, g).

Note: ASAP means t = 0 and g = 16. As a result, will always return an answer as soon as it can.

## Heuristic Output
Folders outline type of heuristic approach. 
See Heuristic Methodologies for categories of folder.
HEAVY folders mean that the corners are weighted more steeply and the leaf nodes are weighted more.

## Todo
* Fix Values in Corner Heuristic to remove overflow on large times.

## Common Questions
### Why Python?
This project was a proof of concept. If the results are shown to work on Python then we know that a well implemented low level system can perform 10x - 100x faster. 

### Will there be a C++ or faster eversion?
Only if there are enough people who want it. Also depending on my schedule/priorities.

### Can I Use This Idea for a Better Version or Iteration?
Sure! I mean, MCST is a methodology that has been known for a while. If you feel that this project has lead significantly to your next project, I would greatly appreciate a shout out or link to my website :) Good luck!

## About the Author
More info about the author can be found at the [ProgrammingIncluded website](http://programmingincluded.com/aboutme/)

I am always looking for feedback. If someone could fund me for my masters for the quarters when I don't have funds, I would greaty appreciate it....