package qlearning;

import java.text.DecimalFormat;

public class QLearning {
	public static final int NUMBEROFSTATES = 10;
	public static final double ALPHA = 0.4; //Learning rate
	public static final double GAMMA = 0.9; //Eagerness - 0 looks in the near future, 1 looks in the distant future

	public static final double rewardStep = 1;
	public static final double rewardWin = 1000;
	public static final double rewardTime = 1;
	
	
	private State[] states = new State[NUMBEROFSTATES];
	private static DecimalFormat df = new DecimalFormat("#.###");
	
}
