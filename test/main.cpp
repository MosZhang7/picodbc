#include "iostream"
#include "picodbc.h"

int main() {
  Picodbc p;
  p.Connect("DSN=MICSOCC;UID=mics;PWD=GZL11mics");
  auto c = p.GetConnection();
  c.ExecuteQuery("select * from location");
  std::cout << "test" << std::endl;
}