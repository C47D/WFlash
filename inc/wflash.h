#ifndef WFLASH_H_
#define WFLASH_H_

#include <stdint.h>
#include <stddef.h>

uint32_t wflash_write(uint32_t addr, void *data, size_t data_sz);

#endif /* WFLASH_H_ */
