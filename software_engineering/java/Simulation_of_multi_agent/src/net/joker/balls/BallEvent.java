package net.joker.balls;

import net.joker.events.Event;

public class BallEvent extends Event {

	private Balls ball;
	
	public BallEvent(long date, Balls ball) {
		super(date);
		this.ball = ball;
	}

	@Override
	public void execute() {
		this.ball.updateState();
	}
}
