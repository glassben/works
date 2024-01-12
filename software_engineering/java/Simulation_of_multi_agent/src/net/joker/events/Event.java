package net.joker.events;

/**
 * @author serafith
 * Comparable to have an order relation between events.
 */
public abstract class Event implements Comparable<Event>{
	
	private long date;
	
	public Event(long date) {
		this.date = date;
	}
	
	public long getDate() {
		return this.date;
	}
	
	public abstract void execute();
	
	//Internet
	//https://www.javatpoint.com/Comparable-interface-in-collection-framework
	
	public int compareTo(Event e1) {
		if(e1.getDate() == this.date) {
			return 0;
		} else if(this.date > e1.getDate()) {
			return 1; //This event is "greater" than e1
		} else {
			return -1; //This event is "lower" than e1
		}
	}
}
