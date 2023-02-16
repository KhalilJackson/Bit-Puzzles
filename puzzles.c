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
 * operator allows us to go from not(x and y) to (x and y).
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
 * The hex representation of this binary pattern is 0x49249249. Using this,
 * we can arrange the particular bytes in order by shifting them to their correct
 * byte positions and using | to combine them.
 *
 * Return statement if broken into two halves. Left half shifts 0x49 to the left
 * byte position of 0x24. Right half 0x92 is shifted to the left byte position of 
 * 0x49. Left half is shifted 16 times to the left so that the bytes fall in order
 * of 0x49249249 when they are | together.
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
 * Create a mask of ones in the first byte position and right shift the number by 
 * (n << 3) to take advantage of the powers of two in binary, which allows one bit 
 * shift operation to shift by an entire byte. Once the desired byte is in the 
 * first byte position, it can be masked to extract the byte.
 */
int byteExtract(int x, int n) {

	int mask = 0x000000FF;
	int val = x >> (n << 3);

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
 *
 * Creates a mask by shifting ones into the nth and mth bytes, | them then ^ by 
 * 0xFFFFFFFF to get a mask of ones with zeros in the nth and mth byte positions. 
 * & this mask with x to get one that maintians the order of the unswitched bytes
 * while placing zeros in the swapped byte positions. 
 *
 * Uses the same approach from byteExtract to gather the nth and mth byte. Then, the
 * bits are shifted into their swapped byte positions and | together to get a 
 * rearranged number.
 */
int byteSwitch(int x, int n, int m) {

	//Placing one bits in byte positions
	int nByte = 255 << (n << 3);
	int mByte = 255 << (m << 3);

	//Combine the byte positions to form a mask
	int switchMask = (nByte | mByte) ^ 0xFFFFFFFF;

	//Create mask in first byte position then shift
	int mask = 0x000000FF;
	int shifted1 = x >> (n << 3);
	int shifted2 = x >> (m << 3);

	//Save the masked values as bytes
	int firstByte = shifted1 & mask;
	int secondByte = shifted2 & mask;

	//Combine the switchMask and rearranged bytes into one number
	int bytesSwap = (x & switchMask) | (firstByte << (m <<3)) | (secondByte << (n <<3));

  return bytesSwap;
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
 * we & the results and ! it to receive the answer in terms
 * of zero and one.
 *
 * Return statement logic. If xSign and ySign are the same and the
 * sumSign is different, the & returns 1 and is ! to 0. The opposite
 * is true for vice versa.
 */
int addOverflow(int x, int y) {

	//Getting the signs of x and y
	int xSign = (x>>31);
	int ySign = (y>>31);

	//Getting the sign of their sum
	int sumSign = ((x+y)>>31);

  return (!((xSign ^ sumSign) & (sumSign ^ ySign)));
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
 *
 * Right shifting will place the necessary bits in the correct position
 * but may leave a trail of zeroes. Creating a mask to turn the ones to
 * zeroes and maintains the shifted bits requires right shifting (1<<31)
 * n - 1 times, which creates ones in the zero bits should be and zeroes
 * where the shifted bits should be. Flipping this pattern switches the
 * positions of the ones and zeroes so that when the shifted number is &
 * with the mask,the potential one bits are turned to zeroes and the
 * shifted bits are maintained.
 */
int shiftLogical(int x, int n) {

	//Shiftright shift normally
	int shift = x >> n;

	//Take 1000...0000, shift it n times
	//Get 1111...1111, left shift one bit
	//Turn the ones to zero and vice versa
	int mask = ~(((1 << 31) >> n) << 1) ;

  return shift & mask; 
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
 *
 * To go from a negative number in signed magnitutde, convert into positive version
 * and change the sign bit to a zero. The first half of the return statment gives 
 * the positive version of x if it is negative and & it with its sign. The second
 * half of the return statment ensures the sign bit is in the correct spot.
 */
int signMagnitude(int x) {

	int p1 = ~x + 1;
	int tMin = 1<<31;
	int sign = x >> 31;

  return (((p1 + tMin) & sign) | (x & (~sign)));
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
 *
 * Creates a mask to gather the exp bits then checks their contents.
 * If the exp bits are all zeros, it falls under NaN and return.
 * Otherwise, mask with a ~(1<<31).
 */
unsigned fp_abs(unsigned uf) {

	//Creates mask for the exp bits
	int mask = 0x000000FF << 23;

	//Shift uf left one to get rid of sign bit
	//Mask than shift to remove lesser bits
	int exp = (mask & (uf << 1)) >> 23; 

	//If NaN,retun uf
	if (exp == 0xFF) {
		return uf;
	}
	else {
		return (uf & ~(1<<31));
	}
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

	//Get sign bit
	int sign = (uf >> 31) << 31;

	//Creates mask for the exp bits
	int mask = 0x000000FF << 23;

	//Gets the exp bits
	int exp = (mask & (uf << 1)) >> 23;

	//If zero or negative zero, return zero
	if ((uf == 0) || (uf == -0)) {
		return 0;
	}

	//If NaN
	if (exp == 0xFF) {
		return uf;
	}

	//If Denormalized
	if (exp == 0) {

		if (sign == (1<<31)) {
 
			return ((uf << 1) + sign);
		}

		return uf << 1;
	}

	//Else are normalized
	return uf + (sign);
}
