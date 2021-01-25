// Code for Set 1, Challenge 1 in Cryptopals
// Single-byte XOR cipher
#include "english_score.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <math.h>
#include <numeric>
#include <string>
#include <vector>

namespace
{
/**
* The approximate frequencies with which the letters of the alphabet appear
* in regular English text.
*/
const std::vector<double> englishFrequencies 
{
	8.34, 1.54, 2.73, 4.14, 12.60,
	2.03, 1.92, 6.11, 6.71, 0.23,
	0.87, 4.24, 2.53, 6.80, 7.70,
	1.66, 0.09, 5.68, 6.11, 9.37,
	2.85, 1.06, 2.34, 0.20, 2.04, 0.06
};
}

namespace CPals
{

/**
* The approximate 'distance' between a provided text and typical English text.
* A lower score means the provided text is closer to typical English. The
* score is calculated based on the Chi-squared distance between the letter
* frequency distributions. Strips input text of non-alphabet characters and
* converts to lower case before comparing.
*
* Parameters:
*	input:	The text to compare.
*
* Result:
*	A 'distance' score of at least zero.
*/
double englishDistanceScore(std::string input)
{
	sanitise(input);

	std::vector<double> frequencies(26);
	std::for_each(input.cbegin(),
				  input.cend(),
				  [&frequencies](unsigned char c) { frequencies[c - 97]++; });

	auto expectedFrequencies{ englishFrequencies };
	const auto scaleFactor{ static_cast<double>(input.length()) / 100.0 };
	std::for_each(expectedFrequencies.cbegin(),
				  expectedFrequencies.cend(),
				  [scaleFactor](double item) { item *= scaleFactor; });

	return chiSquared(expectedFrequencies, frequencies);
}

/**
* Strip a string of non alphabet characters and convert the remaining
* characters to lower case.
*
* Parameters:
*	input:	The string to sanitise.
*/
void sanitise(std::string &input)
{
	const auto end = std::remove_if(input.cbegin(),
				   input.cend(),
				   [](unsigned char c) {return !isalpha(c); });
	input.erase(input.cbegin(), end);
	std::for_each(input.begin(), input.end(), tolower);
}

/**
* Calculate the Chi-squared statistic of a pair of distributions. Useful for
* working out how closely one distribution resembles another, with a lower
* score meaning a closer resemblance.
*
* Parameters:
*	expected:	The expected distribution.
*	actual:		The observed distribution.
*
* Returns:
*	The Chi-squared statistic.
*/
double chiSquared(
	const std::vector<double> &expected,
	const std::vector<double> &actual)
{
	std::vector<double> result;
	std::transform(expected.cbegin(),
				   expected.cend(),
				   actual.cbegin(),
				   std::back_inserter(result),
				   [](double e, double a) {return pow(e - a, 2) / e; });

	return std::accumulate(result.cbegin(), result.cend(), 0);
}

}
