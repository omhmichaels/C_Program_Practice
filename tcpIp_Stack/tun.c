/*
 * Taken from Kernel Documentation/networking/tuntap.txt
 * */


int tun_alloc(char *dev)
{
  struct ifreq ifr;
  int fd, err;      // fd == file  descriptor

  if ((fd= open("/dev/net/tap", O_RDWR)) < 0) {
    print_error("Cannot open TUN/TAP dev");
    exit(1);
  }
  
  CLEAR(ifr);

  /* Flags: IFF_TUN     - TUN device (no ethernet headers)
 *          IFF_TAP     - TAP dev
 *
 *          IFF_NO_PI   - Do not provide practice info
 **/

  ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
  if(*dev) {
     strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }

  if ((err=ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
     print_error("ERR: Could not ioctl tun: %s\n", strerror(errno));
     close(fd);
     return err;
  }
  
  strcpy(dev, ifr.ifr_name);
  return fd;
}

// File descriptor fd can be used to read and write
//   > comms with virtual devices ethernet buffer
//
// IFF_NO_PI
//   > Cruicial
//   > Stops unnessecary info from being prepended to the Ethernet frame
//
