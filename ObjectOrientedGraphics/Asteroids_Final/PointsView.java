package com.mycompany.a3;
import java.util.Observable;
import java.util.Observer;

import com.codename1.charts.util.ColorUtil;
import com.codename1.ui.Container;
import com.codename1.ui.Label;

/*
 * Points view is the bottom container
 * Every time something in GameWorld is updated,
 * the update method is called
 */

public class PointsView extends Container implements Observer{

	private Label score;
	private Label getScore;
	private Label missiles;
	private Label getMissiles;
	private Label time;
	private Label getTime;
	private Label sound;
	private Label getSound;
	
	PointsView (){
		score = new Label("Score: ");
		getScore = new Label("---");
		missiles = new Label("Missiles: ");
		getMissiles = new Label("---");
		time = new Label("Time: ");
		getTime = new Label("---");
		sound = new Label("Sound: ");
		getSound = new Label("---");
		
		score.getUnselectedStyle().setFgColor(ColorUtil.BLUE);
		getScore.getUnselectedStyle().setFgColor(ColorUtil.BLUE);
		getScore.getAllStyles().setPaddingRight(5);
		getScore.getAllStyles().setPaddingLeft(5);
		
		missiles.getUnselectedStyle().setFgColor(ColorUtil.BLUE);
		getMissiles.getUnselectedStyle().setFgColor(ColorUtil.BLUE);
		getMissiles.getAllStyles().setPaddingRight(5);
		getMissiles.getAllStyles().setPaddingLeft(5);
		
		time.getUnselectedStyle().setFgColor(ColorUtil.BLUE);
		getTime.getUnselectedStyle().setFgColor(ColorUtil.BLUE);
		getTime.getAllStyles().setPaddingRight(5);
		getTime.getAllStyles().setPaddingLeft(3);
		getTime.getAllStyles().setMarginBottom(2);
		getTime.getAllStyles().setMarginTop(2);
		getTime.getAllStyles().setMarginLeft(2);
		getTime.getAllStyles().setMarginRight(2);
		
		sound.getUnselectedStyle().setFgColor(ColorUtil.BLUE);
		getSound.getUnselectedStyle().setFgColor(ColorUtil.BLUE);
		getSound.getAllStyles().setPaddingRight(5);
		getSound.getAllStyles().setPaddingLeft(5);
		
		this.add(score);
		this.add(getScore);
		this.add(missiles);
		this.add(getMissiles);
		this.add(time);
		this.add(getTime);
		this.add(sound);
		this.add(getSound);
	}
	
	//Every time something in GameWorld changes,
	//Update is called through Proxy
	public void update(Observable observable, Object data) {
		IGameWorld igw = (IGameWorld) data;
		int scoreU, missilesU, timeU;
		boolean soundU;
		String sv;
		
		scoreU = igw.GetScore();
		getScore.setText(" " + Integer.toString(scoreU) + " ");
		
		missilesU = igw.GetMissiles();
		getMissiles.setText(" " + Integer.toString(missilesU) + " ");
		
		timeU = igw.GetTime();
		getTime.setText(" " + Integer.toString(timeU) + " ");
		
		soundU = igw.GetSound();
		if (soundU)
			sv = "ON";
		else
			sv = "OFF";
		getSound.setText(sv);
	}
}
