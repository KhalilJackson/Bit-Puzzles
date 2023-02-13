/* 
 * Lab 1 - A Bit Puzzling 
 * 
 * Khalil Jackson
 * 
 * puzzles.c - Source file with your puzzle solutions.
 *
 * NOTE: Do not include the <stdio.h> header; it confuses the blc
 * compiler. You can still use printf for debugging, although you
 * might get a compiler warning (this is an exception to the
 * 'never accept compiler warnings' rule!).
 */

/* 
 * maxVal - return maximum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 *
 * One in binary is 0000...0001. Shifting the one bit 31 
 * times to the left gives us 1000...0000,the minimum integer.
 * Flipping the bits gets us to the largest (0111...1111).
 */
int maxVal(void) {
  return ~(1 << 31);
}

/* 
 * negCheck - return 1 if x < 0, return 0 otherwise 
 *   Example: negCheck(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 1
 * 
 * The MSB determines the sign of the number. Right shifting
 * the bit uses arithmetic shift where the bits are either
 * all ones or zeroes. Masking with one ensures that we keep
 * the now LSB bit, which will be one if negative and zero 
 * if positive.
 */
int negCheck(int x) {
  return ((x >> 31) & 1);
}

/* 
 * lsbCopy - set all bits of result to least significant bit of x
 *   Example: lsbCopy(5) = 0xFFFFFFFF, lsbCopy(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 1
 *
 * Left shifting the LSB to the MSB allows us to do an arithmetic
 * right shift where all bits with be replaced by what was in the 
 * MSB, which is the original LSB.
 */
int lsbCopy(int x) {
  return ((x << 31) >> 31);
}

/* 
 * andBitsh - x&y using only ~ and | 
 *   Example: andBits(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 *
 * Using de Morgan's laws gives us the idea that not(x and y) =
 * (not x) or (not y). Using this principle and using the ~
 * operator allows us to go from not(x and y) = to (x and y) =.
 */
int andBits(int x, int y) {
  return ~((~x) | (~y));
}

/* 
 * xorBits - x^y using only ~ and & 
 *   Example: xorBits(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 *
 * Uses de Morgan's laws, which states that not(x or y) = (not x)
 * and (not y). To make it x or y, we distribute the ~ across the 
 * other half of the equation. 
 */
int xorBits(int x, int y) {
  return (~(~x & ~y) & ~(x & y));
}

/* 
 * setThirdBits - return value with every third bit (starting with the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 * 
 * The hex representation of this bianry pattern is 0x49249249. Using this,
 * we can arrange the particular bytes in order by shifting them and using or.
 */
int setThirdBits(void) {
  return ((((0x24)|(0x49 << 8)) << 16) | ((0x49)|(0x92<<8)));
}

/* 
 * byteExtract - Extract byte n from x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: byteExtract(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 *
 * Create a shift factor (4n) that we can rights shift by twice to get the 
 * appropriate byte shift where the desired byte is in the first byte 
 * position before masking it.
 */
int byteExtract(int x, int n) {

	int shift = n + n + n + n;


	int mask = 0x000000FF;
	int val = x >> shift >> shift;


  return val & mask;
}

/* 
 * byteSwitch - swaps the nth byte and the mth byte
 *  Examples: byteSwitch(0x12345678, 1, 3) = 0x56341278
 *            byteSwitch(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwitch(int x, int n, int m) {


  return 2;
}

/* 
 * addOverflow - Determine if can compute x+y without overflow 
 *   Example: addOverflow(0x80000000,0x80000000) = 0,
 *            addOverflow(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 2
 *
 * Right shifts x, y, and their sum to focus on sign bits. Then,
 * uses ^ to determine if the signs of x and y are the same before
 * anding the results and notting it to receive the answer in terms
 * of zero and one.
 */
int addOverflow(int x, int y) {

	int val1 = (x>>31);
	int val2 = (y>>31);

	int val3 = ((x+y)>>31);

  return (!((val1 ^ val3) & (val3 ^ val2)));
}

/* 
 * bitFit - return 1 if x can be represented as an 
 *  n-bit, two's complement integer or 0 otherwise.
 *   1 <= n <= 32
 *   Examples: bitFit(5,3) = 0, bitFit(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3 (shift n minus one)
 *
 * x or with sign bit to ensure number is nonnegative. Right shift
 * that result by n - 1 then not it, which turns zero in to one and
 * any non zero values into zero. Things that can be represented in 
 * that number of bits would return one. 
 */
int bitFit(int x, int n) {

	int variable = x >> 31;

	int newNum = x ^ variable;

	int compare = (newNum >> (n + ((1<<31)>>31)));


  return !(compare);
}

/* 
 * shiftLogical - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: shiftLogical(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int shiftLogical(int x, int n) {

	int val = x >> n;


  return 2; 
}

/* 
 * not - Compute !x without using !
 *   Examples: not(3) = 0, not(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 *
 * Use | on x and its two's complement to determine if the number is 
 * zero or nonzero; non zero values will be right shifted and create one bits. 
 * Adding one to thses bits will lead to a carryout bit of one and binary zero
 * while the value one would be represented otherwise. 
 */
int not(int x) {


  return (((x | (~x + 1)) >> 31) + 1);
}

/* 
 * signMagnitude - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: signMagnitude(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int signMagnitude(int x) {
  return 2;
}

/* 
 * fp_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned fp_abs(unsigned uf) {
  return 2;
}

/* 
 * fp_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
unsigned fp_twice(unsigned uf) {
  return 2;
}

