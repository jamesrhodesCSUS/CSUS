package com.mycompany.a3;

public interface IGameWorld {
	public int GetScore();
	public int GetMissiles();
	public int GetTime();
	public boolean GetSound();
	public void Map();
	public IIterator GetGI();
	public boolean GetIsPaused();
}