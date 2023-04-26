#include <iostream>
#include <gtest/gtest.h>

#include "../route_parser.h"

namespace rp
{
    extern "C" RP_Path *RP_Path_new(const char *path_str, int max_routes, int len, char routes[len][256]);
    extern "C" _RP_Node *_RP_Node_new(RP_Route *route);
}


TEST(route_parser, RP_Path_new)
{
    char routes[3][256] = {"/in", "/index", "/inde"};
    RP_Path *p = rp::RP_Path_new("/index", 256, 3, routes);
    ASSERT_EQ(p->length, 7);
    ASSERT_EQ(p->matched, false);
    ASSERT_STREQ(p->_nodes->route->path, "/in");
    ASSERT_STREQ(p->_nodes->next->route->path, "/index");
    ASSERT_STREQ(p->_nodes->next->next->route->path, "/inde");
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
