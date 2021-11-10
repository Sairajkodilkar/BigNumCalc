
equal() {
	echo "$1 == $2" | bc
}

bc_result() {
	echo "$1 $2 $3" | bc
}

calc_result() {
	echo "$1 $2 $3" | ./calc
}

testing() {
	for operator in '+' '-' '*' '>=' '<=' '>' '<'; do
	
		result1=$(bc_result $1 $operator $2)
		result2=$(calc_result $1 $operator $2)
		equality=$(equal $result1 $result2)
	
		if [ $equality -eq 1 ]; then
			test_status="Passed"
		else
			test_status="Failed"
		fi
		case $operator in 
			'+') echo "$test_status Summation test";;
			'-') echo "$test_status Subtraction test";;
			'*') echo "$test_status Multiplication test";;
			'<') echo "$test_status Less than test";;
			'>') echo "$test_status Greater than test";;
			'<=') echo "$test_status Less than equal to test";;
			'>=') echo "$test_status Greater than equal to test";;
		esac
	
	done
	echo $result
}

echo "Test 1"
operand1=103112142352351351351351351515135
operand2=112413513513513513513513513513515
testing $operand1 $operand2

echo "Test 2"
operand1=-103112142352351351351351351515135
operand2=112413513513513513513513513513515
testing $operand1 $operand2

echo "Test 3"
operand1=0
operand2=-112413513513513513513513513513515
testing $operand1 $operand2

echo "Test 4"
operand1=0
operand2=0
testing $operand1 $operand2

echo "Test 5"
operand1=0
operand2=2
result=$(echo "$operand1 & $operand2" | ./calc)
if [ $result = "BAD EXPRESSION" ];then
	echo "Passed Invalid operation test"
else
	echo "Failed Invalid operation test"
fi


