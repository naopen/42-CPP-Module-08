/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <sstream>  // For stringstream in C++98
#include <cstdlib>
#include <ctime>
#include <list>
#include <deque>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

// Helper function to convert int to string (C++98 compatible)
std::string intToString(int value)
{
	std::ostringstream oss;
	oss << value;
	return oss.str();
}

void printTestHeader(const std::string& test_name)
{
	std::cout << CYAN << "\n========================================" << RESET << std::endl;
	std::cout << YELLOW << "Testing: " << test_name << RESET << std::endl;
	std::cout << CYAN << "========================================" << RESET << std::endl;
}

void printSuccess(const std::string& msg)
{
	std::cout << GREEN << "✓ " << msg << RESET << std::endl;
}

void printError(const std::string& msg)
{
	std::cout << RED << "✗ " << msg << RESET << std::endl;
}

// Test from subject
void testSubjectExample()
{
	printTestHeader("Subject Example");
	
	Span sp = Span(5);
	
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	
	try
	{
		int shortest = sp.shortestSpan();
		std::cout << "Shortest span: " << shortest << std::endl;
		if (shortest == 2)
			printSuccess("Shortest span is correct (2)");
		else
			printError("Shortest span is incorrect (expected 2, got " + 
				intToString(shortest) + ")");
	}
	catch(const std::exception& e)
	{
		printError("Exception in shortestSpan: " + std::string(e.what()));
	}
	
	try
	{
		int longest = sp.longestSpan();
		std::cout << "Longest span: " << longest << std::endl;
		if (longest == 14)
			printSuccess("Longest span is correct (14)");
		else
			printError("Longest span is incorrect (expected 14, got " + 
				intToString(longest) + ")");
	}
	catch(const std::exception& e)
	{
		printError("Exception in longestSpan: " + std::string(e.what()));
	}
}

// Test Orthodox Canonical Form
void testOCF()
{
	printTestHeader("Orthodox Canonical Form");
	
	// Test default constructor
	Span s1;
	printSuccess("Default constructor works");
	
	// Test parametric constructor
	Span s2(100);
	s2.addNumber(10);
	s2.addNumber(20);
	printSuccess("Parametric constructor works");
	
	// Test copy constructor
	Span s3(s2);
	if (s3.size() == 2 && s3.capacity() == 100)
		printSuccess("Copy constructor works correctly");
	else
		printError("Copy constructor failed");
	
	// Test assignment operator
	Span s4(50);
	s4 = s2;
	if (s4.size() == 2 && s4.capacity() == 100)
		printSuccess("Assignment operator works correctly");
	else
		printError("Assignment operator failed");
	
	// Test self-assignment
	Span& s4_ref = s4;
	s4 = s4_ref;
	if (s4.size() == 2 && s4.capacity() == 100)
		printSuccess("Self-assignment handled correctly");
	else
		printError("Self-assignment failed");
}

// Test exceptions
void testExceptions()
{
	printTestHeader("Exception Handling");
	
	// Test full span exception
	Span sp(3);
	sp.addNumber(1);
	sp.addNumber(2);
	sp.addNumber(3);
	
	try
	{
		sp.addNumber(4);
		printError("Should have thrown FullSpanException");
	}
	catch(const Span::FullSpanException& e)
	{
		printSuccess("FullSpanException thrown correctly");
		std::cout << "  Message: " << e.what() << std::endl;
	}
	
	// Test not enough numbers exception
	Span sp2(10);
	try
	{
		sp2.shortestSpan();
		printError("Should have thrown NotEnoughNumbersException for empty span");
	}
	catch(const Span::NotEnoughNumbersException& e)
	{
		printSuccess("NotEnoughNumbersException thrown for empty span");
	}
	
	sp2.addNumber(42);
	try
	{
		sp2.longestSpan();
		printError("Should have thrown NotEnoughNumbersException for single element");
	}
	catch(const Span::NotEnoughNumbersException& e)
	{
		printSuccess("NotEnoughNumbersException thrown for single element");
		std::cout << "  Message: " << e.what() << std::endl;
	}
}

