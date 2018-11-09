package com.mycompany.a3;

import java.io.IOException;

import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.Graphics;
import com.codename1.ui.Image;
import com.codename1.ui.geom.Point;

/*
 * Inherits from MoveableObject
 * Only has size as a individual attribute,
 * and uses the constructor to set other attributes.
 * Can be selected while paused
 */

public class Asteroid extends MoveableObject implements IDrawable, ICollider, ISelectable{
	private int size;
	private final int MAX_ASTEROID_SIZE = 10;
	Image asteroid = null;
	private boolean isSelected;

	Asteroid(){
		SetSpeed(RandSpeed());
		SetHead(RandHeading());
		SetColor(ColorUtil.rgb(0,0,0));
		isSelected = false;
		size = MAX_ASTEROID_SIZE;
		try {
			asteroid = Image.createImage("/Asteroid.png");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public void draw(Graphics G, Point p){
		int xLoc = (int) (p.getX()+ this.GetLocationX());// shape location relative
		int yLoc = (int) (p.getY()+ this.GetLocationY());
		
		G.setColor(GetColor());
		
		if(isSelected)
			G.fillArc((xLoc - (getImageSize()/2)), (yLoc - (getImageSize()/2)), getImageSize(), getImageSize(), 0, 360);
			//USE FOR IMAGEG.drawImage(asteroid, (xLoc - (getImageSize()/2)), (yLoc - (getImageSize()/2)), getImageSize()+10, getImageSize()+10);
		else
			G.drawArc((xLoc - (getImageSize()/2)), (yLoc - (getImageSize()/2)), getImageSize(), getImageSize(), 0, 360);
			//USE FOR IMAGEG.drawImage(asteroid, (xLoc - (getImageSize()/2)), (yLoc - (getImageSize()/2)), getImageSize(), getImageSize());
	}
	public int GetSize(){
		return size;
	}
	//See GameObject for toString notes.
	public String toString(){
		String parentString = super.toString();
		String myString = "Size: " + size +" ";
		return parentString + myString;
	}
	public boolean collidesWith(ICollider other) {
		boolean result = false;
		double thisCenterX = this.GetLocationX();
		double thisCenterY = this.GetLocationY();
		double otherCenterX = ((GameObject) other).GetLocationX();
		double otherCenterY = ((GameObject) other).GetLocationY();
		double dx = thisCenterX - otherCenterX;
		double dy = thisCenterY - otherCenterY;
		double distBetweenCenterSqr = (dx*dx) + (dy*dy);
		//double thisRadius = (this.getImageSize()/2)-10;
		//double otherRadius = (((GameObject) other).getImageSize())-10;
		double thisRadius = (this.getImageSize()/2)-6;
		double otherRadius = (((GameObject) other).getImageSize())-6;
		if (other instanceof Missles) otherRadius = (((GameObject) other).getImageSize())-10;
		double radiiSqr = (thisRadius*thisRadius + 2*thisRadius*otherRadius + otherRadius*otherRadius);
		if (distBetweenCenterSqr <= radiiSqr)
			result = true;
		return result;
	}
	
	public void setSelected(boolean yesNo){
		isSelected = yesNo; 
	}
	
	public boolean isSelected() {
		return isSelected; 
	}
	
	//Determines whether click lands on/in object
	public boolean contains(Point pPtrRelPrnt, Point pCmpRelPrnt) {
		boolean clickedOn;
		int px = pPtrRelPrnt.getX();
		int py = pPtrRelPrnt.getY();
		double xLoc = GetLocationX();
		double yLoc = GetLocationY();
		if ( (px <= xLoc+(getImageSize()/2)) && (px >= xLoc-(getImageSize()/2)) 
				&& (py <= yLoc+(getImageSize()/2)) && (py >= yLoc-(getImageSize()/2)) )
			clickedOn = true; 
		else 
			clickedOn = false;
		
		if (clickedOn == true && isSelected == true){
			isSelected = false;
			return false;
		}
		return clickedOn;
	}
}
