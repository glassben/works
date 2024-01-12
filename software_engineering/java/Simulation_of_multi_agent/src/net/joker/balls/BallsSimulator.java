package net.joker.balls;

import java.awt.Color;
import java.awt.Point;

import gui.GUISimulator;
import gui.Oval;
import gui.Simulable;
import net.joker.events.EventManager;
import net.joker.utils.ColorConsole;
import net.joker.utils.TextComponent;

/**
 * @author serafith
 * Manage the simulation of balls (screen)
 */
public class BallsSimulator implements Simulable {
	
    private Balls balls;
    private GUISimulator gui;
    private EventManager eventManager;
    private int clock = 0;
    
    public BallsSimulator(Balls balls, GUISimulator gui, EventManager manager) {
    	this.balls = balls;
    	this.gui = gui;
    	this.eventManager = manager;
    }
    
    @Override
    public void next(){
       
       /*Display Ball position in terminal*/
       System.out.println(balls.toString());
       
       /*Display Ball in simulation*/
       gui.reset();
       
       displayGraphics();
       
       //Ca marche bien tout ca, bouge tout les 3 clics
       if(eventManager.isFinished()) {
    	   eventManager.addEvent(new BallEvent(clock + 3, balls)); 
    	   System.out.print(new TextComponent(ColorConsole.RED, "Prochaine event pour :" + String.valueOf(clock + 3)).getMessage());
       }
       
       clock++;
       
       eventManager.next();
       System.out.println(new TextComponent(ColorConsole.YELLOW, "clock ball: " + clock).getMessage());
    }
    
    @Override
    public void restart(){
        balls.reInit();
        gui.reset();
        
        eventManager.restart();
        clock = 0;
        eventManager.addEvent(new BallEvent(0, balls));
        
        System.out.println("reset");
        displayGraphics();
    }
    
    private void displayGraphics() {
    	 for(Point p : balls.getPoints()) {
      	   gui.addGraphicalElement(new Oval(p.x, p.y, Color.decode("#1f77b4"), Color.decode("#1f77b4"), 20));
         }  
    }
}
