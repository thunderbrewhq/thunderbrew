#ifndef CONSOLE_DEVICE_HPP
#define CONSOLE_DEVICE_HPP

#include "gx/CGxFormat.hpp"

#include "console/Detect.hpp"

extern DefaultSettings s_defaults;
extern Hardware s_hardware;
extern bool s_hwChanged;
extern bool s_hwDetect;
extern CGxFormat s_requestedFormat;

void ConsoleDeviceInitialize(const char* title);

bool ConsoleDeviceExists();

void ConsoleDeviceDestroy();

#endif
