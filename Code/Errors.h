#pragma once
extern std::mutex messageMutex;

template <typename... ARGS>
void ErrorMessage(const char* title, const char* message, ARGS... args)
{
  std::thread messageThread([=] { 
    messageMutex.try_lock();
    char* buffer = new char[1024];
    sprintf_s(buffer, 1024, message, args...);
    MessageBox(NULL, buffer, title, MB_OK | MB_ICONERROR); 
    delete [] buffer;
    messageMutex.unlock();
  });
  messageThread.detach();
}