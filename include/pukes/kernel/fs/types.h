#ifndef __KERNEL_FS_TYPES_H__
#define __KERNEL_FS_TYPES_H__

typedef struct {
    /**
     * @brief Name of the file system.
     * 
     */
    const char *name;

    /**
     * @brief Initialise the file system.
     */
    int (*init_context)(FileSystemContext_t*);

    DirectoryEntry_t* (*mount)(FileSystem_t*, int, const char*, void*);
} FileSystem_t;

typedef struct {

} FileSystemContext_t;

typedef struct {

} DirectoryEntry_t;

#endif