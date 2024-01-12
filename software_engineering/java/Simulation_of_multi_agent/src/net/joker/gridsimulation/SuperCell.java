package net.joker.gridsimulation;

import java.awt.Point;
import java.util.LinkedHashSet;
import java.util.Set;

/**
 * @author serafith
 * SuperClass of Cell, all class that represent a cell are daughter of this class
 * This class manages the points in the plan and provides a method to get neighbors of a point
 */
public class SuperCell {

	private Point[] points;
	private int widthGrid;
	private int totalPoints;
	
	public SuperCell(Point[] points, int widthGrid, int totalPoint) {
		this.points = points;
		this.widthGrid = widthGrid;
		this.totalPoints = totalPoint;
	}
	
	public Point getPoint(int i) {
		return this.points[i];
	}
	
	public int getTotalPoint() {
		return this.totalPoints;
	}
	
	public Point[] getPointsArray() {
		return this.points;
	}
	
	public Set<Point> getNeighBors(int i) {
		
		Point pUp = null; Point pDown = null; Point pRight = null; Point pLeft = null; Point pUpRight = null; Point pUpLeft = null; Point pDownRight = null; Point pDownLeft = null;
		
		//Generate neighbourdhood of the current cell
		Set<Point> neighborhood = new LinkedHashSet<Point>(8); //Ordered set noralement -> Pour visualiser les voisins j'ai besoin de l'ordre d insertion
	
		if(!isOnBorder(i)) {
			pUp = this.points[i - this.widthGrid]; 				
			pDown = this.points[i + this.widthGrid]; 			
			pRight = this.points[i + 1]; 						
			pLeft = this.points[i - 1]; 						
			pUpRight = this.points[(i - this.widthGrid) + 1]; 	
			pUpLeft = this.points[(i - this.widthGrid) - 1]; 	
			pDownRight = this.points[(i + this.widthGrid) + 1]; 
			pDownLeft = this.points[(i + this.widthGrid) - 1]; 	
			
		} else {
			//Ici il faut prendre en compte le fait que la grille est "circulaire"
			
			//Trouver les voisins circulairement - NE PAS FACTORISER le code POUR DES RAISONS DE LISIBILITé !!!!
			
			if(isOnUpsideBorder(i)) { //Top Row
				
				if(!isOnRightBorder(i) && !isOnLeftBorder(i)) {//Not a corner of top row
					pUp = this.points[this.totalPoints - this.widthGrid + i]; 
					pDown = this.points[i + this.widthGrid];				 
					pRight = this.points[i + 1];							
					pLeft = this.points[i - 1];								
					pUpRight = this.points[(this.totalPoints - this.widthGrid + i) + 1]; 
					pUpLeft = this.points[(this.totalPoints - this.widthGrid + i) - 1];  
					pDownRight = this.points[(i + this.widthGrid) + 1];
					pDownLeft = this.points[(i + this.widthGrid) - 1];
					
				} else if(isOnRightBorder(i)) { //Top Right corner
					pUp = this.points[this.totalPoints - 1]; 
					pDown = this.points[i + this.widthGrid];
					pRight = this.points[0];
					pLeft = this.points[i - 1];	
					pUpRight = this.points[this.totalPoints - this.widthGrid];
					pUpLeft = this.points[(this.totalPoints - this.widthGrid + i) - 1];
					pDownRight = this.points[i + 1];
					pDownLeft = this.points[(i + this.widthGrid) - 1];
					
				} else { //Top left corner
					pUp = this.points[this.totalPoints - this.widthGrid];
					pDown = this.points[i + this.widthGrid]; // ICI i = 0 car c'est top left corner
					pRight = this.points[i + 1];
					pLeft = this.points[this.widthGrid - 1];
					pUpRight = this.points[(this.totalPoints - this.widthGrid) + 1];
					pUpLeft = this.points[this.totalPoints - 1];
					pDownRight = this.points[(i + this.widthGrid) + 1];
					pDownLeft = this.points[(i + this.widthGrid) + this.widthGrid - 1];
					
				}
				
			} else if(isOnDownsideBorder(i)) { //Bottom row
				
				if(!isOnRightBorder(i) && !isOnLeftBorder(i)) {//Not a corner of bottom row
					pUp = this.points[i - this.widthGrid];
					pDown = this.points[this.widthGrid - (this.totalPoints - i)];
					pRight = this.points[i + 1];
					pLeft = this.points[i - 1];
					pUpRight = this.points[(i - this.widthGrid) + 1];
					pUpLeft = this.points[(i - this.widthGrid) - 1];
					pDownRight = this.points[this.widthGrid - (this.totalPoints - i) + 1];
					pDownLeft = this.points[this.widthGrid - (this.totalPoints - i) - 1];
					
				} else if(isOnRightBorder(i)) { //Bottom right corner
					pUp = this.points[i - this.widthGrid];
					pDown = this.points[this.widthGrid - 1];
					pRight = this.points[this.totalPoints - this.widthGrid];
					pLeft = this.points[i - 1];
					pUpRight = this.points[(i - this.widthGrid) - (this.widthGrid - 1)];
					pUpLeft = this.points[(i - this.widthGrid) - 1];
					pDownRight = this.points[0];
					pDownLeft = this.points[(this.widthGrid - 1) - 1];
					
				} else { //Bottom left corner
					pUp = this.points[i - this.widthGrid];
					pDown = this.points[0];
					pRight = this.points[i + 1];
					pLeft = this.points[this.totalPoints - 1];
					pUpRight = this.points[(i - this.widthGrid) + 1];
					pUpLeft = this.points[(i - this.widthGrid) + (this.widthGrid - 1)];
					pDownRight = this.points[1];
					pDownLeft = this.points[this.widthGrid - 1];
				}
				
			} else {
				
				if(isOnRightBorder(i)) { //Right border, not a corner
					pUp = this.points[i - this.widthGrid];
					pDown = this.points[i + this.widthGrid];
					pRight = this.points[i - (this.widthGrid - 1)];
					pLeft = this.points[i - 1];
					pUpRight = this.points[(i - this.widthGrid) - (this.widthGrid - 1)];
					pUpLeft = this.points[(i - this.widthGrid) - 1];
					pDownRight = this.points[(i + this.widthGrid) - (this.widthGrid - 1)];
					pDownLeft = this.points[(i + this.widthGrid) - 1];
					
				} else { // Left border, not a corner
					pUp = this.points[i - this.widthGrid];
					pDown = this.points[i + this.widthGrid];
					pRight = this.points[i + 1];
					pLeft = this.points[i + (this.widthGrid - 1)];
					pUpRight = this.points[(i - this.widthGrid) + 1];
					pUpLeft = this.points[(i - this.widthGrid) + (this.widthGrid - 1)];
					pDownRight = this.points[(i + this.widthGrid) + 1];
					pDownLeft = this.points[(i + this.widthGrid) + (this.widthGrid - 1)];
					
				}
			}
		}
		neighborhood.add(pUp);
		neighborhood.add(pDown);
		neighborhood.add(pRight);
		neighborhood.add(pLeft);
		neighborhood.add(pUpRight);
		neighborhood.add(pUpLeft);
		neighborhood.add(pDownRight);
		neighborhood.add(pDownLeft);
		
		return neighborhood;
	}
	
	/**
	 * @param indexPoint
	 * @return true if point with index "indexPoint" is on the border of the grid
	 */
	private boolean isOnBorder(int indexPoint) {
		//In point on left side of the grid || right side || up side || down side
		if((indexPoint % this.widthGrid == 0) || 
				((indexPoint + 1) % this.widthGrid == 0) ||
				(indexPoint <= (this.widthGrid - 1)) || 
				(indexPoint >= (this.totalPoints - this.widthGrid))) {
			return true;
		}
		return false;
	}
	
	private boolean isOnRightBorder(int indexPoint) {
		return (indexPoint + 1) % this.widthGrid == 0;
	}
	
	private boolean isOnLeftBorder(int indexPoint) {
		return indexPoint % this.widthGrid == 0;
	}
	
	private boolean isOnUpsideBorder(int indexPoint) {
		return indexPoint <= (this.widthGrid - 1);
	}
	
	private boolean isOnDownsideBorder(int indexPoint) {
		return indexPoint >= (this.totalPoints - this.widthGrid);
	}
	
}
