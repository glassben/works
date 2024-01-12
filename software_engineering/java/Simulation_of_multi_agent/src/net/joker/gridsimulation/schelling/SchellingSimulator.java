package net.joker.gridsimulation.schelling;

import java.awt.Color;
import java.awt.Point;
import java.util.Map;

import gui.GUISimulator;
import gui.Oval;
import gui.Simulable;

public class SchellingSimulator implements Simulable{

	public static final int K = 2;
	
	private GUISimulator gui;
	private CellsHabitation cells;
	
	public SchellingSimulator(CellsHabitation hab, GUISimulator gui) {
		this.gui = gui;
		this.cells = hab;
	}
	
	@Override
	public void next() {
		System.out.println("---------------------------------------------");
		/*Display cells in simulator*/
		gui.reset();
		
	    displayGraphics();
	    
		try {
			cells.updateState();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	@Override
	public void restart() {
		gui.reset();
		cells.reInit();
        System.out.println("reset");
        displayGraphics();
        
        try {
			cells.updateState();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private void displayGraphics() {
		for(Map.Entry<Point, Habitation> entries : cells.getMap().entrySet()) {
			Point p = entries.getKey();
			
			if(entries.getValue().isVacant() == false) { //House occupied
				Color color = Color.decode(entries.getValue().getColor().getColorCode());
				gui.addGraphicalElement(new Oval(p.y * 20 , p.x * 20, color, color, 20));
				
			} else { //Empty house
				Color black = Color.decode("#000000");
				gui.addGraphicalElement(new Oval(p.y * 20 , p.x * 20, black, black, 20));
			}
		}
	}

}
