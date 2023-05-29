#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char*argv[]) {
    void *handle;
    char *error;
    void (*main)(int, char**);
    handle = dlopen(argv[1], RTLD_LAZY);
    if (!handle) {
         fprintf(stderr, "1:%s\n", dlerror());
         exit(EXIT_FAILURE);
    }

    *(void **) (&main) = dlsym(handle, "main");
    (*main)(argc+1-2, argv+1);
    
    dlerror();    /* Clear any existing error */

    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    dlclose(handle);
    exit(EXIT_SUCCESS);
}
