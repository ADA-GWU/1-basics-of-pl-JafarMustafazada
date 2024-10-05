[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/YaSjyTlt)


##
# Task 1. Endianness in Programming
Endianness refers to the order in which bytes are arranged in memory. There are two main types: **big-endian (BE)** and **little-endian (LE)**. Where big-endian stores the **most significant byte (MSB)** first (reading it left to right), little-endian stores the **least significant byte (LSB)** first (reading it right to left). Examples:
### Big-Endian
32-bit integer represented as `0x12345678`, would be stored in memory as follows:
```plaintext
Address:  00  01  02  03
Data:     12  34  56  78
```
### Little-Endian
Same 32-bit integer would be stored as:
```plaintext
Address:  00  01  02  03
Data:     78  56  34  12
```
### Additional Thoughts
While different byte orders can change a lot and complicate issues like network protocols, file formats, etc., these days we have standards and best practices for all kinds of specific uses, programming languages that ​​have methods for different byte orders (functions like `htonl()` and `ntohl()` to convert between host and network byte order), and modern processors that can handle both endians efficiently.  


##
# Task 2. Tuples in Python
When I encountered tuples in Python, I immediately compared them to tuples in C# since I am more familiar with them in that language.
### C# Tuples
- **Immutability**: C# tuples are mutable, meaning you can change their elements after creation, YET there also `System.Tuple.Create(1, "hello")` (before System.ValueTuple, mutable tuples, in C#7 was introduced) which is immutable and less risky tuple.
- **Syntax**: Defined using the `Tuple` class or the newer tuple syntax, e.g., `var tpl = (1, 2, 3);`.
- **Use Case**: Useful for grouping multiple values without creating a custom data structure.
- **Performance**: Slightly less efficient than Python tuples due to mutability but still useful for quick data grouping.
### Python Tuples
- **Immutability**: Once created, you cannot change the elements of a tuple.
- **Performance**: Generally faster than lists due to immutability and less memory usage.
### Python Lists
- **Mutability**: You can change, add, or remove elements after the list is created.
- **Performance**: More flexible but generally slower and uses more memory compared to tuples.
### Some Observations
I did some experiment with same python code with diffirent start values and here is results:
```python
print('Size of the tuple:',tpl.__sizeof__())
print('Size of the list:',lst.__sizeof__())
```
exp 1:
```python
tpl = (1,2,3,4)
lst = [1,2,3,4]
```
exp 2:
```python
tpl = (1,2,3)
lst = [1,2,3]
```
exp 3:
```python
tpl = (1,2)
lst = [1,2]
```
exp 4:
```python
tpl = (1)
lst = [1]
```
exp 5:
```python
tpl = ()
lst = []
```
results
```plaintext
element count:      04 | 03 | 02 |  01  | 00
Size of the tuple:  56 | 48 | 40 || 28 || 24
Size of the list:   72 | 72 | 56 |  48  | 40
```
### Thoughts
First of all results same (while elements more than 1) as with integers when instead of integers is used strings (it dosent matter how long is string as long as they not too large). It seems each element is 8 bytes and where tuple always create new container for all elements, list as flexiable it is will preserve some space for future elements. Yet tuples seems to work odly when there are no more than 1 element, taking signifacantly less space and in weird way than I predicted. I got even weirder results with tuples when I tried this:
```python
tpl = ("1")
tp2 = ("12")
tp3 = ("123")
tp4 = ("1234", 2)
tp5 = ("1234",)
tp5 = ()
```
```plaintext
tpl numeration:      01 | 02 | 03 || 04 | 05 | 06
Size of the tuple?:  42 | 43 | 44 || 40 | 32 | 24
```
My not very clever dump only then relaized that it is not tuple but string is created. I hate python for not being able to tell what type I working with :D

