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

#include "MutantStack.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

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

// Test from subject
void testSubjectExample()
{
	printTestHeader("Subject Example - MutantStack");
	
	MutantStack<int> mstack;
	
	mstack.push(5);
	mstack.push(17);
	
	std::cout << "Top element: " << mstack.top() << std::endl;
	if (mstack.top() == 17)
		printSuccess("Top element is correct (17)");
	
	mstack.pop();
	
	std::cout << "Size after pop: " << mstack.size() << std::endl;
	if (mstack.size() == 1)
		printSuccess("Size after pop is correct (1)");
	
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);
	
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	
	// Test increment and decrement
	++it;
	--it;
	
	std::cout << "\nIterating through MutantStack:" << std::endl;
	while (it != ite)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
	
	// Copy to std::stack
	std::stack<int> s(mstack);
	if (s.size() == mstack.size())
		printSuccess("Copy to std::stack successful");
	else
		printError("Copy to std::stack failed");
}

// Same test but with std::list for comparison
void testWithList()
{
	printTestHeader("Comparison with std::list");
	
	std::list<int> lst;
	
	lst.push_back(5);
	lst.push_back(17);
	
	std::cout << "Back element: " << lst.back() << std::endl;
	if (lst.back() == 17)
		printSuccess("Back element is correct (17)");
	
	lst.pop_back();
	
	std::cout << "Size after pop_back: " << lst.size() << std::endl;
	if (lst.size() == 1)
		printSuccess("Size after pop_back is correct (1)");
	
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);
	
	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator ite = lst.end();
	
	++it;
	--it;
	
	std::cout << "\nIterating through std::list:" << std::endl;
	while (it != ite)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;
	
	printSuccess("std::list behaves similarly to MutantStack");
}

// Test Orthodox Canonical Form
void testOCF()
{
	printTestHeader("Orthodox Canonical Form");
	
	// Default constructor
	MutantStack<int> s1;
	s1.push(42);
	printSuccess("Default constructor works");
	
	// Copy constructor
	MutantStack<int> s2(s1);
	if (s2.top() == 42 && s2.size() == 1)
		printSuccess("Copy constructor works correctly");
	else
		printError("Copy constructor failed");
	
	// Assignment operator
	MutantStack<int> s3;
	s3.push(100);
	s3 = s1;
	if (s3.top() == 42 && s3.size() == 1)
		printSuccess("Assignment operator works correctly");
	else
		printError("Assignment operator failed");
	
	// Self-assignment
	MutantStack<int>& s3_ref = s3;
	s3 = s3_ref;
	if (s3.top() == 42)
		printSuccess("Self-assignment handled correctly");
	else
		printError("Self-assignment failed");
}

