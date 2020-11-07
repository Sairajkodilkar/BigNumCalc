#include "num.h"
#include "unistd.h"

num boolone, boolzero;

void initconstants(){
	extern num boolone, boolzero;
	initnum(&boolone);
	initnum(&boolzero);
	insert_digit(&boolone, 1);
	insert_digit(&boolzero, 0);
}


/* void initnum(num *one)
 * use:
 * 		initialise the number;
 * 		user should call it before using the new number
 * precondition:
 * 		one: pointer to the num
 * postconditon:
 * 		number is initialised with sign 1
 */
void initnum(num *one){
	one->part = NULL;
	one->point = -1;//indicating it is not float, 0 meaning frac at start 
	one->count = 0; 
	one->sign = 1;
	return;
}
/* void insert_digit(num *one, int dig)
 * use:
 * 		inserts digit in reverse order
 * precondition:
 * 		one : pointer to the num 
 * 		dig : digit to be inserted
 * postcondition:
 * 		dig is inserted at the front 
 */
void insert_digit(num *one, int dig){
	node *temp;
	(one->count)++;
	temp = one->part;
	one->part = MALLOCNODE;
	one->part->next = temp;
	one->part->digit = dig;
}

/* create a copy of given number*/
void __copy(num *number, node *part){
	if(part == NULL)
		return;
	__copy(number, part->next);
	insert_digit(number, part->digit);
	return;
}

void copy(num one, num *number){
	initnum(number);
	__copy(number, one.part);
	number->point = one.point;
	number->count = one.count;
	number->sign = one.sign;
}

/* void reverse(num *one){
 * use:
 * 		reverse the digits in the number
 * precondition:
 * 		one: pointer to the num
 * postcondition:
 * 		digits of one are reversed
 */
void reverse(num *one){
	if(one->part == NULL || one->part->next == NULL){
		return;
	}
	node *temp = NULL, *next = one->part->next;

	while(next != NULL){
		one->part->next = temp;
		temp = one->part;
		one->part = next;
		next = next->next;
	}
	one->part->next = temp;
}


/* int __isgreater(node *one, node *two)
 * use:
 * 		supporting function for the isgreater(num one, num two)
 * 		NOTE: for internal use only
 * precondition:
 * 		one, two: pointer to the node
 * postcondition:
 * 		if the digits in one > two 1 is returned
 * 		else 0 is returned
 */
int __isgreater(node *one, node *two){
	int x;
	if(one == NULL && two != NULL){
		while(two->next != NULL && two->digit != 0){
			two = two->next;
		}
		if(two->next == 0){
			return 2;
		}
		return 0;
	}
	
	else if(one != NULL && two == NULL){
		while(one->next != NULL && one->digit != 0){
			one = one->next;
		}
		if(one->next == 0){
			return 2;
		}
		return 1;
	}
	
	else if(one->next == NULL && two->next == NULL){
		if(one->digit > two->digit){
			return 1;
		}
		else if(one->digit == two->digit){
			return 2;
		}
		else{ 
			return 0;
		}
	}

	x = __isgreater(one->next, two->next);
	/* if most significant are equal then compare current */
	if(x == 2){
		if(one->digit > two->digit){
			return 1;
		}
		else if(one->digit == two->digit){
			return 2;
		}
		else{
			return 0;
		}
	}
	return x;
}



/* int isgreater(num one, num two)
 * use:
 * 		checks if one is greater than two
 * precondition:
 * 		one, two: are numbers
 * postcondition:
 * 		if one > two 1 is returned
 * 		else 0
 */
int isgreater(num one, num two){
	int x;
	if(one.sign == -1 && two.sign != -1){
		return 0;
	}
	if(two.sign == -1 && one.sign == 1){
		return 1;
	}
	if(one.sign == -1 && two.sign == -1)
		x = __isgreater(two.part, one.part);
	else if(one.sign == 1 && one.sign == 1)
		x = __isgreater(one.part, two.part);
	if(x != 1)
		return 0;
	return 1;
}

int isgreaterequal(num one, num two){
	int x;
	if(one.sign == -1 && two.sign != -1){
		return 0;
	}
	if(two.sign == -1 && one.sign == 1){
		return 1;
	}
	x = __isgreater(one.part, two.part);
	if(x == 0)
		return 0;
	return 1;
}

int isequal(num one, num two){
	int x;
	if(one.sign != two.sign){
		return 0;
	}
	x = __isgreater(one.part, two.part);
	if(x == 2)
		return 1;
	return 0;
}
/* following function are for users */
num equal(num one, num two){
	int x;
	num boolean;
	x = isequal(one, two);
	if(x == 1){
		copy(boolone, &boolean);
		return boolean;
	}
	copy(boolzero, &boolean);
	return boolean;
}

num notequal(num one, num two){
	int x;
	num boolean;
	x = isequal(one, two);
	if(x == 0){
		copy(boolone, &boolean);
		return boolean;
	}
	copy(boolzero, &boolean);
	return boolean;
}

