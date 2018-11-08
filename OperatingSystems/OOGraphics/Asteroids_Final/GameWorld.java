package com.mycompany.a3;
import java.util.Observable;
import java.util.Vector;

import com.codename1.ui.Dialog;
import com.codename1.ui.Display;

public class GameWorld extends Observable implements IGameWorld{
	private int score;
	private int lives;
	private int gameClock;
	private boolean sound = false;
	private boolean isPaused;
	
	private GameObjectCollection gameObjects;
	private Vector<GameObject> toDelete;
	
	private static double MAX_WIDTH;
	private static double MAX_HEIGHT;
	private final int MAX_LIVES = 3;
	
	SoundBG sbg;//Background sound
	Sound gameSound;//Other game sounds
	
	private int gameSpeed;//Passed to the schedule method in Game
	
	public GameWorld(){
		gameObjects = new GameObjectCollection();
		toDelete = new Vector<GameObject>();
		lives = MAX_LIVES;
		score = 0;
		gameClock = 0;
		sbg = new SoundBG("Auxiliary Hydraulic Brake Pump.wav");
		gameSpeed = 100;
		isPaused = false;
	}
	
	public void init(){}
	
	public IIterator GetGI(){
		IIterator i = gameObjects.getIterator();
		return i;
	}
	
	public void SetDimensions(double width, double height){
		MAX_WIDTH = width;
		MAX_HEIGHT = height;
	}
	
	//Creates a new ship, only one allowed.
	public void AddShip(){
		if(isPaused)
			return;
		if (FindShip()==false){
			GameObject newShip = new Ships();
			gameObjects.add(newShip);
			Map();
			ProxyUpdate();
		}
	}
	
	//Adds a space station, only one allowed.
	public void AddStation(){
		if(isPaused)
			return;
		if (FindSS() == false){
			GameObject newStation = new SpaceStation();
			gameObjects.add(newStation);
			Map();
			ProxyUpdate();
		}
	}
	
	//Adds an asteroid, many can be created.
	public void AddAsteroid(){
		if(isPaused)
			return;
		GameObject newAsteroid = new Asteroid();
		gameObjects.add(newAsteroid);
		Map();
		ProxyUpdate();
	}
	
	//Creates a missile.  Is not directly called, is called when a ship decides to fire a missile.
	public void AddMissile(){
		if(isPaused)
			return;
		Ships s = (Ships) ShipSpot();
		MoveableObject newMissile = new Missles(s.GetLocationX(), s.GetLocationY(), s.GetHead());
		gameObjects.add(newMissile);
		Map();
		ProxyUpdate();
	}
	
	//Checks if we have a ship, then increases speed by 1
	public void IncreaseShipSpeed(){
		if(isPaused)
			return;
		if (FindShip()){
			Ships s = (Ships) ShipSpot();
			s.ChangeSpeed(s.GetSpeed()+1);
			Map();
			ProxyUpdate();
		}
	}
	
	//Checks if we have a ship, then decreases by 1
	public void DecreaseShipSpeed(){
		if(isPaused)
			return;
		if (FindShip()){
			Ships s = (Ships) ShipSpot();
			s.ChangeSpeed(s.GetSpeed()-1);
			Map();
			ProxyUpdate();
		}
	}
	
	//Turns ship to the left by 5 degrees.
	//If heading is 0, will be 355 and if is 4, will be 359.
	public void TurnShipLeft(){
		if(isPaused)
			return;
		if (FindShip()){
			Ships s = (Ships) ShipSpot();
			s.ChangeHead(s.GetHead()+10);
			Map();
			ProxyUpdate();
		}
	}
	
	//Will turn ship to the right by 5 degrees.
	//If heading == 359, will now be 4.
	public void TurnShipRight(){
		if(isPaused)
			return;
		if (FindShip()){
			Ships s = (Ships) ShipSpot();
			s.ChangeHead(s.GetHead()-10);
			Map();
			ProxyUpdate();
		}
	}
	
