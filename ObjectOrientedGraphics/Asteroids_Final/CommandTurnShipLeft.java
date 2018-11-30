package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandTurnShipLeft extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;
	
	public CommandTurnShipLeft(GameWorld gw) {
		super("Turn Left");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		gameWorld.TurnShipLeft();
	}
}
