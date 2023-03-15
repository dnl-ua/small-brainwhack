#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <list>
#include <fstream>

auto main(int argc, char** argv) -> int {
    if (argc == 1) { std::cerr << "no file\n"; exit(EXIT_FAILURE); }
    if (!std::string {argv[1]}.ends_with(".bf")) { std::cerr << "not a .bf file\n"; exit(EXIT_FAILURE); }
    std::fstream in {argv[1]};
    if (!in.is_open()) { std::cerr << "file not found\n"; exit(EXIT_FAILURE); }
    std::vector <char> cmds {}, field (1000, 0);
    for (char c; in >> c;) if (*(std::ranges::find(std::string_view {"+-><,.[]"}, c))) cmds.emplace_back(c);
    std::vector <char>::iterator it = std::begin(field);
    std::list <std::vector <char>::iterator> entry_ref {};
    int loop_counter {};
    for (auto bg = cmds.begin(), end = cmds.end(); bg != end; ++bg) {
        switch (*bg) {
            case '+': ++*it; break; case '-': --*it; break;
            case '>': case '<': std::ranges::advance(it, *bg-61); break; 
            case ',': *it = std::getchar(); break; case '.': std::putchar(*it); break;
            case '[': entry_ref.emplace_back(bg); break;
            case ']': if (!entry_ref.size()) { std::cerr << "unopened bracket\n"; exit(EXIT_FAILURE); }
                      if (*it != 0) { bg = entry_ref.back(); } else { entry_ref.pop_back(); } break;
            default: std::cerr << "reached unreachable\n"; exit(EXIT_FAILURE); } 
    }
    if (entry_ref.size()) { std::cerr << "unclosed bracket\n"; exit(EXIT_FAILURE); }
}