num greaterthan(num one, num two){
	int x;
	num boolean;
	x = isgreater(one, two);
	if(x == 1){
		copy(boolone, &boolean);
		return boolean;
	}
	copy(boolzero, &boolean);
	return boolean;
}

num greaterthaneq(num one, num two){
	int x;
	num boolean;
	x = isgreaterequal(one, two);
	if(x != 0){
		copy(boolone, &boolean);
		return boolean;
	}
	copy(boolzero, &boolean);
	return boolean;
}

num lessthan(num one, num two){
	int x;
	num boolean;
	x = isgreaterequal(one, two);
	if(x == 0){
		copy(boolone, &boolean);
		return boolean;
	}
	copy(boolzero, &boolean);
	return boolean;
}

num lessthaneq(num one, num two){
	int x;
	num boolean;
	x = isgreater(one, two);
	if(x == 0){
		copy(boolone, &boolean);
		return boolean;
	}
	copy(boolzero, &boolean);
	return boolean;
}
/* end of boolean functions */

/* 
 * to compute the length of digit 
 * NOTE: supporting function
 */
int len(int x){
	if(x == 0)
		return 1;
	int i = 0;
	while(x){
		i++;
		x = x / 10;
	}
	return i;
}



/* void __printnum(node *start, int sign)
 * use:
 * 		supporting function for the printnum(num one)
 * 		NOTE: for internal use only
 * precondition:
 * 		start is the pointer to the node
 * 		sign is the sign of number allowed : -1 or 1
 * postcondition:
 * 		prints the number on stdout
 */
void __printnum(node *start, int sign, int count){
	int x;
	if(start == NULL){
		if(count == 0)
			printf(".");
		if(sign == -1)
			printf("-");
		return;
	}
	__printnum(start->next, sign, count - 1);
	x = len(start->digit);
	if(x < 8){
		x = 8 - x;
		while(x--)
			printf("0");
	}

	printf("%d", start->digit);
	if(count == 0){
		printf(".");
	}
	return;
}


/* void printnum(num one)
 * use:
 * 		prints the given num
 * precondition:
 * 		one : number to be printed
 * postcondition:
 * 		prints the number on stdout
 */

void printnum(num one){
	if(one.part == NULL){
		printf("0\n");
		return;
	}
	__printnum(one.part, one.sign, one.count - one.point);
	printf("\n");
}



/* erasenum(num *one)
 * use:
 * 		frees the malloced memory occupied by the num
 * 		user should call it before exiting
 * precondition:
 * 		one is the pointer to the num
 * postcondition:
 *		number is dellocated
 */
void erasenum(num *one){
	node *temp = one->part;
	one->part = NULL;
	node *prev;
	while(temp != NULL){
		prev = temp->next;
		free(temp);
		temp = prev;
	}
	return;
}



/* num add(num one, num two)
 * use:
 * 		add the number one and two
 * precondition:
 * 		one, two: number to be added
 * postcondition:
 * 		return the num containing result of addition
 */
num add(num one, num two){

	/* checks if sign are same or different */
	if(one.sign == -1 && two.sign == 1){
		one.sign = 1; //changing locally hence no effect on original number
		return sub(two, one); //two - one
	}
	if(one.sign == 1 && two.sign == -1){
		two.sign = 1;
		return sub(one, two); //one - two
	}

	int frac1, frac2, diff, max = 0;
	num result;
	initnum(&result);

	/* In case number of digits after fraction is not equal */

	if(one.point != -1){
		frac1 = (one.count - one.point);
		max = frac1;
	}
	else
		frac1 = 0;
	if(two.point != -1){
		frac2 = (two.count - two.point);
		max = frac2;
	}
	else
		frac2 = 0;
	diff = frac1 - frac2;
	if(diff > 0){
		max = frac1;
		while(diff){
			insert_digit(&result, one.part->digit); 
			one.part = one.part->next;
			diff--;
		}
	}
	else if(diff < 0){
		max = frac2;
		diff = -diff;
		while(diff){
			insert_digit(&result, two.part->digit); 
			two.part = two.part->next;
			diff--;
		}
	}

	node *x = one.part, *y = two.part;
	int x_d, y_d, r, carry;
	carry = 0;
	while(x != NULL || y != NULL || carry != 0){
		x_d = (x == NULL)?0:x->digit;
		y_d = (y == NULL)?0:y->digit;
		r = x_d + y_d + carry;
		if(r > MAX_DIG)
			carry = r / 100000000;
		else
			carry = 0;
		r = r % 100000000;
		insert_digit(&result, r);

		x = (x == NULL)?x:x->next;
		y = (y == NULL)?y:y->next;
	}
	reverse(&result);

	if(one.sign == -1 && two.sign == -1){
		result.sign = -1;
	}
	if(max){
		result.point = result.count - max;
	}

	return result;
}
/* num sub(num one, num two)
 * use:
 * 		subracts the number two from one
 * precondition:
 * 		one, two: numbers to be subtracted
 * postcondition:
 * 		return the num containing result of subtraction
 */

