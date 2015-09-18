#ifndef __PACKING_H
#define __PACKING_H

#ifdef _MSC_VER
#define PACK() __pragma(pack(push, 1))
#define UNPACK() __pragma(pack(pop))
#define PACKED()
#endif /* _MSC_VER */

#endif /* __PACKING_H */
