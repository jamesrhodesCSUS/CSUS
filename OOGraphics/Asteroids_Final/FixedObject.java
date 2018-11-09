package com.mycompany.a3;

/*
 * FixedObject inherits from GameObject and has attributes
 * available and id.
 * Available starts at one and is static because
 * every FixedObject should have the same basis on
 * where the ID numbers start.  As soon as an ID number is taken,
 * available in incremented and can be used for another fixed object.
 */

public abstract class FixedObject extends GameObject{
	private static int available=0;
	private int id;
	
	public FixedObject(){
		id = available;
		available +=1;
	}
	public int GetID(){
		return id;
	}
	public void SetID(){
		this.id = available;
		available +=1;
	}
	//See GameObject for toString notes.
	public String toString(){
		String parentString = super.toString();
		String myString = "ID: " + id +" ";
		return parentString + myString;
	}
}
