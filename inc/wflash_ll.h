#ifndef WFLASH_LL_H_
#define WFLASH_LL_H_

#include <stdint.h>
#include <stddef.h>

uint32_t wflash_ll_program(uint32_t addr, void *data, size_t data_sz);

#endif /* WFLASH_LL_H_ */
