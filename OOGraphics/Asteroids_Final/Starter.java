package com.mycompany.a3;
import com.codename1.ui.Display;
import com.codename1.ui.Form;
import com.codename1.ui.Dialog;
import com.codename1.ui.plaf.UIManager;
import com.codename1.ui.util.Resources;
import com.codename1.ui.Toolbar;

/* This is the main class.
 * The method start() initiates a new Game().
 */
public class Starter {
    private Form current;
    @SuppressWarnings("unused")
	private Resources theme;
    
    public void init(Object context) {
        theme = UIManager.initFirstTheme("/theme");
        Toolbar.setGlobalToolbar(true);
    }
    public void start() {
        if(current != null){
            current.show();
            return;
        }
        new Game();
    }
    public void stop() {
        current = Display.getInstance().getCurrent();
        if(current instanceof Dialog) {
            ((Dialog)current).dispose();
            current = Display.getInstance().getCurrent();
        }
    }
    public void destroy() {
    }
}
