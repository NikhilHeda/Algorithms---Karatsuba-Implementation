## Karatsuba Algorithm for Multiplication of Large Integers

Divide and Conquer approach to solve the problem of multiplying two large integers in less than quadratic time complexity.

## Algorithm: Karatsuba Algorithm

Algorithm Karatsuba(a, b, k)
//Multiplication of large integers a and b of 2 k decimal digits
if (k = 0) return a*b
m = 2 k
m2 = m/2
a1, a2 = split_at(a, m2)
b1, b2 = split_at(b, m2)
p1 = Karatsuba(a1, b1, k1)
p2 = Karatsuba(a2, b2, k1)
p3 = Karatsuba((a1+a2), (b1+b2), k)
return (p1*10^m )+( (p3-p1-p2) * 10^m2 )+(p2)

## Input Format
Input has two lines each with a large integer in base10(1 ≤ large integer < 10 1M , where 1M means 2^20 ).
That is, each integer can be up to 2^20 digits.

## Output Format

Print the product of the given two large integers in base10.
Note that the product may have upto 2 million(2^21) digits. Print the total time taken in milliseconds.

## Example

#Input:
12345678
32165487
#Output:
397104745215186
12.3 millisec (Note: This value is only representative)