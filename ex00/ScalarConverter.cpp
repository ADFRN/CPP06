/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 11:30:48 by afournie          #+#    #+#             */
/*   Updated: 2026/10/13 14:56:20 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}
ScalarConverter::ScalarConverter(const ScalarConverter &other) { (void)other; }
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
	(void)other;
	return (*this);
}
ScalarConverter::~ScalarConverter() {}

static std::string formatFloating(double value)
{
	if (std::isnan(value))
		return ("nan");
	if (std::isinf(value))
		return (value > 0 ? "+inf" : "-inf");

	std::ostringstream oss;
	// vire le e+ sur les grnd nmbres
	if (std::fabs(value) >= 1e6 && std::fabs(value) < 1e15)
		oss << std::fixed << std::setprecision(1);
	oss << value;
	std::string s = oss.str();
	// Pour le .0 si pas de point
	if (s.find('.') == std::string::npos && s.find('e') == std::string::npos)
		s += ".0";
	return (s);
}

static void printChar(double d)
{
	std::cout << "char: ";
	if (std::isnan(d) || std::isinf(d) || d < 0 || d > 127)
		std::cout << "impossible" << std::endl;
	else if (!std::isprint(static_cast<int>(d)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << static_cast<char>(d) << "'" << std::endl;
}

static void printInt(double d)
{
	std::cout << "int: ";
	if (std::isnan(d) || std::isinf(d) || d < static_cast<double>(INT_MIN)
		|| d > static_cast<double>(INT_MAX))
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(d) << std::endl;
}

static void printFloat(double d)
{
	std::cout << "float: " << formatFloating(static_cast<float>(d)) << "f" << std::endl;
}

static void printDouble(double d)
{
	std::cout << "double: " << formatFloating(d) << std::endl;
}

void ScalarConverter::convert(const std::string &literal)
{
	std::string s = literal;
	double d = 0;

	if (s.empty())
	{
		std::cout << "Erreur : chaine vide" << std::endl;
		return ;
	}

	if (s.length() == 1 && !std::isdigit(static_cast<unsigned char>(s[0])))
	{
		d = static_cast<double>(static_cast<unsigned char>(s[0]));
	}
	else
	{
		if (s[s.length() - 1] == 'f' && s != "+inf" && s != "-inf")
			s.erase(s.length() - 1);

		char *end;
		d = std::strtod(s.c_str(), &end);

		if (s.empty() || *end != '\0')
		{
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return ;
		}
	}

	printChar(d);
	printInt(d);
	printFloat(d);
	printDouble(d);
}
