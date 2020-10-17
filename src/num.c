#include "num.h"
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
	if(one == NULL && two != NULL)
		return 0;
	else if(one != NULL && two == NULL)
		return 1;
	else if(one == NULL && two == NULL)
		return 0;
	if(__isgreater(one->next, two->next))
			return 1;
	else
		return one->digit > two->digit;
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
	return __isgreater(one.part, two.part);
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
	if(start == NULL){
		if(count == 0)
			printf(".");
		if(sign == -1)
			printf("-");
		return;
	}
	__printnum(start->next, sign, count - 1);
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

	num result;
	initnum(&result);
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
	node *x , *y;
	initnum(&result);
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
	int p1, p2;
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
	p1 = (one->count - one->point); 
	p2 = (two->count - two->point);
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
	int i, j;
	i = j = 0;
	initnum(&result);
	initnum(&prev);
	initnum(&garbage);
	node *temp;
	temp = one.part;
	while(temp != NULL){
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
	prev.sign = one.sign * two.sign;
	result.point = result.count - (p1 > 0 ? p1 : 0 + p2 > 0 ? p2 : 0);
	return prev;
}


























/*returns carry*/
/*
   int _add(node *part1, node *part2, num *result){
   int x, y, carry;
   if(part1 == NULL && part2 == NULL){
   return 0;
   }
   x = part1 == NULL?0:part1;
   y = part2 == NULL?0:part2;
   carry = _add(part1->next?part1->next:NULL, part1->next?part1->next:NULL, result);
   digit = x + y + carry;
   insert_front(result, digit % MAXDIGIT);
   return digit % MAX_DIG;

   }
   */




