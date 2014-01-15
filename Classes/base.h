typedef int BOOL;

#define NULL 0
#define TRUE 1
#define FALSE 0

#define KGLOG_CHECK_ERROR(Condition) \
    do  \
    {   \
    if (!(Condition))       \
        {                       \
        printf(        \
        "KGLOG_CHECK_ERROR(%s) at line %d in %s\n", #Condition, __LINE__, __FUNCTION__  \
        );                  \
        }                       \
    } while (false)

#define KGLOG_PROCESS_ERROR(Condition) \
    do  \
    {   \
    if (!(Condition))       \
        {                       \
        printf(        \
        "KGLOG_PROCESS_ERROR(%s) at line %d in %s\n", #Condition, __LINE__, __FUNCTION__  \
        );                  \
        goto Exit0;         \
        }                       \
    } while (false)

#define KGLOG_PROCESS_ERROR_CONTINUE(Condition) \
    do  \
{   \
    if (!(Condition))       \
{                       \
    printf(        \
    "KGLOG_PROCESS_CONTINUE(%s) at line %d in %s\n", #Condition, __LINE__, __FUNCTION__  \
    );                  \
    continue;         \
}                       \
} while (false)

#define KG_PROCESS_ERROR(Condition) \
    do  \
    {   \
    if (!(Condition))   \
    goto Exit0;     \
    } while (false)

#define SAFE_DELETE(p) if(p) {delete p; p = NULL;}
#define SAFE_FREE(p) if(p) { free(p); p = NULL;}