package net.joker.gridsimulation.conway;

import java.awt.Point;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Set;
import net.joker.gridsimulation.SuperCell;
import net.joker.utils.ColorConsole;
import net.joker.utils.TextComponent;

/**
 * @author serafith (alias Trophaigle sur la toile)
 * Class that manages cells in the plan, which is Dead or Alive
 */
public class Cells extends SuperCell{

	/* Associate Points with status(ALIVE / DEAD) */
	private LinkedHashMap<Point, CellState> cellMap;
	
	/* Map of initial states */
	private LinkedHashMap<Point, CellState> initialMap;	
	
	/**
	 * @param points : list of points
	 * @param indexAlive : list of index for points being alive initially
	 * @param heightGrid
	 * @param widthGrid
	 */
	public Cells(Point[] points, int[] indexAlive, int heightGrid, int widthGrid) {
		
		super(points, widthGrid, heightGrid * widthGrid);
		
		this.cellMap = new LinkedHashMap<>();
		
		for(int i = 0; i < points.length; i++) {
			if(contains(indexAlive, i)) {
				this.cellMap.put(getPoint(i), CellState.ALIVE);
			} else {
				this.cellMap.put(getPoint(i), CellState.DEAD);
			}
		}
		this.initialMap = copyMap(this.cellMap);
	}
	
	/**
	 * @return map of points
	 */
	public LinkedHashMap<Point, CellState> getMap(){
		return cellMap;
	}
	
	/**
	 * Update the states of all Cells (ALIVE or DEAD)
	 */
	public void updateState() {
		/*Idea: 
		 * Copy the HashMap of Points
		 * Interate on points
		 * for each point look at the status (Alive or Dead) of neighbourhood in the HashMap copiedMap (never modified during iterations)
		 * Modify the status (or not) of each point in the HashMap cellMap*/
		
		LinkedHashMap<Point, CellState> copy = copyMap(this.cellMap);
		
		for(int i = 0; i < getTotalPoint(); i++) {
			
			Set<Point> neighborhood = super.getNeighBors(i);
			
			//Look at the number of alive cell around current cell
			int nbAliveCell = 0;
			
			System.out.println(getPoint(i).toString() + " states '" + copy.get(getPoint(i)).toString() + "' has for neighbours:");
			System.out.println(" ");
			for(Point p : neighborhood) {
				if(copy.get(p).isState(CellState.ALIVE)) {nbAliveCell++;}
				
				//Display neighbour of current point in terminal
				
				System.out.println(p.toString() + ": " + copy.get(p).toString());
			}
			System.out.println("Nb voisins vivant: " + nbAliveCell);
			System.out.println(" ");
			
			if(copy.get(getPoint(i)).isState(CellState.ALIVE)) { //ALIVE cell
			
				if(nbAliveCell != 2 && nbAliveCell != 3) {
					//Change status to DEAD in the effective map: cellMap
					cellMap.put(getPoint(i), CellState.DEAD); //Supposed to replace the old status of the point -> a verif
				}
				
			} else { //DEAD cell
				if(nbAliveCell == 3) {
					//The cell becomes ALIVE
					cellMap.put(getPoint(i), CellState.ALIVE);
				}
			}
			/*copy non modifié pendant itération -> PARFAIT !*/
			System.out.println(new TextComponent(ColorConsole.GREEN, "Display copy: ").getMessage());
			int alive = 0;
			for (Map.Entry<Point, CellState> kv : copy.entrySet()) {
			    System.out.println(kv);
			    if(kv.getValue() == CellState.ALIVE) {alive++;}
			}
			System.out.println(new TextComponent(ColorConsole.RED, "Alive : " + alive).getMessage());
		}
	}
	
	/**
	 * Reset all cells to their beginning states
	 */
	public void reInit() {
		this.cellMap = copyMap(this.initialMap);
	}
	
	/**
	 * @param originalMap: map to copy
	 * @return the copy of the map
	 */
	private LinkedHashMap<Point, CellState> copyMap(LinkedHashMap<Point, CellState> originalMap){
		LinkedHashMap<Point, CellState> copiedMap = new LinkedHashMap<>();
		for(Map.Entry<Point, CellState> entries : originalMap.entrySet()) {
			copiedMap.put(entries.getKey(), entries.getValue());
		}
		return copiedMap;
	}
	
	/**
	 * @param listInteger
	 * @param integer
	 * @return true if integer is in the list
	 */
	private boolean contains(int[] listInteger, int integer) {

		for(int e : listInteger) {
			if(e == integer) {
				return true;
			}
		}
		return false;
	}
	
	/**
	 * Return a String representation of all cells
	 */
	@Override
	public String toString() {
		StringBuilder str = new StringBuilder();
        str.append("[");
        for (Map.Entry<Point, CellState> entries : this.cellMap.entrySet()) {
        	str.append(entries.getKey().toString() + "->" + entries.getValue().toString() + " ");
        	str.append(System.getProperty("line.separator"));
        }
        str.append("]");
        return str.toString();
	}
}
