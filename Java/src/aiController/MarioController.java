package aiController;

import qlearning.Action;

public class MarioController implements IMarioController {

	@Override
	public void makeAction(Action action) {
		switch(action) {
		case JUMP:
			pressKey('k');
			break;
		case LEFT:
			pressKey('a');
			break;
		case RIGHT:
			pressKey('d');
			break;
		default:	
			break;
		}

	}
	
	@Override
	public void startUpGame() {
		startGame();
	}

	@Override
	public void restartGame() {
		reStartGame();	
	}
	
	private native void pressKey(char Key);
	private native void startGame();
	private native void reStartGame();

	
}
