/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 15:36:32 by afournie          #+#    #+#             */
/*   Updated: 2026/10/13 14:31:33 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <cfloat>
#include <cmath>

class	ScalarConverter
{
	private:
		ScalarConverter();
		ScalarConverter(ScalarConverter const &ref);
		ScalarConverter &operator=(ScalarConverter const &ref);
		~ScalarConverter();

	public:
		static void convert(const std::string& s);
};

#endif
