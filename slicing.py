
matrix1 = [
    [1, 2, 3, 10],
    [4, 5, 6, 11],
    [7, 8, 9, 12],
    [13, 14, 15, 16]
]

def slicing2D(matrix, sRow, sColoumn, eRow, eColoumn):
    sub = [row[sColoumn:eColoumn] for row in matrix[sRow:eRow]]
    return sub

print(slicing2D(matrix1, 1, 1, None, None))
