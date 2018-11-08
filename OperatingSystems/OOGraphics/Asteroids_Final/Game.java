package com.mycompany.a3;
import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.CheckBox;
import com.codename1.ui.Command;
import com.codename1.ui.Form;
import com.codename1.ui.layouts.BorderLayout;
import com.codename1.ui.plaf.Border;
import com.codename1.ui.util.UITimer;
import com.codename1.ui.TextField;
import com.codename1.ui.Toolbar;

/*
 * In the game constructor, it starts a new GameWorld and calls play.
 * play() is referred to as the big switch because all that it does
 * is take in input to a switch statement and then calls methods
 * in GameWorld.
 */

public class Game extends Form implements Runnable{
	private GameWorld gw;
	private MapView mv;
	private PointsView pv;
	
	public Game(){
		gw = new GameWorld();
		mv = new MapView(gw);
		pv = new PointsView();
		gw.addObserver(mv);
		gw.addObserver(pv);
		//Create Tool bar
		Toolbar myToolbar = new Toolbar();
		setToolbar(myToolbar);
		//TextField
		TextField myTF = new TextField("CSC133: Asteroids");
		myToolbar.setTitleComponent(myTF);
		//CheckBox for sound
		CheckBox cb = new CheckBox("Check Side Menu Component");
		cb.getAllStyles().setBgTransparency(255);
		cb.getAllStyles().setBgColor(ColorUtil.LTGRAY);
		Command cbCommand = new CommandSound(gw);
		cb.setCommand(cbCommand);
		cbCommand.putClientProperty("SideComponent", cb);
		myToolbar.addCommandToSideMenu(cbCommand);
		//Commands
		Command addAsteroid = new CommandAddAsteroid(gw);
		myToolbar.addCommandToSideMenu(addAsteroid);
		Command addStation = new CommandAddStation(gw);
		myToolbar.addCommandToSideMenu(addStation);
		Command addShip = new CommandAddShip(gw);
		myToolbar.addCommandToSideMenu(addShip);
		Command increaseShipSpeed = new CommandIncreaseShipSpeed(gw);
		myToolbar.addCommandToSideMenu(increaseShipSpeed);
		Command decreaseShipSpeed = new CommandDecreaseShipSpeed(gw);
		myToolbar.addCommandToSideMenu(decreaseShipSpeed);
		Command turnShipLeft = new CommandTurnShipLeft(gw);
		myToolbar.addCommandToSideMenu(turnShipLeft);
		Command turnShipRight = new CommandTurnShipRight(gw);
		myToolbar.addCommandToSideMenu(turnShipRight);
		Command fireMissile = new CommandFireMissile(gw);
		myToolbar.addCommandToSideMenu(fireMissile);
		Command refuel = new CommandRefuel(gw);
		myToolbar.addCommandToSideMenu(refuel);
		Command hyperJump = new CommandHyperJump(gw);
		myToolbar.addCommandToSideMenu(hyperJump);
		Command quitOption = new CommandQuit();
		myToolbar.addCommandToSideMenu(quitOption);
		//Key Strokes
		addKeyListener('r', addAsteroid);
		addKeyListener('o', addStation);
		addKeyListener('n', addShip);
		addKeyListener('w', increaseShipSpeed);
		addKeyListener('s', decreaseShipSpeed);
		addKeyListener('a', turnShipLeft);
		addKeyListener('d', turnShipRight);
		addKeyListener('k', fireMissile);
		addKeyListener('j', hyperJump);
		//For Overflow drop down
		Command newOption = new CommandNew(gw);
		Command undoOption = new CommandUndo(gw);
		Command saveOption = new CommandSave(gw);
		Command soundO = new CommandSound(gw);
		Command aboutOption = new CommandAbout(gw);
		myToolbar.addCommandToOverflowMenu(newOption);
		myToolbar.addCommandToOverflowMenu(undoOption);
		myToolbar.addCommandToOverflowMenu(saveOption);
		myToolbar.addCommandToOverflowMenu(soundO);
		myToolbar.addCommandToOverflowMenu(aboutOption);
		myToolbar.addCommandToOverflowMenu(quitOption);
		
		//The Top left and right items
		Command titleBarAreaItem1 = new Command("File");
		myToolbar.addCommandToRightBar(titleBarAreaItem1);
		Command titleBarAreaItem2 = new Command("Commands");
		myToolbar.addCommandToLeftBar(titleBarAreaItem2);
		
		//Center Container for MapView
		setLayout(new BorderLayout());
		mv.getAllStyles().setBgTransparency(255);
		mv.getAllStyles().setBgColor(ColorUtil.LTGRAY);
		mv.getAllStyles().setBorder(Border.createLineBorder(4,ColorUtil.BLACK));
		add(BorderLayout.CENTER,mv);
		//Points
		pv.getAllStyles().setBorder(Border.createLineBorder(1,ColorUtil.BLUE));
		add(BorderLayout.SOUTH,pv);

		//SHOW IT
		this.show();
		//Gets MapView Dimensions (sets in GameWorld and inside of Mapview)
		gw.SetDimensions((double) mv.getWidth(), (double) mv.getHeight());
		mv.GetDimensions((double) mv.getWidth(), (double) mv.getHeight());
		//Runs the Timer
		UITimer timer = new UITimer(this);
		timer.schedule(gw.GetGameSpeed(), true, this);
		//Command for Pausing
		Command pauseOption = new CommandPause(gw, timer, this);
		myToolbar.addCommandToOverflowMenu(pauseOption);
	}

	public void run() {
		gw.TickClock();
	}
}
