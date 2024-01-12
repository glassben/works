package net.joker.gridsimulation.immigration;

/**
 * @author serafith
 *	Replace CellState of previous simulation
 *  A cell has a state between 1 and n
 */
public class DynamicState {
	
	/* The current state of the class is represented by a number */
	private int currentState;
	
	/*Each instance of this class is associated with a cell (point)*/
	/**
	 * @param numberState
	 * @param initialState : state chosen
	 */
	public DynamicState(int initialState) {
		this.currentState = initialState;
	}
	
	public int getState() {
		return this.currentState;
	}
	
	/**
	 * @return the futur next state of the cell (need when checking if neighbors is cell's next state (k + 1) mod n)
	 */
	public int getNextState() {
		if(this.currentState == CellsImm.nbState) {
			return 1;
		} else {
			return this.currentState + 1;
		}
	}
	
	/**
	 * @param currentState
	 * Update state as explained in the handout
	 */
	public void updateState(int currentState) {
		if(this.currentState == CellsImm.nbState) { //Already at max state
			this.currentState = 1;
		} else {
			this.currentState++;
		}
	}
	
	
	
	@Override
	public String toString() {
		return String.valueOf(this.currentState);
	}
}
