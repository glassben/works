package net.joker.gridsimulation.schelling;

import java.awt.Point;

/**
 * @author serafith
 * This class represents an habitation (vacant or not), if not vacant we indicate the color of the family.
 */
public class Habitation {

	private boolean isVacant = true; //defaultValue
	private ColorPeople colorPeople;
	private Point point;
	
	public Habitation(Point associatePoint, boolean isVacant, ColorPeople color) {
		this.point = associatePoint;
		this.isVacant = isVacant;
		this.colorPeople = color;
	}
	
	public Point getPoint() {
		return this.point;
	}
	
	public boolean isVacant() {
		return this.isVacant;
	}
	
	public ColorPeople getColor() {
		return this.colorPeople;
	}
	
	public void occupy(ColorPeople color) throws Exception {
		if(isVacant == true) { //empty
			this.isVacant = false;
			this.colorPeople = color;
		} else {
			throw new Exception("Can't occupy a house already occupied !");
		}
	}
	
	public void vacate() throws Exception {
		if(isVacant == false) { //occupied
			this.isVacant = true;
			this.colorPeople = null;
		} else {
			throw new Exception("Can't vacate a house already empty !");
		}
		
	}
	
	@Override
	public String toString() {
		return "[" + String.valueOf(this.isVacant) + ": " + this.colorPeople.toString() + "]";
 	}
}
