#ifndef FinderThread_h
#define FinderThread_h
#include "PngImage.h"
#include "ImageDistributor.h"
#include "Globals.h"
#include "GridScanner.h"
#include "Mapper.h"
class FinderThread{
    private:
        ImageDistributor distr;
        PngImage &resized;
        GridScanner gridsc;
        int modi;
        int typ;
    public:
        FinderThread(int DISTR_IMAGEES);
        ~FinderThread();
        bool search(int xstart, int xend, int ystart, int yend, Mapper *mapper); //xystart xyend
};
#endif