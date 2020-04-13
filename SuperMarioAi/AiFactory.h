#pragma once

#include "IScreenCapture.h"
#include "IAppControl.h"
#include "IEnviroment.h"
#include "IImageScan.h"
#include "IAiAlgorithm.h"
class AiFactory
{
public:
	bool loadSuperMarioAi(bool screenCaptureDummy, bool imageScanDummy, bool enviromentDummy, bool aiAlgoDummy, bool appControlDummy);
	bool loadSuperMarioAi();
	IScreenCapture* getScreenCapture();
	IAppControl* getAppControl();
	IEnviroment* getEnviroment();
	IImageScan* getImageScan();
	IAiAlgorithm* getAiAlgo();
private:
	HWND window;
	IScreenCapture* screenCapture;
	IAppControl* appControl;
	IEnviroment* enviroment;
	IImageScan* imageScan;
	IAiAlgorithm* aiAlgo;
};

