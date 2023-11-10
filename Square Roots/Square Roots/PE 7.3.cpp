/*******************************************************************************
* 
* Author: Zaelfenn Sandow
* 
* created: 10/17/2022
* 
* Purpose: solve a quadratic equation, and display proper equations in the case of imaginary numbers/zeroes in denominators
* 
* *******************************************************************************/

#include <iostream> //for cout and cin

using std::cout;
using std::cin;

#include <cmath> //for square roots

int main() {
	float a = 0,
		b = 0,
		c = 0,
		discriminant = 0,
		denominator = 0,
		zero_1 = 0,
		zero_2 = 0,
		imaginary_discriminant = 0; 


	cout << "what is your A-value?\n";
	cin >> a;

	cout << "\n\nwhat is your B-value?\n";
	cin >> b;

	cout << "\n\nwhat is your C-value?\n";
	cin >> c;

	denominator = 2 * a;

		if ((b * b) - (4 * a * c) >= 0) 
		{
			discriminant = sqrt((b * b) - (4 * a * c));
		}
	
		else 
		{
			imaginary_discriminant = ((b * b) - (4 * a * c)) * -1;
			imaginary_discriminant = sqrt(imaginary_discriminant);
		} //all of this is to help with finding imaginary roots, in case that is requested

	if (denominator == 0)
	{
		cout << "\n\n\tError, denominator cannot be equal to 0.";
	}
	
	else if (imaginary_discriminant > 0) {
		zero_1 = static_cast<float>((-b + imaginary_discriminant) / denominator);
		zero_2 = static_cast<float>((-b - imaginary_discriminant) / denominator);

		cout << "\n\nYou have 2 zeroes, which are " << zero_1 << "i and " << zero_2 << "i.";

	}
	
	else if (discriminant == 0) {
		zero_1 = static_cast<float>( - b / denominator);
		cout << "\n\nBecause the discriminant was 0, you only have one zero, which is " << zero_1 << '.';
	}
	
	else {
		zero_1 = static_cast<float>((-b + discriminant) / denominator);
		zero_2 = static_cast<float>((-b - discriminant) / denominator);

		cout << "\n\nYou have 2 zeroes, which are " << zero_1 << " and " << zero_2 << '.';
	}

	return 0;
}