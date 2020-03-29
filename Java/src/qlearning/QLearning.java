package qlearning;

import java.text.DecimalFormat;

public class QLearning {
	public static final int NUMBEROFSTATES = 20;
	public static final double ALPHA = 0.4; //Learning rate
	public static final double GAMMA = 0.9; //discount factor - 
	
	public static final double REWARDSTEP = -1;
	public static final double REWARDWIN = 1000;
	public static final double REWARDTIME = 1;
	public static final double EPSILON = 0.1; //propability of choosing a random action
	public static final SelectionPolicy policy = SelectionPolicy.GREEDY; //TODO implement different policies
	
	private State[] states = new State[NUMBEROFSTATES];
	private State lastState = null; //TODO initialise at the start
	private static DecimalFormat df = new DecimalFormat("#.###");
	
	/**
	 * Run this to determine the action that will be used
	 * @param stateIndex
	 * @param actions
	 */
	public void runState(int stateIndex, Action... actions) {
		State state = states[stateIndex];
		state.setAvailableActions(actions);
		Action a = chooseAction(state);
		
		double newScore = lastState.getScore(a) + ALPHA * (REWARDSTEP + GAMMA * state.getMaxReward() - lastState.getScore(a));
		lastState.setScore(a, newScore);
		
		lastState = state;
		
		//TODO give Action a to Emulator input
	}
	
	private Action chooseAction(State state) {
		double rnd = Math.random();
		Action a = null;
		switch (policy) {
		case GREEDY:
			if(Math.random() <= EPSILON) {
				Action[] actions = Action.values();
				a = actions[(int) (rnd * actions.length)];
			} else {
				a = state.getLowestScore();
			}
			break;
		case SOFT:
			if(Math.random() >= 1 - EPSILON) {
				a = state.getLowestScore();
			} else {
				Action[] actions = Action.values();
				a = actions[(int) (rnd * actions.length)];
			}
			break;
		case SOFTMAX:
			//TODO SOFTMAX!
			break;
		default:
			break;
		}
		return a;
	}
	
}
