package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandPrintDisplay extends Command{//See ReadMe for notes on CommandClasses
	private GameWorld gameWorld;
	
	public CommandPrintDisplay(GameWorld gw) {
		super("Print Status");
		gameWorld = gw;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		gameWorld.PrintDisplay();
	}
}
