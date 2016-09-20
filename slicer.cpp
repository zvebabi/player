#include "slicer.h"

Slicer::Slicer()
{

}

Slicer::~Slicer()
{

}

/*
 * slice video to frame and send to circular buffer
 */
void Slicer::process() {
    qDebug("Hello word!");
    emit finished();
}


