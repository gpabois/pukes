MEMORY {
    dport0: org = 0x3FF00000, len = 0x1000
    dram0:  org = 0x3FFE8000, len = 0x14000
    iram1:  org = 0x40100000, len = 0x8000
}

PHDRS {
    dport0_phdr: PT_LOAD;
    dram0_phdr: PT_LOAD;
    iram1_phdr: PT_LOAD;
}

ENTRY(_call_boot_stage_2)

EXTERN(DebugExceptionVector)
EXTERN(DoubleExceptionVector)
EXTERN(KernelExceptionVector)
EXTERN(NMIExceptionVector)
EXTERN(UserExceptionVector)

PROVIDE(memmap_vecbase_reset = 0x40000000);

SECTIONS {
    .dport0.rodata: ALIGN(4) {
        _dport0_rodata_start = ABSOLUTE(.);
        *(.dport0.rodata)
        *(.dport.rodata)
        _dport0_rodata_end = ABSOLUTE(.);
    } >dport0 :dport0_phdr

    .dport0.literal: ALIGN(4) {
        _dport0_literal_start = ABSOLUTE(.);
        *(.dport0.literal)
        *(.dport.literal)
        _dport0_literal_end = ABSOLUTE(.);
    } >dport0 :dport0_phdr

    .dport0.data: ALIGN(4) {
        _dport0_data_start = ABSOLUTE(.);
        *(.dport0.data)
        *(.dport.data)
        _dport0_data_end = ABSOLUTE(.);
    } >dport0 :dport0_phdr

    .data: ALIGN(4) {
        _data_start = ABSOLUTE(.);
        *(.data)
        _data_end = ABSOLUTE(.);
    } >dram0 :dram0_phdr

    .rodata: ALIGN(4) {
        _rodata_start = ABSOLUTE(.);
        *(.rodata)
        *(.rodata.*)
        .= ALIGN(4);
        _bss_table_start = ABSOLUTE(.);
        LONG(_bss_start)
        LONG(_bss_end)
        _bss_table_end = ABSOLUTE(.);
        _rodata_end = ABSOLUTE(.);

    } >dram0 :dram0_phdr

    .bss ALIGN(8) (NOLOAD) : ALIGN(4) {
        . = ALIGN(8);
        _bss_start = ABSOLUTE(.);
        *(.bss)
        *(.bss.*)
        . = ALIGN(8);
        _bss_end = ABSOLUTE(.);
        _heap_start = ABSOLUTE(.);
    } >dram0 :dram0_phdr

    .text : ALIGN(4) {
        _stext = .;
        _text_start = ABSOLUTE(.);
        . = ALIGN (16);
        *(.text)
        _text_end = ABSOLUTE(.);
        _etext = .;
    } >iram1 :iram1_phdr
}

INCLUDE "builtins.ld"