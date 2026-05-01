#include <party.hpp>

#include <boost/ut.hpp>

#include <ranges>

namespace {

const boost::ut::suite<"party"> _ = [] {
    using namespace conference;
    using namespace details;
    using namespace boost::ut;
    using enum scientific_interest;
    using si_t = std::underlying_type_t<scientific_interest>;

    "have_common_interests"_test = [] {
        common_interests interests = {};
        expect(!have_common_interests(interests));
        
        interests[size_t(Epidemiology)] = 1;
        expect(!have_common_interests(interests));

        interests.fill(1);
        expect(!have_common_interests(interests));

        interests[size_t(Epidemiology)] = 2;
        expect(have_common_interests(interests));
    };

    "get_common_interests"_test = [] {
        std::vector<person> guests;
        common_interests expected_interests = {};

        auto interests = get_common_interests(guests);
        for (const size_t i : std::ranges::iota_view{si_t(Begin), si_t(End)})
            expect(eq(interests[i], expected_interests[i]));

        guests.push_back(person{.interest = Epidemiology});
        expected_interests[size_t(Epidemiology)] = 1zu;
        interests = get_common_interests(guests);
        for (const size_t i : std::ranges::iota_view{si_t(Begin), si_t(End)})
            expect(eq(interests[i], expected_interests[i]));

        guests.push_back(person{.interest = Epidemiology});
        guests.push_back(person{.interest = Statistics});
        guests.push_back(person{.interest = Healt_Policy});
        expected_interests[size_t(Epidemiology)] = 2zu;
        expected_interests[size_t(Statistics)] = 1zu;
        expected_interests[size_t(Healt_Policy)] = 1zu;
        interests = get_common_interests(guests);
        for (const size_t i : std::ranges::iota_view{si_t(Begin), si_t(End)})
            expect(eq(interests[i], expected_interests[i]));
    };

    "in_room_a"_test = []{
        std::vector<person> guests = invite_guests(5zu);
        for(const size_t i : std::ranges::iota_view{0zu, guests.size()})
            expect(in_room(guests, i));
        for(const size_t i : std::ranges::iota_view{guests.size(), guests.size() + 5zu})
            expect(!in_room(guests, i));
    };

    "in_room_b"_test = []{
        static constexpr size_t Size = 6zu;
        guests_in_room_a guests = invite_guests(Size);
        guests_in_room_b couples(Size / 2);
        for(const size_t i : std::ranges::iota_view{0zu, couples.size()})
            couples[i] = {std::move(guests[2 * i]), std::move(guests[2 * i + 1])};
        
        for(const size_t i : std::ranges::iota_view{0zu, guests.size()})
            expect(in_room(couples, i));
        for(const size_t i : std::ranges::iota_view{guests.size(), guests.size() + 5zu})
            expect(!in_room(couples, i));
    };

    "leave_room"_test = [] {
        std::vector<person> guests = invite_guests(5zu);
        expect(throws([&guests] { leave_room(guests, 5zu, 2zu); }));
        expect(throws([&guests] { leave_room(guests, 0zu, 5zu); }));
        leave_room(guests, 2zu, 3zu);
        expect(!in_room(guests, 2zu));
        expect(!in_room(guests, 3zu));

        guests = invite_guests(5zu);
        leave_room(guests, 4zu, 1zu);
        expect(!in_room(guests, 4zu));
        expect(!in_room(guests, 1zu));

        guests = invite_guests(5zu);
        leave_room(guests, 3zu, 4zu);
        expect(!in_room(guests, 3zu));
        expect(!in_room(guests, 4zu));
    };
};

}