/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 15:18:37 by afournie          #+#    #+#             */
/*   Updated: 2026/09/28 15:20:34 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions.hpp"

int main() {

	std::srand(std::time(NULL));

	for (int i = 0; i < 5; ++i) {
		Base *p = generate();
		identify(p);
		identify(*p);
		delete p;
	}
}
