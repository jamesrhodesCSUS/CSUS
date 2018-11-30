package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandIncreaseShipSpeed extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;
	
	public CommandIncreaseShipSpeed(GameWorld gw) {
		super("Increase Speed");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		gameWorld.IncreaseShipSpeed();
	}
}
