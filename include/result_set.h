#pragma once

#include <memory>
#include <string>
#include <vector>

class ResultSet {
 public:
  // 构造函数：接受查询结果
  ResultSet(std::shared_ptr<std::vector<std::vector<std::string>>> result_set);

  // 获取指定行的指定列的数据
  std::string GetData(int row, int column) const;

  // 获取结果集行数
  int GetRowCount() const;

  // 获取结果集列数
  int GetColumnCount() const;

 private:
  std::shared_ptr<std::vector<std::vector<std::string>>> result_set_;
};
