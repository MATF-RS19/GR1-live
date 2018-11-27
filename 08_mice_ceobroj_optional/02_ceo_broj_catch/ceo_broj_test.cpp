#include <stdexcept>

#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

#include "ceo_broj.h"

TEST_CASE("Construction", "[constructor]") {
    REQUIRE_THROWS(ceo_broj(0, 1000));
    REQUIRE_THROWS_AS(ceo_broj(0, 1000), std::invalid_argument);
}

TEST_CASE("Equality testing", "[equality]") {
    SECTION("Base-10 tests") {
        REQUIRE(ceo_broj(1000, 10) == ceo_broj(1000, 10));
        REQUIRE(ceo_broj(0, 10) == ceo_broj(0, 10));
        REQUIRE_FALSE(ceo_broj(1, 10) == ceo_broj(0, 10));
    }

    SECTION("Base-16 tests") {
        REQUIRE(ceo_broj(1000, 16) == ceo_broj(1000, 16));
        REQUIRE(ceo_broj(0, 16) == ceo_broj(0, 16));
        REQUIRE_FALSE(ceo_broj(1, 16) == ceo_broj(0, 16));
    }
}

