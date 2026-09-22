/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 11:30:48 by afournie          #+#    #+#             */
/*   Updated: 2026/09/22 11:30:53 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <cfloat>
#include <cmath>

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
	(void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
	(void)other;
	return *this;
}

ScalarConverter::~ScalarConverter() {}

namespace {

enum LiteralType { CHAR, INT, FLOAT, DOUBLE, INVALID };

bool isFloatPseudo(const std::string& s) {
	return s == "nanf" || s == "+inff" || s == "-inff";
}

bool isDoublePseudo(const std::string& s) {
	return s == "nan" || s == "+inf" || s == "-inf";
}

static std::string formatFloating(double value) {
	std::ostringstream oss;
	oss << value;
	std::string str = oss.str();
	// Si pas de point, pas de notation scientifique, ni de notation spéciale,
	// on force un format décimal (ex: "42" -> "42.0")
	if (str.find('.') == std::string::npos &&
		str.find('e') == std::string::npos &&
		str.find("nan") == std::string::npos &&
		str.find("inf") == std::string::npos) {
		str += ".0";
	}
	return str;
}

/*
** Analyse la chaîne pour déterminer sa "nature" avant toute conversion.
** On ne fait aucun calcul ici : on regarde juste la forme du texte.
*/
LiteralType getType(const std::string& s) {
	if (s.empty())
		return INVALID;

	if (isDoublePseudo(s))
		return DOUBLE;
	if (isFloatPseudo(s))
		return FLOAT;

	// un char : exactement 1 caractère et ce n'est pas un chiffre isolé
	if (s.length() == 1 && !std::isdigit(static_cast<unsigned char>(s[0])))
		return CHAR;

	size_t i = 0;
	bool hasDigit = false;
	bool hasDot = false;
	bool hasF = false;

	if (s[i] == '+' || s[i] == '-')
		i++;

	for (; i < s.length(); i++) {
		if (std::isdigit(static_cast<unsigned char>(s[i])))
			hasDigit = true;
		else if (s[i] == '.' && !hasDot)
			hasDot = true;
		else if (s[i] == 'f' && i == s.length() - 1 && hasDigit)
			hasF = true;
		else
			return INVALID;
	}

	if (!hasDigit)
		return INVALID;
	if (hasF)
		return FLOAT;
	if (hasDot)
		return DOUBLE;
	return INT;
}

} // namespace anonyme

void ScalarConverter::convert(const std::string& literal) {
	LiteralType type = getType(literal);

	if (type == INVALID) {
		std::cout << "Literal is not valid" << std::endl;
		return;
	}

	double value = 0.0;
	bool isNan = false;
	bool isInf = false;
	bool infNegative = false;

	if (type == CHAR) {
		value = static_cast<double>(static_cast<unsigned char>(literal[0]));
	} else if (type == INT) {
		// on passe par un long pour pouvoir détecter le dépassement d'int
		std::stringstream ss(literal);
		long tmp;
		ss >> tmp;

		if (ss.fail() || !ss.eof()) {
			// La valeur dépasse la capacité d'un long, ou il reste
			// des caractères non consommés après le nombre :
			// on ne peut connaître la vraie valeur numérique,
			// donc aucune des 4 conversions n'est possible.
			std::cout << "char: impossible" << std::endl;
			std::cout << "int: impossible" << std::endl;
			std::cout << "float: impossible" << std::endl;
			std::cout << "double: impossible" << std::endl;
			return;
		}
		value = static_cast<double>(tmp);
	} else { // FLOAT ou DOUBLE
		if (literal.find("nan") != std::string::npos) {
			isNan = true;
		} else if (literal.find("inf") != std::string::npos) {
			isInf = true;
			infNegative = (literal[0] == '-');
		} else {
			value = std::strtod(literal.c_str(), NULL);
		}
	}

	// ---------------- char ----------------
	std::cout << "char: ";
	if (isNan || isInf || value < 0 || value > 127) {
		std::cout << "impossible";
	} else if (!std::isprint(static_cast<int>(value))) {
		std::cout << "Non displayable";
	} else {
		std::cout << "'" << static_cast<char>(value) << "'";
	}
	std::cout << std::endl;

	// ---------------- int ----------------
	std::cout << "int: ";
	if (isNan || isInf || value < INT_MIN || value > INT_MAX) {
		std::cout << "impossible";
	} else {
		std::cout << static_cast<int>(value);
	}
	std::cout << std::endl;

	// ---------------- float ----------------
	std::cout << "float: ";
	if (isNan) {
		std::cout << "nanf";
	} else if (isInf) {
		std::cout << (infNegative ? "-inff" : "+inff");
	} else {
		std::cout << formatFloating(static_cast<float>(value)) << "f";
	}
	std::cout << std::endl;

	// ---------------- double ----------------
	std::cout << "double: ";
	if (isNan) {
		std::cout << "nan";
	} else if (isInf) {
		std::cout << (infNegative ? "-inf" : "+inf");
	} else {
		std::cout << formatFloating(value);
	}
	std::cout << std::endl;
}
