#include "bundle.h"
#include <algorithm>
#include <sstream>

//Returns index of the bundle in the bundles list if exists, -1 otherwise
int findBundle(std::vector<Bundle> bundles, std::string name);

std::string readFileIntoString(const std::string& path);

void init_pipe(std::vector<Bundle>& bundles, std::vector<int>& queue);
