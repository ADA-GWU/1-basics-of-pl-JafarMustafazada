#include <iostream>
#include <string>
#include <ctime>
using namespace std;

static const int size1 = 1024;
static const bool is_console = false;

// stack array
class arr1stack {
public:
	int arr1[size1] = { 0 };
	arr1stack() { if (is_console) cout << "\tstack was created\n"; }
	~arr1stack() { if (is_console) cout << "\tstack was destroyed\n"; }
};

// heap array
class arr2heap {
public:
	int* arr2;
	arr2heap() : arr2(new int[size1]) { if (is_console) cout << "\theap was created\n"; }
	~arr2heap() { 
		if (is_console) cout << "\theap was destroyed\n";
		delete[] arr2;
	}
};

// function-examples
void func1_hh() {
	// heap-heap
	arr2heap* arr2_2;
	arr2_2 = new arr2heap;
	delete arr2_2;
}
void func1_hs() {
	// heap-stack
	arr1stack* arr2_1;
	arr2_1 = new arr1stack;
	delete arr2_1;
}

void func1_ss() {
	// stack-stack
	arr1stack arr1_1 = arr1stack();
}

void func1_sh() {
	// stack-heap
	arr2heap arr1_2 = arr2heap();
	// following causes error with corrupted heap which even cant be catched with trycatch x(
	// commented code line copies object (instead of initialazing) that already deleted heap
	//arr2heap arr1_2;
	//arr1_2 = arr2heap();
}

// class-static-examples
class arr3static {
public:
	inline static arr1stack arrs1 = arr1stack();
	inline static arr2heap arrs1_2 = arr2heap(); // even though obj is in stack, array of obj is in heap
	inline static arr2heap* arrs2 = new arr2heap;
	inline static arr1stack* arrs2_1 = new arr1stack; // even though obj is in heap, array of obj is in stack
};

// function-static-examples
// lines starting with "static" going to be ignored on next function calls even if this lines had arguments
void func_static_hh() {
	static arr2heap* sarr2_2;
	sarr2_2 = new arr2heap;
	delete sarr2_2;
}
void func_static_hs() {
	static arr1stack* sarr2_1;
	sarr2_1 = new arr1stack;
	delete sarr2_1;
}

void func_static_ss() {
	static arr1stack sarr1_1;
	sarr1_1 = arr1stack();
}

void func_static_sh() {
	static arr2heap sarr1_2;
	sarr1_2 = arr2heap();
}

int main() {
	// this cout makes obvius diffirence in terms of start for function-static and class-static when "is_console" is turned on
	cout << "started\n\n";
	int iinput = 10000000;
	string input;
	clock_t start;
	bool insurance = false; // to make sure that -O3 will not affect logic of code turn this on

	if (insurance) {
		cin >> input;
		try { iinput = stoi(input); }
		catch (const std::exception&) { iinput = 100000000; }
	}

	// func //
	start = clock();
	for (int i = 1; i <= iinput; i++) func1_ss();
	cout << (clock() - start) << "ms-stack-stack" << endl;
	
	start = clock();
	for (int i = 1; i <= iinput; i++) func1_sh();
	cout << (clock() - start) << "ms-stack-heap" << endl;

	start = clock();
	for (int i = 1; i <= iinput; i++) func1_hs();
	cout << (clock() - start) << "ms-heap-stack" << endl;

	start = clock();
	for (int i = 1; i <= iinput; i++) func1_hh();
	cout << (clock() - start) << "ms-heap-heap" << endl << endl;

	// func-static //
	start = clock();
	for (int i = 1; i <= iinput; i++) func_static_ss();
	cout << (clock() - start) << "ms-static-stack-stack" << endl;

	start = clock();
	for (int i = 1; i <= iinput; i++) func_static_sh();
	cout << (clock() - start) << "ms-static-stack-heap" << endl;

	start = clock();
	for (int i = 1; i <= iinput; i++) func_static_sh();
	cout << (clock() - start) << "ms-static-heap-stack" << endl;

	start = clock();
	for (int i = 1; i <= iinput; i++) func_static_hh();
	cout << (clock() - start) << "ms-static-heap-heap" << endl << endl;

	// class-static //
	start = clock();
	for (int i = 1; i <= iinput; i++) arr3static::arrs1 = arr1stack();
	cout << (clock() - start) << "ms-static2-stack-stack" << endl;

	start = clock();
	for (int i = 1; i <= iinput; i++) arr3static::arrs1_2 = arr2heap();
	cout << (clock() - start) << "ms-static2-stack-heap" << endl;

	start = clock();
	for (int i = 1; i <= iinput; i++) {
		delete arr3static::arrs2_1;
		arr3static::arrs2_1 = new arr1stack;
	}
	cout << (clock() - start) << "ms-static2-heap-stack" << endl;

	start = clock();
	for (int i = 1; i <= iinput; i++) {
		delete arr3static::arrs2;
		arr3static::arrs2 = new arr2heap;
	}
	cout << (clock() - start) << "ms-static2-heap-heap" << endl;

	cout << "\ndone" << endl;
	return 0;
}
