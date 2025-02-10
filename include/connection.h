#pragma once

#include <string>

#include "odbc_api.h"

class Connection {
 public:
  // 构造函数：通过 ODBCAPI 初始化
  Connection(OdbcApi& odbc_api);

  // 执行 SQL 查询
  void ExecuteQuery(const std::string& query);

 private:
  OdbcApi& odbc_api_;
};
