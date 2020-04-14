#ifndef aifactory_h
#define aifactory_h

#include "IScreenCapture.h"
#include "IAppControl.h"
#include "IEnvironment.h"
#include "ISimplifier.h"
#include "IAgent.h"
class AiFactory
{
public:
	bool loadSuperMarioAi(bool screenCaptureDummy, bool imageScanDummy, bool environmentDummy, bool aiAlgoDummy, bool appControlDummy);
	bool loadSuperMarioAi();
	IScreenCapture* getScreenCapture();
	IAppControl* getAppControl();
	IEnvironment* getEnvironment();
	ISimplifier* getImageScan();
	IAgent* getAiAlgo();
private:
	HWND window;
	IScreenCapture* screenCapture;
	IAppControl* appControl;
	IEnvironment* environment;
	ISimplifier* imageScan;
	IAgent* aiAlgo;
};

#endif