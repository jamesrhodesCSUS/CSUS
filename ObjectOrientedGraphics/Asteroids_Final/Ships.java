package com.mycompany.a3;

import java.io.IOException;

import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.Graphics;
import com.codename1.ui.Image;
import com.codename1.ui.geom.Point;

/*
 * GameWorld will only have one Ship at any time.
 * Inherits from MoveableObject and implements ISteerable
 * because this is the only class that can be steered.
 * Speed and head are set to 0 while the location is going
 * to be the middle of the GameWorld.
 * Has methods that fire missiles, obtain the number of missiles, 
 * add missiles from the SpaceStation, and implements the methods
 * ChangeHead and ChangeSpeed from ISteerable.  I use this to just call
 * SetHead and SetSpeed because everything sets speed and head the same. 
 */

public class Ships extends MoveableObject implements ISteerable, IDrawable, ICollider{
	private int missiles;
	private final int MAX_MISSILES = 10;
	private int height, width;
	Image spaceship=null;
	
	public Ships(){
		missiles = MAX_MISSILES;
		SetSpeed(0);
		SetHead(180);
		SetColor(ColorUtil.rgb(200, 0, 0));
		SetLocationX(GameWorld.GetMaxWidth()/2);
		SetLocationY(GameWorld.GetMaxHeight()/2);
		height = getImageSize();
		width = getMissileSize();
		try {
			spaceship = Image.createImage("/Spaceship.png");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public void draw(Graphics G, Point p){
		int xLoc = (int) (p.getX()+ this.GetLocationX());// shape location relative
		int yLoc = (int) (p.getY()+ this.GetLocationY());//
		
		G.setColor(GetColor());
		
		G.drawRect(xLoc-(width/2), yLoc-(height/2), width, height);
		//G.drawImage(spaceship, xLoc-(getImageSize()/2), yLoc-(getImageSize()/2), getImageSize(), getImageSize());
	}
	public void FireMissile(){
		this.missiles-=1;
	}
	public int GetMissilies()
	{
		return this.missiles;
	}
	public void Restock(){
		this.missiles = MAX_MISSILES;
	}
	//Calls the more general SetHead
	public void ChangeHead(int h){
		SetHead(h);
	}
	//Calls the more general SetSpeed
	public void ChangeSpeed(int s){
		SetSpeed(s);
	}
	//See GameObject for toString notes.
	public String toString(){
		String parentString = super.toString();
		String myString = "Missiles: " + missiles +" ";
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
		double thisRadius = (this.getImageSize()/2)-6;
		double otherRadius = (((GameObject) other).getImageSize())-10;
		double radiiSqr = (thisRadius*thisRadius + 2*thisRadius*otherRadius + otherRadius*otherRadius);
		if (distBetweenCenterSqr <= radiiSqr)
			result = true;
		return result;
	}
}
