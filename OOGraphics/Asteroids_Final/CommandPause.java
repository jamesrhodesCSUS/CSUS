package com.mycompany.a3;
import com.codename1.ui.Command;
import com.codename1.ui.Form;
import com.codename1.ui.events.ActionEvent;
import com.codename1.ui.util.UITimer;

public class CommandPause extends Command{
	private GameWorld realgw;
	private Form realmv;
	private UITimer t;
	public CommandPause(GameWorld gw, UITimer timer, Form mv) {
		super("PausePlay");
		realgw = gw;
		t = timer;
		realmv = mv;
	}
	@Override
	public void actionPerformed(ActionEvent evt){
		if (realgw.GetIsPaused()){
			t.schedule(realgw.GetGameSpeed(), true, realmv);
			realgw.SetIsPaused(false);
		}else{
			t.cancel();
			realgw.SetIsPaused(true);
		}
	}
}
