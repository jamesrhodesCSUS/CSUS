package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandHyperJump extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;
	
	public CommandHyperJump(GameWorld gw) {
		super("Hyper Jump");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		gameWorld.HyperJump();
	}
}
