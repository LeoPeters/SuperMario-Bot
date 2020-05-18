#include "MarioWindow.h"
#include "ScreenCaptureDummy.h"
#include "ScreenCapture.h"
#include "SimplifierDummy.h"
#include "EnvironmentDummy.h"
#include "Agent.h"
#include "AgentLambda.h"
#include "AppControlDummy.h"
#include "MarioController.h"
#include "AiFactory.h"
#include "EnvironmentCalculation.h"

bool AiFactory::loadSuperMarioAi(bool screenCaptureDummy, bool simplifierDummy, bool environmentDummy, bool agentDummy, bool appControlDummy)
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
	if (environmentDummy) {
		this->environment = new EnvironmentDummy();
	}
	else { this->environment = new EnvironmentCalculation(); };
	if (agentDummy) {
		
	} else { this->agent = new AgentLambda(); }
	return true;

}

bool AiFactory::loadSuperMarioAi()
{
	return loadSuperMarioAi(false, true, false, false, false);
}

IScreenCapture* AiFactory::getScreenCapture()
{
	return screenCapture;
}

IAppControl* AiFactory::getAppControl()
{
	return appControl;
}

IEnvironment* AiFactory::getEnvironment()
{
	return environment;
}

ISimplifier* AiFactory::getImageScan()
{
	return imageScan;
}

IAgent* AiFactory::getAiAlgo()
{
	return agent;
}
