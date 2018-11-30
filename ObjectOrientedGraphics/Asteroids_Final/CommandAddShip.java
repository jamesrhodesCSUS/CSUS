package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandAddShip extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;
	
	public CommandAddShip(GameWorld gw) {
		super("Add Ship");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		gameWorld.AddShip();
	}
}
