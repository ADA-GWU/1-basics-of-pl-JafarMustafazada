
##
# Task 1. Static vs stack vs heap in c++
Before we start going into experements some theory and definations need to be read.
##
### Stack Memory
- **Scope and Lifetime**. Stack memory is allocated at runtime and is automatically managed (allocated and deallocated). Variables on the stack are destroyed once the function they belong to exits.
- **Use Cases**. Local variables, function parameters.
- **Pros**. Fast access and allocation.
- **Cons**. Fixed size, often limited to 2GB.

### Heap Memory
- **Scope and Lifetime**. Heap memory is allocated at runtime and must be explicitly managed (allocated and deallocated) by the programmer.
- **Use Cases**. Dynamic memory allocation, objects with a lifetime beyond the function that created them.
- **Pros**. Flexible size, can allocate large amounts of memory.
- **Cons**. Slower allocation/deallocation, requires manual memory management which can lead to potential memory leaks.

### Static Memory
- **Scope and Lifetime**. Static memory is allocated at compile time and persists for the duration of the program.
- **Use Cases**. Used for static variables, global variables, and constants.
- **Pros**. Fast access and allocation.
- **Cons**. Fixed size, no deallocation.

##
### Definations:
In my experements I used following code (custom class for large array allocation) and going to use such naming "static / no static or nothing"-"pointer memory type"-"array memory type" in explanation.
```cpp
static const int size1 = 1024;
// stack array
struct arr1stack {
	int arr1[size1] = { 0 };
};

// heap array
struct arr2heap {
	int* arr2;
	arr2heap() : arr2(new int[size1]) { }
	~arr2heap() { 
		delete[] arr2;
	}
};
```

For example, "static-heap-stack" will mean "declared in compile time, pointer to array allocated in heap, array allocated in stack":
```cpp
	static arr1stack* sarr2_1;
	sarr2_1 = new arr1stack;
	delete sarr2_1;
```

"stack-heap" will mean "declared in runtime, pointer to array allocated in stack, array allocated in heap" (this one specificly is very dangerous because if it written slightly in diffirent way it can cause "heap corruption" error which hard to catch):
```cpp
	arr2heap arr1_2 = arr2heap();
```

##
### Results of experements
There was made 4 perfomance test for run time declared ones, compile time declared ones (static thorugh function) and again compile time declared ones 2 (static thorugh class) on my machine. 4 perfomance test means every combanation of "stack" and "heap" where each test is allocation and deallocation 100,000,000 times:
```plaintext
0ms-stack-stack
2789ms-stack-heap
5196ms-heap-stack
5537ms-heap-heap

4093ms-static-stack-stack
2770ms-static-stack-heap
2749ms-static-heap-stack
5477ms-static-heap-heap

4089ms-static2-stack-stack
2768ms-static2-stack-heap
4800ms-static2-heap-stack
5464ms-static2-heap-heap
```

second time for stronger point.
```plaintext
0ms-stack-stack
2692ms-stack-heap
4873ms-heap-stack
5279ms-heap-heap

3629ms-static-stack-stack
2633ms-static-stack-heap
2606ms-static-heap-stack
5181ms-static-heap-heap

3600ms-static2-stack-stack
2616ms-static2-stack-heap
4715ms-static2-heap-stack
5203ms-static2-heap-heap
```

Reason why c++ stack-stack allocation and deallocation is almost instant is because at the end, in assembly code it is just 1 operation for each allocation/deallocation:
```arm
    sub rsp, 4096       ; allocate space for arr1stack (4 bytes * size1)
    ; Initialization of arr1 to 0 is not shown as it's not necessary in assembly
    add rsp, 4096       ; deallocate space for arr1stack
```
Also reason why I added static2 is because in one test (heap-stack) for some reason static variable accessed thorugh class takes visably longer (4800ms vs 2749ms) than static variable accesed thorugh function. Everything else is as expected. 
###
Heap always takes longer, with pointer being in heap memory, stack array loses almost all perfomance. 
###
In static even stack-stack takes quite much time and it because we not excatly allocating memory, but rather creating object and trying to copy it since static variables is already allocated in compile time (using "move" does not change a thing).

##
### Here is good visual explanation of how memory is managed in c++
author mentioned in image.
[![Cool Image](https://bayanbox.ir/view/581244719208138556/virtual-memory.jpg)](https://bayanbox.ir/view/581244719208138556/virtual-memory.jpg)


