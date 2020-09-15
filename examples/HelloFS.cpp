/**
 * 
 * @file HelloFS.cpp
 * @date 15.09.2020
 * @author Biethi
 * @copyright MIT License
 *
 */

#include "HelloFS.h"

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// This needs to be included in this one cpp file to make sure FuseLowLevel.cpp is part of this Project and compiled.
#include <FuseLowLevel-impl.h>

static constexpr char hello_str[] = "Hello World!\n";
static constexpr char hello_name[] = "hello";

int HelloFS::hello_stat(fuse_ino_t ino, struct stat *stbuf) {
  stbuf->st_ino = ino;
  switch (ino) {
  case 1:
    stbuf->st_mode = S_IFDIR | 0755;
    stbuf->st_nlink = 2;
    break;

  case 2:
    stbuf->st_mode = S_IFREG | 0444;
    stbuf->st_nlink = 1;
    stbuf->st_size = strlen(hello_str);
    break;

  default:
    return -1;
  }
  return 0;
}

void HelloFS::getattr(fuse_req_t req, fuse_ino_t ino,
                                        struct fuse_file_info *fi) {
  struct stat stbuf;

  (void)fi;

  memset(&stbuf, 0, sizeof(stbuf));
  if (hello_stat(ino, &stbuf) == -1)
    fuse_reply_err(req, ENOENT);
  else
    fuse_reply_attr(req, &stbuf, 1.0);
}

void HelloFS::lookup(fuse_req_t req, fuse_ino_t parent,
                                       const char *name) {
  struct fuse_entry_param e;

  if (parent != 1 || strcmp(name, hello_name) != 0)
    fuse_reply_err(req, ENOENT);
  else {
    memset(&e, 0, sizeof(e));
    e.ino = 2;
    e.attr_timeout = 1.0;
    e.entry_timeout = 1.0;
    hello_stat(e.ino, &e.attr);

    fuse_reply_entry(req, &e);
  }
}

void HelloFS::dirbuf_add(fuse_req_t req, struct dirbuf *b,
                                  const char *name, fuse_ino_t ino) {
  struct stat stbuf;
  size_t oldsize = b->size;
  b->size += fuse_add_direntry(req, NULL, 0, name, NULL, 0);
  b->p = (char *)realloc(b->p, b->size);
  memset(&stbuf, 0, sizeof(stbuf));
  stbuf.st_ino = ino;
  fuse_add_direntry(req, b->p + oldsize, b->size - oldsize, name, &stbuf,
                    b->size);
}

#define min(x, y) ((x) < (y) ? (x) : (y))

int HelloFS::reply_buf_limited(fuse_req_t req, const char *buf,
                                        size_t bufsize, off_t off,
                                        size_t maxsize) {
  if (off < bufsize)
    return fuse_reply_buf(req, buf + off, min(bufsize - off, maxsize));
  else
    return fuse_reply_buf(req, NULL, 0);
}

void HelloFS::readdir(fuse_req_t req, fuse_ino_t ino,
                                        size_t size, off_t off,
                                        struct fuse_file_info *fi) {
  (void)fi;

  if (ino != 1)
    fuse_reply_err(req, ENOTDIR);
  else {
    struct dirbuf b;

    memset(&b, 0, sizeof(b));
    dirbuf_add(req, &b, ".", 1);
    dirbuf_add(req, &b, "..", 1);
    dirbuf_add(req, &b, hello_name, 2);
    reply_buf_limited(req, b.p, b.size, off, size);
    free(b.p);
  }
}

void HelloFS::open(fuse_req_t req, fuse_ino_t ino,
                                     struct fuse_file_info *fi) {
  if (ino != 2)
    fuse_reply_err(req, EISDIR);
  else if ((fi->flags & 3) != O_RDONLY)
    fuse_reply_err(req, EACCES);
  else
    fuse_reply_open(req, fi);
}

void HelloFS::read(fuse_req_t req, fuse_ino_t ino,
                                     size_t size, off_t off,
                                     struct fuse_file_info *fi) {
  (void)fi;

  assert(ino == 2);
  reply_buf_limited(req, hello_str, strlen(hello_str), off, size);
}