package com.mycompany.a3;
import java.util.Vector;

/*
 * GameObjectCollection uses a vector to add and remove objects
 * Contains the methodsgetIterator to obtain a new iterator each time
 */

public class GameObjectCollection implements ICollection{
	private Vector<GameObject> collection;
	
	public GameObjectCollection() {
		collection = new Vector<GameObject>();
	}

	public void add(GameObject newObject) {
		collection.addElement(newObject);
	}
	
	public void remove(GameObject o) {
		collection.remove(o);
	}
	
	//Vector adds to the beginning, so to remove a missile,
	//I just remove the first missile(s), which are at the end
	//of the vector
	public void removeEnd(GameObject o){
		collection.remove(collection.lastIndexOf(o));
	}

	public IIterator getIterator() {
		return new GameObjectIterator();
	}
	
	private class GameObjectIterator implements IIterator {

		private int currentIndex;
		
		public GameObjectIterator() {
			currentIndex = -1;
		}
		
		public boolean hasNext() {
			if(collection.size() <= 0){
				return false;
			}
			if(currentIndex == collection.size() - 1){
				return false;
			}
			return true;
		}

		public GameObject next() {
			currentIndex++;
			return(collection.elementAt(currentIndex));
		}		
	} // end GameObjectIterator
}
