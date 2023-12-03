This is a simple CLI application that uses Prof. Donald Knuth's <a href="https://arxiv.org/abs/cs/0011047" target="_blank">Algorithm DLX</a> to find all the solutions of a given sudoku puzzle. The blueprint to reduce a sudoku puzzle into an exact cover problem that can be worked upon by DLX was obtained from <a href="https://www.kth.se/social/files/58861771f276547fe1dbf8d1/HLaestanderMHarrysson_dkand14.pdf" target="_blank">this</a> paper.

To use this application, one can either :
1. Clone this repository and compile it themselves, or
2. Download the executable from the Releases tab for the appropriate OS and run it from a command line terminal of your choice.

The puzzle to be solved must be written in a single line with the clues as it is and the empty spaces replaced by '.'

For example,

![puzzle](https://github.com/BAGUVIX456/sudoku-dlx/assets/85876638/9e2ddf87-fcdb-4211-ba95-7b29a4c0fed4)

must be written as
`..9.6...4.....47.....12..659.4.75..373...1..66....34.146.7.215.2....6.8...1.....2`


![sudoku](https://github.com/BAGUVIX456/sudoku-dlx/assets/85876638/1520ede8-dbbc-4383-acfd-568b800b4163)

