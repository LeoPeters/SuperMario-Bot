package qlearning;

import java.util.LinkedHashMap;
import java.util.Map;
import java.util.Map.Entry;

import qlearning.Action;
import qlearning.exceptions.ActionNotAvailableException;

public class State {
	private Map<Action, Double> score = new LinkedHashMap<Action, Double>();

	/**
	 * All actions that are assigned to this constructor will be available for the state.
	 * @param actions
	 */
	public State(Action... actions) {
		for(Action a : actions) {
			score.put(a, new Double(-1));
		}
	}
	
	/**
	 * All actions from the Action-Enum will be available for the state.
	 */
	public State() {
		for(Action a : Action.values()) {
			score.put(a, new Double(-1));
		}
	}

	/**
	 * Returns the Action with the lowest score. If there is more than one with the
	 * same score it returns the one which was inserted first.
	 * 
	 * @param action
	 * @return
	 */
	public Action getLowestScore() {
		Entry<Action, Double> min = null;
		for (Entry<Action, Double> entry : score.entrySet()) {
			if (min == null || min.getValue() > entry.getValue()) {
				min = entry;
			}
		}
		return min.getKey();
	}

	public void setScore(Action action, double value) {
		try {
			if (!score.containsKey(action)) {
				throw new ActionNotAvailableException();
			} else {
				score.put(action,  value);
			}
		} catch (ActionNotAvailableException e) {
			e.printStackTrace();
		}
	}

	@Override
	public String toString() {
//		score.keySet().forEach(arg0))
		return super.toString();
	}
}
