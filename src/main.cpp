#include "global.h"
#include "utils.h"
#include "poker_algorithms_new.h"
#include "poker_algorithms_old.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace std;
namespace py = pybind11;
using namespace pybind11::literals;

void nice_print_frequencies(vector<map<string,int>> frecs){
    // Print win/draw probabilities
    for (int i = 0; i < frecs.size(); i++){
        float win_chance = ((float) frecs[i]["Win"]/(float) frecs[i]["Total Cases"])*100;
        float draw_chance = ((float) frecs[i]["Draw"]/(float) frecs[i]["Total Cases"])*100;
        py::print("Player: ",i,", Win: ",round_float(win_chance,2),"%, Draw: ",round_float(draw_chance,2),"%","sep"_a="");
    }
    py::print("\nHAND POSSIBILITIES\n");
    // Print Table Headers 
    py::print("\t\t","end"_a="");
    for (int i = 0; i < frecs.size(); i++){
        py::print("Player",i,"\t","end"_a="","sep"_a="");
    }
    py::print("");
    // Print Each hand posibilities
    for (int i = 0; i < 10; i++){
        py::print(hand_names[i],"end"_a="");
        if (hand_names[i].size() > 7){
            py::print("\t","end"_a="");
        }else{
            py::print("\t\t","end"_a="");
        }
        for (int j = 0; j < frecs.size(); j++){
            float hand_pos = ((float) frecs[j][hand_names[i]]/(float) frecs[j]["Total Cases"])*100;;
            py::print(round_float(hand_pos,2),"%\t","end"_a="","sep"_a="");
        }
        py::print("");
    }
}

PYBIND11_MODULE(PokerPy, m) {
    m.doc() = "pybind11 plugin for calculating poker probabilities."; // optional module docstring
    py::class_<Card>(m, "Card")
        .def(py::init<short, short>())
        .def(py::init<string>())
        .def_property("value", [](Card& a){return card_names[a.value - 1];}, [](Card& a, string v){return a.value = card_values[v];})
        .def_property("suit", [](Card& a){return suit_names[a.suit - 1];}, [](Card& a, string s){return a.suit = suit_values[s];})
        .def("__repr__", &Card::to_string)
        .def("__eq__", &Card::operator==)
        .def("__ge__", &Card::operator>=)
        .def("__gt__", &Card::operator>)
        .def("__le__", &Card::operator<=)
        .def("__lt__", &Card::operator<);
    py::class_<Hand>(m, "Hand")
        .def(py::init<short, array<Card,5>>())
        .def(py::init<string, array<Card,5>>())
        .def_property("hand_type", [](Hand& a){return hand_names[a.hand_type - 1];}, [](Hand& a, string ht){return a.hand_type = hand_values[ht];})
        .def_readwrite("Cards", &Hand::Cards)
        .def("hand_heuristic", &Hand::hand_heuristic)
        .def("__repr__", &Hand::to_string)
        .def("__eq__", &Hand::operator==)
        .def("__ge__", &Hand::operator>=);
    m.def("get_best_hand", &poker_algo_old::get_best_hand_not_sorted, "A function that gets the best hands given 7 cards");
    m.def("calculate_hand_frequency", &poker_algo_old::calculate_hand_frequency, "A function that gets the frequencies of the possible hands given any number of cards");
    m.def("get_best_hand_new", &poker_algo_new::get_best_hand_not_sorted, "A function that gets the best hands given 7 cards");
    m.def("calculate_hand_frequency_new", &poker_algo_new::calculate_hand_frequency, "A function that gets the frequencies of the possible hands given any number of cards");
    // to remove
    m.def("_find_flush", &poker_algo_new::find_flush);
    m.def("_is_straight", &poker_algo_new::is_straight);
    m.def("_find_all_straights", &poker_algo_new::find_all_straights);
    m.def("_find_repetition", &poker_algo_new::find_repetition);
    m.def("_find_all_repetitions", &poker_algo_new::find_all_repetitions);
    m.def("_pad_card_vec", &poker_algo_new::pad_card_vec);
    ////
    m.def("nice_print_frequencies", &nice_print_frequencies, "A function that gets the frequencies of the possible hands and prints them in nice format");
}

// int main(){
//     array<Card, 7> test_cards = {Card(13, 3), Card(11, 2), Card(10, 2), Card(2, 4), Card(2, 3), Card(2, 2), Card(2, 1)};
//     Hand hand = poker_algo_new::get_best_hand_not_sorted(test_cards);
//     std::cout << "Hand: "<<hand_names[hand.hand_type - 1] << std::endl;
//     for(auto card:hand.Cards){
//         std::cout<<card.value<<card.suit<<" ";
//     }
//     std::cout<<endl;
//     return 0;
// }