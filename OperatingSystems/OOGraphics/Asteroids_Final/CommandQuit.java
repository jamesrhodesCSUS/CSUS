package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.Dialog;
import com.codename1.ui.Display;
import com.codename1.ui.events.ActionEvent;

public class CommandQuit extends Command{//See ReadMe for notes on CommandClasses
	public CommandQuit() {
		super("Quit");
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		Boolean bOk = Dialog.show("Confirm quit", "Are you sure you want to quit?","Ok", "Cancel");
		if (bOk){
			Display.getInstance().exitApplication();
		}
	}
}