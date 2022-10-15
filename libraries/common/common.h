#pragma once
//simple assert for now

/*
#define LOG(x) { std::cout << x << std::endl; }
#define assert(condition) internal::assertCheck(condition,__FILE__,__LINE__);
namespace internal {
static bool assertCheck(bool condition, std::string file, int line) {
  if (condition) {
    return true;
  }
  LOG("--------------");
  LOG("ASSERT FAILED");
  LOG("File: " + file + ", Line: " + std::to_string(line));
  LOG("--------------");
  return false;
}
}
*/

//Arduino assert condition
#define assert(condition, message) internal::assertionCheck(condition, #condition, __FILE__, __LINE__, message);
//functions like an assert but wont hang the code will simple raise a flag on execution
#define warn(condition, message) internal::warnCheck(condition, #condition, __FILE__, __LINE__, message);


// Graphing macros
#define TOP ",1,"
#define BOT ",2,"
#define GRAPH(name, data, type) Serial.print("g("); Serial.print(name); Serial.print(type); Serial.print(data); Serial.print(")");
#define PRINT(text) Serial.print("t("); Serial.print(text); Serial.print(")");
#define END_LOG Serial.println();

namespace internal {
static bool assertionCheck(bool condition, String conditionS, String file, int line, String message) {
  if (condition) {
    return true;
  }
  PRINT("-------------------------");
  PRINT("Assertion failed!");
  PRINT("Condition: " + conditionS);
  PRINT("File: " + file);
  PRINT("Line: " + String(line));
  PRINT(message);
  PRINT("-------------------------");
  while (true) {}
  return false;
}
static bool warnCheck(bool condition, String conditionS, String file, int line, String message) {
  if (condition) {
    return true;
  }
  PRINT("-------------------------");
  PRINT("Warning");
  PRINT("Condition: " + conditionS);
  PRINT("File: " + file);
  PRINT("Line: " + String(line));
  PRINT(message);
  PRINT("-------------------------");
  return false;
}
}
