num divide(num one, num two){
	static num result;
	num qu;

	if(two.part == NULL){
		initnum(&result);
		initnum(&qu);
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
