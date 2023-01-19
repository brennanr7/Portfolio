package com.csc305card.game;

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.AfterEach;

import static org.junit.jupiter.api.Assertions.*;
import java.util.Vector;

class CardManagerTest {
    Card testCard = new Card("Test Card","Test",0);
    Card testCard1 = new Card("1", "Test", 0);
    Card testCard2 = new Card("2", "Test", 0);
    Card testCard3 = new Card("3", "Test", 0);
    Vector<Card> deck = new Vector<Card>();
    Vector<Card> hand = new Vector<Card>();
    Vector<Card> discard = new Vector<Card>();
    CardManager cardManager = new CardManager(deck, hand, discard);

    @AfterEach
    public void tearDown(){
        deck.clear();
        discard.clear();
        hand.clear();
    }

    @Test
    @DisplayName("Draw moves card from the deck to the hand")
    void drawCard()
    {
        deck.add(testCard);
        cardManager.DrawCard();
        assertTrue(hand.lastElement() == testCard);
    }

    @Test
    @DisplayName("Draw moves card to end of hand")
    void drawCardLargerHand()
    {
        deck.add(testCard);
        hand.add(testCard1);
        hand.add(testCard2);
        hand.add(testCard3);
        cardManager.DrawCard();
        assertTrue(hand.lastElement() == testCard);
    }

    @Test
    @DisplayName("Shuffles contents of discard into deck before drawing a card if deck is empty when DrawCard() is called")
    void drawCardEmptyDeck()
    {
        discard.add(testCard);
        cardManager.DrawCard();
        assertTrue(discard.isEmpty() && hand.contains(testCard));
    }

    @Test
    @DisplayName("Discard moves card from hand to discard")
    void discardCard()
    {
        hand.add(testCard);
        cardManager.DiscardCard(0);
        assertTrue(discard.firstElement() == testCard);
    }

    @Test
    @DisplayName("Discard moves card to top of discard")
    void discardCardLargerDiscard()
    {
        hand.add(testCard);
        discard.add(testCard1);
        discard.add(testCard2);
        discard.add(testCard3);
        cardManager.DiscardCard(0);
        assertTrue(discard.firstElement() == testCard);
    }


    @Test
    @DisplayName("Discard moves card from correct index in hand")
    void discardFromCorrectIndex()
    {
        hand.add(testCard1);
        hand.add(testCard2);
        hand.add(testCard3);
        cardManager.DiscardCard(1);
        assertTrue(discard.firstElement() == testCard2);
    }

    @Test
    @DisplayName("Move card moves card from source vector/index to destination vector/index")
    void moveCard()
    {
        deck.add(testCard);
        cardManager.SetSource(deck).SetSourceIndex(0).SetDestination(discard).SetDestinationIndex(0).MoveCard();
        assertTrue(discard.get(cardManager.GetDestinationIndex()) == testCard);
    }

    @Test
    @DisplayName("Move Card allows destination index to be 1 larger than its size")
    void destinationIndexEqualsSize()
    {
        deck.add(testCard);
        discard.add(testCard1);
        cardManager.SetSource(deck).SetSourceIndex(0).SetDestination(discard).SetDestinationIndex(1).MoveCard();
        assertTrue(discard.get(cardManager.GetDestinationIndex()) == testCard);
    }

    @Test
    @DisplayName("Moves all cards from source vector to destination vector")
    void moveAllCards()
    {
        deck.add(testCard1);
        deck.add(testCard2);
        deck.add(testCard3);
        cardManager.SetSource(deck).SetDestination(discard).MoveAllCards();
        assertTrue(discard.get(0) == testCard1 && discard.get(1) == testCard2 && discard.get(2) == testCard3);
    }

    @Test
    @DisplayName("Source Vector cannot be empty")
    void setSource()
    {
        assertThrows(EmptyVectorException.class, () -> cardManager.SetSource(deck));
    }

    @Test
    @DisplayName("Source Vector cannot have an index out of bounds")
    void setSourceWithIndexTooLarge()
    {
        deck.add(testCard);
        assertThrows(IndexOutOfBoundsException.class, () -> cardManager.SetSource(deck).SetSourceIndex(1));
    }

    @Test
    @DisplayName("Source Vector cannot have an index out of bounds")
    void setSourceWithIndexTooSmall()
    {
        deck.add(testCard);
        assertThrows(IndexOutOfBoundsException.class, () -> cardManager.SetSource(deck).SetSourceIndex(-1));
    }

    @Test
    @DisplayName("Destination Vector cannot have an index greater than its size")
    void setDestinationWithIndexTooLarge()
    {
        assertThrows(IndexOutOfBoundsException.class, () -> cardManager.SetDestination(deck).SetDestinationIndex(1));
    }

    @Test
    @DisplayName("Destination Vector cannot have an index out of bounds")
    void setDestinationWithIndexTooSmall()
    {
        assertThrows(IndexOutOfBoundsException.class, () -> cardManager.SetDestination(deck).SetDestinationIndex(-1));
    }
}