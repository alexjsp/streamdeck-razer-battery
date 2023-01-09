#include "MyStreamDeckPlugin.h"

#include <StreamDeckSDK/ESDMain.h>
#include <StreamDeckSDK/ESDLogger.h>

int main(int argc, const char** argv) {
  ESDLogger::Get()->SetWin32DebugPrefix("[alexraz] ");
  return esd_main(argc, argv, new MyStreamDeckPlugin());
}
