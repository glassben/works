package net.joker.boids;

/**
 * @author serafith, j'ai fais cette class car je trouve pas d'équivalent dans le commerce, 
 * de ce que j'ai compris Point ca gère des int seulement .... (je crois)
 *
 */
public class Vector2D {

	private double x;
	private double y;
	
	public Vector2D() {
		this.x = 0;
		this.y = 0;
	}
	
	public Vector2D(int x, int y) {
		this.x = Double.valueOf(x);
		this.y = Double.valueOf(y);
	}
	
	public Vector2D(double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	public void set(double x, double y) {
		this.x = x;
		this.y = y;
	}
	
	public double[] getComponents() {
		return new double[] {x, y};
	}
	
	public double getX() {
		return this.x;
	}
	
	public double getY() {
		return this.y;
	}
	
	
	public double distance(Vector2D vector) {
		return Math.sqrt(((this.x - vector.getX())*(this.x - vector.getX())) - ((this.y - vector.getY())*(this.y - vector.getY())));
	}
	
	public void addVector(Vector2D vector) {
		this.x = this.x + vector.getX();
		this.y = this.y + vector.getY();
	}
	
	public void soustractVector(Vector2D vector) {
		this.x = this.x - vector.getX();
		this.y = this.y - vector.getY();
	}
	
	public void divise(double n) {
		this.x = this.x / n;
		this.y = this.y / n;
	}
	
	public void multiply(double n) {
		this.x = this.x * n;
		this.y = this.y * n;
	}
	
	public double scalar(Vector2D vector) {
		return this.x * vector.getX() + this.y * vector.getY();
	}
	
	public double getNorm() {
		//origine en 0,0
		return Math.sqrt((this.x * this.x) + (this.y * this.y));
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj instanceof Vector2D) {
			Vector2D vector = (Vector2D) obj;
			if(vector.getX() == this.x && vector.getY() == this.y) {
				return true;
			}
		}
		return true;
	}
	
	@Override
	public String toString() {
		StringBuilder b = new StringBuilder();
		b.append("Vector[x="); b.append(this.x);
		b.append(", ");
		b.append("y="); b.append(this.y);
		b.append("]");
		return b.toString();
	}
}
