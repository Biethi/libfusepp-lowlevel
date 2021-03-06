/**
 * 
 * @file FuseLowLevel.cpp
 * @date 15.09.2020
 * @author Biethi
 * @copyright MIT License
 *
 */

#ifndef FUSE_LOW_LEVEL_H_
#define FUSE_LOW_LEVEL_H_

#ifndef FUSE_USE_VERSION
#define FUSE_USE_VERSION 26
#endif

#include <fuse/fuse_lowlevel.h>
#include <string.h>
#include <stdexcept>

#include <boost/noncopyable.hpp>

namespace FuseppLowLevel
{
  typedef void (*t_init)(void *userdata, struct fuse_conn_info *conn);
  typedef void (*t_destroy)(void *userdata);
  typedef void (*t_lookup)(fuse_req_t req, fuse_ino_t parent, const char *name);
  typedef void (*t_forget)(fuse_req_t req, fuse_ino_t ino, unsigned long nlookup);
  typedef void (*t_getattr)(fuse_req_t req, fuse_ino_t ino,
                            struct fuse_file_info *fi);
  typedef void (*t_setattr)(fuse_req_t req, fuse_ino_t ino, struct stat *attr,
                            int to_set, struct fuse_file_info *fi);
  typedef void (*t_readlink)(fuse_req_t req, fuse_ino_t ino);
  typedef void (*t_mknod)(fuse_req_t req, fuse_ino_t parent, const char *name,
                          mode_t mode, dev_t rdev);
  typedef void (*t_mkdir)(fuse_req_t req, fuse_ino_t parent, const char *name,
                          mode_t mode);
  typedef void (*t_unlink)(fuse_req_t req, fuse_ino_t parent, const char *name);
  typedef void (*t_rmdir)(fuse_req_t req, fuse_ino_t parent, const char *name);
  typedef void (*t_symlink)(fuse_req_t req, const char *link, fuse_ino_t parent,
                            const char *name);
  typedef void (*t_rename)(fuse_req_t req, fuse_ino_t parent, const char *name,
                           fuse_ino_t newparent, const char *newname);
  typedef void (*t_link)(fuse_req_t req, fuse_ino_t ino, fuse_ino_t newparent,
                         const char *newname);
  typedef void (*t_open)(fuse_req_t req, fuse_ino_t ino,
                         struct fuse_file_info *fi);
  typedef void (*t_read)(fuse_req_t req, fuse_ino_t ino, size_t size, off_t off,
                         struct fuse_file_info *fi);
  typedef void (*t_write)(fuse_req_t req, fuse_ino_t ino, const char *buf,
                          size_t size, off_t off, struct fuse_file_info *fi);
  typedef void (*t_flush)(fuse_req_t req, fuse_ino_t ino,
                          struct fuse_file_info *fi);
  typedef void (*t_release)(fuse_req_t req, fuse_ino_t ino,
                            struct fuse_file_info *fi);
  typedef void (*t_fsync)(fuse_req_t req, fuse_ino_t ino, int datasync,
                          struct fuse_file_info *fi);
  typedef void (*t_opendir)(fuse_req_t req, fuse_ino_t ino,
                            struct fuse_file_info *fi);
  typedef void (*t_readdir)(fuse_req_t req, fuse_ino_t ino, size_t size,
                            off_t off, struct fuse_file_info *fi);
  typedef void (*t_releasedir)(fuse_req_t req, fuse_ino_t ino,
                               struct fuse_file_info *fi);
  typedef void (*t_fsyncdir)(fuse_req_t req, fuse_ino_t ino, int datasync,
                             struct fuse_file_info *fi);
  typedef void (*t_statfs)(fuse_req_t req, fuse_ino_t ino);
  typedef void (*t_setxattr)(fuse_req_t req, fuse_ino_t ino, const char *name,
                             const char *value, size_t size, int flags);
  typedef void (*t_getxattr)(fuse_req_t req, fuse_ino_t ino, const char *name,
                             size_t size);
  typedef void (*t_listxattr)(fuse_req_t req, fuse_ino_t ino, size_t size);
  typedef void (*t_removexattr)(fuse_req_t req, fuse_ino_t ino, const char *name);
  typedef void (*t_access)(fuse_req_t req, fuse_ino_t ino, int mask);
  typedef void (*t_create)(fuse_req_t req, fuse_ino_t parent, const char *name,
                           mode_t mode, struct fuse_file_info *fi);
  typedef void (*t_getlk)(fuse_req_t req, fuse_ino_t ino,
                          struct fuse_file_info *fi, struct flock *lock);
  typedef void (*t_setlk)(fuse_req_t req, fuse_ino_t ino,
                          struct fuse_file_info *fi, struct flock *lock,
                          int sleep);
  typedef void (*t_bmap)(fuse_req_t req, fuse_ino_t ino, size_t blocksize,
                         uint64_t idx);
  typedef void (*t_ioctl)(fuse_req_t req, fuse_ino_t ino, int cmd, void *arg,
                          struct fuse_file_info *fi, unsigned flags,
                          const void *in_buf, size_t in_bufsz, size_t out_bufsz);
  typedef void (*t_poll)(fuse_req_t req, fuse_ino_t ino,
                         struct fuse_file_info *fi, struct fuse_pollhandle *ph);
  typedef void (*t_write_buf)(fuse_req_t req, fuse_ino_t ino,
                              struct fuse_bufvec *bufv, off_t off,
                              struct fuse_file_info *fi);
  typedef void (*t_retrieve_reply)(fuse_req_t req, void *cookie, fuse_ino_t ino,
                                   off_t offset, struct fuse_bufvec *bufv);
  typedef void (*t_flock)(fuse_req_t req, fuse_ino_t ino,
                          struct fuse_file_info *fi, int op);
  typedef void (*t_fallocate)(fuse_req_t req, fuse_ino_t ino, int mode,
                              off_t offset, off_t length,
                              struct fuse_file_info *fi);

