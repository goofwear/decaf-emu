#include "nn_save.h"
#include "nn_save_dir.h"
#include "nn_save_file.h"
#include "modules/coreinit/coreinit_fs_dir.h"
#include "modules/coreinit/coreinit_fs_file.h"

FSStatus
SAVEOpenFile(FSClient *client,
             FSCmdBlock *block,
             uint8_t account,
             const char *path,
             const char *mode,
             be_val<FSFileHandle> *handle,
             uint32_t flags)
{
   auto fsPath = nn_save::internal::getSavePath(account, path);
   return FSOpenFile(client, block, fsPath.path().c_str(), mode, handle, flags);
}

FSStatus
SAVEOpenFileAsync(FSClient *client,
                  FSCmdBlock *block,
                  uint8_t account,
                  const char *path,
                  const char *mode,
                  be_val<FSFileHandle> *handle,
                  uint32_t flags,
                  FSAsyncData *asyncData)
{
   auto fsPath = nn_save::internal::getSavePath(account, path);
   return FSOpenFileAsync(client, block, fsPath.path().c_str(), mode, handle, flags, asyncData);
}

void
NN_save::registerFileFunctions()
{
   RegisterKernelFunction(SAVEOpenFile);
   RegisterKernelFunction(SAVEOpenFileAsync);
}
