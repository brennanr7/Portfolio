package com.csc305card.game;
/**
 * The card class creates an instance of different cards
 */
public class Card
{
    private String name, cardType;
    private int mana; //comment

    /**
     * The constructor for the Card class
     * @param name: the name of the card
     * @param type: the type of card
     * @param mana: the cost of the card
     */
    public Card(String name, String type, int mana)
    {
        if(name == "" || type == "" || mana < 0) {
            throw new IllegalArgumentException("A card must have a name, type, and mana greater than or equal to 0");
        }
        this.name = name;
        this.cardType = type;
        this.mana = mana;
    }

    /**
     * Gets the name of the card
     * @return name of the card
     */
    public String getName()
    {
        return name;
    }

    /**
     * Gets the type of the card
     * @return type of card
     */
    public String getCardType()
    {
        return cardType;
    }

    /**
     * Gets the cost of the card
     * @return cost of card
     */
    public int getMana()
    {
        return mana;
    }

    public static void main(String[] args) throws Exception
    {
        Card defend = new Card("shield", "defense", 5);
    }

}
