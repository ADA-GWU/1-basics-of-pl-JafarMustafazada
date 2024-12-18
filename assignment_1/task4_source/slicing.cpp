#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

template <class T1> vector<T1> proSlicing(const vector<T1>& victim, int sRow, int eRow = -1, int step = 1) {
	if (sRow < 0) sRow += victim.size();
	if (eRow < 0) eRow += victim.size();
	if (sRow < 0 || eRow < 0 || sRow > eRow) {
		cout << "oups error 3" << endl;
		throw out_of_range("wrong pro slicing input");
	}

	vector<T1> result;
	for (int i = sRow; i <= eRow; i += step)
	{
		result.push_back(victim[i]);
	}

	return result;
}

vector<vector<int>> matrixSlicing(const vector<vector<int>>& matrix, int sRow, int sColoumn, int eRow = -1, int eColoumn = -1) {
	vector<vector<int>> result = proSlicing(matrix, sRow, eRow);

	for (int i = 0; i < result.size(); i++)
	{
		result[i] = proSlicing(result[i], sColoumn, eColoumn);
	}

	return result;
}

void printMatrix(const vector<vector<int>>& matrix) {
	cout << "[";
	for (int i = 0; i < matrix.size(); i++)
	{
		vector<int> row = matrix[i];
		cout << "[";
		for (int j = 0; j < row.size(); j++)
		{
			cout << row[j] << ",";
		}
		cout << "], ";
	}
	cout << "]";
}

void createImage(const vector<vector<int>>& matrix) {
	string temp = "<style>table, th, td {  border:1px solid black;}</style><table style=\"width:100 % \">";
	for (int i = 0; i < matrix.size(); i++)
	{
		vector<int> row = matrix[i];
		temp += "<tr>";
		for (int j = 0; j < row.size(); j++)
		{
			temp += "<td>" + to_string(row[j]) + "</td>";
		}
		temp += "</tr>";
	}
	temp += "</table>";
	
	ofstream file1("result.html");
	if (file1.is_open()) {
		file1 << temp << std::endl;
		file1.close();
	}
}

int main() {
	vector<vector<int>> matrix = {
	{1, 2, 3, 10},
	{4, 5, 6, 11},
	{7, 8, 9, 12},
	{13, 14, 15, 16},
	};

	printMatrix(matrix);
	cout << endl << endl;

	vector<vector<int>> submatrix = matrixSlicing(matrix, 1, 1, -1, -1);
	printMatrix(submatrix);
	createImage(submatrix);
	cout << "done";


	return 0;
}
