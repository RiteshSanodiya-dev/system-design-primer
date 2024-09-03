/*
Explanation of the Code:

Enum Class for Suit:
- `Suit` is an enum representing the four suits in a deck of cards.

Abstract Base Class `Card`:
- Represents a general card with methods for getting and setting the card's value and availability.

Derived Class `BlackJackCard`:
- Inherits from `Card` and implements the `getValue()` and `setValue()` methods.
- These methods have specific behavior for Blackjack cards, including handling Aces and face cards.

Class `Hand`:
- Manages a collection of cards and can calculate the total score of the hand.

Class `BlackJackHand`:
- Inherits from `Hand` and overrides the `score()` method.
- Provides Blackjack-specific scoring, including possible score calculations considering Aces.

Class `Deck`:
- Manages a collection of cards and provides methods for dealing cards and checking the number of remaining cards.

Additional Notes:
- Some methods like `possibleScores()` and `shuffle()` are placeholders and would need further implementation based on the specific game logic.
- Exception handling and some additional utility functions (like `std::shuffle`) might be needed for a complete implementation.
*/



#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <stdexcept>

enum class Suit {
    HEART = 0,
    DIAMOND = 1,
    CLUBS = 2,
    SPADE = 3
};

class Card {
protected:
    int _value;
    Suit _suit;
    bool _is_available;

public:
    Card(int value, Suit suit) : _value(value), _suit(suit), _is_available(true) {}

    virtual int getValue() const = 0;
    virtual void setValue(int value) = 0;

    bool isAvailable() const {
        return _is_available;
    }

    void setAvailability(bool availability) {
        _is_available = availability;
    }

    virtual ~Card() = default;
};

class BlackJackCard : public Card {
public:
    BlackJackCard(int value, Suit suit) : Card(value, suit) {}

    bool isAce() const {
        return _value == 1;
    }

    bool isFaceCard() const {
        return _value > 10 && _value <= 13;
    }

    int getValue() const override {
        if (isAce()) {
            return 1;
        } else if (isFaceCard()) {
            return 10;
        } else {
            return _value;
        }
    }

    void setValue(int value) override {
        if (value >= 1 && value <= 13) {
            _value = value;
        } else {
            throw std::invalid_argument("Invalid card value: " + std::to_string(value));
        }
    }
};

class Hand {
protected:
    std::vector<Card*> cards;

public:
    Hand(const std::vector<Card*>& cards) : cards(cards) {}

    void addCard(Card* card) {
        cards.push_back(card);
    }

    virtual int score() const {
        int total_value = 0;
        for (const auto& card : cards) {
            total_value += card->getValue();
        }
        return total_value;
    }

    virtual ~Hand() = default;
};

class BlackJackHand : public Hand {
public:
    static const int BLACKJACK = 21;

    BlackJackHand(const std::vector<Card*>& cards) : Hand(cards) {}

    int score() const override {
        int min_over = std::numeric_limits<int>::max();
        int max_under = std::numeric_limits<int>::min();

        for (int score : possibleScores()) {
            if (score > BLACKJACK && score < min_over) {
                min_over = score;
            } else if (score <= BLACKJACK && score > max_under) {
                max_under = score;
            }
        }
        return max_under != std::numeric_limits<int>::min() ? max_under : min_over;
    }

    std::vector<int> possibleScores() const {
        // This method should return possible scores considering Aces, similar to the Python method.
        // For now, it returns an empty vector to match the Python code.
        return std::vector<int>();
    }
};

class Deck {
private:
    std::vector<Card*> cards;
    size_t deal_index;

public:
    Deck(const std::vector<Card*>& cards) : cards(cards), deal_index(0) {}

    size_t remainingCards() const {
        return cards.size() - deal_index;
    }

    Card* dealCard() {
        if (deal_index < cards.size()) {
            Card* card = cards[deal_index];
            card->setAvailability(false);
            ++deal_index;
            return card;
        }
        return nullptr;
    }

    void shuffle() {
        // Implement shuffle logic here.
    }
};
