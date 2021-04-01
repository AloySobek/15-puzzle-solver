from __future__ import print_function
import random
import sys

def genNPuzzle(dim):
    assert dim >= 0
    print(dim)
    a = list(range(0, dim * dim))
    random.shuffle(a)
    for i in range(0, dim):
        for j in range(0, dim):
            print(a[(i*dim) + j], end=' ' * random.randrange(1, 4))
        print('\n', end='')


if __name__ == '__main__':
    if len(sys.argv) > 1 and sys.argv[1] in ('-h', '--help'):
        print('python genNPuzzle.py WIDTH(int)')
        sys.exit(0)

    for i in range(0, 3):
        if random.randrange(0, 2):
            print(["# Comment here\n", "# Comment\tthere\n", "# Comment over\n", "# Comment here\n"][random.randrange(0, 3)], end='')
    
    d = random.randrange(0, 25)

    try:
        d = int(sys.argv[1], 10)
    except (ValueError, IndexError):
        pass
        
    genNPuzzle(d)
