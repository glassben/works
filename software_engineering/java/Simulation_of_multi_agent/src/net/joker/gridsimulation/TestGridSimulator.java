package net.joker.gridsimulation;

import java.awt.Color;
import java.awt.Point;
import java.util.HashMap;

import gui.GUISimulator;
import net.joker.balls.Balls;
import net.joker.balls.BallsSimulator;
import net.joker.gridsimulation.conway.Cells;
import net.joker.gridsimulation.conway.ConveySimulator;
import net.joker.gridsimulation.immigration.CellsImm;
import net.joker.gridsimulation.immigration.ImmigrationSimulator;
import net.joker.gridsimulation.schelling.CellsHabitation;
import net.joker.gridsimulation.schelling.ColorPeople;
import net.joker.gridsimulation.schelling.SchellingSimulator;

/**
 * @author serafith (alias Trophaigle sur la toile)
 * Generate entries for different type of cell test
 */
public class TestGridSimulator {

	public static void testConwaySimulator() {
		
		GUISimulator gui = new GUISimulator(500, 500, Color.BLACK);
		
		//exemple de l'énoncé
		int height = 5;
		int width = 5;
		
		/*Une cellule à la ligne x, colonne y est réprésentée par un point(x,y)*/
		
		Point[] array = generateGrid(height, width);
		
		/*List of index of cells initially alive*/
		int[] indexAlive = {6, 7 , 11, 13, 24};
		
		
    	Cells cells = new Cells(array, indexAlive, height, width);
		
		gui.setSimulable(new ConveySimulator(cells, gui));
	}
	
	public static void testImmigrationSimulator() throws Exception { //Pas fini cette simulation
		
		GUISimulator gui = new GUISimulator(500, 500, Color.BLACK);
		
		int height = 4;
		int width = 4;
		int n = 3; //Number of states
		
		Point[] array = generateGrid(height, width);
		
		/*List of state of each cell ordered */
		int[] statesValues = {1, 3, 3, 1,
								1, 2, 3, 1,
								1, 2, 1, 1,
								1, 1, 1, 1}; //Contains as many value as the number of cells, so here 4*4 = 16
		
		
		String[] colorStateArray = {"#ffffff", "#ff99ff", "#ff66ff"}; //For state 1, 2, 3 here
		
		CellsImm cells = new CellsImm(array, statesValues, n, colorStateArray, height, width);
		
		gui.setSimulable(new ImmigrationSimulator(cells, gui));
		
	}
	
	public static void testSchellingSimulator() throws Exception { //A priori ca à l'air de marcher -> J'ai du mal à verifier sur l'affichage 
																	//En sachant que les demenagements se font dans logements vides aléatoire.
		
		GUISimulator gui = new GUISimulator(500, 500, Color.BLACK);
		
		int height = 5;
		int width = 5;
		
		Point[] array = generateGrid(height, width);
		
		/*Null means empty habitation*/
		ColorPeople[] colors = {null, ColorPeople.GREEN, ColorPeople.RED, ColorPeople.YELLOW, null,
								null, null, ColorPeople.WHITE, null, null,
								ColorPeople.WHITE, null, ColorPeople.RED, ColorPeople.PURPLE, null,
								null, ColorPeople.PURPLE, ColorPeople.RED, ColorPeople.WHITE, ColorPeople.GREEN,
								ColorPeople.RED, ColorPeople.RED, null, ColorPeople.PURPLE, null };
		
		CellsHabitation cells = new CellsHabitation(array, colors, height, width);
		
		gui.setSimulable(new SchellingSimulator(cells, gui));
	}
	
	/**
	 * @param height
	 * @param width
	 * @return a grid of point height x width as a array
	 * A point (x,y) means line x, column y
	 */
	private static Point[] generateGrid(int height, int width) {
/*		example with 4 x 4 grid, DON'T UNCOMMENT - it's an example !
		
		//Ligne 1
    	array[0] = new Point(1, 1);
    	array[1] = new Point(1, 2);
    	array[2] = new Point(1, 3);
    	array[3] = new Point(1, 4);
    	
    	//Ligne 2
    	array[4] = new Point(2, 1);
    	array[5] = new Point(2, 2);
    	array[6] = new Point(2, 3);
    	array[7] = new Point(2, 4);
    	
    	//Ligne 3
    	array[8] = new Point(3, 1);
    	array[9] = new Point(3, 2);
    	array[10] = new Point(3, 3);
    	array[11] = new Point(3, 4);
    	
    	//Ligne 4
    	array[12] = new Point(4, 1);
    	array[13] = new Point(4, 2);
    	array[14] = new Point(4, 3);
    	array[15] = new Point(4, 4);  */
		
		Point[] array = new Point[height * width];
		int index = 0;
		
		for(int x = 1; x <= height; x++) {
			for(int y = 1; y <= width; y++) {
				array[index] = new Point(x, y);
				index++;
			}
		}
		return array;
	}
}
