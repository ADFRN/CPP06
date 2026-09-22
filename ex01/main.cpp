/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 15:12:31 by afournie          #+#    #+#             */
/*   Updated: 2026/09/22 15:15:02 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Serializer.hpp"

int main() {
	Data original;
	original.id = 1;

	uintptr_t raw = Serializer::serialize(&original);
	Data* result = Serializer::deserialize(raw);

	if (result == &original)
		std::cout << "OK : pointeur identique" << std::endl;
	else
		std::cout << "KO : pointeurs different" << std::endl;

	return 0;
}
