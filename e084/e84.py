#!/usr/bin/python
# -*- encoding: utf-8 -*-

import sys
from collections import defaultdict
from random import randint, shuffle

board = ["GO", "A1", "CC1", "A2", "T1", "R1", "B1", "CH1", "B2", "B3", "JAIL",
"C1", "U1", "C2", "C3", "R2", "D1", "CC2", "D2", "D3", "FP", "E1", "CH2", "E2",
"E3", "R3", "F1", "F2", "U2", "F3", "G2J", "G1", "G2", "CC3", "G3", "R4",
"CH3", "H1", "T2", "H2"]

DICE_MAX = 4
def dice():
    global DICE_MAX
    return (randint(1,DICE_MAX), randint(1,DICE_MAX))

cc_orig = ["GO", "JAIL"] + [""]*14
shuffle(cc_orig)
cc_stack = cc_orig

def draw_cc():
    global cc_stack
    card = cc_stack.pop()
    cc_stack = [card] + cc_stack
    return card

ch_orig = ["GO", "JAIL", "C1", "E3", "H2", "R1", "next R", "next R", "next U", "back 3"] + [""]*6
shuffle(ch_orig)
ch_stack = ch_orig

freqs = defaultdict(lambda: 0)
total = 0
cutoff = 250000

def draw_ch():
    global ch_stack
    card = ch_stack.pop()
    ch_stack = [card] + ch_stack
    return card

def main():
    global freqs, total, cutoff
    i = 0
    doubles = 0
    while True:
        at = board[i]
        a, b = dice()
        roll = a + b
        total += 1
        if a == b:
            doubles += 1
        else:
            doubles = 0

        prev = i
        i = (i + roll) % len(board)
        pos = board[i]

        # GO to jail on three do
        if doubles == 3:
            doubles = 0
            pos = "G2J"

        extra = ""
        if i < prev:
            extra += ", passed go"

        if pos.startswith("CC"):
            card = draw_cc()
            extra = ", drew CC card %s" % card
            if card != "":
                i = board.index(card)
                pos = board[i]
        elif pos.startswith("CH"):
            card = draw_ch()
            extra = ", drew CH card %s" % card
            if card == "":
                pass
            elif card.startswith("next"):
                find = card[-1]
                for q in range(i, len(board)*2):
                    if board[q % len(board)].startswith(find):
                        i = q % len(board)
                        pos = board[i]
                        break
            elif card.startswith("back"):
                i = (i-3) % len(board)
                pos = board[i]
            else:
                i = board.index(card)
                pos = board[i]

        if pos == "G2J":
            i = board.index("JAIL")
            pos = board[i]
            extra += ", go to jail"

        freqs[pos] += 1

        #print("at %s rolled %d, landed on %s%s" % (at, roll, pos, extra))
        if total % 10000 == 0:
            sys.stdout.write(".")
            sys.stdout.flush()
        if total == cutoff:
            raise KeyboardInterrupt()

if __name__ == "__main__":
    try:
        print("Hit CTRL+C to stop and print results")
        main()
    except KeyboardInterrupt:
        print("")
        print("Rolled %d times" % total)
        items = sorted(freqs.items(), key=lambda (a,b): b, reverse=True)
        string = ""
        for i, (pos, count) in enumerate(items):
            print("%4s square %02d %f" % (pos, board.index(pos), 100.0*float(count)/total))
            string += "%02d" % board.index(pos)
            if i == 2:
                print("Modal string: %s" % string)
                print("Expected    : 101524")
                #sys.exit(0)