// Test all iterator types
void testIterators()
{
	printTestHeader("Iterator Types");
	
	MutantStack<int> mstack;
	for (int i = 1; i <= 5; ++i)
		mstack.push(i * 10);
	// Stack contains: 10, 20, 30, 40, 50 (50 on top)
	
	// Forward iterator
	std::cout << "Forward iteration: ";
	for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	printSuccess("Forward iteration works");
	
	// Const iterator
	const MutantStack<int> const_stack(mstack);
	std::cout << "Const iteration: ";
	for (MutantStack<int>::const_iterator it = const_stack.begin(); 
		it != const_stack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	printSuccess("Const iteration works");
	
	// Reverse iterator
	std::cout << "Reverse iteration: ";
	for (MutantStack<int>::reverse_iterator it = mstack.rbegin(); 
		it != mstack.rend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	printSuccess("Reverse iteration works");
	
	// Const reverse iterator
	std::cout << "Const reverse iteration: ";
	for (MutantStack<int>::const_reverse_iterator it = const_stack.rbegin(); 
		it != const_stack.rend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	printSuccess("Const reverse iteration works");
}

// Test with STL algorithms
void testWithSTLAlgorithms()
{
	printTestHeader("STL Algorithms Compatibility");
	
	MutantStack<int> mstack;
	mstack.push(3);
	mstack.push(1);
	mstack.push(4);
	mstack.push(1);
	mstack.push(5);
	mstack.push(9);
	mstack.push(2);
	mstack.push(6);
	
	// Find algorithm
	MutantStack<int>::iterator found = std::find(mstack.begin(), mstack.end(), 5);
	if (found != mstack.end() && *found == 5)
		printSuccess("std::find works with MutantStack");
	else
		printError("std::find failed");
	
	// Count algorithm
	int count = std::count(mstack.begin(), mstack.end(), 1);
	if (count == 2)
		printSuccess("std::count works correctly (found 2 ones)");
	else
		printError("std::count failed");
	
	// For_each algorithm
	std::cout << "Using iteration to print: ";
	for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	printSuccess("Iterator-based printing works");
	
	// Min/Max elements
	MutantStack<int>::iterator min_it = std::min_element(mstack.begin(), mstack.end());
	MutantStack<int>::iterator max_it = std::max_element(mstack.begin(), mstack.end());
	std::cout << "Min element: " << *min_it << ", Max element: " << *max_it << std::endl;
	if (*min_it == 1 && *max_it == 9)
		printSuccess("std::min_element and std::max_element work");
	else
		printError("Min/max element algorithms failed");
}

// Test with different types
void testDifferentTypes()
{
	printTestHeader("Different Data Types");
	
	// String stack
	MutantStack<std::string> string_stack;
	string_stack.push("Hello");
	string_stack.push("World");
	string_stack.push("from");
	string_stack.push("MutantStack");
	
	std::cout << "String stack: ";
	for (MutantStack<std::string>::iterator it = string_stack.begin(); 
		it != string_stack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	printSuccess("MutantStack<std::string> works");
	
	// Double stack
	MutantStack<double> double_stack;
	double_stack.push(3.14);
	double_stack.push(2.71);
	double_stack.push(1.41);
	
	std::cout << "Double stack: ";
	for (MutantStack<double>::iterator it = double_stack.begin(); 
		it != double_stack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	printSuccess("MutantStack<double> works");
	
	// Char stack
	MutantStack<char> char_stack;
	char_stack.push('A');
	char_stack.push('B');
	char_stack.push('C');
	
	std::cout << "Char stack: ";
	for (MutantStack<char>::iterator it = char_stack.begin(); 
		it != char_stack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	printSuccess("MutantStack<char> works");
}

// Test with different underlying containers
void testDifferentContainers()
{
	printTestHeader("Different Underlying Containers");
	
	// MutantStack with vector as underlying container
	MutantStack<int, std::vector<int> > vec_stack;
	vec_stack.push(10);
	vec_stack.push(20);
	vec_stack.push(30);
	
	std::cout << "MutantStack with std::vector: ";
	for (MutantStack<int, std::vector<int> >::iterator it = vec_stack.begin(); 
		it != vec_stack.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	if (vec_stack.top() == 30)
		printSuccess("MutantStack with std::vector works");
	else
		printError("MutantStack with std::vector failed");
	
	// Default is deque
	MutantStack<int> deque_stack;
	deque_stack.push(100);
	deque_stack.push(200);
	
	if (deque_stack.top() == 200)
		printSuccess("Default container (std::deque) works");
	else
		printError("Default container failed");
}

// Edge cases
void testEdgeCases()
{
	printTestHeader("Edge Cases");
	
	// Empty stack iteration
	MutantStack<int> empty;
	if (empty.begin() == empty.end())
		printSuccess("Empty stack: begin() == end()");
	else
		printError("Empty stack iterator failed");
	
	// Single element
	MutantStack<int> single;
	single.push(42);
	int count = 0;
	for (MutantStack<int>::iterator it = single.begin(); it != single.end(); ++it)
		count++;
	if (count == 1)
		printSuccess("Single element iteration works");
	else
		printError("Single element iteration failed");
	
	// Large stack
	MutantStack<int> large;
	for (int i = 0; i < 10000; ++i)
		large.push(i);
	
	count = 0;
	for (MutantStack<int>::iterator it = large.begin(); it != large.end(); ++it)
		count++;
	
	if (count == 10000)
		printSuccess("Large stack (10000 elements) iteration works");
	else
		printError("Large stack iteration failed");
	
	// Modify through iterator
	MutantStack<int> modifiable;
	modifiable.push(1);
	modifiable.push(2);
	modifiable.push(3);
	
	for (MutantStack<int>::iterator it = modifiable.begin(); it != modifiable.end(); ++it)
		*it *= 2;
	
	std::cout << "After modification: ";
	for (MutantStack<int>::iterator it = modifiable.begin(); it != modifiable.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	
	if (modifiable.top() == 6)
		printSuccess("Modification through iterator works");
	else
		printError("Modification through iterator failed");
}

int main()
{
	std::cout << MAGENTA << "\n╔══════════════════════════════════════╗" << RESET << std::endl;
	std::cout << MAGENTA << "║    Exercise 02: Mutated abomination   ║" << RESET << std::endl;
	std::cout << MAGENTA << "╚══════════════════════════════════════╝" << RESET << std::endl;
	
	testSubjectExample();
	testWithList();
	testOCF();
	testIterators();
	testWithSTLAlgorithms();
	testDifferentTypes();
	testDifferentContainers();
	testEdgeCases();
	
	std::cout << CYAN << "\n========================================" << RESET << std::endl;
	std::cout << GREEN << "All tests completed!" << RESET << std::endl;
	std::cout << CYAN << "========================================" << RESET << std::endl;
	
	return 0;
}
