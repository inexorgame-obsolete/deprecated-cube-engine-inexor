
/*
#include <svn_client.h>
#include <svn_pools.h>
#include <apr.h>

namespace game
{

    void getmaps() {
        apr_pool_t *pool = NULL;
        apr_pool_create(&pool, NULL);
        svn_client_ctx_t *context = NULL;
        svn_client_create_context(&context, pool);
        svn_opt_revision_t revision;
        revision.kind = svn_opt_revision_head;
        svn_error_t* svn_client_checkout3(
            NULL,
            repo.URL.absoluteString.UTF8String, // repo URL
            remoteURL.path.UTF8String,
            localURL.path.UTF8String,
            &revision,
            &revision,
            svn_depth_infinity,
            true,
            false,
            context,
            pool
        );
        svn_pool_destroy(pool);
        apr_terminate();
    }

}
*/
