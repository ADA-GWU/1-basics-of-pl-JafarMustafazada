[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/YaSjyTlt)



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
While different byte orders can change a lot and complicate issues like network protocols, file formats, etc., these days we have standards and best practices for all kinds of specific uses, programming languages that ​​have methods for different byte orders, and modern processors that can handle both endians efficiently.

