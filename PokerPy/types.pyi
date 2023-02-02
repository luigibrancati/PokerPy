class Card:
    def __init__(self, card:str) -> None: ...
    @property
    def value(self) -> str: ...
    @property
    def color(self) -> str: ...

class Hand:
    def __init__(self, hand_type: str, Cards: list[Card]) -> None: ...
    @property
    def hand_type(self) -> str: ...
    @property
    def Cards(self) -> list[Card]: ...

def get_best_hand(cards: list[Card]) -> Hand: ...

def calculate_hand_frecuency(cards: list[list[Card]]) -> list[dict[str,int]]: ...

def nice_print_frecuencies(frecs: list[dict[str,int]]) -> None: ...

def calculate_hand_heuristic(hand: Hand) -> int: ...