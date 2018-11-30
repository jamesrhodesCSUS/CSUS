package com.mycompany.a3;
import java.io.IOException;
import java.util.Random;

import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.Graphics;
import com.codename1.ui.Image;
import com.codename1.ui.geom.Point;

/*
 * SpaceStation inherits from FixedObject and has
 * blinkRate and blink. BlinkRate determines how long until
 * the station will blink (5 means switch in 5 game ticks)
 * and blink is true when it is 'lit up.'
 * See FixedObject on how it implements an ID number.
 */

public class SpaceStation extends FixedObject implements IDrawable, ICollider{
	private int blinkRate;
	private final int MAX_BLINK_RATE = 10;
	private boolean blink;
	Image spaceStationOn = null;
	Image spaceStationOff = null;
	
	SpaceStation(){
		SetID();
		blinkRate = RandBR();
		SetColor(ColorUtil.rgb(153, 0, 153));
		blink = true;
		try {
			spaceStationOn = Image.createImage("/Station_ON.png");
			spaceStationOff = Image.createImage("/Station_OFF.png");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	public void draw(Graphics G, Point p){
		int xLoc = (int) (p.getX()+ this.GetLocationX());// shape location relative
		int yLoc = (int) (p.getY()+ this.GetLocationY());//
		
		G.setColor(GetColor());
		
		if (blink)
			G.fillRect(xLoc-(getImageSize()/2), yLoc-(getImageSize()/2), getImageSize(), getImageSize());
			//G.drawImage(spaceStationOn, xLoc-(getImageSize()/2), yLoc-(getImageSize()/2), getImageSize(), getImageSize());
		else
			G.drawRect(xLoc-(getImageSize()/2), yLoc-(getImageSize()/2), getImageSize(), getImageSize());
			//G.drawImage(spaceStationOff, xLoc-(getImageSize()/2), yLoc-(getImageSize()/2), getImageSize(), getImageSize());
	}
	public int GetBR(){
		return blinkRate;
	}
	public int RandBR(){
		Random r = new Random();
		return r.nextInt(MAX_BLINK_RATE);
	}
	public void Blink(){
		if (blink==true)
			blink = false;
		else
			blink = true;
	}
	//See GameObject for toString notes.
	public String toString(){
		String parentString = super.toString();
		String myString = "Blink Rate: " + blinkRate +" ";
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
		double thisRadius = (this.getImageSize()/2)-10;
		double otherRadius = (((GameObject) other).getImageSize())-10;
		double radiiSqr = (thisRadius*thisRadius + 2*thisRadius*otherRadius + otherRadius*otherRadius);
		if (distBetweenCenterSqr <= radiiSqr)
			result = true;
		return result;
	}
}
