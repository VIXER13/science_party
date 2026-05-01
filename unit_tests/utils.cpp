#include <utils.hpp>

#include <boost/ut.hpp>

namespace {

const boost::ut::suite<"utils"> _ = [] {
    using namespace utils;
    using namespace boost::ut;

    "text"_test = [] {
        expect(throws([]{ get_number("abc"); }));
    };

    "negative"_test = [] {
        expect(throws([]{ get_number("-5"); }));
    };

    "out_of_range"_test = [] {
        expect(throws([]{ get_number("9999999999999999999999999999999"); }));
    };

    "zero"_test = [] {
        expect(eq(get_number("0"), 0zu));
    };

    "five"_test = [] {
        expect(eq(get_number("5"), 5zu));
    };
};

}