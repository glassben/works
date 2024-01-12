package net.joker.boids;

import java.awt.Color;
import java.util.ArrayList;

/**
 * @author serafith
 * Class pour commune au groupe de bois
 *  class extends SuperBoid (like SuperCell)
 *  Contient ce qui est commun à tous les Boids
 */
public abstract class SuperBoid {
	
	/*Collection of boids*/
	private ArrayList<EntityBoid> entities;
	
	/*Keep a copy of initial state*/
	private ArrayList<EntityBoid> originalEntities;
	
	/*si = 1 alors refresh à chaque next, si 2 tout les 2 next*/
	private int periodRefresh;
	
	private int minDistance; //Distance introduite dans énoncé
	
	public SuperBoid(EntityBoid[] boids, int distMin, int periodRefresh) {
		this.entities = new ArrayList<>();
		for(EntityBoid entity : boids) {
			this.entities.add(entity);
		}
		this.periodRefresh = periodRefresh;
		
		this.originalEntities = new ArrayList<>();
		
		this.minDistance = distMin;
		
		/*Copy in save ArrayList*/
		for(EntityBoid boid : this.entities) {
			this.originalEntities.add(new EntityBoid(boid.getPosition().getX(), boid.getPosition().getY(), boid.getSpeed().getX(), boid.getSpeed().getY()));
		}
	}
	
	public ArrayList<EntityBoid> getEntities(){
		return this.entities;
	}
	
	public int getPeriodRefresh() {
		return this.periodRefresh;
	}
	
	private void restartEntities() {
		/*Vider ancienne ArrayList pour remplir avec Entity d'origine*/
		this.entities.clear();
		/*Copy in save ArrayList*/
		for(EntityBoid boid : this.originalEntities) {
			this.entities.add(new EntityBoid(boid.getPosition().getX(), boid.getPosition().getY(), boid.getSpeed().getX(), boid.getSpeed().getY()));
		}
	}
	
	public abstract Color getColor();
	
	public abstract Color getColorWithTransparency();
	
	public abstract Vector2D computeAcceleration(EntityBoid boid);
	
	public void updateState() {
		System.out.println("new Positions of Boids: ");
		for(EntityBoid currentBoid : getEntities()) {
			
			Vector2D acceleration = computeAcceleration(currentBoid); 
			
			currentBoid.getSpeed().addVector(acceleration);
			limitVelocity(currentBoid);
			
			EntityBoid test = new EntityBoid(currentBoid.getPosition().getX(),currentBoid.getPosition().getY(),currentBoid.getSpeed().getX(),currentBoid.getSpeed().getY());
			test.getPosition().addVector(currentBoid.getSpeed());
			while (test.getPosition().getX()>500 || test.getPosition().getX()<0||test.getPosition().getY()<0||test.getPosition().getY()>500) {
				if (currentBoid.getSpeed().getX()>0 && currentBoid.getSpeed().getY()>0 && test.getPosition().getX()>500){
					currentBoid.getSpeed().set(-test.getSpeed().getX(),test.getSpeed().getY());
					test.getPosition().addVector(currentBoid.getSpeed());	
				}
				if (currentBoid.getSpeed().getX()<0 && currentBoid.getSpeed().getY()<0 && test.getPosition().getX()>500){
					currentBoid.getSpeed().set(-test.getSpeed().getX(),test.getSpeed().getY());
					test.getPosition().addVector(currentBoid.getSpeed());
				}
				if (currentBoid.getSpeed().getX()>0 && currentBoid.getSpeed().getY()>0 && test.getPosition().getY()>500){
					currentBoid.getSpeed().set(test.getSpeed().getX(),-test.getSpeed().getY());
					test.getPosition().addVector(currentBoid.getSpeed());
					}
				
				if (currentBoid.getSpeed().getX()<0 && currentBoid.getSpeed().getY()>0 && test.getPosition().getY()>500){
					currentBoid.getSpeed().set(test.getSpeed().getX(),-test.getSpeed().getY());
					test.getPosition().addVector(currentBoid.getSpeed());
				}
				if (currentBoid.getSpeed().getX()<0 && currentBoid.getSpeed().getY()<0 && test.getPosition().getY()<0){
					currentBoid.getSpeed().set(test.getSpeed().getX(),-test.getSpeed().getY());
					test.getPosition().addVector(currentBoid.getSpeed());
				}
				if (currentBoid.getSpeed().getX()>0 && currentBoid.getSpeed().getY()<0 && test.getPosition().getY()<0) {
					currentBoid.getSpeed().set(-test.getSpeed().getX(),-test.getSpeed().getY());
					test.getPosition().addVector(currentBoid.getSpeed());
				}
				if (currentBoid.getSpeed().getX()<0 && currentBoid.getSpeed().getY()<0 && test.getPosition().getX()<0) {
					currentBoid.getSpeed().set(-test.getSpeed().getX(),test.getSpeed().getY());
					test.getPosition().addVector(currentBoid.getSpeed());
				}
				if (currentBoid.getSpeed().getX()<0 && currentBoid.getSpeed().getY()>0 && test.getPosition().getX()<0) {
					currentBoid.getSpeed().set(-test.getSpeed().getX(),test.getSpeed().getY());
					test.getPosition().addVector(currentBoid.getSpeed());
				}
			}
			currentBoid.getPosition().set(test.getPosition().getX(),test.getPosition().getY());
			
			System.out.println(currentBoid.toString());
			
		}
		System.out.println(" ");
	}
	
	public  void reInit() {
		restartEntities();
	}
	
	/**
	 * @return minDistance to consider when looking at neighbors
	 */
	public int getMinDistance() {
		return this.minDistance;
	}
	
	private void limitVelocity(EntityBoid b) {
		int vlim = 10;
		double normSpeed = b.getSpeed().getNorm();
		if(normSpeed > vlim) {
			Vector2D newSpeed = new Vector2D();
			newSpeed.set(b.getSpeed().getX(), b.getSpeed().getY());
			newSpeed.divise(normSpeed);
			newSpeed.multiply(vlim);
			b.setSpeed(newSpeed);
		}
	}
}
