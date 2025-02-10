#pragma once

#include <sql.h>
#include <sqlext.h>

#include <memory>
#include <string>
#include <vector>

#include "odbc_api.h"

class Statement {
 public:
  // 构造函数：通过 ODBCAPI 初始化 Statement
  Statement(OdbcApi& odbc_api);

  // 执行查询语句
  void ExecuteQuery(const std::string& query);

  // 获取查询结果
  std::shared_ptr<std::vector<std::vector<std::string>>> GetResultSet();

 private:
  OdbcApi& odbc_api_;
  SQLHSTMT h_stmt_;  // SQL 语句句柄
  std::shared_ptr<std::vector<std::vector<std::string>>>
      result_set_;  // 存放查询结果
};
