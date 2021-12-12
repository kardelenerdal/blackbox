/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _PART_B_H_RPCGEN
#define _PART_B_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct numbers {
	int a;
	int b;
	char pathOfBlackbox[500];
};
typedef struct numbers numbers;

#define BLACKBOX_PROG 0x12345678
#define BLACKBOX_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define blackbox 1
extern  char ** blackbox_1(numbers *, CLIENT *);
extern  char ** blackbox_1_svc(numbers *, struct svc_req *);
extern int blackbox_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define blackbox 1
extern  char ** blackbox_1();
extern  char ** blackbox_1_svc();
extern int blackbox_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_numbers (XDR *, numbers*);

#else /* K&R C */
extern bool_t xdr_numbers ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_PART_B_H_RPCGEN */
