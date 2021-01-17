/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
         
/* 
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  //only returns 1 if both x and y are 0       
  return (~x & ~y);
    //bitwise not changes each bit to opposite 0 or 1
    //and compares if each bit are both 1's, otherwise is 0
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: !(logical not) ~(bitwise not) & ^(xor) | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
    //can be rep by 16-bit 2's comp
    //possible int range from -32768 to 32767
    int sol1 = x << 16; //left shift will fill w all 0's or 1's if a 16 bit int (LSB)
    int sol2 = sol1 >> 16; //right shift of the prev will ensure all 0's or 1's (LSB)
    int sol3 = sol2 ^ x; //xor compares all 1's or 0's to original int
    int result = !sol3; //logical not "flips" the overall result (1 if a number that isn't 0, otherwise 0)
    return result; //tbh I'm a little confused
    
}
/* 
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
    int a, b, c, d;
    a = 73 << 9; //73 in binary, every third bit is a 1 (01001001)
    b = a | 73; //left shift makes a all 1's, logical or adds more 1's to every third bit
    c = b << 18; //left shift again adds 1's to lengthen?
    d = c | b; //logical or repeats process of placing 1's every third
    return d;
}
/* 
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
    //int a = 0x55555555; no out of bounds
    int a = (0x55<<8) + 0x55; //left shifting a bunch of times (by 8) and adding 0x55 to make every even numbered bit a 1
    a = (a<<8) + 0x55;
    a = (a<<8) + 0x55;
    a = (a<<8) + 0x55;
    int b = x & a; //and compares the bits of 0x55555555 to the given int, and returns 1 if both bits are 1, otherwise 0
    int res = !!b; //!! is equivalent to res != b
    return res;
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
    int a = x << 31; //left shift to isolate LSB
    int b = a >> 31; //right (arithmetic) shift to copy LSB
    return b; //could i have done this in one step rather?
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
    int a = !x; //logical not "flips" truth val of x
    int b = a | y; //or is 1 if one or both bits are 1
    return b; //x->y is only 0 if x is true and y is false
}
/* 
 * bitMask - Generate a mask consisting of all 1's 
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
    int a = ~0; //bitwise not sets bits to all 1's
    int h = a << lowbit; //left shift adds 1's
    int b = 1 << highbit << 1; //more left shifting to create more 1's
    int l = b + a; //adding 1's to mask
    int res = h & l; //and on high and low masks to determine overlap and return where both bits are 1's, otherwise become 0
    return res;
}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
    int a;
    int b;
    int c;
    int d;
    int res;
    a = (x << 1) + x; //copy LSB and then add given int to multiply x*3, using powers of 2
    b = a >> 31; //sign at leftmost bit
    c = (1 << 2) + ~0; //mask of a bunch of 1's
    d = (c & b); //and to determine if neg or pos
    res = ((a+d) >> 2); //dividing the x*3 by 4, which is the same as x*(3/4)
    return res;    
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    int i;
    int j;
    a = x << 1; //x*2
    b = a + x; //x*3, similar to idea in ezThreeFourths, using powers of 2 with shifts
    c = b ^ x; //xor compares x*3 to original val
    d = a ^ x; //xor compares x*2 to original val
    e = (d | c) >> 31; //or compares d and c to determine overflow?
    f = ~(1 << 31); //max val
    g = x >> 31; //find if x is negative or not
    h = ~e & b; //"flips" overflow and compares to x*3
    i = f ^ g; //xor max val and the sign of x
    j = h | (e & i); //???
    return j;
    //was working, i have changed absolutely nothing, now btest says it is not working
    //says it returns 0x7fffffff, but that it should return 0x7ffffffd? confused
    
    
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
    int a = x >> 16;
    x = x ^ a; //xor of bits to count num of 1's in first 16 bits
    int b = x >> 8;
    x = x ^ b; //xor is only 1 if one of bits compared is one, but not both
    int c = x >> 4;
    x = x ^ c;
    int d = x >> 2;
    x = x ^ d;
    int e = x >> 1; //continue shifting and xor-ing until final LSB of input
    x = x ^ e;
    int res = x & 1; //return 1 if odd number
    return res;
    //essentially "looping" through bits and counting 1's to determine if odd or even (32 bits is even, so if num of 1's are odd, then num of 0's will be too)
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {    
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    int i;
    int j;
    int res;
    
    //looking for the most significant bit and then count
    a = x >> 16; //just use half of the bits
    b = !!a; //find if a is 0 or not (b is 1)
    c = b << 4;
    x = x >> c;
    
    d = !!(x >> 8); //left 8 bits
    e = d << 3;
    x = x >> e;
    
    c = c | e;
    
    f = !!(x >> 4); //left 4 bits
    g = f << 2;
    x = x >> g;
    
    c = c | g;
    
    h = !!(x >> 2); //left 2 bits
    i = h << 1;
    x = x >> i;
    
    c = c | i;
    
    j = x >> 1;
    res = c | j;
    
    return res;
    //move opp direction of bitParity and determine how many 1's in order to divide by 2 the appropriate number of times
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
    int a = x >> 2; //div by 4
    int b = x & 0x3; //find remainder
    
    int c = a << 1;
    int d = a + c; //x/4 multiplied by 3
    
    int e = x >> 31; //sign of x
    int f = b << 1;
    int g = b + f; //find remainder of x*3
    
    int h = e & 0x3; //determine if pos or neg
    int i = h + g; //add the remainder
    int j = i >> 2; //dividing again?
    
    int res = d + j;
    return res;
}
/*
 * Extra credit
 */
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    unsigned res = 0;
    int a = x & (1 << 31);
    int c = 0x7F;
    int b, d, e, f, g, h, i, j, k, l, m;
    
    if(x == 0)
    {
        return 0;
    }
    if((x) = (1 << 31)) //x is minimum val, can't negate
    {
        return 0xCF000000;
    }
    
    res = res | a; //save sign
    
    if(a) //only positive val
    {
        b = -x;
    }
    
    while(b/=2) //exponent val
    {
        c = c + 1;
    }
    
    d = c - 0x7F; //get last bit
    e = (1 << d) - 1; //mask
    f = e & b;
    g = 23 - d;
    
    if(d <= 23)
    {
        res = res + (f << g);
    }
    else
    {
        h = -g - 1;
        i = 1 << h;
        j = f & (i - 1);
        k = f & (1 << (-g));
        l = f & i;
        m = f >> (-g);
        
        m = m + (l & (j || k));
        res = res | m;
    }
    res = res + (c << 23);
    
    return res;
    //return 2;
}

/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    unsigned a;
    unsigned b = uf >> 23; //right shift to isolate bits at the left
    unsigned c = b & 0xFF; //compare to 1's
    unsigned d;
    unsigned e;
    if(uf <= 0) //undefined case
    {
        a = uf;
    }
    else if(c == 0xFF) //if the exponent is a special value
    {
        a = uf;
    }
    else if(c == 0) //if exponent is 0
    {
        d = uf << 1; //gets rid of sign
        e = uf & (1 << 31); //compares to 1000000000...
        a = e | d;
        //or means one or both can be a 1, little bit confused
    }
    else //exponent is greater than 0
    {
        a = uf + (1 << 23); //otherwise return bit version of uf
    }
    return a;
}
