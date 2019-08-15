#pragma once

extern std::mutex messageMutex;

template <typename... ARGS>
void AlertMessage(const char* title, const char* message, ARGS... args)
{
  std::string* messageString = new std::string(message);
  std::thread messageThread([=] { 
    messageMutex.try_lock();
    char* buffer = new char[1024];
    sprintf_s(buffer, 1024, messageString->c_str(), args...);
    MessageBox(NULL, buffer, title, MB_OK | MB_ICONERROR);
    delete [] buffer;
    delete messageString;
    messageMutex.unlock();
  });
  messageThread.detach();
}

#define ErrorTest(isError, codeOnError, errorMessage, ...) if (isError) { AlertMessage("Error", errorMessage, __VA_ARGS__); codeOnError; }
#define FatalErrorTest(isError, errorMessage, ...) if (isError) { AlertMessage("Error", errorMessage, __VA_ARGS__); exit(0); }

template <typename... ARGS>
void DebugPrint(const char* message, ARGS... args)
{
  char buffer[1024];
  sprintf_s(buffer, 1024, message, args...);
  OutputDebugString(buffer);
}