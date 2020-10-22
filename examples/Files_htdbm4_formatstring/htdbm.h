#include <stdlib.h>

#define APR_SUCCESS EXIT_SUCCESS
#define APR_EGENERAL EXIT_SUCCESS
#define APR_ENOENT EXIT_SUCCESS

typedef struct apr_status_t apr_status_t;

typedef struct htdbm_list * phtdbm_list;


apr_status_t apr_dbm_firstkey();
apr_status_t apr_dbm_fetch();
apr_status_t apr_dbm_nextkey();

typedef struct{
    int dbm;
    char filename;
}htdbm_t;

struct htdbm_t *htdbm;

typedef struct {
    int dsize;
    char *dptr;
}apr_datum_t;

apr_datum_t key;
apr_datum_t val;