	//If there is a ship, it will fire a missile (creates first)
	//If missiles==0, it does nothing.
	public void FireMissle(){
		if(isPaused)
			return;
		if (FindShip()){
			Ships s = (Ships) ShipSpot();
			if (s.GetMissilies() > 0){
				AddMissile();
				s.FireMissile();
				if (sound){
					gameSound = new Sound("MISSILE3.WAV");
					gameSound.play();
				}
				Map();
				ProxyUpdate();
			}
		}
	}
	
	//Sets the ships location to half of the max screen width and height.
	public void HyperJump(){
		if(isPaused)
			return;
		if (FindShip()){
			Ships s = (Ships) ShipSpot();
			s.SetLocationX(MAX_WIDTH/2);
			s.SetLocationY(MAX_HEIGHT/2);
			Map();
			ProxyUpdate();
		}
	}
	
	//Moves the game clock forward by one,
	//updates the objects location based on speed and heading,
	//tells a SS to blink if it is time,
	//and updates the fuel level on missiles and deletes them if necessary.
	//Detects collision
	public void TickClock(){
		gameClock +=1;
		ProxyUpdate();
		IIterator iM = gameObjects.getIterator();
		boolean remove = false;
		if (iM.hasNext() == false)
			return;
		else{
			Object currentObj = new Object();
			while (iM.hasNext()){
				currentObj = iM.next();
				if (currentObj instanceof IMoveable){
					IMoveable mObj = (IMoveable) currentObj;
					mObj.move(gameSpeed);
				}
			}
		
			if (FindMissile()){
				GameObject m;
				IIterator i = gameObjects.getIterator();
				while(i.hasNext()){
					m = i.next();
					if (m instanceof Missles)
						((Missles) m).DecFuel();
				}
				CheckMissiles();
			}
			
			if (FindSS()){
				SpaceStation ss = (SpaceStation) SSSpot();
				if (gameClock % ss.GetBR() == 0)
					ss.Blink();
			}
			//Start collision
			IIterator iter = gameObjects.getIterator();
			while(iter.hasNext()){
				ICollider current = (ICollider)iter.next();
				IIterator iter2 = gameObjects.getIterator();
				
				while(iter2.hasNext()){
					ICollider other = (ICollider) iter2.next();
					
					if(current instanceof Asteroid && other instanceof Asteroid && current!=other){
						if(current.collidesWith(other) && !(toDelete.contains(current) && toDelete.contains(other))){
							toDelete.add((GameObject)current);
							toDelete.add((GameObject)other);
							remove = true;
						}
					}else if((current instanceof Asteroid && other instanceof Ships || other instanceof Ships && current instanceof Asteroid)
							&& !(toDelete.contains(current) && toDelete.contains(other))){
						if(current.collidesWith(other)){
							if(current instanceof Ships){
								toDelete.add((GameObject)current);
								toDelete.add((GameObject)other);
							}else{
								toDelete.add((GameObject)other);
								toDelete.add((GameObject)current);
							}
							remove = true;
						}
					}else if((current instanceof Missles && other instanceof Asteroid) || (current instanceof Asteroid && other instanceof Missles)){
						if (!(toDelete.contains(current)) && (current instanceof Missles || other instanceof Missles))
							if(current.collidesWith(other)){
								score+=100;
								if(current instanceof Missles){
									toDelete.add((GameObject)current);
									toDelete.add((GameObject)other);
								}else{
									toDelete.add((GameObject)other);
									toDelete.add((GameObject)current);
								}
								if (sound){
									gameSound = new Sound("IMPACT.WAV");
									gameSound.play();
								}
								remove = true;
							}
					}else if((current instanceof SpaceStation && other instanceof Ships) || (current instanceof Ships && other instanceof SpaceStation)){
						if(current.collidesWith(other)){
							Ships s;
							if(current instanceof Ships){
								s = (Ships) current;
								s.Restock();
							}else{
								s = (Ships) other;
								s.Restock();
							}
						}
					}
				}
			}
		}
		if (remove)//If it is necessary to remove items
			Remove();
		
		if (gameClock % 15 == 0)
			Map();//Will print occasionally!
		
		ProxyUpdate();
	}
	
