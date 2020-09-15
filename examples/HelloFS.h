#ifndef HELLOFS_H_
#define HELLOFS_H_

#include <FuseLowLevel-impl.h>
#include <FuseLowLevel.h>

class HelloFS
    : public FuseppLowLevel::FuseLowLevel<HelloFS> {
private:
  struct dirbuf {
    char *p;
    size_t size;
  };

public:
  HelloFS(int argc, char **argv)
      : FuseppLowLevel::FuseLowLevel<HelloFS>(argc, argv){};
  ~HelloFS() = default;

  static int hello_stat(fuse_ino_t ino, struct stat *stbuf);
  static void getattr(fuse_req_t req, fuse_ino_t ino,
                      struct fuse_file_info *fi);
  static void lookup(fuse_req_t req, fuse_ino_t parent, const char *name);
  static void dirbuf_add(fuse_req_t req, struct dirbuf *b, const char *name,
                         fuse_ino_t ino);
  static int reply_buf_limited(fuse_req_t req, const char *buf, size_t bufsize,
                               off_t off, size_t maxsize);
  static void readdir(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off,
                      struct fuse_file_info *fi);
  static void open(fuse_req_t req, fuse_ino_t ino, struct fuse_file_info *fi);
  static void read(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off,
                   struct fuse_file_info *fi);
};

#endif // HELLOFS_H_