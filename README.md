# Monte Carlo Tree Search for 2048 (CPP Ver.)
## General Description
This is a MCTS AI implementation in order to play 2048.
Includes a basic 2048 logic. Implementations of MCTS and 2048 Game are not optimal, this is a proof of concept project that is not funded. This was done as a Winter Break 2017 project as a MS-CSE student at UCSD with emphasis in AI/ML (more info about author on bottom).

2048 has been shown to be NP-HARD.

## Heuristic Methodologies (CPP Ver.)
1. Naive MCTS

   Run Monte Carlo Tree Search without any value function. Just run as many simulations as possible.

2. Monotonically Weighted

   Give more reward for orientations with increasing columns and rows. Winning boards are given high positive weights and negative of that for losing nodes.

## Discoveries
### Naive MCTS
In theory this is enough to solve the problem. C++ version can go around 512 with 1 second thinking time.

Interesting observation to note is that the algorithm through tree search can detect that the weighted tiles should be clumped together. Furthermore, a priority should be given that maximizes space towards end-game.

### Monotonically Increasing
ASAP approach (one branch sample per children of root) takes us in the range of 512 to 1024. This heuristic takes advantage of the fact that space should be maximized by clumping things in corners and that heavy nodes should be clumped together.

### Future Research
Checkered patterns are bad in 2048. Checkered patterns mean more directional movement is required to break up the parity. A future heuristic check on these parity can be done. The parity's resolution should be proportional to the space allowed. The theory is the allow detection of these parity's will allow MCTS to find the optimal resolution.

## CPP Files
| File Name | Description |
| ---------------- |:-------------:|
| main.cpp | Main file to start an instance of MCTS and 2048. |
| MCT.cpp | File housing Monte Carlo Tree Search. |
| MCTNode.cpp | File to hold node implementation for MCTree. |
| TFE.cpp | File to hold 2048 program. |
| grid_util.cpp | File to hold grid manipulation helper functions. |
| config.cpp | Config files. |

## Edits
Ilana added a running loop within main to continue playing up to a 100 games, though this would take a long time. Ilana also had "my-naive-output" showing the output she got after running 16 games herself. Main function was changed to print to seperate txt files rather than the terminal.

## Common Questions
### Can I Use This Idea for a Better Version or Iteration?
Sure! I mean, MCST is a methodology that has been known for a while. If you feel that this project has lead significantly to your next project, I would greatly appreciate a shout out or link to my website :) Good luck!

## About the Author
More info about the author can be found at the [ProgrammingIncluded website](http://programmingincluded.com/aboutme/)

I am always looking for feedback. If someone could fund me for my masters for the quarters when I don't have funds (the uncertainty of CSE Master's gradlife) or would like to hire me, I would greaty appreciate it, thanks!
