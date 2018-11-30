package com.mycompany.a3;
import java.util.Observable;
import java.util.Observer;
import com.codename1.ui.Container;
import com.codename1.ui.Graphics;
import com.codename1.ui.geom.Point;

/*
 * The MapView is the middle container
 * Unused so far, but Update is called often (indirectly)
 */

public class MapView extends Container implements Observer{
	private double maxWidth;
	private double maxHeight;
	private IGameWorld igw;
	
	public MapView(GameWorld gw){
		igw = gw;
	}

	public void update(Observable o, Object data) {
		this.igw = (IGameWorld) data;
		//igw.Map();
		setWidth((int) maxWidth);
		setHeight((int) maxHeight);
		this.repaint();
	}
	//Paints the objects to the screen using our IIterator from IGameWorld
	public void paint(Graphics G){
		super.paint(G);
		Point pCmpRelPrnt = new Point(getX(),getY());
		IIterator i = igw.GetGI();
		while (i.hasNext() && (i!=null)){
			GameObject obj = i.next();
			((IDrawable)obj).draw(G, pCmpRelPrnt);
			if(igw.GetIsPaused() == false){
				if (obj instanceof Asteroid)
					((Asteroid) obj).setSelected(false);
				if(obj instanceof Missles)
					((Missles) obj).setSelected(false);
			}
		}
	}
	
	public void pointerPressed(int x, int y) {
		x = x - getParent().getAbsoluteX();
		y = y - getParent().getAbsoluteY();
		Point pPtrRelPrnt = new Point(x, y);
		Point pCmpRelPrnt = new Point(getX(), getY());
		if(igw.GetIsPaused()){
			IIterator i = igw.GetGI();
			while(i.hasNext()){
				 GameObject obj = i.next();			    
				 if (obj instanceof Asteroid){
					 if (((Asteroid) obj).contains(pPtrRelPrnt, pCmpRelPrnt)){
					 	((Asteroid) obj).setSelected(true);
					 }
				 }	 	
				 if (obj instanceof Missles){ 	
					 if (((Missles) obj).contains(pPtrRelPrnt, pCmpRelPrnt)){
				 			((Missles) obj).setSelected(true);
				 	 }
				 }
				 repaint(); 
		    }//end while 
		}
	}
	
	public void GetDimensions(double x, double y){
		maxWidth = x;
		maxHeight = y;
	}
}
