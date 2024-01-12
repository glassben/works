package net.joker.gridsimulation.immigration;

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
public class ImmigrationSimulator implements Simulable {
	//Ctr + 1 on class name to add methods to implement
	
	
	private GUISimulator gui;
	private CellsImm cells;
	
	public ImmigrationSimulator(CellsImm cells, GUISimulator gui) {
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
		for(Map.Entry<Point, DynamicState> entries : cells.getMap().entrySet()) {
			Point p = entries.getKey();
			
			Color color = Color.decode(CellsImm.color_Scale[cells.getMap().get(p).getState() - 1]);
			
			gui.addGraphicalElement(new Oval(p.y * 20 , p.x * 20, color, color, 20));
		}
	}
	

}
