#pragma once

#include <mutex>
#include <queue>

#include "connection.h"
#include "odbc_api.h"

class Picodbc {
 public:
  // 构造函数：初始化ODBCAPI和连接池
  Picodbc();

  // 连接到数据库
  void Connect(const std::string& connection_string);

  // 获取数据库连接
  Connection GetConnection();

  // 释放连接
  void ReleaseConnection(Connection conn);

 private:
  OdbcApi odbc_api_;  // ODBCAPI实例
  std::queue<Connection> connection_pool_;
  std::mutex pool_mutex_;  // 用于保护连接池
};
