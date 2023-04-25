#include <iostream>
#include <gtest/gtest.h>

#include "../route_parser.h"

namespace rp {
    extern "C" RP_Path *RP_Path_new(const char *path_str, int max_routes, int len, char routes[len][256]);
    extern "C" _RP_Node *_RP_Node_new(RP_Route *route);
}


TEST(route_parser, RP_Path_new)
{
    char routes[3][256] = {"/in", "/index", "/"};
    RP_Path *p = rp::RP_Path_new("/index", 256, 3, routes);
    ASSERT_EQ(p->length, 7);
    ASSERT_EQ(p->matched, false);
    RP_Route *r = (RP_Route*)malloc(sizeof(RP_Route));
    _RP_Node *tempNodePtr = (_RP_Node*)malloc(sizeof(_RP_Node));
    int count = 1;
    ASSERT_EQ(p->_nodes->route->path, routes[0]);
    while (tempNodePtr->next != NULL)
    {
        tempNodePtr = p->_nodes->next;
        ASSERT_EQ(tempNodePtr->route->path, routes[count]);
        count++;
    }

}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
