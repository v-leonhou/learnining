
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_fastcgi.h"

/* If you declare any globals in php_fastcgi.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(fastcgi)
*/

/* True global resources - no need for thread safety here */
static int le_fastcgi;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("fastcgi.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_fastcgi_globals, fastcgi_globals)
    STD_PHP_INI_ENTRY("fastcgi.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_fastcgi_globals, fastcgi_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_fastcgi_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_fastcgi_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "fastcgi", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_fastcgi_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_fastcgi_init_globals(zend_fastcgi_globals *fastcgi_globals)
{
	fastcgi_globals->global_value = 0;
	fastcgi_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(fastcgi)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(fastcgi)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(fastcgi)
{
#if defined(COMPILE_DL_FASTCGI) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(fastcgi)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(fastcgi)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "fastcgi support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ fastcgi_functions[]
 *
 * Every user visible function must have an entry in fastcgi_functions[].
 */
const zend_function_entry fastcgi_functions[] = {
	PHP_FE(confirm_fastcgi_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in fastcgi_functions[] */
};
/* }}} */

/* {{{ fastcgi_module_entry
 */
zend_module_entry fastcgi_module_entry = {
	STANDARD_MODULE_HEADER,
	"fastcgi",
	fastcgi_functions,
	PHP_MINIT(fastcgi),
	PHP_MSHUTDOWN(fastcgi),
	PHP_RINIT(fastcgi),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(fastcgi),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(fastcgi),
	PHP_FASTCGI_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_FASTCGI
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(fastcgi)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
