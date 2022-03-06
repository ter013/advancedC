#include <iostream>
#include <iterator>
#include <regex>
#include <vector>

std::vector<std::string> search(const std::regex& pattern,
                                const std::string& text) {
    auto begin = std::sregex_iterator(std::begin(text),
                                      std::end(text), pattern);
    auto end = std::sregex_iterator();
    std::vector<std::string> results(std::distance(begin, end));
    std::transform(begin, end, std::back_inserter(results), [](auto x){
        return x.str();
    });
    return results;
}

int main() {
    std::regex pattern("([0-9]{4}\.((0[13578]{1}|1[02]{1})\.(0[1-9]{1}|[1-2]{1}[0-9]{1}|3[0-1]{1})|"
                       "(0[469]{1}|11)\.(0[1-9]{1}|[1-2]{1}[0-9]{1}|30)|(02)\.(0[1-9]{1}|1[0-9]|2[0-8]))|"
                       "([01]{1}[0-9]|2[0-3]{1}):[0-5]{1}[0-9]{1}:[0-5]{1}[0-9]{1})");
    std::string test_sequence = "1234.11.32 \n" "1234.05.00 \n" "1234.10.20 \n" "1234.12.31 \n" "1234.09.11 \n"
                                "1234.02.29 \n" "1234.09.31 \n" "1234.10.11 \n" "23:65:04 \n" "25: \n"
                                                                                              "03:45:54 \n" "00:00:00 \n" "03:45:64 \n";

    auto result = search(pattern, test_sequence);
    std::copy(std::begin(result), std::end(result), std::ostream_iterator<std::string>(std::cout, " "));
}
