package com.mycompany.a3;
import java.util.Random;
import com.codename1.charts.util.ColorUtil;

/*
 * Everything is kept inside of a Vector that is in GameWorld.
 * Every GameObject has a color and a location.  Location is set
 * to random unless it is overridden by an object.
 * The sizes are setup to play in iPhone mode only!
 * I do not scale to iPad
 */

public abstract class GameObject{
	private int color;
	private double locationX;
	private double locationY;
	private final int imageSize = 26;
	private final int missileSize = 14;
	
	public GameObject(){
		locationX = RandLocX();
		locationY = RandLocY();
	}
	public double GetLocationX(){
		return locationX;
	}
	public double GetLocationY(){
		return locationY;
	}
	public int GetColor(){
		return color;
	}
	public void SetLocationX(double x){
		this.locationX = x;
	}
	public void SetLocationY(double y){
		this.locationY = y;
	}
	public void SetColor(int x){
		this.color = x;
	}
	//Tests to see if it gets too close to left/right walls.
	public double RandLocX(){
		Random r = new Random();
		double x = (r.nextInt((int) GameWorld.GetMaxWidth()-imageSize));
		if ((x<(imageSize)))
			x=imageSize+10;
		return x;
	}
	//Tests to see if it gets too close to top/bottom Walls
	public double RandLocY(){
		Random r = new Random();
		double y = (r.nextInt((int) GameWorld.GetMaxHeight()-imageSize));
		if ((y<(imageSize)))
			y=imageSize+10;
		return y;
	}

	public String toString(){
		String myStringLocX = "X Loc: " + Math.round(locationX*10.0)/10.0 +" ";
		String myStringLocY = "Y Loc: " + Math.round(locationY*10.0)/10.0 +" ";
		String myStringColor = "Color: " + "[" + ColorUtil.red(color) + ","
				+ ColorUtil.green(color) + ","
				+ ColorUtil.blue(color) + "] ";
		return myStringLocX + myStringLocY + myStringColor;
	}
	public int getImageSize() {
		return imageSize;
	}
	public int getMissileSize(){
		return missileSize;
	}
}
