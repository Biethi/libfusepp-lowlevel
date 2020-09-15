/**
 * 
 * @file FuseLowLevel.cpp
 * @date 15.09.2020
 * @author Biethi
 * @copyright MIT License
 *
 */

#include "FuseLowLevel.h"

template<class T> FuseppLowLevel::t_init FuseppLowLevel::FuseLowLevel<T>::init = nullptr;
template<class T> FuseppLowLevel::t_destroy FuseppLowLevel::FuseLowLevel<T>::destroy = nullptr;
template<class T> FuseppLowLevel::t_lookup FuseppLowLevel::FuseLowLevel<T>::lookup = nullptr;
template<class T> FuseppLowLevel::t_forget FuseppLowLevel::FuseLowLevel<T>::forget = nullptr;
template<class T> FuseppLowLevel::t_getattr FuseppLowLevel::FuseLowLevel<T>::getattr = nullptr;
template<class T> FuseppLowLevel::t_setattr FuseppLowLevel::FuseLowLevel<T>::setattr = nullptr;
template<class T> FuseppLowLevel::t_readlink FuseppLowLevel::FuseLowLevel<T>::readlink = nullptr;
template<class T> FuseppLowLevel::t_mknod FuseppLowLevel::FuseLowLevel<T>::mknod = nullptr;
template<class T> FuseppLowLevel::t_mkdir FuseppLowLevel::FuseLowLevel<T>::mkdir = nullptr;
template<class T> FuseppLowLevel::t_unlink FuseppLowLevel::FuseLowLevel<T>::unlink = nullptr;
template<class T> FuseppLowLevel::t_rmdir FuseppLowLevel::FuseLowLevel<T>::rmdir = nullptr;
template<class T> FuseppLowLevel::t_symlink FuseppLowLevel::FuseLowLevel<T>::symlink = nullptr;
template<class T> FuseppLowLevel::t_rename FuseppLowLevel::FuseLowLevel<T>::rename = nullptr;
template<class T> FuseppLowLevel::t_link FuseppLowLevel::FuseLowLevel<T>::link = nullptr;
template<class T> FuseppLowLevel::t_open FuseppLowLevel::FuseLowLevel<T>::open = nullptr;
template<class T> FuseppLowLevel::t_read FuseppLowLevel::FuseLowLevel<T>::read = nullptr;
template<class T> FuseppLowLevel::t_write FuseppLowLevel::FuseLowLevel<T>::write = nullptr;
template<class T> FuseppLowLevel::t_flush FuseppLowLevel::FuseLowLevel<T>::flush = nullptr;
template<class T> FuseppLowLevel::t_release FuseppLowLevel::FuseLowLevel<T>::release = nullptr;
template<class T> FuseppLowLevel::t_fsync FuseppLowLevel::FuseLowLevel<T>::fsync = nullptr;
template<class T> FuseppLowLevel::t_opendir FuseppLowLevel::FuseLowLevel<T>::opendir = nullptr;
template<class T> FuseppLowLevel::t_readdir FuseppLowLevel::FuseLowLevel<T>::readdir = nullptr;
template<class T> FuseppLowLevel::t_releasedir FuseppLowLevel::FuseLowLevel<T>::releasedir = nullptr;
template<class T> FuseppLowLevel::t_fsyncdir FuseppLowLevel::FuseLowLevel<T>::fsyncdir = nullptr;
template<class T> FuseppLowLevel::t_statfs FuseppLowLevel::FuseLowLevel<T>::statfs = nullptr;
template<class T> FuseppLowLevel::t_setxattr FuseppLowLevel::FuseLowLevel<T>::setxattr = nullptr;
template<class T> FuseppLowLevel::t_getxattr FuseppLowLevel::FuseLowLevel<T>::getxattr = nullptr;
template<class T> FuseppLowLevel::t_listxattr FuseppLowLevel::FuseLowLevel<T>::listxattr = nullptr;
template<class T> FuseppLowLevel::t_removexattr FuseppLowLevel::FuseLowLevel<T>::removexattr = nullptr;
template<class T> FuseppLowLevel::t_access FuseppLowLevel::FuseLowLevel<T>::access = nullptr;
template<class T> FuseppLowLevel::t_create FuseppLowLevel::FuseLowLevel<T>::create = nullptr;
template<class T> FuseppLowLevel::t_getlk FuseppLowLevel::FuseLowLevel<T>::getlk = nullptr;
template<class T> FuseppLowLevel::t_setlk FuseppLowLevel::FuseLowLevel<T>::setlk = nullptr;
template<class T> FuseppLowLevel::t_bmap FuseppLowLevel::FuseLowLevel<T>::bmap = nullptr;
template<class T> FuseppLowLevel::t_ioctl FuseppLowLevel::FuseLowLevel<T>::ioctl = nullptr;
template<class T> FuseppLowLevel::t_poll FuseppLowLevel::FuseLowLevel<T>::poll = nullptr;
template<class T> FuseppLowLevel::t_write_buf FuseppLowLevel::FuseLowLevel<T>::write_buf = nullptr;
template<class T> FuseppLowLevel::t_retrieve_reply FuseppLowLevel::FuseLowLevel<T>::retrieve_reply = nullptr;
template<class T> FuseppLowLevel::t_flock FuseppLowLevel::FuseLowLevel<T>::flock = nullptr;
template<class T> FuseppLowLevel::t_fallocate FuseppLowLevel::FuseLowLevel<T>::fallocate = nullptr;

template<class T> struct fuse_lowlevel_ops FuseppLowLevel::FuseLowLevel<T>::operations_;
