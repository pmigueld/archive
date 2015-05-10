function multiple_of_3(n) {	return n % 3 == 0; }
function multiple_of_5(n) {	return n % 5 == 0; }

for(var i = 1; i <= 100; i++) {
	var output = "";

	if (!multiple_of_3(i) && !multiple_of_5(i)) {
		output = i;
	}

	if (multiple_of_3(i)) output += "Fizz";
	if (multiple_of_5(i)) output += "Buzz";

	console.log(output + "\n");
}