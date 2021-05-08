#!/usr/bin/env python3

import sys
import math

try:
    from tkinter import *
except ImportError:
    print('tkinter not found.. abort operation..')
    sys.exit(1)
    

w = 100
b = 10
class F(Frame):
    state = None
    def draw(self, state):
        if not self.state:
            self.state = state
        new = []
        for ra, rb in zip(self.state, state):
            row = []
            for a, b in zip(ra, rb):
                row.append((b, 1 if a != b else 0))
            new.append(row)
        self.state = state
        state = new
        [w.destroy() for w in self.winfo_children()]
        self.master.title("N-Puzzle")
        self.pack(fill=BOTH, expand=1)
        canvas = Canvas(self)
        for c, rows in enumerate(state):
            for r, col in enumerate(rows):
                x = r*w+b
                y = c*w+b
                col, ch = col
                color = "#8f8f8f"
                if not col:
                    color = "#bf9e65"
                elif ch:
                    color = "#c95562"
                canvas.create_rectangle(x, y, r*w + w, c*w + w, outline="#05f", fill=color)
                canvas.create_text(x+(w - b)/2, y+(w - b)/2, text=f"{col}", font=("Purisa", 32), justify=CENTER)
        canvas.pack(fill=BOTH, expand=1)

def main():
    if len(sys.argv) > 1 and sys.argv[1].isdigit():
        delay = int(sys.argv[1])
    else:
        delay = 1000
    root = Tk()
    frame = F()
    def update():
        try:
            inp = sys.stdin.readline()
            if inp.strip():
                print (inp, end='')
            inp = inp.strip().split(' ')
            if all([s.isdigit() for s in inp]):
                root.after(delay, update)
                s = int(math.sqrt(len(inp)))
                state = []
                for i in range(s):
                    p = []
                    for j in range(s):
                        p.append(int(inp[i * s + j], 10))
                    state.append(p)
                
                root.geometry(f"{len(state) * w + b * (len(state) - 2)}x{len(state) * w + b * (len(state) - 2)}")
                frame.draw(state)
            else:
                root.after(10, update)
        except Exception as e:
            print(e)
            return
    update()
    mainloop()

if __name__ == '__main__':
    main()