  template <class T>
  class FuseLowLevel : private boost::noncopyable
  {
  public:
  /**
   * @brief Constructor
   * @param argc
   * @param argv
   * @throw std::runtime_error
   */
    FuseLowLevel(int argc, char **argv) : args_(FUSE_ARGS_INIT(argc, argv))
    {
      memset(&T::operations_, 0, sizeof(struct fuse_lowlevel_ops));
      load_operations_();

      if (fuse_parse_cmdline(&args_, &mountpoint_, nullptr, nullptr) != -1 &&
          (ch_ = fuse_mount(mountpoint_, &args_)) != nullptr)
      {

        se_ = fuse_lowlevel_new(&args_, &operations_, sizeof(operations_),
                                nullptr);

        if (se_ != nullptr)
        {
          if (fuse_set_signal_handlers(se_) != -1)
          {
            fuse_session_add_chan(se_, ch_);
          }
          else
          {
            throw std::runtime_error("Fuse signal handler can't be set.");
          }
        }
        else
        {
          throw std::runtime_error("Creation of new fuse session failed.");
        }
      }
      else
      {
        throw std::runtime_error(
            "Command line args error. No filesystem mounted.");
      }
    }

    ~FuseLowLevel()
    {
      fuse_remove_signal_handlers(se_);
      fuse_session_remove_chan(ch_);

      fuse_unmount(mountpoint_, ch_);

      fuse_session_destroy(se_);

      fuse_opt_free_args(&args_);
    }

    int run() { return fuse_session_loop(se_); }

    static struct fuse_lowlevel_ops *Operations() { return &operations_; }

  private:
    struct fuse_args args_;
    struct fuse_chan *ch_;
    char *mountpoint_;
    struct fuse_session *se_;

    static void load_operations_()
    {
      operations_.init = T::init;
      operations_.destroy = T::destroy;
      operations_.lookup = T::lookup;
      operations_.forget = T::forget;
      operations_.getattr = T::getattr;
      operations_.setattr = T::setattr;
      operations_.readlink = T::readlink;
      operations_.mknod = T::mknod;
      operations_.mkdir = T::mkdir;
      operations_.unlink = T::unlink;
      operations_.rmdir = T::rmdir;
      operations_.symlink = T::symlink;
      operations_.rename = T::rename;
      operations_.link = T::link;
      operations_.open = T::open;
      operations_.read = T::read;
      operations_.write = T::write;
      operations_.flush = T::flush;
      operations_.release = T::release;
      operations_.fsync = T::fsync;
      operations_.opendir = T::opendir;
      operations_.readdir = T::readdir;
      operations_.releasedir = T::releasedir;
      operations_.fsyncdir = T::fsyncdir;
      operations_.statfs = T::statfs;
      operations_.setxattr = T::setxattr;
      operations_.getxattr = T::getxattr;
      operations_.listxattr = T::listxattr;
      operations_.removexattr = T::removexattr;
      operations_.access = T::access;
      operations_.create = T::create;
      operations_.getlk = T::getlk;
      operations_.setlk = T::setlk;
      operations_.bmap = T::bmap;
      operations_.ioctl = T::ioctl;
      operations_.poll = T::poll;
      operations_.write_buf = T::write_buf;
      operations_.retrieve_reply = T::retrieve_reply;
      operations_.flock = T::flock;
      operations_.fallocate = T::fallocate;
    }

    static struct fuse_lowlevel_ops operations_;

    static t_init init;
    static t_destroy destroy;
    static t_lookup lookup;
    static t_forget forget;
    static t_getattr getattr;
    static t_setattr setattr;
    static t_readlink readlink;
    static t_mknod mknod;
    static t_mkdir mkdir;
    static t_unlink unlink;
    static t_rmdir rmdir;
    static t_symlink symlink;
    static t_rename rename;
    static t_link link;
    static t_open open;
    static t_read read;
    static t_write write;
    static t_flush flush;
    static t_release release;
    static t_fsync fsync;
    static t_opendir opendir;
    static t_readdir readdir;
    static t_releasedir releasedir;
    static t_fsyncdir fsyncdir;
    static t_statfs statfs;
    static t_setxattr setxattr;
    static t_getxattr getxattr;
    static t_listxattr listxattr;
    static t_removexattr removexattr;
    static t_access access;
    static t_create create;
    static t_getlk getlk;
    static t_setlk setlk;
    static t_bmap bmap;
    static t_ioctl ioctl;
    static t_poll poll;
    static t_write_buf write_buf;
    static t_retrieve_reply retrieve_reply;
    static t_flock flock;
    static t_fallocate fallocate;
  };
}; // namespace FuseppLowLevel

#endif
