#include <stdio.h>
//Harshavardhan Reddipalli
//CS230
//Project 2b
//Bits and Bytes
//I have written comments for each function as to how it works.
//I added a print statemnet for a new line after every function so it looks better when outputted.

void print_it() {
// TODO1
//This function is pretty staright forward as I just print the given statement.
printf("Bit operations are fun!\n");
printf("\n");
}

void print_int() {
// TODO2
//In this function I added two print statements to print out the size of x in bytes and bits.
//In the end I addded a print statment to print the addition of x and y.
signed int x = 10;
signed int y = 13;
printf("x = %d\n", x);
printf("y = %d\n", y);
printf("size of signed int in bytes is %zu.\n",sizeof(x));
printf("size of signed int in bits is %zu.\n",8*sizeof(x));//1 byte is 8 bits so I multiplied it by 8.
printf("%d + %d = %d.\n",x,y,x+y);
printf("\n");
}

void print_float() {
// TODO3
//This function is similar to the last function but instead of int we have float.
float x = 10.000000;
float y = 13.000000;
printf("x = %f\n", x);
printf("y = %f\n", y);
printf("size of single float in bytes is %zu.\n",sizeof(x));
printf("size of single float in bits is %zu.\n",8*sizeof(x));//1 byte is 8 bits so I multiplied it by 8.
printf("%f + %f = %f.\n",x,y,x+y);
printf("%f + %f = %d.\n",x,y,(int)x+(int)y);//I cast x an y to output the float as an integer.
printf("\n");
}

void print_char() {
// TODO4
//In this function I created 3 new characters and assigned them to their corresponding values.
//I then print out the character string "CAFEBABE".
char c = 'C';
char a = 65;
char f = 'F';
char e = 'E';
char b = 'B';
char str[] = "CAFEBABE";
printf("c = %c\n", c);
printf("a = %c\n", a);
printf("%c%c%c%c%c%c%c%c\n",c,a,f,e,b,a,b,e);
printf("number of bytes: %lu.\n",sizeof(str));//Number of bytes is total number of characters plus one beacuse of the terminator.
printf("\n");
}

void packing_bytes() {
// TODO5
//In this function I created 4 unsigned characters b3 to b0 and assigned them to their corresponding values.
//I then used the left shift operator to store them in the integer u and used the or operator to add them up.
unsigned char b3 = 202;
unsigned char b2 = 254;
unsigned char b1 = 186;
unsigned char b0 = 190;
unsigned int u = (b3<<24) | (b2<<16) | (b1<<8) | (b0<<0);//I know b0<<0 is the same as b0,but still included it as it matches the style.
printf("%X\n",u);
printf("\n");
}

void unpacking_bytes() {
// TODO6
//In this function I created 8 unsigned integers to store the values of i1 and i2 after the right shift operations.
//Each bytes has 8 bits and i1 and i2 are stored in 4 bytes.
//I also created 2 unsigned integers,so it makes it easier to print out the results from the loops.
unsigned int i1 = 1835098984u;
unsigned int i2 = 1768842611u;
unsigned int x;
unsigned int y;
for(int i =24;i>=0;i--){
x = i1>>i;
if(i%8==0){//Because 24,16,8 and 0 are divisible by 8.
printf("%c",x);}}
for(int i =24;i>=0;i--){
y = i2>>i;
if(i%8==0){//Because 24,16,8 and 0 are divisible by 8.
printf("%c",y);}}
printf("\n");
printf("\n");//not a mistake,just added this print statement so it makes the output easier to read.
}

void print_bits() {
// TODO7
//First we create and initialize the unsigned and signed characters.
//Then I create 16 other characters to store the values of the shift operations.
unsigned char x = 181;
signed char y = -75;
unsigned char ax,bx,cx,dx,ex,fx,gx,hx;
signed char ay,by,cy,dy,ey,fy,gy,hy;
ax = (x>>7)&1;
bx = (x>>6)&1;
cx = (x>>5)&1;
dx = (x>>4)&1;
ex = (x>>3)&1;
fx = (x>>2)&1;
gx = (x>>1)&1;
hx = (x>>0)&1;
printf("%d%d%d%d%d%d%d%d\n",ax,bx,cx,dx,ex,fx,gx,hx);//I print out the values after shift operations to x.
ay = (y>>7)&1;
by = (y>>6)&1;
cy = (y>>5)&1;
dy = (y>>4)&1;
ey = (y>>3)&1;
fy = (y>>2)&1;
gy = (y>>1)&1;
hy = (y>>0)&1;
printf("%d%d%d%d%d%d%d%d\n",ay,by,cy,dy,ey,fy,gy,hy);//I print out the values after shift operations to y.
printf("\n");
}

void extracting_fields() {
// TODO8
//Firstly we create a new variable and asign it to the give value,so we could perform steps and extract 10 fields from it.
//Then I create a for loop to make it more concise.
//Then we perform shift wise operations on them to extract our fields.
//We perform basic addition and subtraction of number to find out what numbers we should perform shift operations with the variable.(diff[])
unsigned int var = 0xCAFEBABE,fields[9],width[9] = {0,3,7,11,14,17,21,25,28},diff[10]={29,28,28,29,29,28,28,29,30};
for(int i=0;i<9;i++){
fields[i] = ((var<<width[i])>>diff[i]);
printf("%d ",fields[i]);}
printf("%d",(var<<30)>>30);//placed the last one here as there shouldn't be a space after the last number.
printf("\n");
printf("\n");//not a mistake,just added this print statement so it makes the output easier to read.
}

void updating_fields() {
// TODO9
//Firstly we start by creating a new unsigned integer and initializing it.
//Then we initialize any other variable that are going to be useful.
unsigned int var = 17512807u;
unsigned int x = 8;
unsigned int y = 17;
unsigned int vac = 0;
x = x<<18;//used to place 8 between 18 and 21.
y = y<<10;//used to place 17 between 10 and 14.
vac = ~(((1<<4)-1)<<18);//After doing the basic math this should be the formula for the bit mask.
var = var & (vac);
var = var | x;
vac = ~(((1<<4)-1)<<10);//After doing the basic math this should be the formula for the bit mask.
var = var & (vac);
var = var | y;
printf("%08x",var);//prints the value as a hexadecimal.
printf("\n");
}
