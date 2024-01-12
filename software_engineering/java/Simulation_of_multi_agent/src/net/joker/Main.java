package net.joker;

import net.joker.balls.TestBallsSimulator;
import net.joker.boids.TestBoidsSimulator;
import net.joker.events.TestEventManager;
import net.joker.gridsimulation.TestGridSimulator;

/**
 * @author serafith
 * Main class for tests 
 * THE UNIQUE MAIN METHOD IS HERE, NOT SOMEWHERE ELSE !!!
 */
public class Main {

	//Penser à deplacer la fenêtre lorsqu'elle s'ouvre l'autre est CACHE DERRIERE !
	public static void main(String[] args) throws Exception  {
		//tout marche à priori 
		
		//TestBallsSimulator.testBallsSimulator(); 
		//TestGridSimulator.testImmigrationSimulator(); 
		//TestGridSimulator.testConwaySimulator();
		//TestGridSimulator.testSchellingSimulator(); 
		//TestEventManager.testEventManager();
		TestBoidsSimulator.testBoidsSimulator(); 
	}
}
