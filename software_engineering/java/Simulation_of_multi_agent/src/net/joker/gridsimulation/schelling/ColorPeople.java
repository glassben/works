package net.joker.gridsimulation.schelling;

public enum ColorPeople {

	WHITE("White", "#ffffff"),
	YELLOW("Yellow", "#ffff33"),
	RED("Red", "#ff0000"),
	PURPLE("Purple", "#6600cc"),
	GREEN("Green", "#008000");
	
	private String stringName;
	private String colorCode;
	
	ColorPeople(String name, String colorCode) {
		this.stringName = name;
		this.colorCode = colorCode;
	}
	
	public String getColorCode() {
		return this.colorCode;
	}
	
	/**
	 * Return String representation of color
	 */
	@Override
	public String toString() {
		return this.stringName;
	}
}
