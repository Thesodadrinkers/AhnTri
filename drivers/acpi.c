//Codename Pari(means 'fly' in Korean)

#include "acpi.h"

void parse_rsdp(uint8_t* addr){
	rsdp_v1_t* rsdp = (rsdp_v1_t*) addr;
	printf("\nSignature: ");
	printf(rsdp->sign);
	uint8_t csum = rsdp->csum;
	printf("\nOEMID: ");
	printf(rsdp->oemid);
	uint8_t revision = rsdp->revision;
	uint32_t rsdtaddr = rsdp->rsdtaddr;
	printf("\nRSDT Address: ");
	printf_hex(rsdtaddr);
}

void parse_rsdt(uint8_t* rsdpaddr){					//Address of RSDP
	rsdp_v1_t* rsdp = (rsdp_v1_t*) rsdpaddr;
	uint32_t* addr = rsdp->rsdtaddr;
	rsdt_t* rsdt = (rsdt_t*) addr;
	acpi_header_t head = rsdt->head;
	printf("\nSigniture: ");
	printf(head.sign);
	uint32_t len = head.len;
	uint8_t revision = head.revision;
	uint8_t csum = head.csum;
	printf("\nOEMID: ");
	printf(head.oemid);
	printf("\nOEM Table ID: ");
	printf(head.oemtbleid);
	uint32_t oemrevision = head.oemrevision;
	uint32_t creatorid = head.creatorid;
	uint32_t creatorrevision = head.creatorrevision;
	int numofrsdtbles = (head.len-sizeof(acpi_header_t))/4;
}

void parse_xsdt(uint8_t* rsdpaddr){					//Address of RSDP
	rsdp_v1_t* rsdp = (rsdp_v1_t*) rsdpaddr;
	uint32_t* addr = rsdp->rsdtaddr;
	xsdt_t* xsdt = (xsdt_t*) addr;
	acpi_header_t head = xsdt->head;
	printf("\nSigniture: ");
	printf(head.sign);
	uint32_t len = head.len;
	uint8_t revision = head.revision;
	uint8_t csum = head.csum;
	printf("\nOEMID: ");
	printf(head.oemid);
	printf("\nOEM Table ID: ");
	printf(head.oemtbleid);
	uint32_t oemrevision = head.oemrevision;
	uint32_t creatorid = head.creatorid;
	uint32_t creatorrevision = head.creatorrevision;
	int numofxsdtbles = (head.len-sizeof(acpi_header_t))/4;
}

uint8_t checksum(const char* addr, uint8_t size){
	const char* end = addr + size;
	uint8_t sum = 0;
	while (addr < end) {
		sum += *addr;
		addr++;
	}
	return sum;
}


void searchforrsdp(){
	uint8_t* addr = (uint8_t*)0x000E0000;
	uint8_t* end = (uint8_t*)0x000FFFFF;
	printf("\nPari ACPI Manager says: ");
	while(addr<end){
		if(*(uint64_t*)addr == 0x2052545020445352 && checksum(addr, sizeof(rsdp_v1_t)) == 0){
			parse_rsdp(addr);
			parse_rsdt(addr);
		}
		addr += 16;
	}
}