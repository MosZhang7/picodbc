#include "statement.h"

Statement::Statement(OdbcApi& api)
    : odbc_api_(api),
      h_stmt_(SQL_NULL_HSTMT),
      result_set_(std::make_shared<std::vector<std::vector<std::string>>>()) {
  SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_STMT,
                                 odbc_api_.GetConnectionHandle(), &h_stmt_);
  if (!SQL_SUCCEEDED(ret)) {
    throw std::runtime_error("Failed to allocate statement handle");
  }
}

void Statement::ExecuteQuery(const std::string& query) {
  SQLRETURN ret = SQLExecDirect(h_stmt_, (SQLCHAR*)query.c_str(), SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
    throw std::runtime_error("Failed to execute SQL query");
  }

  // 获取结果集
  SQLSMALLINT columns;
  ret = SQLNumResultCols(h_stmt_, &columns);
  if (!SQL_SUCCEEDED(ret)) {
    throw std::runtime_error("Failed to get number of columns in result");
  }

  // 循环获取每一行数据
  while (SQL_SUCCEEDED(ret = SQLFetch(h_stmt_))) {
    std::vector<std::string> row;
    for (SQLSMALLINT col = 1; col <= columns; ++col) {
      SQLCHAR colData[256];
      SQLLEN indicator;
      ret = SQLGetData(h_stmt_, col, SQL_C_CHAR, colData, sizeof(colData),
                       &indicator);
      if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        row.push_back((char*)colData);
      } else {
        row.push_back("");
      }
    }
    result_set_->push_back(row);  // 存储一行数据
  }
}

std::shared_ptr<std::vector<std::vector<std::string>>>
Statement::GetResultSet() {
  return result_set_;
}
