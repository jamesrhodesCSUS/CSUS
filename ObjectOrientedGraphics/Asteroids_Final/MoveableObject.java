package com.mycompany.a3;

import java.util.Random;
/*
 * MoveableObject extends from GameObject and implements IMoveable.
 * it implements IM because every object from here and below can move,
 * but not all can steer.  It has speed and head which are set to random
 * unless another object overrides in its constructor.  The final ints
 * are here just to easily and quickly set the maximums for various
 * attributes.  See below notes for more information.
 */

public abstract class MoveableObject extends GameObject implements IMoveable{
	private int speed;
	private int heading;
	private final int MAX_SPEED=5;
	private final int MIN_SPEED=0;
	private final int MAX_HEADING=359;
	private final int MIN_HEADING=0;
	
	MoveableObject(){
		SetSpeed(RandSpeed());
		SetHead(RandHeading());
	}
	
	public int GetSpeed(){
		return speed;
	}
	public int GetHead(){
		return heading;
	}
	public int GetMaxSpeed(){
		return MAX_SPEED;
	}
	/*
	 * Speed can only be between 0 and 10 inclusive.
	 */
	public void SetSpeed(int s){
		if (s>MAX_SPEED)
			this.speed = MAX_SPEED;
		else if (s<MIN_SPEED)
			this.speed = MIN_SPEED;
		else
			this.speed = s;
	}
	public void SetMissileSpeed(){
		this.speed = 15;
	}
	/*
	 * Heading can only be between 0 and 359, inclusive.
	 * If it gets a value outside of that, it either
	 * adds or subtracts 360 until it gets a value
	 * that is acceptable.
	 */
	public void SetHead(int h){
		while (h < MIN_HEADING) h+=360;
		while (h > MAX_HEADING) h-=360;
		heading = h;
	}
	public int RandSpeed(){
		Random r = new Random();
		return (r.nextInt(MAX_SPEED));
	}
	public int RandHeading(){
		Random r = new Random();
		return (r.nextInt(MAX_HEADING));
	}
	//See GameObject for toString notes.
	public String toString(){
		String parentString = super.toString();
		String myStringS = "Speed: " + speed +" ";
		String myStringH = "Heading: " + heading +" ";
		return parentString + myStringS + myStringH;
	}
	//Move is here because everything in Move able can, you guessed it, move.
	public void move(int elapsedTime){
		double dist = (speed) * ((double) elapsedTime/100);
		double theta = Math.toRadians(90-heading);
		double deltaX = (Math.cos(theta))*dist;
		double deltaY = (Math.sin(theta))*dist;
		
		if ((deltaX + GetLocationX() + (getImageSize()/2) > GameWorld.GetMaxWidth()) || (deltaX + GetLocationX() - (getImageSize()/2) < 0)){
			deltaX = -deltaX;
			SetHead(360-heading);
		}
		
		if ((deltaY + GetLocationY() + (getImageSize()/2) > GameWorld.GetMaxHeight()) || (deltaY + GetLocationY() - (getImageSize()/2) < 0)){
			deltaY = -deltaY;
			SetHead(180-heading);
		}
		
		double xBound = (GetLocationX() + deltaX);
		double yBound = (GetLocationY() + deltaY);
		
		SetLocationX(xBound);
		SetLocationY(yBound);
	}
}