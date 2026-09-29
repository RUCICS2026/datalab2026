/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return (~(~x | ~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y)&(~(x&y));
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x)
        return (!y);
    if(!y)
        return 0;
    return !((x>>31)^(y>>31));

}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int shift;
    int result;
    int mask16 = (0xFF << 8) | 0xFF;

    shift = (v > mask16) << 4;
    result = shift;
    v = v >> shift;
    shift = (v > 0xFF) << 3;
    result = result | shift;
    v = v >> shift;
    shift = (v > 0xF) << 2;
    result = result | shift;
    v = v >> shift;
    shift = (v > 0x3) << 1;
    result = result | shift;
    v = v >> shift;
    result = result | (v > 1);
    return result;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int nshift=n<<3;
    int mshift=m<<3;
    int nbyte=(x>>nshift)&0xFF;
    int mbyte=(x>>mshift)&0xFF;
    int difference=nbyte^mbyte;
    return x^((difference<<nshift)|(difference<<mshift));
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result=0;
    unsigned count=32;
    while(count){
        result=(result<<1)|(v&1);
        v=v>>1;
        count=count-1;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask= ~(((1<<31)>>n)<<1);
    return (x>>n) & mask;//mask清除右移产生的符号位，因此要构造mask前n位为0
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int count;
    int shift;

    shift = !(~x >> 16) << 4;
    count = shift;
    x = x << shift;
    shift = !(~x >> 24) << 3;
    count = count + shift;
    x = x << shift;
    shift = !(~x >> 28) << 2;
    count = count + shift;
    x = x << shift;
    shift = !(~x >> 30) << 1;
    count = count + shift;
    x = x << shift;
    shift = !(~x >> 31);
    count = count + shift;
    x = x << shift;
    count = count + !(~x >> 31);
    return count;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
     unsigned sign;
    unsigned magnitude;
    unsigned significand;
    unsigned remainder;
    unsigned halfway;
    int highest = 0;
    int drop;

    if (x == 0)
        return 0;
    sign = x & (1 << 31);
    if (x < 0)
        magnitude = ~x + 1;
    else
        magnitude = x;

    while ((magnitude >> highest) > 1)

        highest = highest + 1;

    if (highest > 23) {
        drop = highest - 23;
        significand = magnitude >> drop;
        remainder = magnitude & ((1 << drop) - 1);
        halfway = 1 << (drop - 1);
        if (remainder > halfway)
            significand = significand + 1;
        else if (remainder == halfway)
            if (significand & 1)
                significand = significand + 1;
    } else {
        significand = magnitude << (23 - highest);
    }
    return sign | (((highest + 127) << 23) + significand - (1 << 23));
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & (1 << 31);
    unsigned exponent = uf & 0x7F800000;

    if (exponent == 0x7F800000)
        return uf;
    if (exponent == 0)
        return sign | ((uf & 0x7FFFFFFF) << 1);
    if (exponent == 0x7F000000)
        return sign | 0x7F800000;
    return uf + 0x00800000;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned sign = uf2 >> 31;
    int exponent = (uf2 >> 20) & 0x7FF;
    unsigned high = (uf2 & 0xFFFFF) | (1 << 20);
    unsigned value;
    int power = exponent - 1023;

    if (!(exponent < 0x7FF) & !(exponent > 0x7FF))
        return 0x80000000;
    if (power < 0)
        return 0;
    if (power > 30)
        return 0x80000000;
    if (power < 20)
        value = high >> (20 - power);
    else {
        value = high << (power - 20);
        if (power > 20)
            value = value | (uf1 >> (52 - power));
    }
    if (sign)
        return -value;
    return value;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x<-149)
        return 0;
    if(x<-126)
        return 1<<(x+149);
    if(x<=127)
        return (x+127)<<23;
    return 0x7F800000;
}
