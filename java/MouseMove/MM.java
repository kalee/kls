/* MouseMove program
 * Created by Kenneth Lee
 * Initially Created 2012
 * Created so current VPN connection doesn't disconnect.  Also works 
 * to show IM connection as active, if you like to be devious.
 * 
 * Tristan sugested addin to only move the mouse 1 pixel.  
 */
import java.awt.*;
import java.util.*;

public class MM {
	private int x=0;
	private int y=0;
	public static void main(String[] args) throws Exception {
		MM mm = new MM();
		mm.setXY();
		Robot hal = new Robot();
		Random random = new Random();
		while(true) {
			int storedX = mm.getX();
			int storedY = mm.getY();
			hal.delay(1000*60);
			mm.setXY();
			if ( (storedX==mm.getX()) && (storedY==mm.getY()) ) {
				int x = mm.getX()+(random.nextInt(3)-1);
				int y = mm.getY()+(random.nextInt(3)-1);
				//If haven't moved, move
				System.out.println("(x,y) = " + x + " , " + y);
				hal.mouseMove(x,y);
				mm.setXY();
			} else {
				System.out.println("Mouse already moved, current position: (x,y) = " + mm.getX() + " , " + mm.getY());
			}	
		}
	}
	
	public void setXY() {
		PointerInfo a = MouseInfo.getPointerInfo();
		Point b = a.getLocation();
		int x = (int) b.getX();
		int y = (int) b.getY();
		setX(x);
		setY(y);
	}

	public void setX(int xval) {
		x = xval;
	}

	public void setY(int yval) {
		y = yval;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}
}