	//displays score, elapsed time, and if possible, the missiles your ship has.
	public void PrintDisplay(){
		System.out.println("Current Score: " + score);
		System.out.println("Time elapsed: " + gameClock);
		System.out.println("Lives left: " + lives);
		if (FindShip()){
			Ships s = (Ships) ShipSpot();
			System.out.println("Your ship has " + s.GetMissilies() + " missiles");
		}
		else
			System.out.println("Currently you have no ship.");
	}
	
	//Goes through and finds each object and displays them.
	//It starts with the bottom level of toString, and works its way up until
	//it reaches the toString in each gameobject class.
	//EX: Ship = Ships -> MoveableObject -> GameObject
	//Each class displays the attributes with that class.
	public void Map(){
		// get an iterator for the collection
		IIterator anIteratorS = gameObjects.getIterator();
		
		// placeholder object
		Object currentObj = new Object();
		if (anIteratorS.hasNext() == false)
			System.out.println("Nothing to print!");
		else{
			System.out.println("\nTheMap!\n");
			if(FindShip()){
			// iterate through, and print each one
				System.out.println("Ship:");
				while(anIteratorS.hasNext() ){
					currentObj = anIteratorS.next();
					if (currentObj instanceof Ships){
						System.out.println(currentObj.toString());
						break;
					}
				}
				System.out.println();
			}
			if(FindSS()){
				IIterator anIteratorSS = gameObjects.getIterator();
				System.out.println("Space Station:");
				while(anIteratorSS.hasNext() ){
					currentObj = anIteratorSS.next();
					if (currentObj instanceof SpaceStation){
						System.out.println(currentObj.toString());
						break;
					}
				}
				System.out.println();
			}
			if(FindAsteroid()){
				IIterator anIteratorA = gameObjects.getIterator();
				System.out.println("Asteroids:");
				while(anIteratorA.hasNext() ){
					currentObj = anIteratorA.next();
					if (currentObj instanceof Asteroid)
						System.out.println(currentObj.toString() );
				}
				System.out.println();
			}
			if(FindMissile()){
				IIterator anIteratorM = gameObjects.getIterator();
				System.out.println("Missiles:");
				while(anIteratorM.hasNext() ){
					currentObj = anIteratorM.next();
					if (currentObj instanceof Missles)
						System.out.println(currentObj.toString() );
				}
				System.out.println();
			}
		}
	}
	
	//Start auxiliary methods.
	//Returns true if there is a ship
	public boolean FindShip(){
		IIterator i = gameObjects.getIterator();
		while (i.hasNext())
			if (i.next() instanceof Ships){
				return true;
			}
		return false;
	}
	
	//Returns true if there is an asteroid
	public boolean FindAsteroid(){
		IIterator i = gameObjects.getIterator();
		while (i.hasNext())
			if (i.next() instanceof Asteroid){
				return true;
			}
		return false;
	}
	
	//Returns true if there is a missile
	public boolean FindMissile(){
		IIterator i = gameObjects.getIterator();
		while (i.hasNext())
			if (i.next() instanceof Missles){
				return true;
			}
		return false;
	}
	
	//Returns true if there is a SS
	public boolean FindSS(){
		IIterator i = gameObjects.getIterator();
		while (i.hasNext())
			if (i.next() instanceof SpaceStation){
				return true;
			}
		return false;
	}
	
	//Returns the actual ship
	public GameObject ShipSpot(){
		IIterator i = gameObjects.getIterator();
		GameObject ship;
		while (i.hasNext()){
			ship = i.next();
			if (ship instanceof Ships)
				return ship;
		}
		return null;
	}
	
