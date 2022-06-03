#include <iostream>
#include <memory>
#include <range/v3/all.hpp>
#include <map>
int main() {

    //using namespace std;

    std::vector<double> daily_price = {100.3, 101.5, 99.2, 105.1, 101.93, 96.7, 97.6, 103.9, 105.8, 101.2};

    auto price_jumps = daily_price
                       | ranges::views::enumerate
                       | ranges::views::adjacent_filter([](const auto &p1, const auto &p2) {
        return p2.second - p1.second > 5;
    })
                       | ranges::views::tail;

    if (price_jumps.empty()) {
        std::cout << "no results!" << std::endl;
    } else {
        std::cout
                << "Price first jumped by more then 5 on day "
                << price_jumps.front().first << std::endl;
//        ranges::for_each(price_jumps.front(), [](const auto &line){
//           std::cout << line.front().first <<std::endl;
//        });
        //std::cout << "Range:" << price_jumps << std::endl;
    }

    std::string formatted_days = price_jumps
                                 | ranges::views::transform([](const auto &p) {
        return std::to_string(p.first + 1);
    })
                                 | ranges::views::intersperse(", ")
                                 | ranges::actions::join;

    std::cout << "All days where the price has jumped:" << formatted_days << std::endl;

    auto ints = ranges::views::ints(42, 52);
    std::cout << "pippp:" << ints << std::endl;


    class normal_random_range : public ranges::view_facade<normal_random_range, ranges::cardinality::infinite> {
        std::shared_ptr<std::random_device> rd_{};
        std::shared_ptr<std::mt19937> gen_;
        std::shared_ptr<std::normal_distribution<>> d_;

        double value_ = 0.0;
        friend ranges::range_access;
        double const &read() const { return value_;}
        bool equal(ranges::default_sentinel_t) const {return false;}
        void next(){
            value_=(*d_)(*gen_);
        }
    public:
        normal_random_range():
        rd_{std::make_shared<std::random_device>()},
        gen_{std::make_shared<std::mt19937>()},
        d_{std::make_shared<std::normal_distribution<>>(0,2)}{
            next();
        }

    };

    auto r=normal_random_range();
    auto values=r|ranges::views::take(10000);

    std::map<int,size_t> histogram;

    ranges::for_each(values,[&histogram](auto value){
        ++histogram[round(value)];
    });


    return 0;
}
