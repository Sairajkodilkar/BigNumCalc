# BASIC CALCULATOR
Implementing High precision calculator with basic fuctionalities  
The calculator take cares of precedance of operators as well as brackets  
variables which are less than 18 characters and contains a-z A-z or _ are valid identifiers

## Github link  
[Sairajkodilkar](https://github.com/Sairajkodilkar/Project.git)

## How to build and run
Makefile is provided. Type following command in shell and the executable file **calc** is created 
```shell
make
```
type following command to run the program
```shell
./calc
```
to remove object files( including calc ) type 
```shell
make clean
```

## Operations supported
    1. Addition (+)
    2. Subtraction (-)
    3. Multiplication (*)
    4. Division (/)
    5. Boolean (==, <=, >=, >, <)
    6. Assignment (=)
   
## Valid syntax
```
>>> ((3 + 10) * 4) - 66)
>>> a = 124327893248904.92873
>>> b = 24873421988324898478723408.09823748
>>> a = a + b
>>> b = b * a * ( (b + a) * a) / b
>>> output = a < b
>>> output = b > a
>>> output = a <= b
>>> output = b >= a
>>> output = a == b

```

## Implemantion details

### Basic data structures used
    * Stack
    * Linklist
    * Hashtable
    
### Representation of Number 
The number is implimented using linked list using following structure.
```C
typedef struct node{
	int digit;
	struct node *next;
}node;

typedef struct num{
	node *part;
	int point;
	int count;
	int sign;
}num;
```


each node of list contains 8 digit of the number starting from left to right before decimal
and right to left after decimal in little endian format.
**e.g.** number 1234.6789 is stored as 
|node 1|node 2|
|------|------|
|6789|1234|

point is the location of decimal point.  
count is the count of all digits.  
sign is sign of number.  

    * -1 for negative 
    * 1 for positive
    * 2 specifying don't print this number (a placeholder) 
    * 3 for error
 

### Lexical analysis
Lexical analysis is done using finite state machine which uses following states.  
**START, OPERATOR, NUMBER, FRAC, SPACE, VAR, END, ERR**
and returns token in structure
```C
typedef struct token{
	int type;
	union{
		num number;
		char op;
		char var[20];
	}data;
}token;
```
* type stores the token type 
* number stores num
* op stores operator
* var stores identifier

### Evaluation
The output of lexical analyser is evaluated by the eval fuction using stacks and identifier
For identifiers the symbol table is hashtable which resolves collision by chaining 
which passes the output to the main which is either printable or not printable

























