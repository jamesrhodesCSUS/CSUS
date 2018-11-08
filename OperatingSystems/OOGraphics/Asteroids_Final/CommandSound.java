package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandSound extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;
	
	public CommandSound(GameWorld gw){
		super("Sound");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		if(!gameWorld.GetIsPaused())
			gameWorld.ChangeSound();
	}
}
