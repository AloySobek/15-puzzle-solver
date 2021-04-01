from __future__ import print_function
import random
import sys

def genNPuzzle(dim, lim):
    assert dim >= 0
    assert lim >= 0
    print(dim)
    for _ in range(0, dim):
        for n in range(0, dim):
            print(random.randrange(0, lim), end=' ' * random.randrange(1, 4))
        print('\n', end='')


if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] in ('-h', '--help'):
        print('python genNPuzzle.py WIDTH(int) UPPERLIMIT(int)')
        sys.exit(0)

    for i in range(0, 3):
        if random.randrange(0, 2):
            print(["# Comment here\n", "# Comment\tthere\n", "# Comment over\n", "# Comment here\n"][random.randrange(0, 3)], end='')
    
    d = random.randrange(0, 100)
    l = 4294967295
    try:
        d = int(sys.argv[1], 10)
    except (ValueError, IndexError):
        pass
    try:
        l = int(sys.argv[2], 10)
    except (ValueError, IndexError):
        pass
        
    genNPuzzle(d, l)
