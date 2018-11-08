package com.mycompany.a3;

import java.io.IOException;
import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.Graphics;
import com.codename1.ui.Image;
import com.codename1.ui.geom.Point;

/*
 * Inherits from MoveableObject and only has fuelLevel as a individual attribute.
 * Missiles should be removed from the GameWorld if they have 0 fuel.
 * Fuel and color are set, but everything else depends on the ship.
 */

public class Missles extends MoveableObject implements IDrawable, ICollider, ISelectable{
	private int fuelLevel;
	private final int MAX_FUEL = 20;
	Image missile = null;
	private boolean isSelected;
	
	Missles(double ShipXLocation, double ShipYLocation, int ShipHeading){
		fuelLevel = MAX_FUEL;
		SetColor(ColorUtil.rgb(255, 255, 0));
		SetLocationX(ShipXLocation);
		SetLocationY(ShipYLocation);
		SetHead(ShipHeading);
		SetMissileSpeed();
		isSelected=false;
		try {
			missile = Image.createImage("/missile.png");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public void draw(Graphics G, Point p){
		int xLoc = (int) (p.getX()+ this.GetLocationX());// shape location relative
		int yLoc = (int) (p.getY()+ this.GetLocationY());//
		
		G.setColor(GetColor());
		
		if (isSelected)
			G.setColor(ColorUtil.GREEN);
		G.drawLine(xLoc, yLoc-getMissileSize(), xLoc, yLoc+getMissileSize());
		//G.drawImage(missile, xLoc-(getMissileSize()/2), yLoc-(getMissileSize()/2), getMissileSize(), getMissileSize());
	}
	public int GetFuel(){
		return fuelLevel;
	}
	public void DecFuel(){
		fuelLevel-=1;
	}
	public void Refuel(){
		fuelLevel = MAX_FUEL;
	}
	//See GameObject for toString notes.
	public String toString(){
		String parentString = super.toString();
		String myString = "Fuel Level: " + fuelLevel +" ";
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
		double thisRadius = (this.getImageSize()/2)-13;
		double otherRadius = (((GameObject) other).getImageSize())-12;
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