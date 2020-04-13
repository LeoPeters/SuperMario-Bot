#include "MarioWindow.h"
#include "ScreenCaptureDummy.h"
#include "ScreenCapture.h"
#include "SimplifierDummy.h"
#include "EnviromentDummy.h"
#include "AgentDummy.h"
#include "AppControlDummy.h"
#include "MarioController.h"
#include "AiFactory.h"
bool AiFactory::loadSuperMarioAi(bool screenCaptureDummy, bool simplifierDummy, bool enviromentDummy, bool aiAlgoDummy, bool appControlDummy)
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
	if (simplifierDummy) {
		this->imageScan = new SimplifierDummy();
	}
	else {}
	if (enviromentDummy) {
		this->enviroment = new EnviromentDummy();
	}
	else {}
	if (aiAlgoDummy) {
		this->aiAlgo = new AgentDummy();
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

ISimplifier* AiFactory::getImageScan()
{
	return imageScan;
}

IAgent* AiFactory::getAiAlgo()
{
	return aiAlgo;
}
