import PokerPy
from itertools import product
import timeit

test_cards_besthand = [PokerPy.Card(12, 2),PokerPy.Card(9, 1),PokerPy.Card(12, 3),PokerPy.Card(13, 3),PokerPy.Card(3, 3),PokerPy.Card(2, 2),PokerPy.Card(1, 2)]
test_cards_frequency = [[PokerPy.Card(12, 2), PokerPy.Card(8, 1)], [PokerPy.Card(12, 3), PokerPy.Card(13, 3)]]

t = timeit.timeit(lambda: PokerPy.get_best_hand(test_cards_besthand), number=1000000)
print(f"get_best_hand: {t:.3f}")

t = timeit.timeit(lambda: PokerPy.get_best_hand_new(test_cards_besthand), number=1000000)
print(f"get_best_hand_new: {t:.3f}")

t = timeit.timeit(lambda: PokerPy.calculate_hand_frequency(test_cards_frequency), number=1)
print(f"calculate_hand_frequency: {t:.3f}")

t = timeit.timeit(lambda: PokerPy.calculate_hand_frequency_new(test_cards_frequency, []), number=1)
print(f"calculate_hand_frequency_new: {t:.3f}")
