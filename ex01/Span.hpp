/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <exception>
#include <limits>
#include <iterator>

class Span
{
private:
	unsigned int		_maxSize;
	std::vector<int>	_numbers;

public:
	// Orthodox Canonical Form - REQUIRED by subject
	Span();										// Default constructor
	Span(unsigned int N);						// Parametric constructor
	Span(const Span& src);						// Copy constructor
	Span& operator=(const Span& rhs);			// Assignment operator
	~Span();									// Destructor
	
	// Required member functions
	void	addNumber(int number);
	int		shortestSpan() const;
	int		longestSpan() const;
	
	// Improved addNumber using iterators (required by subject)
	template <typename Iterator>
	void	addNumbers(Iterator begin, Iterator end)
	{
		// Calculate how many elements we're trying to add
		unsigned int count = std::distance(begin, end);
		
		// Check if we have enough space
		if (_numbers.size() + count > _maxSize)
			throw FullSpanException();
		
		// Add all elements using STL algorithm
		_numbers.insert(_numbers.end(), begin, end);
	}
	
	// Alternative: add multiple numbers with a single call
	void	addNumbers(const std::vector<int>& numbers);
	
	// Utility functions for testing
	unsigned int	size() const;
	unsigned int	capacity() const;
	
	// Exception classes
	class FullSpanException : public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return "Span is full, cannot add more numbers";
		}
	};
	
	class NotEnoughNumbersException : public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return "Not enough numbers to calculate span (need at least 2)";
		}
	};
};

#endif
