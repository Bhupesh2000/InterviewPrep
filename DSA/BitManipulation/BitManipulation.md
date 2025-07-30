1's and 2's compliment
1's compliment - (Just flip all the bits)
13 -> (1 1 0 1)  flip -> (0 0 1 0)

2's compliment -
Find 1's compliment
Add 1 to it
13 -> (1 1 0 1) -> (0 0 1 0) + 1 -> (0 0 1 1)

--------------------------------------------------------------------------------------------------------------------------------------------

Storing -ve numbers in binary
The integer has 32 bits, the last bit from right to left(31st bit) is the sign bit; 0 -> +ve, 1 -> -ve
13 -> 0 0 ...... 1 1 0 1
to store -13
2's compliment of 13 ->
    1's compliment of 13 -> 1 1 .... 0 0 1 0
    + 1 -> 1 1 ..... 0 0 1 1
-13 -> 1 1 ...... 0 0 1 1
Now the 31st bit is 1, this when the machine knows it is a -ve number.

--------------------------------------------------------------------------------------------------------------------------------------------

Operators - 
1. AND - all true -> true
         1 false -> false
         13(1 1 0 1) & 7(0 1 1 1) -> 5(0 1 0 1)

2. OR -  1 true -> true
         all false -> false
         13(1 1 0 1) | 7(0 1 1 1) -> 15(1 1 1 1)

3. XOR - no. of 1s odd -> 1
         no. of 1s even -> 0
         13(1 1 0 1) ^ 7(0 1 1 1) -> 10(1 0 1 0)

4. SHIFT
   Right shift - 13(1 1 0 1) >> 1 -> 6(0 1 1 0) 
                 13(1 1 0 1) >> 2 -> 3(0 0 1 1)
                 x >> k -> x / (pow(2, k))
   Left shift - 13(1 1 0 1) << 1 -> 26(1 1 0 1 0)
                x << k -> x * pow(2, k)
                pow(2, 31) - 1(INT_MAX) << 1 -> overflow

5. NOT - 
    1. Flip
    2. Check if -ve number
        a. if yes, 2's compliment
        b. else stop
    ~(5) -> -6
    ~(-6) -> 5

--------------------------------------------------------------------------------------------------------------------------------------------