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
#define TERMINAL_BEGINNING "q8_Q7"
#define TERMINAL_ENDING "I761r"
#define GRAPHING_BEGINNING "l058~"
#define GRAPHING_ENDING "zC43_"
#define TOP ",1,"
#define BOT ",2,"
#define GRAPH(name, data, type) \
    Serial.print(GRAPHING_BEGINNING);         \
    Serial.print(name);         \
    Serial.print(type);         \
    Serial.print(data);         \
    Serial.print(GRAPHING_ENDING);
#define PRINT(text)     \
    Serial.print(TERMINAL_BEGINNING); \
    Serial.print(text); \
    Serial.print(TERMINAL_ENDING);
#define PRINTLN(text)     \
    Serial.print(TERMINAL_BEGINNING); \
    Serial.print(text); \
    Serial.println(TERMINAL_ENDING);
#define PRINTHEX(text)     \
    Serial.print(TERMINAL_BEGINNING); \
    Serial.print(text,HEX) \
    Serial.println(TERMINAL_ENDING);
#define PRINTF(float, places)  \
    Serial.print(TERMINAL_BEGINNING); \
    Serial.print(float,places); \
    Serial.print(TERMINAL_ENDING);
#define PRINTFLN(float, places)  \
    Serial.print(TERMINAL_BEGINNING); \
    Serial.print(float,places); \
    Serial.println(TERMINAL_ENDING);
#define PRINTRAW(text) Serial.print(text);
#define PRINTRAWLN(text) Serial.println(text);
#define END_LOG Serial.println();

namespace internal {

template <typename T>
void read(T bus, uint8_t addr, uint8_t reg, uint8_t* buf, uint16_t len) {
    bus->beginTransmission(addr);
    bus->write(reg);
    bus->endTransmission();

    bus->requestFrom(addr, len);
    while (bus->available()) {
        for (uint16_t i = 0; i < len; i ++) {
            buf[i] = bus->read();
        }
    }
}

template <typename T>
static int writeByte(T bus, uint8_t addr, uint8_t reg, uint8_t data){
    bus->beginTransmission(addr);
    bus->write(reg);
    bus->write(data);
    auto sad = bus->endTransmission();
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
    if (!condition) {
        return true;
    }
    delay(1000);
    while (true) {
    PRINT("Assertion failed!");
    PRINT("Condition: " + conditionS);
    PRINT("File: " + file);
    PRINT("Line: " + String(line));
    PRINT(message);
    END_LOG;
    }
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
