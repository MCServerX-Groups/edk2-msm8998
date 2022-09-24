#ifndef _DEVICE_MEMORY_MAP_H_
#define _DEVICE_MEMORY_MAP_H_

#include <Library/ArmLib.h>

#define MAX_ARM_MEMORY_REGION_DESCRIPTOR_COUNT 95

/* Below flag is used for system memory */
#define SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES                               \
  EFI_RESOURCE_ATTRIBUTE_PRESENT | EFI_RESOURCE_ATTRIBUTE_INITIALIZED |        \
      EFI_RESOURCE_ATTRIBUTE_TESTED | EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |     \
      EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |                               \
      EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |                         \
      EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE |                            \
      EFI_RESOURCE_ATTRIBUTE_EXECUTION_PROTECTABLE

typedef enum { NoHob, AddMem, AddDev, MaxMem } DeviceMemoryAddHob;

#define MEMORY_REGION_NAME_MAX_LENGTH 32

typedef struct {
  CHAR8                        Name[MEMORY_REGION_NAME_MAX_LENGTH];
  EFI_PHYSICAL_ADDRESS         Address;
  UINT64                       Length;
  DeviceMemoryAddHob           HobOption;
  EFI_RESOURCE_TYPE            ResourceType;
  EFI_RESOURCE_ATTRIBUTE_TYPE  ResourceAttribute;
  EFI_MEMORY_TYPE              MemoryType;
  ARM_MEMORY_REGION_ATTRIBUTES ArmAttributes;
} ARM_MEMORY_REGION_DESCRIPTOR_EX, *PARM_MEMORY_REGION_DESCRIPTOR_EX;

#define MEM_RES EFI_RESOURCE_MEMORY_RESERVED
#define MMAP_IO EFI_RESOURCE_MEMORY_MAPPED_IO
#define SYS_MEM EFI_RESOURCE_SYSTEM_MEMORY

#define SYS_MEM_CAP SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES
#define INITIALIZED EFI_RESOURCE_ATTRIBUTE_INITIALIZED
#define UNCACHEABLE EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE
#define WRITE_THROUGH_CACHEABLE EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE

#define Reserv EfiReservedMemoryType
#define Conv EfiConventionalMemory
#define BsData EfiBootServicesData
#define RtData EfiRuntimeServicesData
#define BsCode EfiBootServicesCode
#define MaxMem EfiMaxMemoryType
#define MmIO EfiMemoryMappedIO

#define NS_DEVICE ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE
#define WRITE_THROUGH ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH
#define DEVICE ARM_MEMORY_REGION_ATTRIBUTE_DEVICE
#define WRITE_BACK ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK
#define UNCACHED_UNBUFFERED ARM_MEMORY_REGION_ATTRIBUTE_UNCACHED_UNBUFFERED

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
    /* Name               Address     Length      HobOption        ResourceAttribute    ArmAttributes
                                                          ResourceType          MemoryType */

    /* DDR */
    {"Kernel",              0x80000000, 0x01AC0000, AddMem, SYS_MEM, SYS_MEM_CAP, BsCode, WRITE_BACK},
    {"Display Reserved",    0x9D400000, 0x02400000, AddMem, MEM_RES, WRITE_THROUGH_CACHEABLE, MaxMem, WRITE_THROUGH},
    {"DBI Dump",            0x9D330000, 0x000D0000, NoHob,  MMAP_IO, INITIALIZED, Conv, DEVICE},
    {"HLOS1",               0x81AC0000, 0x03C40000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"MPSS_EFS",            0x85E00000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, DEVICE},
    {"SMEM",                0x86000000, 0x00200000, AddMem, MEM_RES, UNCACHEABLE, Reserv, UNCACHED_UNBUFFERED},
    {"TZApps",              0x86D00000, 0x00E00000, NoHob,  SYS_MEM, SYS_MEM_CAP, Reserv, DEVICE},
    {"TGCM",                0x87B00000, 0x00A00000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, DEVICE},

#ifdef LG_PIL_FIXED
    {"PIL Reserved",        0x8AB00000, 0x0B415000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, DEVICE},
#else
    {"PIL Reserved",        0x8AB00000, 0x0AD15000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, DEVICE},
