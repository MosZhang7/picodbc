#include "odbc_api.h"

#include <iostream>

OdbcApi::OdbcApi() : h_env_(SQL_NULL_HENV), h_dbc_(SQL_NULL_HDBC) {
  SQLRETURN ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &h_env_);
  if (!SQL_SUCCEEDED(ret)) {
    HandleError(ret, h_env_, SQL_HANDLE_ENV);
    throw std::runtime_error("Unable to allocate ODBC environment handle");
  }

  ret = SQLSetEnvAttr(h_env_, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);
  if (!SQL_SUCCEEDED(ret)) {
    HandleError(ret, h_env_, SQL_HANDLE_ENV);
    throw std::runtime_error("Unable to set ODBC version");
  }

  ret = SQLAllocHandle(SQL_HANDLE_DBC, h_env_, &h_dbc_);
  if (!SQL_SUCCEEDED(ret)) {
    HandleError(ret, h_dbc_, SQL_HANDLE_DBC);
    throw std::runtime_error("Unable to allocate ODBC connection handle");
  }
}

OdbcApi::~OdbcApi() {
  if (h_dbc_ != SQL_NULL_HDBC) {
    SQLDisconnect(h_dbc_);
    SQLFreeHandle(SQL_HANDLE_DBC, h_dbc_);
  }

  if (h_env_ != SQL_NULL_HENV) {
    SQLFreeHandle(SQL_HANDLE_ENV, h_env_);
  }
}

void OdbcApi::Connect(const std::string& connectionString) {
  SQLCHAR outConnStr[1024];
  SQLSMALLINT outConnStrLen;
  SQLRETURN ret = SQLDriverConnect(
      h_dbc_, NULL, (SQLCHAR*)connectionString.c_str(), SQL_NTS, outConnStr,
      sizeof(outConnStr), &outConnStrLen, SQL_DRIVER_COMPLETE);
  if (!SQL_SUCCEEDED(ret)) {
    HandleError(ret, h_dbc_, SQL_HANDLE_DBC);
    throw std::runtime_error("Database connection failed");
  }
  std::cout << "Connected to database successfully!" << std::endl;
}

void OdbcApi::Disconnect() {
  SQLRETURN ret = SQLDisconnect(h_dbc_);
  if (!SQL_SUCCEEDED(ret)) {
    HandleError(ret, h_dbc_, SQL_HANDLE_DBC);
    throw std::runtime_error("Failed to disconnect from database");
  }
  std::cout << "Disconnected from database successfully!" << std::endl;
}

SQLHDBC OdbcApi::GetConnectionHandle() const { return h_dbc_; }

void OdbcApi::HandleError(SQLRETURN retCode, SQLHANDLE handle,
                          SQLSMALLINT handleType) {
  SQLCHAR sqlState[6];
  SQLCHAR errorMessage[256];
  SQLINTEGER nativeError;
  SQLSMALLINT textLength;

  SQLGetDiagRec(handleType, handle, 1, sqlState, &nativeError, errorMessage,
                sizeof(errorMessage), &textLength);
  std::cerr << "Error: " << errorMessage << " (SQLSTATE: " << sqlState << ")"
            << std::endl;
}
