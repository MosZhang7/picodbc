#include "connection.h"

#include <sql.h>
#include <sqlext.h>

#include <iostream>

#include "odbc_api.h"

Connection::Connection(OdbcApi& api) : odbc_api_(api) {
  // 使用 ODBCAPI 获取数据库连接句柄
  SQLHDBC hDbc = odbc_api_.GetConnectionHandle();
  // 这里你可以初始化其他与连接相关的内容
}

void Connection::ExecuteQuery(const std::string& query) {
  SQLHSTMT h_stmt;
  SQLRETURN ret =
      SQLAllocHandle(SQL_HANDLE_STMT, odbc_api_.GetConnectionHandle(), &h_stmt);
  if (!SQL_SUCCEEDED(ret)) {
    throw std::runtime_error("Failed to allocate statement handle");
  }

  ret = SQLExecDirect(h_stmt, (SQLCHAR*)query.c_str(), SQL_NTS);
  if (!SQL_SUCCEEDED(ret)) {
    throw std::runtime_error("Failed to execute SQL query");
  }

  // 处理查询结果（例如获取数据等）

  SQLFreeHandle(SQL_HANDLE_STMT, h_stmt);
}
