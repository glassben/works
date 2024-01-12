package net.joker.gridsimulation.schelling;

import java.awt.Point;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Random;
import java.util.Set;
import net.joker.gridsimulation.SuperCell;
import net.joker.gridsimulation.immigration.DynamicState;

public class CellsHabitation extends SuperCell {

	private LinkedHashMap<Point, Habitation> cellMap;
	
	/*Store repartition of colors initially*/
	private ColorPeople[] initialColors;
	
	/*Store vacant habitations*/
	private ArrayList<Habitation> vacantHabitation;
	
	public CellsHabitation(Point[] points, ColorPeople[] colors, int heightGrid, int widthGrid) throws Exception {
		
		super(points, widthGrid, heightGrid * widthGrid);
	
		if(colors.length != (heightGrid * widthGrid)) {throw new Exception("colors.length must equal number of points !");}
		
		this.cellMap = new LinkedHashMap<>();
		this.initialColors = colors;
		this.vacantHabitation = new ArrayList<>();
		
		initializeMap(getPointsArray(), colors);

	}
	
	private void initializeMap(Point[] points, ColorPeople[] colors) {
		for(int i = 0; i < points.length; i++) {
			Habitation habitation;
			if(colors[i] == null) {
				habitation = new Habitation(getPoint(i), true, null);
				this.vacantHabitation.add(habitation);
			} else {
				habitation = new Habitation(getPoint(i), false, colors[i]);
			}
			this.cellMap.put(getPoint(i), habitation);
		}
	}
	
	/**
	 * @return map of points
	 */
	public LinkedHashMap<Point, Habitation> getMap(){
		return cellMap;
	}
	
	public void updateState() throws Exception {
		
		for(int i = 0; i < getTotalPoint(); i++) {
			
			if(this.cellMap.get(getPoint(i)).isVacant()) { //Si une habitation vacante -> pas de famille -> pas comparaison avec voisins à faire
				continue;
			}
			
			Set<Point> neighborhood = getNeighBors(i);
			
			ColorPeople currentFamilyColor = this.cellMap.get(getPoint(i)).getColor();
			
			//Let's Count the number of family around with a different color
			int number = 0;
			
			ArrayList<ColorPeople> array = new ArrayList<>();
			
			for(Point p : neighborhood) {
				ColorPeople colorPoint = this.cellMap.get(p).getColor();
				if(!(colorPoint == null)) {
					if((colorPoint != currentFamilyColor) && (!array.contains(colorPoint))) { //On rencontre une nouvelle couleur differente de la current et de toute les autres avant
						number++;
						array.add(colorPoint); //On dit qu'on a deja vu cette couleur
					}
				}
			}
			
			System.out.println("Nombre voisin de couleur différente de " + getPoint(i).toString() + ": " + number);
			
			if(number > SchellingSimulator.K) { //On demenage (we move in english) si plus de K voisin de couleur differente autour
			
//				attention 2 famille ne peuvent pas demenager au meme endroit -> arraylist
				Random rndm = new Random();
				
				//Find a vacant habitation
				Habitation rndmVacantHabitation = this.vacantHabitation.get(rndm.nextInt(this.vacantHabitation.size()));
				
				//Rendre habitation courant vacant et l'habitation de destination occupé
				this.cellMap.get(getPoint(i)).vacate(); //vacate the habitation
				this.vacantHabitation.add(this.cellMap.get(getPoint(i))); //Add to vacant houses the current point
				
				Point pointDest = rndmVacantHabitation.getPoint();
				
				this.cellMap.get(pointDest).occupy(currentFamilyColor); //make the dest point occupied
				
				//The dest habitation is no longer vacant
				this.vacantHabitation.remove(rndmVacantHabitation);
			}
		}
	}
	
	public void reInit() {
		this.vacantHabitation.clear();
		this.cellMap.clear();
		initializeMap(getPointsArray(), this.initialColors);
	}
	
	/**
	 * @param originalMap: map to copy
	 * @return the copy of the map
	 */
	private LinkedHashMap<Point, Habitation> copyMap(LinkedHashMap<Point, Habitation> originalMap){
		LinkedHashMap<Point, Habitation> copiedMap = new LinkedHashMap<>();
		for(Map.Entry<Point, Habitation> entries : originalMap.entrySet()) {
			copiedMap.put(entries.getKey(), entries.getValue());
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
        for (Map.Entry<Point, Habitation> entries : this.cellMap.entrySet()) {
        	str.append(entries.getKey().toString() + "->" + entries.getValue().toString() + " ");
        	str.append(System.getProperty("line.separator"));
        }
        str.append("]");
        return str.toString();
	}
}
