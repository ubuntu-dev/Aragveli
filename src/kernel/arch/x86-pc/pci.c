/*
 * Copyright (c) 2018 Konstantin Tcholokachvili.
 * All rights reserved.
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include <lib/types.h>
#include <lib/c/stdio.h>
#include <arch/x86-pc/vbe.h>
#include <arch/x86/io-ports.h>
#include <arch/x86-pc/pci.h>

// https://wiki.osdev.org/PCI

const char* PCI_CLASS_IDS[18] =
{
    "no class specification",
    "Mass Storage Controller",
    "Network Controller",
    "Display Controller",
    "Multimedia Device",
    "Memory Controller",
    "Bridge Device",
    "Simple Communication Controller",
    "Base System Peripheral",
    "Input Device",
    "Docking Station",
    "Processor",
    "Serial Bus Controller",
    "Wireless Controller",
    "Intelligent I/O Controller",
    "Satellite Communication Controller",
    "Encryption/Decryption Controller",
    "Data Acquisition and Signal Processing Controller"
};

pci_device_t pci_devices[16];
uint8_t pci_devices_idx = 0;

uint16_t
pci_config_read_word(uint16_t bus, uint16_t slot, uint16_t func, uint8_t offset)
{
	uint32_t address;
	uint32_t lbus = (uint32_t)bus;
	uint32_t lslot = (uint32_t)slot;
	uint32_t lfunc = (uint32_t)func;
	uint16_t tmp = 0;

	address = (uint32_t)((lbus << 16) | (lslot << 11) | (lfunc << 8)
			| (offset & 0xfc) | ((uint32_t)0x80000000));

	outl(PCI_CONFIG_ADDR, address);

	tmp = (uint16_t)((inl(PCI_CONFIG_DATA) >> ((offset & 2) * 8)) & 0xffff);

	return tmp;
}

void
pci_config_write_dword (uint16_t bus, uint16_t device, uint16_t function,
		uint8_t offset, uint32_t value)
{
	uint32_t address =
		(uint32_t)(1 << 31)  //enabled
		| (uint32_t)(bus << 16)  //bus number
		| (uint32_t)(device << 11)  //device number
		| (uint32_t)(function << 8) //function number
		| ((uint32_t)offset & 0xfc); //Register number

	outl(PCI_CONFIG_ADDR, address);
	outl(PCI_CONFIG_DATA, value);
}

uint16_t
pci_get_vendor_id(uint16_t bus, uint16_t slot, uint16_t function)
{
	return pci_config_read_word(bus, slot, function, 0);
}

uint16_t
pci_get_device_id(uint16_t bus, uint16_t slot, uint16_t function)
{
	return pci_config_read_word(bus, slot, function, 2);
}

uint16_t
pci_get_device_class_id(uint16_t bus, uint16_t slot, uint16_t function)
{
	uint32_t class_id_seg;
	class_id_seg = pci_config_read_word(bus, slot, function, 0xA);

	return (class_id_seg & ~0x00ff) >> 8;
}

static void
pci_device_add(uint16_t bus, uint16_t slot, uint16_t vendor_id,
		uint16_t device_id, uint16_t class_id, uint16_t function)
{
	pci_devices[pci_devices_idx].bus       = bus;
	pci_devices[pci_devices_idx].slot      = slot;
	pci_devices[pci_devices_idx].func      = function;
	pci_devices[pci_devices_idx].vendor_id = vendor_id;
	pci_devices[pci_devices_idx].device_id = device_id;
	pci_devices[pci_devices_idx].class_id  = class_id;

	pci_devices_idx++;
}

void
pci_scan(void)
{
	for (uint16_t bus = 0; bus < 256; bus++)
	{
		for (uint16_t slot = 0; slot < 32; slot++)
		{
			for (uint16_t function = 0; function < 8; function++)
			{
				if (pci_devices_idx > 15)
				{
					printf("PCI device not added... Limit reached!\n");
					return;
				}

				uint16_t vendor_id = pci_get_vendor_id(bus, slot, function);
				if (vendor_id == 0xffff)
					continue;

				uint16_t device_id = pci_get_device_id(bus, slot, function);
				uint16_t class_id = pci_get_device_class_id(bus, slot, function);

				pci_device_add(bus, slot, vendor_id, device_id, class_id, function);
			}
		}
	}
}

pci_device_t
pci_device_lookup(uint16_t vendor_id, uint16_t device_id)
{
	for (int i = 0; i < 15; i++)
	{
		if (pci_devices[i].vendor_id == vendor_id
				&& pci_devices[i].device_id == device_id)
		{
			return pci_devices[i];
		}
	}

	return (pci_device_t){0, 0, 0, 0, 0, 0};
}

void
pci_devices_print(void)
{
	vbe_set_color(NORMAL_CYAN);

	for (int i = 0; i < 15; i++)
	{
		if (pci_devices[i].vendor_id == 0
			&& pci_devices[i].device_id == 0)
		{
			return;
		}

		printf("PCI Vendor ID:%x Device ID:%x Class:%s\n",
				pci_devices[i].vendor_id,
				pci_devices[i].device_id,
				PCI_CLASS_IDS[pci_devices[i].class_id]);
	}
}
