# Automate-simulator
This is a deterministic finite automate written in c++. Configuration is given from a file.

# File structure
The file consists of two parts.
First part is for enter alphabet, exit alphabet and states in strict order. Duplicate names are not allowed. 
Symbols are seperated with ','.
example.
        a1, a2, a3
        b1, b2
        q0, q1
        
Second part is the state-transition table. Each cell is seperated with '|' symbol.
example.
        0,q1 | 0, q0
        1,q2 | 0, q2
        1,q2 | 1, q2
Empty lines and spaces are accepted.

# Automate Class
parsing() function takes a file name as an argument. It fills the alphabets and states into vectors.
The table is filled into "Table" map container.
solve() function takes a string from standart input then "translates" it.

     
