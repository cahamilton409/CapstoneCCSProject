/*
 * FlashMem.h
 *
 *  Created on: Sep 28, 2021
 *      Author: Chris
 */

#ifndef FLASH_MEMORY_H_
#define FLASH_MEMORY_H_

#define MEMORY_LOCATION 0x1800

void flash_memory_init(void);
void save_mappings(void);
void load_mappings(void);

#endif /* FLASH_MEMORY_H_ */