#endif

    {"DXE Heap",            0x97C00000, 0x05800000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv, WRITE_BACK},
    {"FV Region",           0x9F800000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"ABOOT FV",            0x9FA00000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, Reserv, WRITE_BACK},
    {"UEFI FD",             0x9FC00000, 0x00300000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"SEC Heap",            0x9FF00000, 0x0008C000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"CPU Vectors",         0x9FF8C000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"MMU PageTables",      0x9FF8D000, 0x00003000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"UEFI Stack",          0x9FF90000, 0x00040000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"RSRV1",               0x9FFD0000, 0x0000A000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
    {"TPMControl",          0x9FFDA000, 0x00003000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
    {"Reset Data",          0x9FFDD000, 0x00004000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
    {"RSRV3",               0x9FFE1000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
    {"Capsule Header",      0x9FFE2000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
    {"RSRV2",               0x9FFE3000, 0x00014000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
    {"Log Buffer",          0x9FFF7000, 0x00008000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
    {"Info Blk",            0x9FFFF000, 0x00001000, AddMem, SYS_MEM, SYS_MEM_CAP, RtData, UNCACHED_UNBUFFERED},
	 
#ifdef MEMORY_4G
	{"4GB Memory",          0xA0000000, 0xDE4C0000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv, WRITE_BACK},
#else
    {"4.6GB Memory 1/2",    0xA0000000, 0x60000000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv, WRITE_BACK},
    {"4.6GB Memory 2/2",    0x100000000, 0xBD8C0000,AddMem, SYS_MEM, SYS_MEM_CAP, Conv, WRITE_BACK},
#endif
 
    /* Other memory regions */
    {"IMEM Base",           0x14680000, 0x00040000, AddDev, MMAP_IO, INITIALIZED, Conv, DEVICE},
	{"IMEM Cookie Base",    0x146BF000, 0x00001000, AddDev, MMAP_IO, INITIALIZED, Conv, DEVICE},
    {"QDSS_STM",            0x16000000, 0x01000000, AddDev, MMAP_IO, INITIALIZED, Conv, DEVICE},

    /*  Registers  */ 
    {"BOOT_CONFIG",         0x00070000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"GCC CLK CTL",         0x00100000, 0x000B0000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"UFS_RUMI",            0x00620000, 0x00020000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"RPM MSG RAM",         0x00778000, 0x00008000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"SECURITY CONTROL",    0x00780000, 0x00007000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"PRNG_CFG_PRNG",       0x00790000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"MPM2_SLP_CNTR",       0x010A3000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"MPM2_TSENS0",         0x010AA000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"MPM2_TSENS0_TM",      0x010AB000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"MPM2_PSHOLD",         0x010AC000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"MPM2_TSENS1",         0x010AD000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"MPM2_TSENS1_TM",      0x010AE000, 0x00001000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
	{"A1_NOC",              0x01680000, 0x00009000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"PCIE WRAPPER AHB",    0x01C00000, 0x00007000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"UFS UFS REGS",        0x01DA0000, 0x00020000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"CRYPTO0 CRYPTO",      0x01DC0000, 0x00040000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"TCSR_TCSR_REGS",      0x01FC0000, 0x00026000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"TLMM CSR",            0x03400000, 0x00C00000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"GPMU_DRAM",           0x05026000, 0x00002000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"GPMU_BLOCK0",         0x0502A000, 0x00002000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"GPU_ISENSE",          0x05030000, 0x00002000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"GPUCC",               0x05065000, 0x00009000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"QDSS_QDSS",           0x06000000, 0x00100000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"HMSS_QLL",            0x06400000, 0x00200000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"PMIC ARB SPMI",       0x08000000, 0x02800000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"USB30_PRIM",          0x0A800000, 0x0011B000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"USB_RUMI",            0x0A920000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"PERIPH_SS",           0x0C000000, 0x00200000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"MMSS",                0x0C800000, 0x00800000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"APCS_CC",             0x17800000, 0x00100000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"QTIMER",              0x17900000, 0x00030000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"APCS_GIC500_GICD",    0x17A00000, 0x00010000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"APCS_GIC500_GICR",    0x17B00000, 0x00100000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
	{"APCS_GIC500_GICC",    0x17C00000, 0x00100000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},
    {"PCIE WRAPPER AXI",    0x1B000000, 0x01000000, AddDev, MMAP_IO, UNCACHEABLE, MmIO, DEVICE},

    /* Terminator for MMU*/
    {"Terminator_MMU", 0},

    /* Terminator for LibMem */
    {"Terminator_LibMem",   0xFFFFFFFF, 0x00001000, AddDev, MMAP_IO,  UNCACHEABLE, MmIO, DEVICE}

};

#endif