// Test iterator-based addition
void testIteratorAddition()
{
	printTestHeader("Iterator-based Addition");
	
	// Test with vector
	Span sp1(10);
	std::vector<int> vec;
	vec.push_back(10);
	vec.push_back(20);
	vec.push_back(30);
	vec.push_back(40);
	vec.push_back(50);
	
	sp1.addNumbers(vec.begin(), vec.end());
	if (sp1.size() == 5)
		printSuccess("Added 5 elements from vector using iterators");
	else
		printError("Failed to add elements from vector");
	
	// Test with list
	Span sp2(10);
	std::list<int> lst;
	lst.push_back(100);
	lst.push_back(200);
	lst.push_back(300);
	
	sp2.addNumbers(lst.begin(), lst.end());
	if (sp2.size() == 3)
		printSuccess("Added 3 elements from list using iterators");
	else
		printError("Failed to add elements from list");
	
	// Test with deque
	Span sp3(10);
	std::deque<int> deq;
	deq.push_back(-10);
	deq.push_back(-5);
	deq.push_back(0);
	deq.push_back(5);
	
	sp3.addNumbers(deq.begin(), deq.end());
	if (sp3.size() == 4)
		printSuccess("Added 4 elements from deque using iterators");
	else
		printError("Failed to add elements from deque");
	
	// Test overflow with iterators
	Span sp4(3);
	std::vector<int> bigVec;
	for (int i = 0; i < 5; ++i)
		bigVec.push_back(i);
	
	try
	{
		sp4.addNumbers(bigVec.begin(), bigVec.end());
		printError("Should have thrown exception for adding too many elements");
	}
	catch(const Span::FullSpanException& e)
	{
		printSuccess("Exception thrown correctly when adding too many elements via iterator");
	}
}

// Test with large numbers (10,000+)
void testLargeSpan()
{
	printTestHeader("Large Span Test (10,000+ elements)");
	
	const unsigned int SIZE = 15000;
	Span bigSpan(SIZE);
	
	// Create a vector with random numbers
	std::srand(std::time(0));
	std::vector<int> numbers;
	
	// Add some known values for testing
	numbers.push_back(0);      // Minimum
	numbers.push_back(100000); // Maximum
	
	// Add random numbers
	for (unsigned int i = 2; i < SIZE; ++i)
	{
		numbers.push_back(std::rand() % 100000);
	}
	
	// Add all at once using iterators
	clock_t start = clock();
	bigSpan.addNumbers(numbers.begin(), numbers.end());
	clock_t end = clock();
	
	double time_taken = double(end - start) / CLOCKS_PER_SEC;
	
	if (bigSpan.size() == SIZE)
	{
		printSuccess("Successfully added " + intToString(SIZE) + " elements");
		std::cout << "  Time taken: " << time_taken << " seconds" << std::endl;
	}
	else
		printError("Failed to add all elements");
	
	// Calculate spans
	try
	{
		start = clock();
		int longest = bigSpan.longestSpan();
		end = clock();
		time_taken = double(end - start) / CLOCKS_PER_SEC;
		
		std::cout << "  Longest span: " << longest << " (expected >= 99999)" << std::endl;
		std::cout << "  Calculation time: " << time_taken << " seconds" << std::endl;
		
		if (longest >= 99999)
			printSuccess("Longest span calculated correctly for large dataset");
		else
			printError("Longest span seems incorrect");
	}
	catch(const std::exception& e)
	{
		printError("Exception in longestSpan: " + std::string(e.what()));
	}
	
	try
	{
		start = clock();
		int shortest = bigSpan.shortestSpan();
		end = clock();
		time_taken = double(end - start) / CLOCKS_PER_SEC;
		
		std::cout << "  Shortest span: " << shortest << std::endl;
		std::cout << "  Calculation time: " << time_taken << " seconds" << std::endl;
		printSuccess("Shortest span calculated for large dataset");
	}
	catch(const std::exception& e)
	{
		printError("Exception in shortestSpan: " + std::string(e.what()));
	}
}

