import numpy as np


def get_blocknum(r, c):
    return (r//3)*3 + c//3

def dfs(step, question, to_fill, row_mark, col_mark, block_mark, row, col, block):
    if step == len(to_fill):
        printboard(question)
        return True
    r, c, _ = to_fill[step]
    for i in range(1,10):
        if judge(r, c, i, row_mark, col_mark, block_mark):
            question[r,c] = i
            setmark(r, c, i, 1, row_mark, col_mark, block_mark)
            if dfs(step+1, question, to_fill, row_mark, col_mark, block_mark, row, col, block):
                return True
            setmark(r, c, i, 0, row_mark, col_mark, block_mark)
            question[r, c] = 0
    return False

def judge(r, c, i, row_mark, col_mark, block_mark):
    if row_mark[r,i-1] or col_mark[c,i-1] or block_mark[get_blocknum(r,c),i-1]:
        return False
    else:
        return True

def setmark(r, c, i, flag, row_mark, col_mark, block_mark):
    row_mark[r, i-1] = flag
    col_mark[c, i-1] = flag
    block_mark[get_blocknum(r,c), i-1] = flag

def printboard(question):
    print("The answer is: ")
    for i in range(9):
        ele = [str(p) for p in question[i]]
        print(' '.join(list(ele)))

def main():
    question, row_mark, col_mark, block_mark = np.zeros((9,9),dtype='int'), np.zeros((9,9),dtype='int'), np.zeros((9,9),dtype='int'), np.zeros((9,9),dtype='int')
    row, col, block = np.zeros((9,),dtype='int'), np.zeros((9,),dtype='int'), np.zeros((9,),dtype='int')
    print("Please input the puzzle:")
    for i in range(9):
        inp = raw_input()
        numbers = np.array([int(ele) for ele in inp.split()])
        question[i] = numbers

    to_fill = []
    for i in range(9):
        for j in range(9):
            if question[i,j] == 0:
                to_fill.append([i,j,0])
            else:
                setmark(i, j, question[i,j], 1, row_mark, col_mark, block_mark)
                row[i] += 1
                col[j] += 1
                block[get_blocknum(i,j)] += 1

    for i in range(len(to_fill)):
        r, c, _ = to_fill[i]
        to_fill[i][2] = row[r] + col[c] + block[get_blocknum(r,c)]
    to_fill.sort(key=lambda x:x[2])
    to_fill = list(reversed(to_fill))

    dfs(0, question, to_fill, row_mark, col_mark, block_mark, row, col, block)

if __name__ == "__main__":
	# Example
	# 9 0 4 0 5 0 0 2 0
	# 0 0 7 0 0 0 0 1 0
	# 0 0 3 2 8 0 0 0 0
	# 0 0 0 0 9 0 0 0 0
	# 0 0 0 8 0 0 0 3 6
	# 5 0 0 7 0 0 0 0 2
	# 1 0 0 0 0 3 0 4 0
	# 0 0 0 0 0 6 0 0 5
	# 0 4 0 0 0 0 0 0 9
    main()
