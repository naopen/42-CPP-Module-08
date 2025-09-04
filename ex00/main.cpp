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

#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

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

// Test with std::vector
void testVector()
{
	printTestHeader("std::vector");
	
	std::vector<int> vec;
	vec.push_back(1);
	vec.push_back(5);
	vec.push_back(3);
	vec.push_back(8);
	vec.push_back(3);  // Duplicate
	vec.push_back(10);
	
	// Test 1: Find existing element
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 5);
		printSuccess("Found element 5 at position " + 
			std::string(it != vec.end() ? "valid" : "invalid"));
		std::cout << "  Value at iterator: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed to find element 5: " + std::string(e.what()));
	}
	
	// Test 2: Find first occurrence of duplicate
	try
	{
		std::vector<int>::iterator it = easyfind(vec, 3);
		int position = std::distance(vec.begin(), it);
		printSuccess("Found first occurrence of 3 at position " + 
			std::string(position == 2 ? "2 (correct)" : "wrong"));
		std::cout << "  Position: " << position << ", Value: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed to find element 3: " + std::string(e.what()));
	}
	
	// Test 3: Element not found
	try
	{
		easyfind(vec, 42);
		printError("Should have thrown exception for non-existent element");
	}
	catch(const NotFoundException& e)
	{
		printSuccess("Exception thrown correctly for non-existent element");
		std::cout << "  Exception message: " << e.what() << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Wrong exception type: " + std::string(e.what()));
	}
	
	// Test 4: Empty vector
	std::vector<int> empty_vec;
	try
	{
		easyfind(empty_vec, 1);
		printError("Should have thrown exception for empty vector");
	}
	catch(const NotFoundException& e)
	{
		printSuccess("Exception thrown correctly for empty vector");
	}
	
	// Test 5: Const vector
	const std::vector<int> const_vec(vec);
	try
	{
		std::vector<int>::const_iterator it = easyfind(const_vec, 8);
		printSuccess("Found element 8 in const vector");
		std::cout << "  Value: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed with const vector: " + std::string(e.what()));
	}
}

// Test with std::list
void testList()
{
	printTestHeader("std::list");
	
	std::list<int> lst;
	lst.push_back(15);
	lst.push_back(23);
	lst.push_back(42);
	lst.push_back(4);
	lst.push_back(16);
	lst.push_back(42);  // Duplicate
	
	// Test 1: Find existing element
	try
	{
		std::list<int>::iterator it = easyfind(lst, 42);
		printSuccess("Found element 42 in list");
		std::cout << "  Value at iterator: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed to find element 42: " + std::string(e.what()));
	}
	
	// Test 2: Find first element
	try
	{
		std::list<int>::iterator it = easyfind(lst, 15);
		printSuccess("Found first element 15");
		std::cout << "  Value: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed to find first element: " + std::string(e.what()));
	}
	
	// Test 3: Find last unique element
	try
	{
		std::list<int>::iterator it = easyfind(lst, 16);
		printSuccess("Found element 16");
		std::cout << "  Value: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed to find element 16: " + std::string(e.what()));
	}
	
	// Test 4: Element not found
	try
	{
		easyfind(lst, 999);
		printError("Should have thrown exception for element 999");
	}
	catch(const NotFoundException& e)
	{
		printSuccess("Exception thrown correctly for non-existent element");
	}
}

// Test with std::deque
void testDeque()
{
	printTestHeader("std::deque");
	
	std::deque<int> deq;
	deq.push_back(100);
	deq.push_front(200);
	deq.push_back(300);
	deq.push_front(400);
	// Order: 400, 200, 100, 300
	
	// Test 1: Find element added with push_front
	try
	{
		std::deque<int>::iterator it = easyfind(deq, 400);
		printSuccess("Found element 400 (push_front)");
		std::cout << "  Value: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed to find element 400: " + std::string(e.what()));
	}
	
	// Test 2: Find element added with push_back
	try
	{
		std::deque<int>::iterator it = easyfind(deq, 300);
		printSuccess("Found element 300 (push_back)");
		std::cout << "  Value: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed to find element 300: " + std::string(e.what()));
	}
	
	// Test 3: Large deque test
	std::deque<int> large_deq;
	for (int i = 0; i < 10000; ++i)
		large_deq.push_back(i);
	
	try
	{
		std::deque<int>::iterator it = easyfind(large_deq, 9999);
		printSuccess("Found element 9999 in large deque (10000 elements)");
		std::cout << "  Found at valid position: " << (it != large_deq.end()) << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed with large deque: " + std::string(e.what()));
	}
}

// Edge cases
void testEdgeCases()
{
	printTestHeader("Edge Cases");
	
	// Test 1: Single element
	std::vector<int> single;
	single.push_back(42);
	
	try
	{
		std::vector<int>::iterator it = easyfind(single, 42);
		printSuccess("Found single element");
		std::cout << "  Value: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed with single element: " + std::string(e.what()));
	}
	
	// Test 2: Negative numbers
	std::list<int> negative;
	negative.push_back(-10);
	negative.push_back(-5);
	negative.push_back(0);
	negative.push_back(5);
	
	try
	{
		std::list<int>::iterator it = easyfind(negative, -5);
		printSuccess("Found negative number -5");
		std::cout << "  Value: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed with negative numbers: " + std::string(e.what()));
	}
	
	// Test 3: Zero
	try
	{
		std::list<int>::iterator it = easyfind(negative, 0);
		printSuccess("Found zero");
		std::cout << "  Value: " << *it << std::endl;
	}
	catch(const std::exception& e)
	{
		printError("Failed to find zero: " + std::string(e.what()));
	}
	
	// Test 4: INT_MIN and INT_MAX
	std::vector<int> extremes;
	extremes.push_back(2147483647);  // INT_MAX
	extremes.push_back(-2147483648); // INT_MIN
	extremes.push_back(0);
	
	try
	{
		easyfind(extremes, 2147483647);
		printSuccess("Found INT_MAX");
	}
	catch(const std::exception& e)
	{
		printError("Failed with INT_MAX: " + std::string(e.what()));
	}
	
	try
	{
		easyfind(extremes, -2147483648);
		printSuccess("Found INT_MIN");
	}
	catch(const std::exception& e)
	{
		printError("Failed with INT_MIN: " + std::string(e.what()));
	}
}

int main()
{
	std::cout << MAGENTA << "\n╔══════════════════════════════════════╗" << RESET << std::endl;
	std::cout << MAGENTA << "║       Exercise 00: Easy find         ║" << RESET << std::endl;
	std::cout << MAGENTA << "╚══════════════════════════════════════╝" << RESET << std::endl;
	
	testVector();
	testList();
	testDeque();
	testEdgeCases();
	
	std::cout << CYAN << "\n========================================" << RESET << std::endl;
	std::cout << GREEN << "All tests completed!" << RESET << std::endl;
	std::cout << CYAN << "========================================" << RESET << std::endl;
	
	return 0;
}