num sub(num one, num two){
	/* checks if sign are same or different */
	if(one.sign == -1 && two.sign == 1){
		two.sign = -1;
		return add(one, two);
	}

	if(one.sign == 1 && two.sign == -1){
		two.sign = 1;
		return add(one, two);
	}

	num result;
	int diff, frac1, frac2, tem, max = 0;
	node *x , *y;
	initnum(&result);

	if(one.point != -1){
		frac1 = (one.count - one.point);
	}
	else
		frac1 = 0;
	if(two.point != -1){
		frac2 = (two.count - two.point);
	}
	else
		frac2 = 0;

	tem = diff = frac1 - frac2;
	max = frac1 > frac2 ? frac1 : frac2;
	if(diff > 0){
		while(diff){
			insert_digit(&two, 0);
			diff--;
		}	
	}
	else if(diff < 0){
		while(diff){
			insert_digit(&one, 0);
		}
	}

	if(isgreater(two, one)){
		x = two.part;
		y = one.part;
		result.sign = -1;
	}
	else{
		x = one.part;
		y = two.part;
	}

	int x_d, y_d, r, borrow = 0;
	while(x != NULL || y != NULL){
		x_d = (x == NULL)?0:x->digit;
		y_d = (y == NULL)?0:y->digit;
		if(y_d > x_d){
			x_d = x_d + 100000000 - borrow;
			borrow = 1;
		}
		else{
			x_d = x_d - borrow;
			borrow = 0;
		}
		r = x_d - y_d;
		insert_digit(&result, r);
		x = (x == NULL)?x:x->next;
		y = (y == NULL)?y:y->next;
	}

	/* To prevent memory leak */
	if(tem > 0){
		while(tem){
			free(two.part);
			(two.part) = (two.part)->next;
			two.count--;
			tem--;
		}
	}
	else if(tem < 0){
		while(tem){
			free(one.part);
			one.part = one.part->next;
			one.count--;
			tem--;
		}
	}
	if(max){
		result.point = result.count - max;
	}

	reverse(&result);
	return result;
}



/* num __multiply(node *one, node *two)
 * use:
 * 		supporting function for multiply 
 * 		this multiplies one with each node in two
 * precondition:
 * 		one, two: pointer to the node
 * postcontion:
 * 		the result of multiplication is returned in number
 */

num __multiply(node *one, node *two){
	node *temp = two;
	num result;
	initnum(&result);
	int dig = (one != NULL) ? one->digit : 0, dig2;

	if(dig == 0){
		insert_digit(&result, 0);
		return result;
	}

	long r, carry = 0;

	while(temp != NULL || carry != 0){

		dig2 = temp ? temp->digit : 0;
		r = (long)dig2 * (long)dig + carry;

		carry = r / 100000000;
		r = r % 100000000;

		temp = temp == NULL ? NULL : temp->next;

		insert_digit(&result, (int)r);
	}
	reverse(&result);
	return result;
}


/* num multiply(num one, num two)
 * use:
 * 		supporting function for multiply 
 * 		this multiplies one with each node in two
 * precondition:
 * 		one, two: pointer to the node
 * postcontion:
 * 		the result of multiplication is returned in number
 */
num multiply(num one, num two){
	num result, prev, garbage;
	int frac1, frac2;
	int i, j;
	i = j = 0;
	initnum(&result);
	initnum(&prev);
	initnum(&garbage);
	node *temp;
	temp = one.part;
	while(temp != NULL){
		j = 0;
		garbage = prev;
		result = __multiply(temp, two.part);
		while(j < i){
			insert_digit(&result, 0);
			j++;
		}
		prev = add(result, prev);

		/* to prevent memory leak */
		erasenum(&result);
		initnum(&result);
		erasenum(&garbage);
		initnum(&garbage);

		temp = temp->next;
		i++;
	}
	/* fraction point just get adds up in multiplication */
	frac1 = one.point == -1 ? 0 : (one.count - one.point);
	frac2 = two.point == -1 ? 0 : (two.count - two.point);
	i = frac1 + frac2;
	if(i != 0){
		prev.point = prev.count - i;
	}

	prev.sign = one.sign * two.sign;
	return prev;
}

/* num divide(num one, num two)
 * precondition:
 * 		one: divisor
 * 		two: divident
 * postcondition:
 * 		two / one returned
 */


num divide(num one, num two){
	static num result;
	num qu;

	if(two.part == NULL){
		initnum(&result);
		initnum(&qu);
		qu.sign = one.sign * two.sign;
		one.sign = two.sign = 1;
		return qu;
	}

	num forward;
	num curr;
	num prevq;
	num prevr;
	initnum(&forward);
	initnum(&curr);
	initnum(&qu);

	int i = 0;

	forward.part = two.part->next;
	qu = divide(one, forward);
	prevq = qu;
	insert_digit(&result, two.part->digit);
	insert_digit(&qu, 0);
	prevq = qu;

	while(isgreaterequal(result, one)){
		prevr = result;
		result = sub(result, one);
		erasenum(&prevr);
		i++;
	}
	insert_digit(&curr, i);
	qu = add(qu, curr);
	erasenum(&prevq);

	return qu;
}







