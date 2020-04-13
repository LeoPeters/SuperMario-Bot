#include "MarioWindow.h"
#include "ScreenCaptureDummy.h"
#include "ScreenCapture.h"
#include "ImageScanDummy.h"
#include "EnviromentDummy.h"
#include "AiAlgoDummy.h"
#include "AppControlDummy.h"
#include "MarioController.h"
#include "AiFactory.h"
bool AiFactory::loadSuperMarioAi(bool screenCaptureDummy, bool imageScanDummy, bool enviromentDummy, bool aiAlgoDummy, bool appControlDummy)
{
	if (appControlDummy) {
		this->appControl = new AppControlDummy();
	}
	else { this->appControl = new MarioController(); }
	window = this->appControl->startGame();
	if (window == NULL) {
		return false;
	}

	if (screenCaptureDummy) {
		this->screenCapture = new ScreenCaptureDummy();
	}else{ this->screenCapture = new ScreenCapture(window);}
	if (imageScanDummy) {
		this->imageScan = new ImageScanDummy();
	}
	else {}
	if (enviromentDummy) {
		this->enviroment = new EnviromentDummy();
	}
	else {}
	if (aiAlgoDummy) {
		this->aiAlgo = new AiAlgoDummy();
	}
	else {}
	return true;

}

bool AiFactory::loadSuperMarioAi()
{
	return loadSuperMarioAi(false, true, true, true, false);
}

IScreenCapture* AiFactory::getScreenCapture()
{
	return screenCapture;
}

IAppControl* AiFactory::getAppControl()
{
	return appControl;
}

IEnviroment* AiFactory::getEnviroment()
{
	return enviroment;
}

IImageScan* AiFactory::getImageScan()
{
	return imageScan;
}

IAiAlgorithm* AiFactory::getAiAlgo()
{
	return aiAlgo;
}
