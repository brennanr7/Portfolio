package com.csc305card.game;
import static java.util.Collections.shuffle;
import java.util.Vector;

/**
 * CardManager handles the transfer of a player's cards between their Hand, Deck, and Discard pile
 *
 * Contains several methods for common card movements, such as drawing from the deck and discarding from the hand,
 * as well as methods to handle abnormal movements through manually setting a source and destination
 *
 * The "top" card of the deck, hand, and discard piles are assumed to be index 0, and the "bottom" the last index
 */
public class CardManager {
    private Vector<Card> deck;
    private Vector<Card> hand;
    private Vector<Card> discard;
    private Vector<Card> sourceVector;
    private int sourceIndex;
    private Vector<Card> destinationVector;
    private int destinationIndex;

    /**
     * CardManager instance for a player consists of 3 Vectors of Cards from their Hand, Deck, and Discard
     * Modifications performed by CardManager should change the contents of the original Vectors
     *
     * @param deck The Vector<Card> from the player's Deck
     * @param hand The Vector<Card> from the player's Hand
     * @param discard The Vector<Card> from the player's Discard
     */
    public CardManager(Vector<Card> deck, Vector<Card> hand, Vector<Card> discard)
    {
        this.deck = deck;
        this.hand = hand;
        this.discard = discard;
    }

    /**
     * Moves the top card from the player's deck to the end of the player's hand
     *
     * If the deck is empty, shuffles cards from the discard pile back into the deck instead
     */
    public void DrawCard()
    {
        if(deck.isEmpty())
        {
            SetSource(discard).SetDestination(deck);
            MoveAllCards();
            ShuffleDeck();
        }

        hand.add(deck.remove(0));
    }

    /**
     * Moves the card at the specified index in the hand to the discard pile
     */
    public void DiscardCard(int cardIndex)
    {
        discard.add(0, hand.remove(cardIndex));
    }

    /**
     * Moves the card at the source index of the source Vector of cards to the destination index of the destination Vector of cards.
     * This method should only be used if there is no method that already moves a card to/from the appropriate index or if the card needs to be placed at a specific index
     *
     * Source Vector/index and destination Vector/index must be set with their associated accessors first!
     */
    public void MoveCard()
    {
        destinationVector.add(destinationIndex, sourceVector.remove(sourceIndex));
    }

    /**
     * Moves all cards from the source Vector of cards to the destination Vector of cards
     *
     * Source Vector and destination Vector must be set with their associated accessors first!
     */
    public void MoveAllCards()
    {
        int sourceLength = sourceVector.size();
        for(int i = 0; i < sourceLength; i++)
        {
            destinationVector.add(sourceVector.remove(0));
        }
    }

    /**
     * Shuffles the deck
     */
    public void ShuffleDeck()
    {
        shuffle(deck);
    }

    /**
     * Sets the Vector of the source for use with MoveCard() and MoveAllCards()
     *
     * Source Vector must not be empty!
     *
     * @param sourceVector Vector of source
     * @return CardManager with this source Vector
     */
    public CardManager SetSource(Vector<Card> sourceVector)
    {
        this.sourceVector = sourceVector;
        if(sourceVector.isEmpty())
            throw new EmptyVectorException();
        return this;
    }

    /**
     * Sets the index of source card for use with MoveCard() and MoveAllCards()
     *
     * Source Vector must be set before the index!
     *
     * Source index must be an index within the bounds of the source Vector!
     *
     * @param sourceIndex Index of Source Card
     * @return CardManager with this source index
     */
    public CardManager SetSourceIndex(int sourceIndex)
    {
        if(sourceIndex < 0 || sourceIndex >= sourceVector.size())
            throw new IndexOutOfBoundsException();
        this.sourceIndex = sourceIndex;
        return this;
    }

    /**
     * Sets the Vector of the destination for use with MoveCard() and MoveAllCards()
     *
     * @param destinationVector Vector of destination
     * @return CardManager with this destination vector
     */
    public CardManager SetDestination(Vector<Card> destinationVector)
    {
        this.destinationVector = destinationVector;
        return this;
    }

    /**
     * Sets the index of the destination for use with MoveCard() and MoveAllCards()
     *
     * Destination index must be within bounds of the Destination Vector size! (destination index can be 1 index higher
     * than the largest current index of the destination Vector)
     *
     * @param destinationIndex Index of destination
     * @return CardManager with this destination index
     */
    public CardManager SetDestinationIndex(int destinationIndex)
    {
        if(destinationIndex < 0 || destinationIndex > 0 && destinationIndex > destinationVector.size())
            throw new IndexOutOfBoundsException();
        this.destinationIndex = destinationIndex;
        return this;
    }

    /**
     * Gets the current source Vector
     *
     * @return sourceVector
     */
    public Vector<Card> GetSourceVector()
    {
        return this.sourceVector;
    }

    /**
     * Gets the current source index
     *
     * @return sourceIndex
     */
    public int GetSourceIndex()
    {
        return this.sourceIndex;
    }

    /**
     * Gets the current destination Vector
     *
     * @return destinationVector
     */
    public Vector<Card> GetDestinationVector()
    {
        return this.destinationVector;
    }

    /**
     * Gets the current destination index
     *
     * @return destinationIndex
     */
    public int GetDestinationIndex()
    {
        return this.destinationIndex;
    }
}
