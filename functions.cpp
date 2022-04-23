#include "functions.h"

int findBundle(std::vector<Bundle> bundles, std::string name){
    int n = bundles.size();
    for(int i = 0; i < n; i++){
        if(bundles[i].get_name() == name){
            return i;
        }
    }
    return -1;
}