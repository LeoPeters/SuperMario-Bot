package qlearning.exceptions;

public class ActionNotAvailableException extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	public ActionNotAvailableException() {
		super("This Action is not available for the current state");
	}

}
