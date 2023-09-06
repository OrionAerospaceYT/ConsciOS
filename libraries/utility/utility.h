#pragma once

// Arduino assert condition
#define sk_assert(condition, message)                                      \
    internal::assertionCheck(condition, #condition, __FILE__, __LINE__, \
                             message);
// functions like an assert but wont hang the code will simple raise a flag on
// execution
#define sk_warn(condition, message) \
    internal::warnCheck(condition, #condition, __FILE__, __LINE__, message);

// Graphing macros
#define TOP ",1,"
#define BOT ",2,"
#define GRAPH(name, data, type) \
    Serial.print("g(");         \
    Serial.print(name);         \
    Serial.print(type);         \
    Serial.print(data);         \
    Serial.print(")");
#define PRINT(text)     \
    Serial.print("t("); \
    Serial.print(text); \
    Serial.print(")");
#define PRINTLN(text)     \
    Serial.print("t("); \
    Serial.print(text); \
    Serial.println(")");
#define PRINTHEX(text)     \
    Serial.print("t("); \
    Serial.print(text,HEX) \
    Serial.println(")");
#define PRINTRAW(text) Serial.print(text);
#define PRINTRAWLN(text) Serial.println(text);
#define END_LOG Serial.println();

namespace internal {

template <typename T>
static int writeByte(T bus, uint8_t addr, uint8_t reg, uint8_t data){
    bus->beginTransmission(addr);
    bus->write(reg);
    bus->write(data);
    auto sad = bus->endTransmission();
    PRINTLN(sad)
    return sad;
}

template <typename T>
static uint8_t readByte(T bus, uint8_t addr, uint8_t reg){
    bus->beginTransmission(addr);
    bus->write(reg);
    bus->endTransmission();

    bus->requestFrom((uint8_t)addr, (uint8_t)1);
    return bus->read();
}
static bool assertionCheck(bool condition, String conditionS, String file,
                           int line, String message) {
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
    while (true) {
    }
    return false;
}
static bool warnCheck(bool condition, String conditionS, String file, int line,
                      String message) {
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
}  // namespace internal
