#include <iostream>
#include <gtest/gtest.h>

#include "../route_parser.h"

namespace rp {
    extern "C" RP_Path *RP_Path_new(const char *path_str, int max_routes, int len, char routes[len][256]);
    extern "C" _RP_Node *RP_Node_new(RP_Route *route);
}


TEST(route_parser, RP_Path_new)
{
    char routes[3][256] = {"/in", "/index", "/"};
    RP_Path *p = rp::RP_Path_new("/index", 256, 3, routes);
    ASSERT_EQ(p->length, 7);
    ASSERT_EQ(p->matched, false);
    int count = 0;
    RP_Route *r = (RP_Route*)malloc(sizeof(RP_Route));
    _RP_Node * tempNodePtr = (_RP_Node*)malloc(sizeof(_RP_Node));
    while (tempNodePtr->next != NULL)
    {
       // TODO
    }

}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
