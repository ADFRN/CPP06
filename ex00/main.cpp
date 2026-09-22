/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afournie <afournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 10:42:38 by afournie          #+#    #+#             */
/*   Updated: 2026/09/22 10:43:02 by afournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>

// Petit helper pour afficher un séparateur lisible entre chaque test
static void printHeader(const std::string& literal) {
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Input: \"" << literal << "\"" << std::endl;
    std::cout << "---------------------------------" << std::endl;
}

static void testLiteral(const std::string& literal) {
    printHeader(literal);
    ScalarConverter::convert(literal);
    std::cout << std::endl;
}

int main(int argc, char** argv) {
    // Mode "sujet" : si un argument est donné en ligne de commande,
    // on ne teste que celui-là (comportement attendu par le sujet).
    if (argc == 2) {
        testLiteral(argv[1]);
        return 0;
    }

    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " <literal>" << std::endl;
        return 1;
    }

    // Mode "batch" : sans argument, on lance une batterie de tests
    // couvrant les cas normaux ET les cas limites du sujet.

    // --- char valides ---
    testLiteral("a");
    testLiteral("z");
    testLiteral(" ");        // char affichable (espace)

    // --- char non affichable ---
    // \x01 = caractère de contrôle non imprimable
    testLiteral("\x01");

    // --- int classiques ---
    testLiteral("0");
    testLiteral("42");
    testLiteral("-42");
    testLiteral("+42");

    // --- int overflow (dépasse INT_MAX/INT_MIN) ---
    testLiteral("2147483648");   // INT_MAX + 1
    testLiteral("-2147483649");  // INT_MIN - 1
    testLiteral("999999999999"); // très grand nombre

    // --- float classiques ---
    testLiteral("42.0f");
    testLiteral("-4.2f");
    testLiteral("42.42f");
    testLiteral("0.0f");

    // --- double classiques ---
    testLiteral("42.0");
    testLiteral("-4.2");
    testLiteral("42.42");
    testLiteral("0.0");

    // --- valeurs spéciales ---
    testLiteral("nan");
    testLiteral("nanf");
    testLiteral("+inf");
    testLiteral("-inf");
    testLiteral("+inff");
    testLiteral("-inff");

    // --- entrées invalides ---
    testLiteral("");
    testLiteral("abc");
    testLiteral("42abc");
    testLiteral("4.2.3");
    testLiteral("f");
    testLiteral("42f");        // pas de point => pas un float valide dans ta logique actuelle
    testLiteral(".");
    testLiteral("-");
    testLiteral("+");

    // --- char qui ressemble à un chiffre isolé (doit être traité comme int, pas char) ---
    testLiteral("5");

    return 0;
}
