# 15-puzzle-solver

[15 puzzle](https://en.wikipedia.org/wiki/15_puzzle) solver written in C++

## Usage

```
Usage: n-puzzle [options] [file]

Allowed options:
  --help                               show help message
  -r [ --random ] arg (=3)             random puzzle
  -p [ --puzzle ] arg                  puzzle file
  -s [ --solution ] arg (=snail)       solution pattern
  -a [ --algorithm ] arg (=A*)         solve algorithm
  -t [ --algo-type ] arg (=UCS+GREEDY) solve algorithm type
  -h [ --heuristic ] arg (=manhattan)  heuristic function
```

Build
========

`cmake -B build && cmake --build build`
