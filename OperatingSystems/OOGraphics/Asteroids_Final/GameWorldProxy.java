package com.mycompany.a3;
import java.util.Observable;

/**A proxy which prohibits removal of GameWorldObjects from the GameWorld*/
public class GameWorldProxy extends Observable implements IGameWorld  {
	
	// code here to accept and hold a GameWorld, provide implementations
	// of all the public methods in a GameWorld, forward allowed
	// calls to the actual GameWorld, and reject calls to methods
	// which the outside should not be able to access in the GameWorld.
	
	private GameWorld gameWorld;
	
	public GameWorldProxy (GameWorld gw){ 
		gameWorld = gw; 
		this.setChanged();
	}
	
	//return Score 
	public int GetScore(){
		return gameWorld.GetScore();
	}
	
	//return MissleCount
	public int GetMissiles(){
		return gameWorld.GetMissiles();
	}
	
	//return ClockTime()
	public int GetTime(){
		return gameWorld.GetTime();
	}
	
	//return Sound
	public boolean GetSound(){
		return gameWorld.GetSound();
	}
	
	public void Map(){
		gameWorld.Map();
	}
	
	public IIterator GetGI(){
		return gameWorld.GetGI();
	}
	
	public boolean GetIsPaused(){
		return gameWorld.GetIsPaused();
	}

}