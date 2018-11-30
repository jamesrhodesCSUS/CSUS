package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.events.ActionEvent;

public class CommandNew extends Command{//See ReadMe for notes on CommandClasses
	public CommandNew(GameWorld gw) {
		super("New");
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		System.out.println("Feature coming soon!");
	}
}
