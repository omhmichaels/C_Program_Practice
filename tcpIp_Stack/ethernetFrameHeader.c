/*
 * Ethernet Frame Header
 **/

#include <linux/if_ether.h>

struct eth_hdr
{
  unsigned char dmac[6];
  unsigned char smac[6];
  uint16_t ethertype;
  unsigned char [payload[];
}
__attribute__((packed)):

// dmac == destination mac
// smac == sender mac
//
// ethertype
//   > 2 octet field
//    - indicates lenght or type payload.
//    - If field value greater  than or equal to 1536
//    - Payload == IPv4, ARP
//    - If less states lenght of payload
//
// After type field several tag possibilities
//   - describe VLAN
//   - Describe Quality of Service type frame
//
// payload
//   > Contains pointer Ethernet Frames payload
//     - If payload lenght shorter than min req 48 bytes(without tags)
//       pad bytes are appended to the end of payload to meet the requirement
//
//   > if_ether.h
//     - provides mapping between ethertypes and hexadecimal values
//   
// Ethernet Frame Format
//   > Frame Check Sequence (FCS)
//     - End field
//     - Used with Cyclic Redundancy Check (CRC) 
//       + Checks frame integrity

// __attribute((packed))
//   > implementation detail.
//   > Used to instruct GNU C compiler not to optimize the struct memory
//     layout for data alignment with padding bytes
//    + Stems from how we parse the protocol buffer
//    + type cast over the data buffer with the proper protocol struct

struct eth_hdr *hdr = (struct eth_hdr *) buf;

// Portable Laborouis approach would be to serialize the protocol data manually
//  > The compiler is then free to add padding bytes to conform better to 
//    different processors data alignment requirments.

// Overall Scenario for parsing

if (tun_read(buf, BUFLEN) < 0 {
  print_error("ERR: Read from tun_fd: %s\n", strerror(errno));
}

struct eth_hdr *hdr = init_eth_hdr(buf);
  handle_frame(&netdev, hdr);



