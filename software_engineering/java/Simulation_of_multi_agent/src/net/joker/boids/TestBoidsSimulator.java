package net.joker.boids;

import java.awt.Color;

import gui.GUISimulator;
import net.joker.boids.types.Boids1Manager;
import net.joker.boids.types.Boids2Manager;
import net.joker.events.EventManager;

/**
 * @author serafith
 * Boid test class
 */
public class TestBoidsSimulator {

	public static void testBoidsSimulator() { //PAS FINI
		
		GUISimulator gui = new GUISimulator(500, 500, Color.BLACK);
		
		EntityBoid[] poisson = {new EntityBoid(10, 10, 10, 10),
								new EntityBoid(100, 100, 20, 20),
								new EntityBoid(200, 200, -10, -5)};
		
		EntityBoid[] hirondelles = {new EntityBoid(40, 60, 10, 10),
				new EntityBoid(30, 70, 10, 3),
				new EntityBoid(100, 300, 4, -3),
				new EntityBoid(50, 500, 4, -10),
				new EntityBoid(400, 400, 4, -10),
				new EntityBoid(300, 300, 10, 20)};
		
		Boids1Manager manager1 = new Boids1Manager(poisson);
//		Boids2Manager manager2 = new Boids2Manager(entities2);
		EventManager event1 = new EventManager();
//		EventManager event2 = new EventManager();
		
//		gui.setSimulable(new BoidsSimulator(new SuperBoid[] {manager1, manager2} , gui, new EventManager[] {event1, event2}));
		gui.setSimulable(new BoidsSimulator(new SuperBoid[] {manager1} , gui, new EventManager[] {event1}));
	}
}
