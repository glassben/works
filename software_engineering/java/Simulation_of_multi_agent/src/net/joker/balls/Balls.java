package net.joker.balls;

import java.awt.*;

/**
 * @author serafith
 * Manager class of balls
 */
public class Balls {
	//ALT + SHIFT + J pour ajouter JavaDoc
	
	/* Balls are represented by point in the plan */
    private Point[] points;
    private Point[] pointsInitial;

    private int[] dx;
    private int[] dy;
    
    public Balls(Point[] points, int[] dx, int[] dy){
        this.points = points;
        this.dx = dx;
        this.dy = dy;
        pointsInitial = new Point[this.points.length];
        
        for(int i = 0; i < this.pointsInitial.length; i++) {
        	pointsInitial[i] = new Point(this.points[i].x, this.points[i].y);
        }
    }
    
    public void updateState() {
    	 translate(this.dx, this.dy, 770, 500);
    }
    
    /**
     * @param dx 
     * @param dy
     * Permet rebond sur les bords
     */
    public void translate(int[] dx, int[] dy, int xlim, int ylim){
        for (int i = 0; i < this.points.length; i++){
            if(this.points[i].x > xlim || this.points[i].x < 0){
                this.dx[i] = -this.dx[i];
            }
            if(this.points[i].y > ylim || this.points[i].y < 0) {
                this.dy[i] = -this.dy[i];
            }
            this.points[i].translate(dx[i],dy[i]);
        }
    }
    
    public void reInit(){
        for(int i = 0; i < this.points.length; i ++) {
        	copyPoint(this.points[i], this.pointsInitial[i]);
        }
    }
    
    public Point[] getPoints() {
    	return this.points;
    }
    
    
    /**
     * @param p1 destination point
     * @param p2 copied point
     */
    private void copyPoint(Point p1, Point p2) {
    	p1.x = p2.x;
    	p1.y = p2.y;
    }
    
    @Override
    public String toString(){
        StringBuilder str = new StringBuilder();
        str.append("[");
        for (int i = 0; i < this.points.length; i++){
        	str.append(this.points[i].toString());
        	if(i != this.points.length - 1) {str.append(", ");}
        	str.append(System.getProperty("line.separator"));
        }
        str.append("]");
        return str.toString();
    }
}
