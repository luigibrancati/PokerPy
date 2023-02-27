import PokerPy
import timeit

# test_cards_besthand = [PokerPy.Card(12, 2),PokerPy.Card(9, 1),PokerPy.Card(12, 3),PokerPy.Card(13, 3),PokerPy.Card(3, 3),PokerPy.Card(2, 2),PokerPy.Card(1, 2)]
test_cards_frequency = [[PokerPy.Card(13, 4), PokerPy.Card(12, 4)], [PokerPy.Card(11, 4), PokerPy.Card(10, 4)], [PokerPy.Card(3, 4), PokerPy.Card(2, 4)]]
N = 10

# t = timeit.timeit(lambda: PokerPy.get_best_hand(test_cards_besthand), number=1000000)
# print(f"get_best_hand: {t:.3f}")

# t = timeit.timeit(lambda: PokerPy.get_best_hand_new(test_cards_besthand), number=1000000)
# print(f"get_best_hand_new: {t:.3f}")

t1 = timeit.timeit(lambda: PokerPy.calculate_hand_frequency(test_cards_frequency), number=N)
print(f"calculate_hand_frequency: {t1:.3f}")

t2 = timeit.timeit(lambda: PokerPy.calculate_hand_frequency_new(test_cards_frequency, []), number=N)
print(f"calculate_hand_frequency_new: {t2:.3f}")
