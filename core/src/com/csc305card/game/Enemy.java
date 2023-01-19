package com.csc305card.game;

/**
 * Enemy class that controls the backend of the enemy
 */
public class Enemy{
    private int damage;
    private String name;
    private int health;

    /**
     * Constructor of the enemy class, creates stable version of Enemy Class
     *
     * @param name the name of the monster (in case we implement multiple monsters)
     * @param health the current health of the monster
     * @param damage the damage that the enemy deals to the user
     */
    public Enemy(String name, int health, int damage) {
        this.name = name;
        this.health = health;
        this.damage = damage;
    }

    /**
     * Method that will attack the player, subtracting health from them
     *
     * @param name name of the player that will be attacked
     * @param damageAmount the amount of damage to deal to the player
     */
    public void attack(String name, int damageAmount) {

    }

    /**
     * Method that will get the health of the monster so other classes can access it
     *
     */
    public int getHealth() {
        return health;
    }

    /**
     * Create the visuals for the monster to display on the screen
     */
    public void getVisuals() {

    }

    public static void main(String[] args) throws Exception {
        Enemy enemyOne = new Enemy("Christian", 100, 5);
    }


}
