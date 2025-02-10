#include "result_set.h"

#include <stdexcept>

ResultSet::ResultSet(
    std::shared_ptr<std::vector<std::vector<std::string>>> result_set)
    : result_set_(result_set) {}

std::string ResultSet::GetData(int row, int column) const {
  if (row < 0 || row >= GetRowCount() || column < 0 ||
      column >= GetColumnCount()) {
    throw std::out_of_range("Row or Column out of range");
  }
  return result_set_->at(row).at(column);
}

int ResultSet::GetRowCount() const { return result_set_->size(); }

int ResultSet::GetColumnCount() const {
  if (result_set_->empty()) return 0;
  return result_set_->at(0).size();
}
