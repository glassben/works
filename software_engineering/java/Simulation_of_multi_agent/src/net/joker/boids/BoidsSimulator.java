package net.joker.boids;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.Polygon;
import gui.GUISimulator;
import gui.GraphicalElement;
import gui.Oval;
import gui.Simulable;
import net.joker.events.EventManager;

public class BoidsSimulator implements Simulable{
	
	 private GUISimulator gui;
	 /*Ensemble des essainms, des mouches, des abeilles, des vaches*/
	 private SuperBoid[] boidManagerTab;
	 
	 /*Un event manager associé à un type de Boid*/
	 private EventManager[] eventManagerTab;
	 private int clock = 0;

	public BoidsSimulator(SuperBoid[] managerTab, GUISimulator gui, EventManager eventManager[]) {
		this.boidManagerTab = managerTab;
		this.gui = gui;
		this.eventManagerTab = eventManager;
	}
	
	@Override
	public void next() {
		/*Display cells in simulator*/
		gui.reset();
		
	    displayGraphics();
	    
	    /*Il faut actualiser tous les types de Boids dans la même fenêtre mais chacun avec son propre manager d'event*/
		for(int i = 0; i < this.eventManagerTab.length; i++) {
			EventManager eventM = this.eventManagerTab[i];
			SuperBoid b = this.boidManagerTab[i];
			if(eventM.isFinished()) { //Si plus d'events en attente
				eventM.addEvent(new BoidRefreshEvent(clock + b.getPeriodRefresh(), b));
			}
		}
		clock++;
		
		for(EventManager eM : this.eventManagerTab) {
			eM.next();
		}
	}

	@Override
	public void restart() {
		gui.reset();
		
		for(EventManager eM : this.eventManagerTab) {
			eM.restart();
		}
		
		clock = 0;
		
		for(int i = 0; i < this.eventManagerTab.length; i++) {
			EventManager eventM = this.eventManagerTab[i];
			SuperBoid b = this.boidManagerTab[i];
			b.reInit();
			
			eventM.addEvent(new BoidRefreshEvent(0, b));
		}
		
        System.out.println("reset");
        
        displayGraphics();
	}
	
	private void displayGraphics() { //A REVOIR, TRACER TRIANGLE DANS LA DIRECTION SPEED
		for(SuperBoid boid : this.boidManagerTab) {
		
			for(EntityBoid entity : boid.getEntities()) {
				
				//Draw triangle with the right direction (that's why we need a vector   -> pos + speed vector ?
				//keeping the current direction of each boid
				Vector2D position = entity.getPosition();
				Vector2D speed = entity.getSpeed(); //Give the direction
			
				/*Angle fait par rapport à l'horizontal*/
				double theta;
				if(speed.getY() > 0) {
					//acos à value dans [0, pi]
					theta = Math.acos(speed.getX() / speed.getNorm());
				} else {
					theta = 2*Math.PI  - Math.acos(speed.getX() / speed.getNorm());
				}
				
				/*Au niveau de l origine*/
				
				Vector2D pointDroite = new Vector2D(20 * Math.cos(theta + (Math.PI/2)), 20 * Math.sin(theta + (Math.PI/2)));
				
				Vector2D pointGauche = new Vector2D(20 * Math.cos((Math.PI/2) - theta), 20 * Math.sin((Math.PI/2) - theta));
				
				Vector2D pointCentre = new Vector2D(50 * Math.cos(theta), 50 * Math.sin(theta));
				
				/*Au niveau du point effectivement concerné*/
				pointDroite.addVector(position);
				pointGauche.addVector(position);
				pointCentre.addVector(position);
				
			//https://www-igm.univ-mlv.fr/~berstel/Cours/CoursJava/8-Dessin.pdf
			gui.addGraphicalElement(new GraphicalElement() {
				
			
				@Override
				public void paint(Graphics2D g) {
					int[] polyx = {(int) Math.floor(pointDroite.getX()), (int) Math.floor(position.getX()),(int) Math.floor(pointGauche.getX()), (int) Math.floor(pointCentre.getX())};
					int[] polyy = {(int) Math.floor(pointDroite.getY()), (int) Math.floor(position.getY()),(int) Math.floor(pointGauche.getY()), (int) Math.floor(pointCentre.getY())};
					Polygon p = new Polygon(polyx, polyy, 4);
					
					g.setColor(Color.BLUE);
					g.fillPolygon(p);
					
				}
			});
				/*Je mets juste un point à la position*/
				gui.addGraphicalElement(new Oval((int) position.getX(), (int) position.getY(), boid.getColor(), boid.getColor(), 10));
				
				/* afficher "rayon d'action" avec voisinage, peut être commenté si on voit plus rien sur la simu*/
				//gui.addGraphicalElement(new Oval((int) position.getX(), (int) position.getY(), boid.getColorWithTransparency(), boid.getColorWithTransparency(), boid.getMinDistance()));
				}
			}
		}
}
