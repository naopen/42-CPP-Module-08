/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: na-kannan <na-kannan@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 00:00:00 by na-kannan          #+#    #+#             */
/*   Updated: 2025/01/01 00:00:00 by na-kannan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <deque>

// MutantStack inherits from std::stack and adds iterator functionality
// std::stack uses std::deque as default container, which already supports iterators
template <typename T, typename Container = std::deque<T> >
class MutantStack : public std::stack<T, Container>
{
public:
	// Orthodox Canonical Form - REQUIRED by subject
	MutantStack() : std::stack<T, Container>() {}
	
	MutantStack(const MutantStack& src) : std::stack<T, Container>(src) {}
	
	MutantStack& operator=(const MutantStack& rhs)
	{
		if (this != &rhs)
			std::stack<T, Container>::operator=(rhs);
		return *this;
	}
	
	~MutantStack() {}
	
	// Iterator types - use the underlying container's iterators
	typedef typename Container::iterator				iterator;
	typedef typename Container::const_iterator			const_iterator;
	typedef typename Container::reverse_iterator		reverse_iterator;
	typedef typename Container::const_reverse_iterator	const_reverse_iterator;
	
	// Iterator access functions
	// Access the underlying container using the protected member 'c'
	iterator begin()
	{
		return this->c.begin();
	}
	
	iterator end()
	{
		return this->c.end();
	}
	
	const_iterator begin() const
	{
		return this->c.begin();
	}
	
	const_iterator end() const
	{
		return this->c.end();
	}
	
	reverse_iterator rbegin()
	{
		return this->c.rbegin();
	}
	
	reverse_iterator rend()
	{
		return this->c.rend();
	}
	
	const_reverse_iterator rbegin() const
	{
		return this->c.rbegin();
	}
	
	const_reverse_iterator rend() const
	{
		return this->c.rend();
	}
};

#endif
