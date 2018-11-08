package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandAddStation extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;
	
	public CommandAddStation(GameWorld gw) {
		super("Add Station");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		gameWorld.AddStation();
	}

}
