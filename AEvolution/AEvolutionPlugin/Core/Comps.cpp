
#include "Comps.h"

CompH addComp(const std::string& name, std::pair<int, int> dimensions, float frameRate, float duration, float pixelAspectRatio, ItemH parentFolder)
{
	auto& message = enqueueSyncTask(Addcomp, name, dimensions.first, dimensions.second, frameRate, duration, pixelAspectRatio, parentFolder);
	message->wait();
}
