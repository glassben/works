package net.joker.gridsimulation.conway;

/**
 * @author serafith (alias Trophaigle sur la toile)
 *
 */
public enum CellState {

	ALIVE("Alive", "#1f77b4"),
	DEAD("Dead", "#e5ffcc");
	
	private String stringName;
	private String colorCode;
	
	CellState(String name, String colorCode) {
		this.stringName = name;
		this.colorCode = colorCode;
	}
	
	public String getColorCode() {
		return this.colorCode;
	}
	
	/**
	 * Return String representation of state
	 */
	@Override
	public String toString() {
		return this.stringName;
	}
	
	public boolean isState(CellState state) {
		return this.stringName.equals(state.stringName);
	}
}
