package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandRefuel extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;
	
	public CommandRefuel(GameWorld gw){
		super("Refuel (Pause Only");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		gameWorld.RefuelMissiles();
	}
}
