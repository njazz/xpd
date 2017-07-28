#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_object", "[cpd PureData wrapper]")
{
    SECTION("init")
    {
        auto cnv = cpd_root_canvas_new();
        auto obj1 = cpd_object_new(cnv, "float", 0, 0, 0);
        cpd_object_free(cnv, obj1);
        cpd_canvas_free(cnv);

        // free NULL
        cpd_object_free(cnv, nullptr);
    }

    SECTION("free")
    {
        // nullptr
        cpd_object_free(nullptr, nullptr);
    }

    SECTION("arguments")
    {
        REQUIRE(cpd_object_arguments(0) == nullptr);

        SECTION("empty")
        {
            auto cnv = cpd_root_canvas_new();
            auto obj1 = cpd_object_new(cnv, "float", 0, 0, 0);

            auto args = cpd_object_arguments(obj1);

            REQUIRE(args);
            REQUIRE(cpd_list_size(args) == 0);

            cpd_list_free(args);

            cpd_object_free(cnv, obj1);
            cpd_canvas_free(cnv);
        }

        SECTION("non-empty")
        {
            auto cnv = cpd_root_canvas_new();

            auto in_args = cpd_list_new(0);
            cpd_list_append_float(in_args, 100);
            REQUIRE(cpd_list_size(in_args) == 1);
            REQUIRE(cpd_list_get_float_at(in_args, 0) == 100);

            auto obj1 = cpd_object_new(cnv, "float", in_args, 0, 0);
            cpd_list_free(in_args);

            auto out_args = cpd_object_arguments(obj1);

            REQUIRE(out_args);
            REQUIRE(cpd_list_size(out_args) == 1);
            REQUIRE(cpd_list_get_float_at(out_args, 0) == 100);

            cpd_list_free(out_args);

            cpd_object_free(cnv, obj1);
            cpd_canvas_free(cnv);
        }
    }

    SECTION("help path")
    {
        REQUIRE(cpd_object_help_name(nullptr) == std::string());

        auto cnv = cpd_root_canvas_new();

        // [+]
        auto obj1 = cpd_object_new(cnv, "+", 0, 0, 0);
        REQUIRE(cpd_object_help_name(obj1) == std::string("operators"));
        cpd_object_free(cnv, obj1);

        // [metro]
        auto obj2 = cpd_object_new(cnv, "metro", 0, 0, 0);
        REQUIRE(cpd_object_help_name(obj2) == std::string("metro"));
        cpd_object_free(cnv, obj2);

        cpd_canvas_free(cnv);
    }

    SECTION("help dir")
    {
        REQUIRE(cpd_object_help_dir(nullptr) == std::string());

        auto cnv = cpd_root_canvas_new();

        // [+]
        auto obj1 = cpd_object_new(cnv, "+", 0, 0, 0);
        REQUIRE(cpd_object_help_dir(obj1) == std::string(""));
        cpd_object_free(cnv, obj1);

        // [metro]
        auto obj2 = cpd_object_new(cnv, "metro", 0, 0, 0);
        REQUIRE(cpd_object_help_dir(obj2) == std::string(""));
        cpd_object_free(cnv, obj2);

        cpd_canvas_free(cnv);
    }
}
