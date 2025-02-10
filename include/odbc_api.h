#pragma once

#include <sql.h>
#include <sqlext.h>

#include <stdexcept>
#include <string>

class OdbcApi {
 public:
  // 构造函数：初始化ODBC环境
  OdbcApi();

  // 析构函数：释放ODBC资源
  ~OdbcApi();

  // 连接到数据库
  void Connect(const std::string& connection_string);

  // 断开连接
  void Disconnect();

  // 获取ODBC连接句柄
  SQLHDBC GetConnectionHandle() const;

 private:
  SQLHENV h_env_;  // 环境句柄
  SQLHDBC h_dbc_;  // 连接句柄

  // 错误处理函数
  void HandleError(SQLRETURN ret_code, SQLHANDLE handle, SQLSMALLINT handle_type);
};
