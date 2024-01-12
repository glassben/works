package net.joker.balls;

import java.awt.Color ;
import java.awt.Point;
import gui.GUISimulator ;
import net.joker.events.EventManager;

/**
 * @author serafith
 * Generate entries for a ball simulation
 * 
 */
public class TestBallsSimulator {
   
    public static void testBallsSimulator() {

        GUISimulator gui = new GUISimulator(500, 500, Color.BLACK);

        Point[] array = new Point[3];

        array[0] = new Point(10,10);
        array[1] = new Point(50,43);
        array[2] = new Point(14,100);

        int[] dx = new int[3];
        int[] dy = new int[3];
        for(int i = 0; i < 3; i++){
            dx[i] = 10;
            dy[i] = 10;
        }
        Balls balls = new Balls(array, dx, dy);

        EventManager eM = new EventManager();
        eM.addEvent(new BallEvent(0, balls));

        gui.setSimulable(new BallsSimulator(balls, gui, eM));
    }
}