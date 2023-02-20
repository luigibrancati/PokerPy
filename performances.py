import PokerPy
import time

# test_cards_frequency = [[Card(12, 2), Card(8, 1)], [Card(12, 3), Card(13, 3)]]
# test_cards_besthand = [Card(12, 2),Card(9, 1),Card(12, 3),Card(13, 3),Card(3, 3),Card(2, 2),Card(1, 2)]

# start_old = time.time()
# hf_old = calculate_hand_frequency(test_cards_frequency)
# end_old = time.time()
# print(f"Old time: {(end_old - start_old) * 1000:.0f} ms")


# start_new = time.time()
# hf_new = calculate_hand_frequency_new(test_cards_frequency)
# end_new = time.time()
# print(f"New time: {(end_new - start_new) * 1000:.0f} ms")

# print(hf_old)
# print(hf_new)
# assert hf_new == hf_old

from itertools import product
import random
import timeit

N = 100000
old_time = 0
new_time = 0
all_cards = [PokerPy.Card(v, s) for v, s in product(range(1, 14), range(1, 5))]
print(all_cards)
print(len(all_cards))
sample_cards = [random.sample(all_cards, 7) for _ in range(N)]


start_old = time.time()
for sample in sample_cards:
    PokerPy.get_best_hand(sample)
end_old = time.time()

start_new = time.time()
for sample in sample_cards:
    PokerPy.get_best_hand_new(sample)
end_new = time.time()

# for i in range(N):
#     print()
#     print(i)
#     sample_cards = random.sample(all_cards, 7)
#     # sample_cards = [PokerPy.Card('JD'), PokerPy.Card('JC'), PokerPy.Card('8H'), PokerPy.Card('9S'), PokerPy.Card('4D'), PokerPy.Card('9C'), PokerPy.Card('2C')]
#     print(f"Cards: {sample_cards}")

#     start_old = time.time()
#     hf_old = PokerPy.get_best_hand(sample_cards)
#     end_old = time.time()
#     hf_old.Cards = sorted(hf_old.Cards, reverse=True)

#     start_new = time.time()
#     hf_new = PokerPy.get_best_hand_new(sample_cards)
#     end_new = time.time()
#     hf_new.Cards = sorted(hf_new.Cards, reverse=True)

#     print(f"Old time: {(end_old - start_old) * 1000000:.0f} us")
#     print(f"New time: {(end_new - start_new) * 1000000:.0f} us")
#     old_time += (end_old - start_old) * 1000000
#     new_time += (end_new - start_new) * 1000000
#     print(f"Old Hand: {hf_old}")
#     print(f"New Hand {hf_new}")
#     # for i in range(5):
#     #     assert hf_new.Cards[i].value == hf_old.Cards[i].value
print(f"Old time: {old_time:.0f} us")
print(f"New time: {new_time:.0f} us")