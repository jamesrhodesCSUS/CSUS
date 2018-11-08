package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandTurnShipRight extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;

	public CommandTurnShipRight(GameWorld gw) {
		super("Turn Right");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		gameWorld.TurnShipRight();
	}
}
