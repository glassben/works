package net.joker.gridsimulation.conway;

import java.awt.Color;
import java.awt.Point;
import java.util.Map;

import gui.GUISimulator;
import gui.Oval;
import gui.Simulable;

/**
 * @author serafith (alias Trophaigle sur la toile)
 * 
 */
public class ConveySimulator implements Simulable {
	//Ctr + 1 on class name to add methods to implement
	
	
	private GUISimulator gui;
	private Cells cells;
	
	public ConveySimulator(Cells cells, GUISimulator gui) {
		this.gui = gui;
		this.cells = cells;
	}
	
	@Override
	public void next() {
		/*Display cell states in terminal*/
		System.out.println("--------------------------------------------------------");
		System.out.println(cells.toString());
		
		/*Display cells in simulator*/
		gui.reset();
		
	    displayGraphics();
	    
		cells.updateState();
		
	}

	@Override
	public void restart() {
		gui.reset();
		cells.reInit();
        System.out.println("reset");
        displayGraphics();
        
        cells.updateState();
	}
	
	/**
	 * Display cells in the window - work nicely !
	 */
	private void displayGraphics() {
		for(Map.Entry<Point, CellState> entries : cells.getMap().entrySet()) {
			Point p = entries.getKey();
			
			String colorCode = entries.getValue().getColorCode();
			
			gui.addGraphicalElement(new Oval(p.y * 20 , p.x * 20, Color.decode(colorCode), Color.decode(colorCode), 20));
			
		}
	}
}
