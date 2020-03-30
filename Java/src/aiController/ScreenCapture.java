package aiController;

public class ScreenCapture implements IScreenCapture {

	@Override
	public void capture(String fileName) {
		captureScreen(fileName);
	}
	
	public static native void captureScreen(String fileName);
}
