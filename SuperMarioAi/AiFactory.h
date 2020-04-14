#ifndef aifactory_h
#define aifactory_h

#include "IScreenCapture.h"
#include "IAppControl.h"
#include "IEnviroment.h"
#include "ISimplifier.h"
#include "IAgent.h"
class AiFactory
{
public:
	bool loadSuperMarioAi(bool screenCaptureDummy, bool imageScanDummy, bool enviromentDummy, bool aiAlgoDummy, bool appControlDummy);
	bool loadSuperMarioAi();
	IScreenCapture* getScreenCapture();
	IAppControl* getAppControl();
	IEnviroment* getEnviroment();
	ISimplifier* getImageScan();
	IAgent* getAiAlgo();
private:
	HWND window;
	IScreenCapture* screenCapture;
	IAppControl* appControl;
	IEnviroment* enviroment;
	ISimplifier* imageScan;
	IAgent* aiAlgo;
};

#endif