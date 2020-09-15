/**
 * 
 * @file fuse_test_main.cpp
 * @date 15.09.2020
 * @author Biethi
 * @copyright MIT License
 *
 */

#include "HelloFS.h"

#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <thread>

int main(int argc, char *argv[])
{
  std::cout << "my pid: " << ::getpid() << std::endl;
  std::cout << "running thread id: " << std::this_thread::get_id() << std::endl;

  std::unique_ptr<std::thread> fuse_thread;
  std::unique_ptr<HelloFS> fs;

  const char *my_argv[] = {"HelloFS", "./test_dir"};
  try
  {
    fs = std::make_unique<HelloFS>(2, const_cast<char **>(my_argv));
    fuse_thread =
        std::make_unique<std::thread>(&HelloFS::run, std::ref(*fs));
  }
  catch (std::runtime_error e)
  {
    std::cout << "HelloFS not created: " << e.what() << std::endl;
  }

  if (fuse_thread)
  {
    std::cout << "running fuse thread: " << fuse_thread->get_id() << std::endl;
    while (1)
    {
      std::cout << "Type 'stop' to exit or 'print' to print content: ";
      std::string input;
      std::cin >> input;
      if (input.compare("stop") == 0)
      {
        break;
      }
      else if (input.compare("print") == 0)
      {
        std::ifstream hello_file("test_dir/hello");
        if (hello_file.is_open())
        {
          std::string line;
          getline(hello_file, line);
          std::cout << line << std::endl;
        }
      }
    }
  }

  std::cout << "Left main loop." << std::endl;

  fs.reset();

  std::cout << "Stopped fuse." << std::endl;

  if (fuse_thread)
  {
    fuse_thread->join();
  }

  return 0;
}