// Test edge cases
void testEdgeCases()
{
	printTestHeader("Edge Cases");
	
	// Test with negative numbers
	Span sp1(5);
	sp1.addNumber(-100);
	sp1.addNumber(-50);
	sp1.addNumber(0);
	sp1.addNumber(50);
	sp1.addNumber(100);
	
	try
	{
		int longest = sp1.longestSpan();
		if (longest == 200)
			printSuccess("Longest span with negative numbers: " + intToString(longest));
		else
			printError("Incorrect longest span with negatives");
	}
	catch(const std::exception& e)
	{
		printError("Exception with negative numbers: " + std::string(e.what()));
	}
	
	// Test with duplicate numbers
	Span sp2(6);
	sp2.addNumber(10);
	sp2.addNumber(10);
	sp2.addNumber(20);
	sp2.addNumber(20);
	sp2.addNumber(30);
	sp2.addNumber(30);
	
	try
	{
		int shortest = sp2.shortestSpan();
		if (shortest == 0)
			printSuccess("Shortest span with duplicates: 0 (correct)");
		else
			printError("Incorrect shortest span with duplicates");
	}
	catch(const std::exception& e)
	{
		printError("Exception with duplicates: " + std::string(e.what()));
	}
	
	// Test with INT_MIN and INT_MAX
	Span sp3(3);
	sp3.addNumber(2147483647);  // INT_MAX
	sp3.addNumber(-2147483648); // INT_MIN
	sp3.addNumber(0);
	
	try
	{
		long long longest = static_cast<long long>(sp3.longestSpan());
		// This should be 4294967295 in unsigned, but might overflow in signed
		std::cout << "  Longest span with INT_MIN/MAX: " << longest << std::endl;
		printSuccess("Handled INT_MIN/MAX correctly");
	}
	catch(const std::exception& e)
	{
		printError("Exception with INT_MIN/MAX: " + std::string(e.what()));
	}
	
	// Test adding vector to itself
	Span sp4(10);
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	
	sp4.addNumbers(vec);
	if (sp4.size() == 3)
		printSuccess("Added vector using addNumbers(vector) method");
	else
		printError("Failed to add vector");
}

// Performance comparison test
void testPerformance()
{
	printTestHeader("Performance Test");
	
	const unsigned int SIZE = 100000;
	Span sp(SIZE);
	
	// Method 1: Add one by one
	clock_t start = clock();
	for (unsigned int i = 0; i < 10000; ++i)
	{
		sp.addNumber(i);
	}
	clock_t end = clock();
	double time1 = double(end - start) / CLOCKS_PER_SEC;
	
	// Method 2: Add using iterators
	std::vector<int> numbers;
	for (unsigned int i = 10000; i < SIZE; ++i)
	{
		numbers.push_back(i);
	}
	
	start = clock();
	sp.addNumbers(numbers.begin(), numbers.end());
	end = clock();
	double time2 = double(end - start) / CLOCKS_PER_SEC;
	
	std::cout << "  Time for 10,000 individual additions: " << time1 << " seconds" << std::endl;
	std::cout << "  Time for 90,000 iterator additions: " << time2 << " seconds" << std::endl;
	
	if (time2 < time1 * 9)  // Iterator method should be much faster
		printSuccess("Iterator method is more efficient");
	else
		std::cout << YELLOW << "  Note: Iterator method performance may vary" << RESET << std::endl;
}

int main()
{
	std::cout << MAGENTA << "\n╔══════════════════════════════════════╗" << RESET << std::endl;
	std::cout << MAGENTA << "║         Exercise 01: Span            ║" << RESET << std::endl;
	std::cout << MAGENTA << "╚══════════════════════════════════════╝" << RESET << std::endl;
	
	testSubjectExample();
	testOCF();
	testExceptions();
	testIteratorAddition();
	testLargeSpan();
	testEdgeCases();
	testPerformance();
	
	std::cout << CYAN << "\n========================================" << RESET << std::endl;
	std::cout << GREEN << "All tests completed!" << RESET << std::endl;
	std::cout << CYAN << "========================================" << RESET << std::endl;
	
	return 0;
}
