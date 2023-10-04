#include <string>
#include <cstring>

namespace mtg{
    bool tags[30];
    std::string filePath[4];
    void TagsReset()
    {
        memset (tags,0,sizeof(tags));
    }
}