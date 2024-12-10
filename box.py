# A small python script that takes in a line as a set of points and draws the line using ascii characters
# No practical use I could think of, but a fun little idea I had one day

import numpy as np
import curses
stdscr = curses.initscr()
curses.cbreak()
stdscr.keypad(True)
curses.noecho()

lines = [(0,0),(1,0),(1,1),(2,1),(2,2)]
#─┐ 
# └┐
#  │

def box3(a,b,c):    #used when the current cell connects 2 adjecent cells
    if(np.subtract(a,b)[0]==-1 and np.subtract(b,c)[1]<1):
        return '┐'
    elif(np.subtract(a,b)[0]==-1 and np.subtract(b,c)[0]<1):
        return '┌'
    elif(np.subtract(a,b)[0]==0 and np.subtract(a,b)[1]==-1 and np.subtract(b,c)[0]<1 and np.subtract(b,c)[1]==0):
        return '└'
    elif(np.subtract(a,b)[0]==0 and np.subtract(b,c)[0]==1):
        return '┘'
    else:
        return ''

def box2(a,b):    #used when the current cell connects 3 adjecent cells
    if(np.subtract(a,b)[1]==0):
        return '─'
    elif(np.subtract(a,b)[0]==0):
        return '│'
    else:
        return ''

def arr_box(arr):   #returns the required characters as a list
    print(box2(arr[0], arr[1]),end='')
    for i in range(1,len(arr)-1):
        print(box3(arr[i-1], arr[i], arr[i+1]),end='')
    print(box2(arr[len(arr)-2], arr[len(arr)-1]))

def arr_disp(arr):  #a sample display using curses
    stdscr.addch(arr[0][1],arr[0][0],box2(arr[0], arr[1]))
    for i in range(1,len(arr)-1):
        stdscr.addch(arr[i][1],arr[i][0],box3(arr[i-1], arr[i], arr[i+1]))
    stdscr.addch(arr[len(arr)-1][1],arr[len(arr)-1][0],box2(arr[len(arr)-2], arr[len(arr)-1]))

if __name__ == "__main__":
    arr_disp(lines)
    stdscr.refresh()
    stdscr.getch()
    curses.endwin()
