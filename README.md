# 15-puzzle-solver

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
