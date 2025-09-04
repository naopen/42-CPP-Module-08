/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <numeric>

// ============================================================================
// Orthodox Canonical Form Implementation
// ============================================================================

// Default constructor
Span::Span() : _maxSize(0)
{
}

// Parametric constructor
Span::Span(unsigned int N) : _maxSize(N)
{
	// Reserve space for efficiency
	_numbers.reserve(N);
}

// Copy constructor
Span::Span(const Span& src) : _maxSize(src._maxSize), _numbers(src._numbers)
{
}

// Assignment operator
Span& Span::operator=(const Span& rhs)
{
	if (this != &rhs)
	{
		_maxSize = rhs._maxSize;
		_numbers = rhs._numbers;
	}
	return *this;
}

// Destructor
Span::~Span()
{
	// Nothing special to do, std::vector handles its own cleanup
}

// ============================================================================
// Member Functions
// ============================================================================

// Add a single number
void Span::addNumber(int number)
{
	if (_numbers.size() >= _maxSize)
		throw FullSpanException();
	
	_numbers.push_back(number);
}

// Calculate shortest span using STL algorithms
int Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw NotEnoughNumbersException();
	
	// Create a copy and sort it using STL algorithm
	std::vector<int> sorted = _numbers;
	std::sort(sorted.begin(), sorted.end());
	
	// Calculate differences between adjacent elements
	std::vector<int> differences(sorted.size() - 1);
	std::adjacent_difference(sorted.begin() + 1, sorted.end(), differences.begin());
	
	// Find the minimum difference using STL algorithm
	return *std::min_element(differences.begin(), differences.end());
}

// Calculate longest span using STL algorithms
int Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw NotEnoughNumbersException();
	
	// Use STL algorithms to find min and max
	std::vector<int>::const_iterator min_it = std::min_element(_numbers.begin(), _numbers.end());
	std::vector<int>::const_iterator max_it = std::max_element(_numbers.begin(), _numbers.end());
	
	return *max_it - *min_it;
}

// Add multiple numbers from a vector
void Span::addNumbers(const std::vector<int>& numbers)
{
	// Check if we have enough space
	if (_numbers.size() + numbers.size() > _maxSize)
		throw FullSpanException();
	
	// Add all elements using STL algorithm
	_numbers.insert(_numbers.end(), numbers.begin(), numbers.end());
}

// Utility functions
unsigned int Span::size() const
{
	return _numbers.size();
}

unsigned int Span::capacity() const
{
	return _maxSize;
}
