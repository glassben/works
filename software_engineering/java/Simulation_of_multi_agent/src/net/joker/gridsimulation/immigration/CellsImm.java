package net.joker.gridsimulation.immigration;

import java.awt.Point;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Set;

import net.joker.gridsimulation.SuperCell;
import net.joker.gridsimulation.conway.CellState;
import net.joker.utils.ColorConsole;
import net.joker.utils.TextComponent;

/**
 * @author serafith (alias Trophaigle sur la toile)
 * Class that manages cells in the plan, each one having a state from 1 to n.
 */
public class CellsImm extends SuperCell{

	/*Associate Points with status(ALIVE / DEAD)*/
	private LinkedHashMap<Point, DynamicState> cellMap;

	public static int nbState;
	public static String[] color_Scale;
	private int[] initialStateValue;
	
	/**
	 * @param points
	 * @param stateValue: array (ordered) of state's value of each cells 
	 * @param n : number of states
	 * @param colorScale array (ordered) of color of state: first color corresponds to state 1, last color corresponds to state n
	 * @param heightGrid
	 * @param widthGrid
	 * @throws Exception 
	 */
	public CellsImm(Point[] points, int[] stateValue, int n, String[] colorScale, int heightGrid, int widthGrid) throws Exception {
		
		
		super(points, widthGrid, heightGrid * widthGrid);
		
		this.initialStateValue = stateValue;
		nbState = n;
		color_Scale = colorScale;
		
		this.cellMap = new LinkedHashMap<>();
		
		if(stateValue.length != points.length) { throw new Exception("stateValue.length must be equal to points.length !"); }
		if(colorScale.length != n) { throw new Exception("Must be as many colors as the number of state"); }
		
		initializeMap(getPointsArray(), stateValue);
		
	}
	
	private void initializeMap(Point[] points, int[] stateValue) {
		for(int i = 0; i < points.length; i++) {
			DynamicState state = new DynamicState(stateValue[i]);
			this.cellMap.put(getPoint(i), state);
		}
	}
	
	/**
	 * @return map of points
	 */
	public LinkedHashMap<Point, DynamicState> getMap(){
		return this.cellMap;
	}
	
	/**
	 * Update the states of all Cells (ALIVE or DEAD)
	 */
	public void updateState() {
		/*Idea: 
		 * Copy the HashMap of Points
		 * Interate on points
		 * for each point look at the status of neighbourhood in the HashMap copiedMap (never modified during iterations)
		 * Modify the status (or not) of each point in the HashMap cellMap*/
		
		LinkedHashMap<Point, DynamicState> copy = copyMap(this.cellMap);
		
		for(int i = 0; i < getTotalPoint(); i++) {
			
			Set<Point> neighborhood = getNeighBors(i);
			
			//Look at the number of alive cell around current cell
			int nbCellWithOneUpperState = 0;
			
			System.out.println(getPoint(i).toString() + " states '" + copy.get(getPoint(i)).toString() + "' has for neighbours:");
			System.out.println(" ");
			
			int currentState = copy.get(getPoint(i)).getState();
			
			/*Passage délicat : ATTENTION MODULO n*/
			for(Point p : neighborhood) { 
				DynamicState stateCurrentPoint = copy.get(getPoint(i));
				DynamicState stateP = copy.get(p);
				if(stateP.getState() == stateCurrentPoint.getNextState()) {nbCellWithOneUpperState++;} //NextState n'est pas forcement currentState + 1!!! (modulo n)
				
				//Display neighbour of current point in terminal
				
				System.out.println(p.toString() + ": " + copy.get(p).toString());
			}
			System.out.println("Nb voisins à l'état k + 1: " + nbCellWithOneUpperState);
			System.out.println(" ");
			
			if(nbCellWithOneUpperState >= 3) { //On passe à l'état suivant
				this.cellMap.get(getPoint(i)).updateState(currentState); //A verif que ca foute pas la merde dans la hashmap !
			} 
		
			/*Censé de pas changer  ELLE EST MODIFIER AU COURS DES ITERATIONS ALORS QU'ELLE DEVRAIT PAS*/
			/*copy non modifié pendant itération -> PARFAIT !*/
			System.out.println(new TextComponent(ColorConsole.GREEN, "Display copy: ").getMessage());
			
			for (Map.Entry<Point, DynamicState> kv : copy.entrySet()) {
			    System.out.println(kv);
			}
		}
		
	}
	
	/**
	 * Reset all cells to their beginning states
	 */
	public void reInit() {
//		this.cellMap = copyMap(this.initialMap); -> marche pas: question de reference et de copie ....
		//Le code si dessous fait bien ce qu'on veut mais avec plus de variable stockée
		this.cellMap.clear();
		initializeMap(getPointsArray(), this.initialStateValue);
	}
	
	/**
	 * @param originalMap: map to copy
	 * @return the copy of the map
	 */
	private LinkedHashMap<Point, DynamicState> copyMap(LinkedHashMap<Point, DynamicState> originalMap){
		LinkedHashMap<Point, DynamicState> copiedMap = new LinkedHashMap<>();
		for(Map.Entry<Point, DynamicState> entries : originalMap.entrySet()) {
			copiedMap.put(entries.getKey(), new DynamicState(entries.getValue().getState()));
			//copiedMap.put(entries.getKey(), entries.getValue()); -> FAUX car on mets une référence en value et non une copy de la donnée !!!
		}
		
		return copiedMap;
	}
	
	/**
	 * Return a String representation of all cells
	 */
	@Override
	public String toString() {
		StringBuilder str = new StringBuilder();
        str.append("[");
        for (Map.Entry<Point, DynamicState> entries : this.cellMap.entrySet()) {
        	str.append(entries.getKey().toString() + "->" + entries.getValue().toString() + " ");
        	str.append(System.getProperty("line.separator"));
        }
        str.append("]");
        return str.toString();
	}
}
