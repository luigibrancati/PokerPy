There is an issue with the card ordering inside calculate_hand_frequency: the cards are not ordered by suit, so in some cases the get_best_hand gives different results when ordering them correctly

Below, `Cards 1` and `Hand 1` refer to the old algorithm which doesn't take into account the suit, while `Cards 2` and `Hand 2` refer to the sorted cards. Cards are the same, just sorted differently.

Cards 1: 133 134 123 113 103 93 92 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 92 
Hand 2: Royal Flush     133 123 113 103 93

Cards 1: 133 134 123 113 103 93 91 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 91 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 84 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 84 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 83 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 83 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 82 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 82 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 74 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 74 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 73 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 73 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 72 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 72 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 71 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 71 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 64 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 64 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 63 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 63 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 62 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 62 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 61 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 61 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 54 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 54 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 53 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 53 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 52 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 52 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 51 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 51 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 44 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 44 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 43 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 43 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 42 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 42 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 41 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 41 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 34 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 34 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 33 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 33 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 32 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 32 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 31 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 31 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 24 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 24 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 23 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 23 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 22 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 22 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 21 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 21 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 14 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 14 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 13 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 13 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 12 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 12 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 133 134 123 113 103 93 11 
Hand 1: Flush   133 123 113 103 93 
Cards 2: 134 133 123 113 103 93 11 
Hand 2: Royal Flush     133 123 113 103 93 

Cards 1: 134 122 112 102 92 81 82 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 134 122 112 102 92 82 81 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 133 134 123 54 44 34 24 
Hand 1: Flush   134 54 44 34 24 
Cards 2: 134 133 123 54 44 34 24 
Hand 2: Royal Flush     134 54 44 34 24 

Cards 1: 131 122 112 102 92 81 82 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 131 122 112 102 92 82 81 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 133 123 124 114 104 94 84 
Hand 1: Straight Flush  124 114 104 94 84 
Cards 2: 133 124 123 114 104 94 84 
Hand 2: Flush   124 114 104 94 84 

Cards 1: 122 124 112 102 92 81 82 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 124 122 112 102 92 82 81 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 121 111 101 91 81 84 
Hand 1: Straight Flush  121 111 101 91 81 
Cards 2: 122 121 111 101 91 84 81 
Hand 2: Flush   121 111 101 91 81 

Cards 1: 122 121 111 101 91 81 83 
Hand 1: Straight Flush  121 111 101 91 81 
Cards 2: 122 121 111 101 91 83 81 
Hand 2: Flush   121 111 101 91 81 

Cards 1: 122 121 111 101 91 81 82 
Hand 1: Straight Flush  121 111 101 91 81 
Cards 2: 122 121 111 101 91 82 81 
Hand 2: Flush   121 111 101 91 81 

Cards 1: 122 112 102 92 81 82 74 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 74 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 73 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 73 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 72 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 72 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 71 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 71 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 64 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 64 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 63 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 63 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 62 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 62 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 61 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 61 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 54 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 54 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 53 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 53 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 52 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 52 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 51 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 51 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 44 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 44 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 43 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 43 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 42 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 42 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 41 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 41 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 34 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 34 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 33 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 33 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 32 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 32 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 31 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 31 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 24 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 24 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 23 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 23 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 22 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 22 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 21 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 21 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 14 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 14 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 13 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 13 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 12 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 12 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 112 102 92 81 82 11 
Hand 1: Flush   122 112 102 92 82 
Cards 2: 122 112 102 92 82 81 11 
Hand 2: Straight Flush  122 112 102 92 82 

Cards 1: 122 81 84 74 64 54 44 
Hand 1: Straight Flush  84 74 64 54 44 
Cards 2: 122 84 81 74 64 54 44 
Hand 2: Flush   84 74 64 54 44 

Cards 1: 122 81 84 71 61 51 41 
Hand 1: Flush   81 71 61 51 41 
Cards 2: 122 84 81 71 61 51 41 
Hand 2: Straight Flush  81 71 61 51 41 

Cards 1: 122 81 83 73 63 53 43 
Hand 1: Straight Flush  83 73 63 53 43 
Cards 2: 122 83 81 73 63 53 43 
Hand 2: Flush   83 73 63 53 43 

Cards 1: 122 81 83 71 61 51 41 
Hand 1: Flush   81 71 61 51 41 
Cards 2: 122 83 81 71 61 51 41 
Hand 2: Straight Flush  81 71 61 51 41 

Cards 1: 122 81 82 71 61 51 41 
Hand 1: Flush   81 71 61 51 41 
Cards 2: 122 82 81 71 61 51 41 
Hand 2: Straight Flush  81 71 61 51 41 