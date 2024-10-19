
matrix1 = [
    [1, 2, 3, 10],
    [4, 5, 6, 11],
    [7, 8, 9, 12],
    [13, 14, 15, 16]
]

def create_image(matrix):
    temp = '<style>table, th, td {  border:1px solid black;}</style><table style="width:100%">'
    for row in matrix:
        temp += '<tr>'
        for item in row:
            temp += f'<td>{item}</td>'
        temp += '</tr>'
    temp += '</table>'

    with open("result_py.html", "w") as file:
        file.write(temp)
        
def slicing2D(matrix, sRow, sColoumn, eRow, eColoumn):
    sub = [row[sColoumn:eColoumn] for row in matrix[sRow:eRow]]
    return sub

sub1 = slicing2D(matrix1, 1, 1, None, None)
create_image(sub1)
print(sub1)
