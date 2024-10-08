
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;


vector<vector<int>> matrixMult(const vector<vector<int>> matrix1, const vector<vector<int>> matrix2) {
	vector<vector<int>> result;

	int row1 = matrix1.size();
	int col1 = (row1) ? (matrix1[0].size()) : (0);

	int row2 = matrix2.size();
	if (col1 != row2) return result;
	int col2 = (row2) ? (matrix2[0].size()) : (0);

	result.resize(row1);

	for (int i = 0; i < row1; i++) {
		result[i].resize(col2);

		for (int j = 0; j < col2; j++) {
			result[i][j] = 0;

			for (int k = 0; k < row2; k++) {
				result[i][j] += matrix1[i][k] * matrix2[k][j];
			}
		}
	}

	return result;
}

int main() 
{
	ifstream file("testcases.txt");
	vector<vector<int>> mat1, mat2, mat3;
	int row1, col1, col2, count = 0;

	if (file.is_open()) {
		while (file >> row1 >> col1 >> col2) {
			count++;

			//mat1.clear(); mat2.clear(); mat3.clear();
			mat1.resize(row1); mat2.resize(col1); mat3.resize(row1);

			for (int i = 0; i < row1; i++) {
				mat1[i].resize(col1);

				for (int j = 0; j < col1; j++) {
					file >> mat1[i][j];
				}
			}

			for (int i = 0; i < col1; i++) {
				mat2[i].resize(col2);

				for (int j = 0; j < col2; j++) {
					file >> mat2[i][j];
				}
			}

			for (int i = 0; i < row1; i++) {
				mat3[i].resize(col2);

				for (int j = 0; j < col2; j++) {
					file >> mat3[i][j];
				}
			}

			vector<vector<int>> mat3t2 = matrixMult(mat1, mat2);
			bool isfail = false;

			for (int i = 0; i < row1; i++) {
				for (int j = 0; j < col2; j++) {
					if (mat3[i][j] != mat3t2[i][j]) {
						isfail = true;
						break;
					}
				}
				if (isfail) break;
			}

			cout << "test case " << count << " is ";
			if (isfail) cout << "fail" << endl;
			else cout << "success" << endl;
		}
	}


	return 0;
}