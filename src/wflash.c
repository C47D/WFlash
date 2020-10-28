/**/

#include <stdio.h>

#include "wflash.h"
#include "wflash_ll.h"

#define WFLASH_PAGE_SIZE    32

/* The flash memory can't handle writing past the page boundary
 * (it roll over to the begginning of the page), so we need to
 * divide the data transfers in chunks of max size WFLASH_PAGE_SIZE. */
uint32_t wflash_write(uint32_t addr, void *data, size_t data_sz)
{
    uint8_t *data_ptr = data;
    uint32_t bytes_to_write = data_sz;
    uint32_t chunk_size = 0;

    while (bytes_to_write) {
        
        /* if we have more than WFLASH_PAGE_SIZE bytes to write */
        if (bytes_to_write >= WFLASH_PAGE_SIZE) {
            /* Offset from beginning of page to addr */
            uint32_t offset = addr % WFLASH_PAGE_SIZE;
            printf("offset: %d\r\n", offset);
            chunk_size = WFLASH_PAGE_SIZE - offset;
        } else {
            /* last chunk to write */
            chunk_size = bytes_to_write % WFLASH_PAGE_SIZE;
        }
        
        printf("Writting %d bytes in addr: %d\r\n", chunk_size, addr);
            
        wflash_ll_program(addr, data_ptr, chunk_size);

        bytes_to_write -= chunk_size;
        addr += chunk_size;
        data_ptr += chunk_size;
    }

    return 1;
}
