#ifndef GRALLOC_PRIV_H_
#define GRALLOC_PRIV_H_

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <errno.h>
#include <linux/fb.h>
#include <sys/types.h>
#include <unistd.h>

#include <cutils/native_handle.h>

#define GRALLOC_ARM_UMP_MODULE 0
#define GRALLOC_ARM_DMA_BUF_MODULE 1
#define SPRD_ION 0
#define SPRD_DITHER_ENABLE 0

// what?
struct _ion_user_handle {
    struct ion_handle *hnd;
    int ion_client;
    int is_used;
};
typedef struct _ion_user_handle ion_user_handle_t;

#define ION_INVALID_HANDLE 0

#define NUM_INTS_IN_PRIVATE_HANDLE ((sizeof(struct private_handle_t) - sizeof(native_handle)) / sizeof(int) - sNumFds)

typedef enum
{
    MALI_YUV_NO_INFO,
    MALI_YUV_BT601_NARROW,
    MALI_YUV_BT601_WIDE,
    MALI_YUV_BT709_NARROW,
    MALI_YUV_BT709_WIDE,
} mali_gralloc_yuv_info;

#ifdef __cplusplus
struct private_handle_t : public native_handle
{
#else
struct private_handle_t
{
    struct native_handle nativeHandle;
#endif

    enum
    {
        PRIV_FLAGS_FRAMEBUFFER = 0x00000001,
        PRIV_FLAGS_USES_UMP    = 0x00000002,
        PRIV_FLAGS_USES_ION    = 0x00000004,
        PRIV_FLAGS_USES_PHY  = 0x00000008,
        PRIV_FLAGS_NOT_OVERLAY   = 0x00000010,
#ifdef SPRD_DITHER_ENABLE
        PRIV_FLAGS_SPRD_DITHER = 0x80000000
#endif
    };

    enum
    {
        LOCK_STATE_WRITE     =   1 << 31,
        LOCK_STATE_MAPPED    =   1 << 30,
        LOCK_STATE_READ_MASK =   0x3FFFFFFF
    };
#if SPRD_ION
    //fds
    int     fd;
#endif
    // ints
#if GRALLOC_ARM_DMA_BUF_MODULE
    /*shared file descriptor for dma_buf sharing*/
    int     share_fd;
#endif

#if GRALLOC_ARM_DMA_BUF_MODULE
    ion_user_handle_t* ion_hnd;
#endif

    // ints
    int        magic;
    int        format;
    uint64_t   internal_format;
    int        byte_stride;
    int        flags;
    int        usage;
    int        size;
    int        width;
    int        height;
    int        stride;
    union {
        void*    base;
        uint64_t padding;
    };
    int        lockState;
    int        writeOwner;
    int        pid;

    mali_gralloc_yuv_info yuv_info;

// #define GRALLOC_ARM_UMP_NUM_INTS 0

    // Following members is for framebuffer only
    // int     fd;

    // Following members is for framebuffer only
    int   fd;
    int   buf_idx;
    union {
        off_t    offset;
        uint64_t padding4;
    };

    // int     offset;

    int     phyaddr;

#if SPRD_ION
    int     resv0;
    int     resv1;
#endif

#if SPRD_ION
#define SPRD_ION_NUM_INTS 2
#else
#define SPRD_ION_NUM_INTS 1
#endif
#if GRALLOC_ARM_DMA_BUF_MODULE
//     int     ion_client;
//     struct ion_handle *ion_hnd;
#define GRALLOC_ARM_DMA_BUF_NUM_INTS 3
#else
#define GRALLOC_ARM_DMA_BUF_NUM_INTS 0
#endif

#if GRALLOC_ARM_DMA_BUF_MODULE
#define GRALLOC_ARM_NUM_FDS 1
#else
#define GRALLOC_ARM_NUM_FDS 0
#endif

#ifdef __cplusplus
    /*
     * We track the number of integers in the structure. There are 11 unconditional
     * integers (magic - pid, yuv_info, fd and offset). The GRALLOC_ARM_XXX_NUM_INTS
     * variables are used to track the number of integers that are conditionally
     * included.
     */
    // static const int sNumInts = 15 + SPRD_ION_NUM_INTS + GRALLOC_ARM_UMP_NUM_INTS + GRALLOC_ARM_DMA_BUF_NUM_INTS;
    static const int sNumFds = GRALLOC_ARM_NUM_FDS;
    static const int sMagic = 0x3141592;

#if GRALLOC_ARM_UMP_MODULE
    private_handle_t(int flags, int usage, int size, int base, int lock_state, ump_secure_id secure_id, ump_handle handle, int offset = 0, int fd = 0):
#if GRALLOC_ARM_DMA_BUF_MODULE
        share_fd(-1),
#endif
        magic(sMagic),
        flags(flags),
        usage(usage),
        size(size),
        width(0),
        height(0),
        format(0),
        stride(0),
        base(base),
        lockState(lock_state),
        writeOwner(0),
        pid(getpid()),
        yuv_info(MALI_YUV_NO_INFO),
        ump_id((int)secure_id),
        ump_mem_handle((int)handle),
        fd(fd),
        offset(offset)
#if GRALLOC_ARM_DMA_BUF_MODULE
        , ion_client(-1),
        ion_hnd(NULL)
#endif

