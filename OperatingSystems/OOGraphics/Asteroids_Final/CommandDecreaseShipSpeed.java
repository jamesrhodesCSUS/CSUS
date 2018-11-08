package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandDecreaseShipSpeed extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;
	
	public CommandDecreaseShipSpeed(GameWorld gw) {
		super("Decrease Speed");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		gameWorld.DecreaseShipSpeed();
	}
}
