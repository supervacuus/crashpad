// Copyright 2017 The Crashpad Authors. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <sys/epoll.h>

#include <dlfcn.h>
#include <sys/syscall.h>
#include <unistd.h>

#if __ANDROID_API__ < 21

extern "C" {

int epoll_create1(int flags) {
  static const auto epoll_create1_p =
      reinterpret_cast<int (*)(int)>(dlsym(RTLD_DEFAULT, "epoll_create1"));
  if (epoll_create1_p) {
    return epoll_create1_p(flags);
  }

  return syscall(SYS_epoll_create1, flags);
}

}  // extern "C"

#endif  // __ANDROID_API__ < 21
