package aiController;

import qlearning.Action;

public interface IMarioController {
	public void makeAction(Action action);
	public void startUpGame();
	public void restartGame();
}
