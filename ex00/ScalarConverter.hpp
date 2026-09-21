#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>

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
