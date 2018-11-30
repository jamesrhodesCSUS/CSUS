package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandAddMissile extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;
	
	public CommandAddMissile(GameWorld gw) {
		super("Add Missile");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		gameWorld.AddMissile();
	}
}
