from PokerPy import Card, Hand, _find_flush, _is_straight, _find_all_straights, _find_repetition, _find_all_repetitions, _pad_card_vec, get_best_hand_new, calculate_hand_frequency_new
import pytest


@pytest.mark.parametrize(
    "vec,cards,N,res",
    [
        ([1, 2, 3], [Card(12, 2), Card(11, 4), Card(11, 3), Card(11, 2), Card(11, 1), Card(6, 3), Card(2, 2)], 5, [0, 1, 2, 3, 4]),
        ([1, 3, 5], [Card(12, 2), Card(11, 4), Card(11, 3), Card(11, 2), Card(6, 1), Card(6, 3), Card(2, 2)], 6, [0, 1, 2, 3, 4, 5]),
        ([1, 2, 5, 6], [Card(12, 2), Card(11, 4), Card(11, 3), Card(10, 2), Card(6, 1), Card(2, 3), Card(2, 2)], 5, [0, 1, 2, 5, 6]),
        ([0, 2, 3, 5, 6], [Card(12, 2), Card(11, 4), Card(11, 2), Card(10, 2), Card(6, 1), Card(3, 2), Card(2, 2)], 6, [0, 1, 2, 3, 5, 6]),
    ]
)
def test_pad_card_vec(vec, cards, N, res):
    assert _pad_card_vec(vec, cards, N) == res


@pytest.mark.parametrize(
    "test_cards,value",
    [
        ([Card(8, 2), Card(7, 1), Card(6, 2), Card(5, 2), Card(4, 2), Card(3, 2), Card(2, 2)], [0, 2, 3, 4, 5]),
        ([Card(8, 3), Card(7, 1), Card(6, 2), Card(5, 2), Card(4, 2), Card(3, 2), Card(2, 2)], [2, 3, 4, 5, 6]),
        ([Card(8, 2), Card(7, 1), Card(6, 3), Card(5, 4), Card(4, 2), Card(3, 2), Card(2, 2)], []),
    ]
)
def test_find_flush(test_cards, value):
    assert _find_flush(test_cards) == value


@pytest.mark.parametrize(
    "test_cards,range,value",
    [
        ([Card(12, 2), Card(9, 1), Card(6, 1), Card(5, 3), Card(4, 3), Card(3, 3), Card(2, 2)], (2, 6), True),
        ([Card(12, 2), Card(9, 1), Card(6, 1), Card(5, 3), Card(4, 3), Card(3, 3), Card(2, 2)], (0, 4), False),
        ([Card(9, 1), Card(8, 1), Card(5, 3), Card(4, 3), Card(3, 3), Card(2, 2), Card(1, 1)], (2, 6), True),
        ([Card(12, 2), Card(6, 1), Card(5, 1), Card(4, 3), Card(3, 3), Card(1, 3), Card(1, 2)], (2, 6), False),
    ]
)
def test_is_straight(test_cards, range, value):
    assert _is_straight(test_cards, range) == value


@pytest.mark.parametrize(
    "test_cards,value",
    [
        ([Card(8, 2), Card(7, 1), Card(6, 1), Card(5, 3), Card(4, 3), Card(3, 3), Card(2, 2)], [[0, 1, 2, 3, 4], [1, 2, 3, 4, 5], [2, 3, 4, 5, 6]]),
        ([Card(12, 2), Card(9, 1), Card(6, 1), Card(5, 3), Card(4, 3), Card(3, 3), Card(2, 2)], [[2, 3, 4, 5, 6]]),
        ([Card(13, 1), Card(12, 1), Card(11, 3), Card(5, 3), Card(4, 3), Card(3, 2), Card(2, 2)], [[0, 3, 4, 5, 6]]),
        ([Card(13, 1), Card(12, 1), Card(11, 3), Card(4, 3), Card(4, 3), Card(3, 2), Card(2, 2)], []),
    ]
)
def test_find_all_straights(test_cards, value):
    assert _find_all_straights(test_cards) == value