	//Returns an actual asteroid
	public GameObject AsteroidSpot(){
		IIterator i = gameObjects.getIterator();
		GameObject asteroid;
		while (i.hasNext()){
			asteroid = i.next();
			if (asteroid instanceof Asteroid)
				return asteroid;
		}
		return null;
	}
	
	//Returns an actual missile
	public GameObject MissileSpot(){
		IIterator i = gameObjects.getIterator();
		GameObject missile;
		while (i.hasNext()){
			missile = i.next();
			if (missile instanceof Missles)
				return missile;
		}
		return null;
	}
	
	//Returns the actual SpaceStation
	public GameObject SSSpot(){
		IIterator i = gameObjects.getIterator();
		GameObject ss;
		while (i.hasNext()){
			ss = i.next();
			if (ss instanceof SpaceStation)
				return ss;
		}
		return null;
	}	
	//Returns the max width for lower methods
	public static double GetMaxWidth(){
		return MAX_WIDTH;
	}
	
	//returns the max height for lower methods
	public static double GetMaxHeight(){
		return MAX_HEIGHT;
	}
	
	//returns score
	public int GetScore(){
		return score;
	}
	
	//returns lives
	public int GetLives(){
		return lives;
	}
	
	//returns elapsed time
	public int GetTime(){
		return gameClock;
	}
	
	//returns if sound is on
	public boolean GetSound(){
		return sound;
	}
	public void TurnSoundOff(){
		sound = false;
		sbg.pause();
	}
	
	//gets missiles
	public int GetMissiles(){
		if (FindShip()){
			Ships s = (Ships) ShipSpot();
			return s.GetMissilies();
		}
		else
			return 0;
	}
	//Changes sound
	public void ChangeSound(){
		if(isPaused){
			sbg.pause();
			return;
		}else{
			if (sound){
				sound = false;
				sbg.pause();
				System.out.println("Sound is now off!");
			}
			else{
				sound = true;
				sbg.play();
				System.out.println("Sound is now on!");
			}
		}
		ProxyUpdate();
	}
	
	public boolean GetIsPaused(){
		return isPaused;
	}
	public void SetIsPaused(boolean s){
		isPaused = s;
		if (s==true)
			sbg.pause();	
	}
	
	//This is placed in most GW methods
	//Updates the Proxy
	public void ProxyUpdate(){
		this.setChanged();
		GameWorldProxy gwProxy = new GameWorldProxy(this);
		this.notifyObservers(gwProxy);
	}
	
	public int GetGameSpeed(){
		return gameSpeed;
	}
	
	public void CheckMissiles(){
		IIterator i = gameObjects.getIterator();
		GameObject m;
		if (i.hasNext() == false)
			return;
		else{
			while(i.hasNext()){
				m = i.next();
				if (m instanceof Missles && ((Missles) m).GetFuel() == 0){
					gameObjects.removeEnd(m);
					CheckMissiles();
					break;
				}
			}
		}
		Map();
	}
	//Removes objects from game
	//Will display score if game over,
	//Will add a ship if need be
	public void Remove(){
		boolean addShip=false;
		while(!toDelete.isEmpty()){
			if(toDelete.firstElement() instanceof Ships){
				addShip = true;
				lives-=1;
			}
			gameObjects.remove((GameObject)toDelete.firstElement());
			toDelete.remove(0);
		}
		if (lives == 0){
			String scorestring = "Your final Score is " + score;
			Dialog.show("Great Job!", scorestring,"For Playing", "Thank You");
			if (sound){
				gameSound = new Sound("AhUneProute3.wav");
				gameSound.play();
			}
			Display.getInstance().exitApplication();
		}
		if (addShip)
			AddShip();
		Map();
		ProxyUpdate();
	}
	
	public void RefuelMissiles(){
		if (isPaused == false)
			return;
		IIterator i = gameObjects.getIterator();
		GameObject m;
		while(i.hasNext()){
			m = i.next();
			if (m instanceof Missles)
				if (((Missles) m).isSelected())
					((Missles) m).Refuel();
		}
		Map();
		ProxyUpdate();
	}
}