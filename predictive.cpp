#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Grammar {
public:
  std::unordered_map<char, std::vector<std::string>> productions;
  std::unordered_set<char> terminals;
  std::unordered_set<char> non_terminals;
  char start_symbol = '\0';

  void add_production(char lhs, const std::string &rhs) {
    productions[lhs].push_back(rhs);
    non_terminals.insert(lhs);
    for (char symbol : rhs) {
      if (std::isupper(static_cast<unsigned char>(symbol))) {
        non_terminals.insert(symbol);
      } else if (symbol != 'e') { // 'e' represents ε
        terminals.insert(symbol);
      }
    }
  }
};

std::unordered_map<char, std::unordered_set<char>>
find_first(const Grammar &grammar) {
  std::unordered_map<char, std::unordered_set<char>> first;

  // Initialize FIRST sets
  for (char nt : grammar.non_terminals) {
    first[nt] = std::unordered_set<char>();
  }
  for (char t : grammar.terminals) {
    first[t] = std::unordered_set<char>{t};
  }

  bool updated;
  do {
    updated = false;
    for (const auto &[nt, productions] : grammar.productions) {
      for (const auto &production : productions) {
        bool all_derive_e = true;
        for (char symbol : production) {
          if (symbol == 'e') { // ε-production
            if (first[nt].insert('e').second)
              updated = true;
            break;
          }

          auto it = first.find(symbol);
          if (it != first.end()) {
            size_t old_size = first[nt].size();
            auto temp = it->second;
            temp.erase('e');
            first[nt].insert(temp.begin(), temp.end());
            if (first[nt].size() != old_size)
              updated = true;
          }

          if (it == first.end() || it->second.find('e') == it->second.end()) {
            all_derive_e = false;
            break;
          }
        }
        if (all_derive_e && production != "e") {
          if (first[nt].insert('e').second)
            updated = true;
        }
      }
    }
  } while (updated);

  return first;
}

std::unordered_map<char, std::unordered_set<char>>
find_follow(const Grammar &grammar,
            const std::unordered_map<char, std::unordered_set<char>> &first) {
  std::unordered_map<char, std::unordered_set<char>> follow;

  // Initialize FOLLOW sets
  for (char nt : grammar.non_terminals) {
    follow[nt] = std::unordered_set<char>();
  }
  if (grammar.start_symbol != '\0') {
    follow[grammar.start_symbol].insert('$');
  }

  bool updated;
  do {
    updated = false;
    for (const auto &[nt, productions] : grammar.productions) {
      for (const auto &production : productions) {
        std::unordered_set<char> trailer = follow[nt];
        for (auto it = production.rbegin(); it != production.rend(); ++it) {
          char symbol = *it;
          if (grammar.non_terminals.find(symbol) !=
              grammar.non_terminals.end()) {
            size_t old_size = follow[symbol].size();
            follow[symbol].insert(trailer.begin(), trailer.end());
            if (follow[symbol].size() != old_size)
              updated = true;

            auto first_it = first.find(symbol);
            if (first_it != first.end() &&
                first_it->second.find('e') != first_it->second.end()) {
              trailer.insert(first_it->second.begin(), first_it->second.end());
              trailer.erase('e');
            } else {
              trailer = first_it != first.end() ? first_it->second
                                                : std::unordered_set<char>();
            }
          } else {
            auto first_it = first.find(symbol);
            trailer = first_it != first.end() ? first_it->second
                                              : std::unordered_set<char>();
          }
        }
      }
    }
  } while (updated);

  return follow;
}

void print_set(const std::unordered_set<char> &set) {
  std::cout << "{ ";
  for (char c : set) {
    if (c == 'e') {
      std::cout << "ε ";
    } else {
      std::cout << c << " ";
    }
  }
  std::cout << "}";
}

int main() {
  Grammar grammar;
  int numProductions;
  std::cout << "Enter the number of productions: ";
  std::cin >> numProductions;

  char lhs;
  std::string rhs;
  for (int i = 0; i < numProductions; i++) {
    std::cout << "Production: ";
    std::cin >> lhs >> rhs;
    grammar.add_production(lhs, rhs);
  }

  std::cout << "Enter the start symbol: ";
  std::cin >> grammar.start_symbol;

  auto first = find_first(grammar);
  auto follow = find_follow(grammar, first);

  std::cout << "FIRST sets:\n";
  for (const auto &[symbol, set] : first) {
    std::cout << "FIRST(" << symbol << ") = ";
    print_set(set);
    std::cout << "\n";
  }

  std::cout << "\nFOLLOW sets:\n";
  for (const auto &[symbol, set] : follow) {
    if (grammar.non_terminals.find(symbol) != grammar.non_terminals.end()) {
      std::cout << "FOLLOW(" << symbol << ") = ";
      print_set(set);
      std::cout << "\n";
    }
  }

  return 0;
}