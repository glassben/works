package net.joker.boids;

import net.joker.events.Event;

/**
 * @author serafith
 *
 */
public class BoidRefreshEvent extends Event {

	private SuperBoid boidManager;
	
	public BoidRefreshEvent(long date, SuperBoid boid) {
		super(date);
		this.boidManager = boid;
	}

	@Override
	public void execute() {
		boidManager.updateState();
		System.out.println("Movement of boids de period: " + boidManager.getPeriodRefresh());
	}
}
