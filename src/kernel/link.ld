ENTRY(kernel_entry)
OUTPUT_FORMAT("binary")
addr = 0x00007f00;

SECTIONS
{
  . = addr;
  .entry              : { __entry_start = .;      *(.entry)   }
  .text               : { __text_start = .;       *(.text)    }
  .data               : { __data_start = .;       *(.data)    }
  .rodata             : { __rodata_start = .;     *(.rodata)  }
  .bss                : { __bss_start = .;        *(.bss)     }
  
  __end = .;
}
