#include "bundle.h"
#include <algorithm>
#include <sstream>

//Returns index of the bundle in the bundles list if exists, -1 otherwise
int findBundle(std::vector<Bundle> bundles, std::string name);

//Creates and executes pipes for each bundle in the queue
void init_pipe(std::vector<Bundle>& bundles, std::vector<int>& queue);