    {
        printf("%s %d\n", __FUNCTION__, __LINE__);
        version = sizeof(native_handle);
        numFds = sNumFds;
        numInts = NUM_INTS_IN_PRIVATE_HANDLE;
    }
#endif

    private_handle_t(int flags, int usage, int size, void *base, int lock_state):
#if GRALLOC_ARM_DMA_BUF_MODULE
        share_fd(-1),
#endif
#if MALI_AFBC_GRALLOC == 1
        share_attr_fd(-1),
#endif
#if GRALLOC_ARM_DMA_BUF_MODULE
        ion_hnd(ION_INVALID_HANDLE),
#endif
        magic(sMagic),
        flags(flags),
        usage(usage),
        size(size),
        width(0),
        height(0),
        stride(0),
        base(base),
        lockState(lock_state),
        writeOwner(0),
        pid(getpid()),
#if MALI_AFBC_GRALLOC == 1
        attr_base(MAP_FAILED),
#endif
        yuv_info(MALI_YUV_NO_INFO),
        fd(0),
        buf_idx(0),
        offset(0)
#if GRALLOC_ARM_UMP_MODULE
        , ump_id(UMP_INVALID_SECURE_ID),
        ump_mem_handle(UMP_INVALID_MEMORY_HANDLE)
#endif
    {
        printf("%s %d\n", __FUNCTION__, __LINE__);
        version = sizeof(native_handle);
        printf("==========%s %d version:%d\n", __FUNCTION__, __LINE__, version);
        numFds = sNumFds;
        numInts = NUM_INTS_IN_PRIVATE_HANDLE;
    }

    private_handle_t(int flags, int usage, int size, void *base, int lock_state, int fb_file, off_t fb_offset, int unused):
#if GRALLOC_ARM_DMA_BUF_MODULE
        share_fd(-1),
#endif
#if MALI_AFBC_GRALLOC == 1
        share_attr_fd(-1),
#endif
#if GRALLOC_ARM_DMA_BUF_MODULE
        ion_hnd(ION_INVALID_HANDLE),
#endif
        magic(sMagic),
        flags(flags),
        usage(usage),
        size(size),
        width(0),
        height(0),
        stride(0),
        base(base),
        lockState(lock_state),
        writeOwner(0),
        pid(getpid()),
#if MALI_AFBC_GRALLOC == 1
        attr_base(MAP_FAILED),
#endif
        yuv_info(MALI_YUV_NO_INFO),
        fd(fb_file),
        buf_idx(0),
        offset(fb_offset)
#if GRALLOC_ARM_UMP_MODULE
        , ump_id(UMP_INVALID_SECURE_ID),
        ump_mem_handle(UMP_INVALID_MEMORY_HANDLE)
#endif
    {
        printf("%s %d\n", __FUNCTION__, __LINE__);
        version = sizeof(native_handle);
        numFds = sNumFds;
        numInts = NUM_INTS_IN_PRIVATE_HANDLE;
    }

    ~private_handle_t()
    {
        magic = 0;
    }

    bool usesPhysicallyContiguousMemory()
    {
        // return (flags & (PRIV_FLAGS_FRAMEBUFFER | PRIV_FLAGS_USES_PHY)) ? true : false;
        return (flags & PRIV_FLAGS_FRAMEBUFFER) ? true : false;
    }

    static int validate(const native_handle *h)
    {
        const private_handle_t* hnd = (const private_handle_t*)h;
        printf("============%p\n", hnd);
        printf("========version:%d====native_handle:%d\n", hnd->version, sizeof(native_handle));
        if (!h ||
                h->version != sizeof(native_handle) ||
                h->numInts != NUM_INTS_IN_PRIVATE_HANDLE ||
                h->numFds != sNumFds ||
                hnd->magic != sMagic)
        {
            printf("%s %d\n", __FUNCTION__, __LINE__);
            return -EINVAL;
        }
        return 0;
    }

    static private_handle_t *dynamicCast(const native_handle *in)
    {
        if (validate(in) == 0)
        {
            return (private_handle_t*) in;
        }

        printf("%s %d\n", __FUNCTION__, __LINE__);
        return NULL;
    }
#endif
};

#endif /* GRALLOC_PRIV_H_ */
