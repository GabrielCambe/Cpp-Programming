#include <iostream>
#include "../../inc/pizza.hpp"

using std::vector<Pizza> = vecf;

std::vector<Pizza>pizzas={
    {0.5*0.25,7.49,"Dominos","s"},
    {0.5*0.28,8.99,"Dominos","m"},
    {0.5*0.32,10.99,"Dominos","l"},
    {0.5*0.20,4.00,"BistroAnanas","s"},
    {0.5*0.25,5.90,"BistroAnanas","m"},
    {0.5*0.30,7.50,"BistroAnanas","l"},
    {0.5*0.26,6.30,"PizzeriaKing","m"},
    {0.5*0.30,7.80,"PizzeriaKing","l"},
    {0.5*0.26,5.50,"PizzeriaNapoli","s"},
    {0.5*0.32,7.50,"PizzeriaNapoli","l"},
    {0.5*0.32,7.40,"GoldenerHecht","m"},
    {0.5*0.48,15.50,"GoldenerHecht","l"},
    {0.5*0.26,5.00,"SanRemo","s"},
    {0.5*0.32,6.50,"SanRemo","m"},
    {0.5*0.20,3.80,"Mardino","s"},
    {0.5*0.26,5.70,"Mardino","m"},
    {0.5*0.30,7.30,"Mardino","l"}
};

int main() {
    // Itero sobre o vetor de pizzas
        // Para cada elemento:
            // cheque o nome da pizzaria
            // execute uma busca no vetor de pizzarias
            // se nao achar a pizzaria:
                // adicione uma nova pizzaria
            // se achar a pizzaria
                // adicione a nova pizza no vetor de pizzas da pizzaria 

    // Itero sobre o vetor de restaurantes
        // Para cada pizza do restaurante
            // calculo a area da pizza
            // calculo o preço por area da pizza
            // adiciono o valor do preço por area, o tamanho da pizza e o nome do restaurante num vetor de pizzas "global"

    // Ordeno o vetor pelo preço por area
    // IMprimo os tres primeiros elementos dos vetores

    // Leia input do usuario
    // Faca uma busca sobre o vetor de pizzas global
    // Faça uma busca sobre o vetor de pizzarias
        // imprima o nome do restaurante

    
}