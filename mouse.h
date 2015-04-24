void mouse_handler(struct regs *r)
{
  static unsigned char cycle = 0;
  static char mouse_bytes[3];
  mouse_bytes[cycle++] = inb(0x60);

  if (cycle == 3) { // if we have all the 3 bytes...
    cycle = 0; // reset the counter
    // do what you wish with the bytes, this is just a sample
    if ((mouse_bytes[0] & 0x80) || (mouse_bytes[0] & 0x40))
      return; // the mouse only sends information about overflowing, do not care about it and return
    if (!(mouse_bytes[0] & 0x20))
      y |= 0xFFFFFF00; //delta-y is a negative value
    if (!(mouse_bytes[0] & 0x10))
      x |= 0xFFFFFF00; //delta-x is a negative value
    if (mouse_bytes[0] & 0x4)
      puts("Middle button is pressed!n");
    if (mouse_bytes[0] & 0x2)
      puts("Right button is pressed!n");
    if (mouse_bytes[0] & 0x1)
      puts("Left button is pressed!n");
    // do what you want here, just replace the puts's to execute an action for each button
    // to use the coordinate data, use mouse_bytes[1] for delta-x, and mouse_bytes[2] for delta-y
  }
}
