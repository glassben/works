package net.joker.boids.types;

import java.awt.Color;
import java.util.ArrayList;

import net.joker.boids.EntityBoid;
import net.joker.boids.SuperBoid;
import net.joker.boids.Vector2D;

/**
 * @author glassb sur la 5e Symphonie de Beethoven et le Portrait de Calogero
 *	Gestion de l'update des states des entity a chaque itération
 * 
 * 	Un premier type de Boids avec ses règles à lui
 */
public class Boids1Manager extends SuperBoid {

	private final double alpha = Math.PI; //A Change, il s'agit de l'angle sur le dessin de l'enoncé
	
	private final double angleDePerception = alpha / 3; //création d'un angle de perception de telle sorte que 
	//le boid puisse réagir avec les voisins qui sont dans son champ visuel.
	//On considère le champ visuel comme un cône dont l'angle d'ouverture
	public Boids1Manager(EntityBoid[] entities) {
		super(entities, 200,1); //refresh tout les 1 ticks (à chaque next) , distmin de 200
	}
	
	/**
	 * @param boid
	 * @return 2D vector of summ of v1 + v2 + v3
	 */
	public Vector2D computeAcceleration(EntityBoid boid) {
		//TODO
		//intervention de la force et des voisins -> getNeighborHood
		ArrayList<EntityBoid> neighbors = getNeighborHood(boid);
		
		Vector2D v1 = rule1(boid);
		Vector2D v2 = rule2(neighbors, boid);
		Vector2D v3 = rule3(boid);
		
		v1.addVector(v2);
		v1.addVector(v3);
		
		return v1;
	}
	
	/*Rules in pseudo code*/
	/*https://vergenet.net/~conrad/boids/pseudocode.html*/	
	
	/** Boids try to fly towards the centre of mass of neighbouring boids
	 * @param neighbors
	 * @param boid
	 * @return vector
	 */
	private Vector2D rule1(EntityBoid boid) {
		Vector2D pcJ = new Vector2D();
		
		for(EntityBoid entity : getEntities()) { //Center of mass of all boids
			if(entity.equals(boid)) {continue;} // Attention: b != bJ
			pcJ.addVector(entity.getPosition());
		}
		
		pcJ.divise(getEntities().size() - 1);
		pcJ.soustractVector(boid.getPosition());
		pcJ.divise(100);
		
		return  pcJ; //(pcJ - bJ.position) / 100
	}
	
	/** Boids try to keep a small distance away from other objects (including other boids
	 * @param neighbors
	 * @param boid
	 * @return vector
	 */
	private Vector2D rule2(ArrayList<EntityBoid> neighbors, EntityBoid boid) {
		Vector2D c = new Vector2D();
		
		for(EntityBoid entity : neighbors) {
			Vector2D diffVector = entity.getPosition(); //b.position
			diffVector.soustractVector(boid.getPosition()); //b.position - bJ.position
			
			c.soustractVector(diffVector); //c = c - (b.position - bJ.position)
		}
		return c;
	}
	
	/** Boids try to match velocity with near boids.
	 * @param neighbors
	 * @param boid
	 * @return vector
	 */
	private Vector2D rule3(EntityBoid boid) {
		Vector2D pvJ = new Vector2D();
		
		for(EntityBoid entity : getEntities()) {
			if(entity.equals(boid)) {continue;}
			pvJ.addVector(entity.getSpeed());
		}
		
		pvJ.divise(getEntities().size() - 1);
		pvJ.soustractVector(boid.getSpeed());
		pvJ.divise(8);
		
		return pvJ; //(pvJ - bJ.velocity) / 8
	}
	
	/**
	 * @param boid
	 * @return ArrayList of neighbors of boid (critere de distance pour l'instant)
	 */
	private ArrayList<EntityBoid> getNeighborHood(EntityBoid boid) {
		ArrayList<EntityBoid> neighbors = new ArrayList<>();
		//En premier temps on considère le concept de voisin en critere de distance
		double[] composante_boid=boid.getPosition().getComponents();
		for(EntityBoid other : getEntities()) {
			if(other.equals(boid)) {continue;} //we don't considerer the boid itself, Attention: b != bJ
			double[] composante_other=other.getPosition().getComponents();
			if(boid.getPosition().distance(other.getPosition()) <= getMinDistance() && Math.cos(angleDePerception)<=(composante_other[1]-composante_boid[1])/Math.sqrt(Math.pow((composante_other[1]-composante_boid[1]),2)+Math.pow((composante_other[0]-composante_boid[0]),2))){
				//ici on vérifie que le boid testé est proche du boid considéré et se situe dans le champ visuel de celui-ci.
				//pour cela on verifie que l'angle fait entre la verticale et le vecteur délimité par les boids est inférieur à l'angle de perception divisé par 2.
				neighbors.add(other);
			}
		}
		return neighbors;

	}

	@Override
	public Color getColor() { //afficher ces boids en Bleu
		return Color.BLUE;
	}

	@Override
	public Color getColorWithTransparency() {
		
		return new Color(0, 0, 255, 50); //Blue with transparency
	}
}
