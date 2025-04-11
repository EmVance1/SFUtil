#include <unordered_set>
#include <vector>


template<typename T>
void remove_many(std::vector<T>& self, const std::vector<size_t>& list) {
    const size_t end_size = self.size() - list.size();
    if (end_size == 0) {
        self.clear();
        return;
    }
    size_t offset = 0;

    for (size_t i = 0; i < end_size; i++) {
        while (std::find(list.begin(), list.end(), i + offset) != list.end()) {
            offset++;
        }
        if (offset != 0) {
            self[i] = self[i + offset];
        }
    }

    self.resize(end_size);
}

template<typename T>
void remove_many(std::vector<T>& self, std::unordered_set<size_t>& list) {
    const size_t end_size = self.size() - list.size();
    if (end_size == 0) {
        self.clear();
        return;
    }
    size_t offset = 0;

    for (size_t i = 0; i < end_size; i++) {
        while (list.contains(i + offset)) {
            offset++;
            list.erase(i + offset);
        }
        if (offset != 0) {
            self[i] = self[i + offset];
        }
    }

    self.resize(end_size);
}

template<typename T>
void swap_remove(std::vector<T>& self, const std::vector<size_t>& list) {
    if (list.size() == self.size()) {
        self.clear();
        return;
    }
    size_t eff_size = self.size();

    for (size_t index : list) {
        if (index < eff_size) {
            while (std::find(list.begin(), list.end(), eff_size - 1) != list.end()) {
                eff_size--;
                if (index == eff_size) {
                    goto outer_break;
                }
            }
            self[index] = self[eff_size - 1];
            eff_size--;
        }
    }

outer_break:
    self.resize(eff_size);
}

