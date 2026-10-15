#include "misc.h"

void
presult (struct descriptor result)
{
  bool printed = false;
  if (result.entry)
    {
      puts (result.entry, stderr);
      printed = true;
    }
  if (result.ident > 0)
    {
      if (printed)
        puts (": ", stderr);
      puts (strerror (result.ident), stderr);
      printed = true;
    }
  if (printed)
    putc (EOL, stderr);
}
