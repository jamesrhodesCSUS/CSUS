package com.mycompany.a3;

public interface ICollection {
	public void add(GameObject o);
	public void remove(GameObject o);
	public void removeEnd(GameObject o);
	public IIterator getIterator();
}
