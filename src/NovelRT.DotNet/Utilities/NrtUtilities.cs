// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

using NovelRT.Ecs;
using NovelRT.Interop;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NovelRT.Utilities
{
    internal static class NrtUtilities
    {
        internal static void ThrowExceptionIfFailed(NrtResult result, ShimObject caller){
            if(result!=NrtResult.NRT_SUCCESS){
                switch(result)
                {
                    case NrtResult.NRT_FAILURE_NULLPTR_PROVIDED: throw new ObjectDisposedException(caller.GetType().FullName);
                    case NrtResult.NRT_FAILURE_ARGUMENT_OUT_OF_RANGE: throw new ArgumentOutOfRangeException();
                    //TODO: Implement all NrtResults when Matt stops messing with them
                }
            }
        }
        internal static bool NrtBoolToBool(NrtBool boolean){
            if (boolean == NrtBool.NRT_TRUE)
                return true;
            return false;
        }
    }
}
