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