@pytest.mark.parametrize(
    "test_cards,range,N,value",
    [
        ([Card(12, 2), Card(12, 1), Card(12, 1), Card(12, 3), Card(12, 3), Card(12, 3), Card(12, 2)], (0, 6), 7, (0, 6)),
        ([Card(12, 2), Card(9, 1), Card(6, 1), Card(6, 3), Card(6, 2), Card(3, 3), Card(2, 2)], (0, 6), 3, (2, 4)),
        ([Card(12, 2), Card(9, 1), Card(6, 1), Card(6, 3), Card(6, 2), Card(3, 3), Card(2, 2)], (0, 6), 2, (2, 3)),
        ([Card(12, 2), Card(12, 1), Card(12, 1), Card(12, 3), Card(12, 3), Card(12, 3), Card(12, 2)], (0, 6), 8, (-1, -1)),
        ([Card(12, 2), Card(11, 1), Card(10, 1), Card(9, 3), Card(8, 3), Card(7, 3), Card(6, 2)], (0, 6), 2, (-1, -1)),
    ]
)
def test_find_repetition(test_cards, range, N, value):
    assert _find_repetition(test_cards, range, N) == value


@pytest.mark.parametrize(
    "test_cards,N,value",
    [
        ([Card(12, 2), Card(12, 1), Card(12, 1), Card(6, 3), Card(6, 2), Card(6, 3), Card(2, 2)], 3, [(0, 2), (3, 5)]),
        ([Card(12, 2), Card(12, 1), Card(11, 1), Card(6, 3), Card(6, 2), Card(2, 3), Card(2, 2)], 2, [(0, 1), (3, 4), (5, 6)]),
        ([Card(12, 2), Card(11, 1), Card(10, 1), Card(9, 3), Card(8, 3), Card(7, 3), Card(6, 2)], 2, []),
    ]
)
def test_find_all_repetitions(test_cards, N, value):
    assert _find_all_repetitions(test_cards, N) == value


