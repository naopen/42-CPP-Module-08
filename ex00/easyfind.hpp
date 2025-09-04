/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <exception>
#include <iterator>

class NotFoundException : public std::exception
{
public:
	virtual const char* what() const throw()
	{
		return "Element not found in container";
	}
};

// Template function declaration
// T must be a container of integers
// Uses STL algorithm std::find as required by the subject
template <typename T>
typename T::iterator easyfind(T& container, int value)
{
	typename T::iterator it = std::find(container.begin(), container.end(), value);
	
	if (it == container.end())
		throw NotFoundException();
	
	return it;
}

// Const version for const containers
template <typename T>
typename T::const_iterator easyfind(const T& container, int value)
{
	typename T::const_iterator it = std::find(container.begin(), container.end(), value);
	
	if (it == container.end())
		throw NotFoundException();
	
	return it;
}

#endif
