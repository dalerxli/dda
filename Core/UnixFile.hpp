/*
 * Copyright (c) 2010-2013 Steffen Kieß
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef CORE_UNIXFILE_HPP_INCLUDED
#define CORE_UNIXFILE_HPP_INCLUDED

#include <Core/Util.hpp>

#if OS_UNIX

#include <Core/Assert.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/shared_ptr.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/socket.h>

namespace Core {
  class UnixFile {
    struct Shared {
      int fd;
      Shared (int fd) : fd (fd) {}
      ~Shared ();
    };
    boost::shared_ptr<Shared> shared;

  public:
    UnixFile () : shared () {}
    explicit UnixFile (int fd) : shared (new Shared (fd)) {}

    int fd () const {
      ASSERT (shared);
      return shared->fd;
    }

    int dup () const;

    static UnixFile open (const boost::filesystem::path& path, int flags, mode_t mode = 0);
    static UnixFile socket (int domain, int type, int protocol);
  };
}

#endif // OS_UNIX

#endif // !CORE_UNIXFILE_HPP_INCLUDED
