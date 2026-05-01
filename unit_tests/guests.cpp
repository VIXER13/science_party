#include <guests.hpp>

#include <boost/ut.hpp>

#include <ranges>
#include <sstream>

namespace {

const boost::ut::suite<"guests"> _ = [] {
    using namespace conference;
    using namespace boost::ut;
    using namespace std::string_literals;
    using si_t = std::underlying_type_t<scientific_interest>;

    "person_text"_test = [] {
        const person guest = {
            .name = "David",
            .id = 37,
            .interest = scientific_interest::Statistics
        };
        std::stringstream stream;
        stream << guest;
        expect(eq(stream.str(), "David(37)"s));
    };
    
    "no_invites"_test = [] {
        const auto guests = invite_guests(0zu);
        expect(eq(guests.size(), 0zu));
    };

    "check_ids"_test = [] {
        static constexpr size_t Size = 10zu;
        const auto guests = invite_guests(Size);
        expect(eq(guests.size(), Size));
        for (const size_t i : std::ranges::iota_view{0zu, Size})
            expect(eq(guests[i].id, i));
    };

    "check_interests"_test = [] {
        static constexpr size_t Size = 1000zu;
        const auto guests = invite_guests(Size);
        expect(eq(guests.size(), Size));
        for (const size_t i : std::ranges::iota_view{0zu, Size}) {
            expect(ge(guests[i].interest, scientific_interest::Begin));
            expect(lt(guests[i].interest, scientific_interest::End));
        }
    };
};

}