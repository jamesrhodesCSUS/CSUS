package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.Dialog;
import com.codename1.ui.events.ActionEvent;

public class CommandAbout extends Command{//See ReadMe for notes on CommandClasses
	public CommandAbout(GameWorld gw) {
		super("About");
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		Dialog.show("James Rhodes", "CSC 133 Asteroids","Ok", "Ok?");
	}
}
