// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_STDPTR_H
#define NOVELRT_INTEROP_STDPTR_H

#if __cplusplus
extern "C" {
#endif



  struct weakPtr {
    void* obj;
  };

  struct uniquePtr {
    void* obj;
  };

  struct sharedPtr {
    void* obj;
  };








}
#endif
