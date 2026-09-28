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
//按位与
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
//异或操作
int bitXor(int x, int y) {
    return ~(~x&~y)&~(x&y);
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
//是否同号，0单独考虑；其余数考虑符号位；
int samesign(int x, int y) {
    if(!x&&!y){return 1;}
    if(!(x&&y)){return 0;}
    else{
        return !((x>>31)^(y>>31));
    }
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
//找到二进制下最高位的1所在位置，即可表示以2为底对数值；
//采用二分法；
int logtwo(int v) {
    int shift_num=0;
    int res=0;
    shift_num=(v>0xFFFF)<<4;
    res=res|shift_num;
    v=v>>shift_num;
    shift_num=(v>0xFF)<<3;
    res=res|shift_num;
    v=v>>shift_num;
    shift_num=(v>0xF)<<2;
    res=res|shift_num;
    v=v>>shift_num;
    shift_num=(v>0x3)<<1;
    res=res|shift_num;
    v=v>>shift_num;
    shift_num=(v>0x1)<<0;
    res=res|shift_num;
    return res;
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
//取位交换
int byteSwap(int x, int n, int m) {
    int shift_n=n<<3;
    int shift_m=m<<3;
    int byte_n=(x>>shift_n)&0xFF;
    int byte_m=(x>>shift_m)&0xFF;
    int res=(x&~((0xFF<<shift_n)|(0xFF<<shift_m)))|(byte_n<<shift_m)|(byte_m<<shift_n);
    return res;
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
//遍历取位逆序
unsigned reverse(unsigned v) {
    unsigned a=0;
    unsigned cnt=0xffffffff;
    while(cnt!=0){
        a=(a<<1)|(v&1);
        v=v>>1;
        cnt=cnt<<1;
    }
    return a;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
//右移n位，利用a改变int右移带符号问题
int logicalShift(int x, int n) {
    int a=~((1<<31)>>n<<1);
    return (x>>n)&a;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
//计数最左侧连续的1的数量；二分法；
int leftBitCount(int x) {
    int cnt=0;
    int shift;
    shift=!(~(x>>16))<<4;//如果前16位都是1，则shift=16；
    cnt+=shift;
    x=x<<shift;//左移shift位

    shift=!(~(x>>24))<<3;
    cnt+=shift;
    x=x<<shift;

    shift=!(~(x>>28))<<2;
    cnt+=shift;
    x=x<<shift;

    shift=!(~(x>>30))<<1;
    cnt+=shift;
    x=x<<shift;

    shift=!(~(x>>31))<<0;
    cnt+=shift;
    x=x<<shift;

    cnt+=!(~(x>>31));//最后剩余一位也可能是1
    return cnt;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
//将x转化为浮点数表示形式
unsigned float_i2f(int x) {
    if(x==0){return 0;}
    unsigned S=0;
    unsigned E=31;
    unsigned M=0;
    unsigned abs_x=x;
    if(x<0){S=1;abs_x=-abs_x;}
    while(!(abs_x>>E)){E--;}//计算最高位1的位置，即指数
    unsigned shift=E-23;
    unsigned s=shift-1;
    unsigned extra_bits=abs_x&((1<<s)-1);
    unsigned R=((abs_x>>s)&1);
    if(E>23){
        M=(abs_x>>shift)&0x7FFFFF;
        //考虑进位，如果舍弃位的最高位为1，看剩余舍弃位非0进位；如果是0，看保留位是1则进位。
        if(R){
            if(extra_bits==0){
                if(M&1){M++;}
            }else{M++;}
        }
        if(M&0x800000){E++;}//M超过23位，向E进位
    }else{
        M=abs_x<<(-shift);
    }
    E+=127;
    unsigned res=(S<<31)|(E<<23)|(M&0x7FFFFF);
    return res;
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
//浮点数的两倍
unsigned floatScale2(unsigned uf) {
    int S=uf>>31&1;
    int E=(uf>>23)&0xFF;
    //考虑NaN和无穷
    if(E==0xFF){return uf;}
    int M=uf&0x7FFFFF;
    if(E==0xFF){
        return uf;
    }
    //考虑非规格化数
    if(E==0){
        M=M<<1;
        if(M&0x800000){E=1;M=M&0x7FFFFF;}
    }else{E+=1;}
    int res=(S<<31)|(E<<23)|M;
    return res;
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
//将两个int类型拼接成32位浮点数
int float64_f2i(unsigned uf1, unsigned uf2) {
    int S=(uf2>>31)&1;
    int E=(uf2>>20)&0x7FF;
    int M_higher=(uf2&0xFFFFF);
    int M_lower=uf1;
    int res;
    if(!E){return 0;}
    if(E>=0x7FF){return 0x80000000;}
    E=E-1023;
    if(E<0){return 0;}
    if(E>=31){
        return 0x80000000;
    }
    int shift_extra=52-E;
    if(shift_extra<=32){
        int m_l=(M_lower>>shift_extra)&((1<<(32-shift_extra))-1);
        int m_h=M_higher<<shift_extra;
        res=(1<<E)|m_h|m_l;
    }else{
        int s=shift_extra-32;
        res=(1<<E)|(M_higher>>s);
    }
    if(S){
        res=~res+1;
    }
    return res ;
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
//2的x次方，即二进制下，第x位置1；浮点数表示。
unsigned floatPower2(int x) {
    int E;
    if(x>127){return 0x7F800000;}
    if(x<-149){return 0;}
    if(x>=-126){
        E=x+127;
        return E<<23;
    }else{
        int shift=-126-x;
        return 1<<(23-shift);
    }
}
