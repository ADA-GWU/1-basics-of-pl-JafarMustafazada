import random

def matrixmult(matrix1, matrix2):
    rows_1, cols_1 = len(matrix1), len(matrix1[0])
    rows_2, cols_2 = len(matrix2), len(matrix2[0])

    if cols_1 != rows_2: return None
    
    result = [[0 for _ in range(cols_2)] for _ in range(rows_1)]
    
    for i in range(rows_1):
        for j in range(cols_2):
            for k in range(rows_2):
                result[i][j] += matrix1[i][k] * matrix2[k][j]

    return result

def generate_matrices(rows_1, cols_1, cols_2):
    matrix1 = [[random.randint(10, 99) for _ in range(cols_1)] for _ in range(rows_1)]
    matrix2 = [[random.randint(10, 99) for _ in range(cols_2)] for _ in range(cols_1)]    
    return matrix1, matrix2

def write_testc(amount = 100):
    with open('testcases.txt', 'w') as file:
        for i in range(amount):
            rows_1 = random.randint(2, 5)
            cols_1 = random.randint(2, 5)
            cols_2 = random.randint(2, 5)

            file.write(str(rows_1) + " ")
            file.write(str(cols_1) + " ")
            file.write(str(cols_2) + "\n\n")

            mat1, mat2 = generate_matrices(rows_1, cols_1, cols_2)
            
            mat3 = matrixmult(mat1, mat2)

            for row1 in mat1:
                for int1 in row1:
                    file.write(str(int1) + " ")
                file.write("\n")
            file.write("\n")

            for row1 in mat2:
                for int1 in row1:
                    file.write(str(int1) + " ")
                file.write("\n")
            file.write("\n")

            for row1 in mat3:
                for int1 in row1:
                    file.write(str(int1) + " ")
                file.write("\n")
            file.write("\n")
            
            file.write("\n")
            # print(i, "th case added")
        print("done")


write_testc()