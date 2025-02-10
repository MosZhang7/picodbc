#include "picodbc.h"

Picodbc::Picodbc() : odbc_api_() {}

void Picodbc::Connect(const std::string& connectionString) {
  odbc_api_.Connect(connectionString);
  // 初始化连接池（例如创建一定数量的连接并放入池中）
  for (int i = 0; i < 10; ++i) {
    connection_pool_.push(Connection(odbc_api_));
  }
}

Connection Picodbc::GetConnection() {
  std::lock_guard<std::mutex> lock(pool_mutex_);
  if (connection_pool_.empty()) {
    throw std::runtime_error("No available connections in pool");
  }
  Connection conn = connection_pool_.front();
  connection_pool_.pop();
  return conn;
}

void Picodbc::ReleaseConnection(Connection conn) {
  std::lock_guard<std::mutex> lock(pool_mutex_);
  connection_pool_.push(conn);
}