@pytest.mark.parametrize(
    "test_cards,hand",
    [
        (
            [Card(13, 2), Card(12, 2), Card(11, 2), Card(10, 2), Card(9, 2), Card(2, 2), Card(2, 3)],
            Hand("Royal Flush", [Card(13, 2), Card(12, 2), Card(11, 2), Card(10, 2), Card(9, 2)])
        ),
        (
            [Card(13, 4), Card(13, 3), Card(13, 2), Card(12, 2), Card(11, 2), Card(10, 2), Card(9, 2)],
            Hand("Royal Flush", [Card(13, 2), Card(12, 2), Card(11, 2), Card(10, 2), Card(9, 2)])
        ),
        (
            [Card(13, 3), Card(11, 2), Card(10, 2), Card(9, 2), Card(8, 2), Card(7, 2), Card(2, 2)],
            Hand("Straight Flush", [Card(11, 2), Card(10, 2), Card(9, 2), Card(8, 2), Card(7, 2)])
        ),
        (
            [Card(12, 2), Card(11, 2), Card(10, 2), Card(9, 2), Card(8, 2), Card(7, 2), Card(2, 2)],
            Hand("Straight Flush", [Card(12, 2), Card(11, 2), Card(10, 2), Card(9, 2), Card(8, 2)])
        ),
        (
            [Card(13, 1), Card(12, 2), Card(11, 2), Card(10, 2), Card(9, 2), Card(8, 2), Card(6, 2)],
            Hand("Straight Flush", [Card(12, 2), Card(11, 2), Card(10, 2), Card(9, 2), Card(8, 2)])
        ),
        (
            [Card(13, 3), Card(11, 2), Card(10, 2), Card(2, 4), Card(2, 3), Card(2, 2), Card(2, 1)],
            Hand("Poker", [Card(13, 3), Card(2, 4), Card(2, 3), Card(2, 2), Card(2, 1)])
        ),
        (
            [Card(13, 4), Card(13, 3), Card(13, 2), Card(13, 1), Card(2, 3), Card(2, 2), Card(2, 1)],
            Hand("Poker", [Card(13, 4), Card(13, 3), Card(13, 2), Card(13, 1), Card(2, 3)])
        ),
        (
            [Card(13, 3), Card(11, 4), Card(11, 3), Card(11, 2), Card(11, 1), Card(2, 2), Card(2, 1)],
            Hand("Poker", [Card(13, 3), Card(11, 4), Card(11, 3), Card(11, 2), Card(11, 1)])
        ),
        (
            [Card(13, 3), Card(13, 2), Card(13, 1), Card(4, 4), Card(3, 3), Card(2, 2), Card(2, 1)],
            Hand("Full House", [Card(13, 3), Card(13, 2), Card(13, 1), Card(2, 2), Card(2, 1)])
        ),
        (
            [Card(13, 3), Card(13, 2), Card(13, 1), Card(4, 4), Card(4, 3), Card(2, 2), Card(2, 1)],
            Hand("Full House", [Card(13, 3), Card(13, 2), Card(13, 1), Card(4, 4), Card(4, 3)])
        ),
        (
            [Card(13, 3), Card(13, 2), Card(11, 1), Card(10, 4), Card(9, 3), Card(8, 2), Card(7, 1)],
            Hand("Straight", [Card(11, 1), Card(10, 4), Card(9, 3), Card(8, 2), Card(7, 1)])
        ),
        (
            [Card(13, 3), Card(12, 2), Card(11, 1), Card(10, 4), Card(9, 3), Card(8, 2), Card(7, 1)],
            Hand("Straight", [Card(13, 3), Card(12, 2), Card(11, 1), Card(10, 4), Card(9, 3)])
        ),
        (
            [Card(12, 3), Card(12, 2), Card(11, 1), Card(10, 4), Card(9, 3), Card(8, 2), Card(7, 1)],
            Hand("Straight", [Card(12, 2), Card(11, 1), Card(10, 4), Card(9, 3), Card(8, 2)])
        ),
        (
            [Card(13, 3), Card(12, 2), Card(11, 1), Card(6, 4), Card(6, 3), Card(6, 2), Card(2, 1)],
            Hand("Triples", [Card(13, 3), Card(12, 2), Card(6, 4), Card(6, 3), Card(6, 2)])
        ),
        (
            [Card(13, 3), Card(11, 2), Card(11, 1), Card(7, 4), Card(6, 3), Card(6, 2), Card(2, 1)],
            Hand("Double Pairs", [Card(13, 3), Card(11, 2), Card(11, 1), Card(6, 3), Card(6, 2)])
        ),
        (
            [Card(13, 3), Card(11, 2), Card(10, 1), Card(7, 4), Card(7, 3), Card(6, 2), Card(2, 1)],
            Hand("Pairs", [Card(13, 3), Card(11, 2), Card(10, 1), Card(7, 4), Card(7, 3)])
        )
    ]
)
def test_best_hand(test_cards, hand):
    best_hand = get_best_hand_new(test_cards)
    assert best_hand.hand_type == hand.hand_type
    assert best_hand.Cards == hand.Cards


def test_calculate_frec():
    test_cards = [[Card(12, 2),Card(8, 1)],[Card(12, 3),Card(13, 3)]]
    frecs = calculate_hand_frequency_new(test_cards, [])
    test_frecs = [
        {'Double Pairs': 357732, 'Draw': 18348, 'Flush': 38757, 'Full House': 28846, 'High Card': 358523, 'Pairs': 796506, 'Poker': 1430, 'Royal Flush': 34, 'Straight': 63602, 'Straight Flush': 182, 'Total Cases': 1712305, 'Triples': 66692, 'Win': 370182},
        {'Double Pairs': 349041, 'Draw': 18348, 'Flush': 124854, 'Full House': 28846, 'High Card': 338887, 'Pairs': 757097, 'Poker': 1430, 'Royal Flush': 562, 'Straight': 46435, 'Straight Flush': 17, 'Total Cases': 1712305, 'Triples': 65135, 'Win': 1323774}
    ]
    assert frecs == test_frecs