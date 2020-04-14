#pragma once

#include "IScreenCapture.h"
#include "IAppControl.h"
#include "IEnvironment.h"
#include "IImageScan.h"
#include "IAiAlgorithm.h"
class AiFactory
{
public:
	bool loadSuperMarioAi(bool screenCaptureDummy, bool imageScanDummy, bool enviromentDummy, bool aiAlgoDummy, bool appControlDummy);
	bool loadSuperMarioAi();
	IScreenCapture* getScreenCapture();
	IAppControl* getAppControl();
	IEnvironment* getEnviroment();
	IImageScan* getImageScan();
	IAiAlgorithm* getAiAlgo();
private:
	HWND window;
	IScreenCapture* screenCapture;
	IAppControl* appControl;
	IEnvironment* enviroment;
	IImageScan* imageScan;
	IAiAlgorithm* aiAlgo;
};

