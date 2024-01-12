package net.joker.boids;

/**
 * @author serafith
 * Cette class représente une entity de l'essaims (abeille, truite, hirondelle, sardine ...)
 */
public class EntityBoid {
	
	private Vector2D position; //x_n -> point(double, double) in 2D space 
	
	private Vector2D speed; //x_n'  vector  size 2
	
	public EntityBoid(double intialX, double initialY, double intialSpeedX, double initialSpeedY) {
		this.position = new Vector2D(intialX, initialY);
		this.speed = new Vector2D(intialSpeedX, initialSpeedY);
	}
	
	public EntityBoid(int intialX, int initialY, int intialSpeedX, int initialSpeedY) {
		this.position = new Vector2D(intialX, initialY);
		this.speed = new Vector2D(intialSpeedX, initialSpeedY);
	}
	
	public Vector2D getPosition() {
		return this.position;
	}
	
	public Vector2D getSpeed() {
		return this.speed;
	}
	
	public void setSpeed(Vector2D v) {
		this.speed = v;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof EntityBoid) {
			EntityBoid boid = (EntityBoid) obj;
			if(boid.getPosition().equals(this.position) && boid.getSpeed().equals(this.speed)) {
				return true;
			}
		}
		return false;
	}
	
	@Override
	public String toString() {
		StringBuilder b = new StringBuilder();
		b.append("Position: ");
		b.append(this.position.toString());
		b.append(", Speed: ");
		b.append(this.speed.toString());
		return b.toString();
	}
}
