package net.joker.events;

import java.util.ArrayList;
import java.util.Collections;

import net.joker.utils.ColorConsole;
import net.joker.utils.TextComponent;

public class EventManager {

	private long currentDate = 0; 
	
	private ArrayList<Event> collectionEvent = new ArrayList<>();
	private ArrayList<Event> toRemove = new ArrayList<>();
	
	public void addEvent(Event e) {
		this.collectionEvent.add(e);
	}
	
	public boolean isFinished() {
		return this.collectionEvent.isEmpty();
	}
	
	public void next() { 
		currentDate++;
		System.out.println(new TextComponent(ColorConsole.GREEN, "CurrentDate: " + currentDate).getMessage());
		
		/* Thanks to Comparable<Event> we can "sort" events based on their dates, ascending order */
		Collections.sort(this.collectionEvent); 
		
		for(Event e : this.collectionEvent) {
			if(e.getDate() <= currentDate) {
				e.execute();
				this.toRemove.add(e);
			}
		}
		for(Event e : toRemove) {									//bof mais ca eviter acces concurrent dans collectionEvent !
			this.collectionEvent.remove(e);
		}
		this.toRemove.clear();
	}
	
	public void restart() {
		this.collectionEvent.clear();
		this.currentDate = 0;
	}
	
	public long getTimer() {
		return this.currentDate;
	}
}
