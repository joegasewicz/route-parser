#include <iostream>
#include <gtest/gtest.h>

#include "../route_parser.h"

namespace rp {
    extern "C" RP_Path *RP_Path_new(const char *path_str, int max_routes, int len, char routes[len][256]);
}


TEST(route_parser, RP_Path_new)
{
    char routes[3][256] = {"/in", "/index", "/"};
    RP_Path *r = rp::RP_Path_new("/index", 256, 3, routes);
    ASSERT_EQ(r->length, 7);
    ASSERT_EQ(r->matched, false);

}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
