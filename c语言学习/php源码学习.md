CG  
    extern ZEND_API struct _zend_compiler_globals compiler_globals;
    struct _zend_compiler_globals {
        zend_stack loop_var_stack;

        zend_class_entry *active_class_entry;

        zend_string *compiled_filename;

        int zend_lineno;

        zend_op_array *active_op_array;

        HashTable *function_table;	/* function symbol table */
        HashTable *class_table;		/* class table */

        HashTable filenames_table;

        HashTable *auto_globals;

        zend_bool parse_error;
        zend_bool in_compilation;
        zend_bool short_tags;

        zend_bool unclean_shutdown;

        zend_bool ini_parser_unbuffered_errors;

        zend_llist open_files;

        struct _zend_ini_parser_param *ini_parser_param;

        uint32_t start_lineno;
        zend_bool increment_lineno;

        zend_string *doc_comment;
        uint32_t extra_fn_flags;

        uint32_t compiler_options; /* set of ZEND_COMPILE_* constants */

        HashTable const_filenames;

        zend_oparray_context context;
        zend_file_context file_context;

        zend_arena *arena;

        zend_string *empty_string;
        zend_string *one_char_string[256];
        zend_string **known_strings;
        uint32_t    known_strings_count;

        HashTable interned_strings;

        const zend_encoding **script_encoding_list;
        size_t script_encoding_list_size;
        zend_bool multibyte;
        zend_bool detect_unicode;
        zend_bool encoding_declared;

        zend_ast *ast;
        zend_arena *ast_arena;

        zend_stack delayed_oplines_stack;

    #ifdef ZTS
        zval **static_members_table;
        int last_static_member;
    #endif
    };

EG

PG 全局变量宏
# define PG(v) (core_globals.v)
extern ZEND_API struct _php_core_globals core_globals;
#endif
struct _php_core_globals {
    zend_bool implicit_flush;

    zend_long output_buffering;

    zend_bool sql_safe_mode;
    zend_bool enable_dl;

    char *output_handler;

    char *unserialize_callback_func;
    zend_long serialize_precision;

    zend_long memory_limit;
    zend_long max_input_time;

    zend_bool track_errors;
    zend_bool display_errors;
    zend_bool display_startup_errors;
    zend_bool log_errors;
    zend_long      log_errors_max_len;
    zend_bool ignore_repeated_errors;
    zend_bool ignore_repeated_source;
    zend_bool report_memleaks;
    char *error_log;

    char *doc_root;
    char *user_dir;
    char *include_path;
    char *open_basedir;
    char *extension_dir;
    char *php_binary;
    char *sys_temp_dir;

    char *upload_tmp_dir;
    zend_long upload_max_filesize;

    char *error_append_string;
    char *error_prepend_string;

    char *auto_prepend_file;
    char *auto_append_file;

    char *input_encoding;
    char *internal_encoding;
    char *output_encoding;

    arg_separators arg_separator;

    char *variables_order;

    HashTable rfc1867_protected_variables;

    short connection_status;
    short ignore_user_abort;

    unsigned char header_is_being_sent;

    zend_llist tick_functions;

    zval http_globals[6];

    zend_bool expose_php;

    zend_bool register_argc_argv;
    zend_bool auto_globals_jit;

    char *docref_root;
    char *docref_ext;

    zend_bool html_errors;
    zend_bool xmlrpc_errors;

    zend_long xmlrpc_error_number;

    zend_bool activated_auto_globals[8];

    zend_bool modules_activated;
    zend_bool file_uploads;
    zend_bool during_request_startup;
    zend_bool allow_url_fopen;
    zend_bool enable_post_data_reading;
    zend_bool report_zend_debug;

    int last_error_type;
    char *last_error_message;
    char *last_error_file;
    int  last_error_lineno;

    char *php_sys_temp_dir;

    char *disable_functions;
    char *disable_classes;
    zend_bool allow_url_include;
#ifdef PHP_WIN32
    zend_bool com_initialized;
#endif
    zend_long max_input_nesting_level;
    zend_long max_input_vars;
    zend_bool in_user_include;

    char *user_ini_filename;
    zend_long user_ini_cache_ttl;

    char *request_order;

    zend_bool mail_x_header;
    char *mail_log;

    zend_bool in_error_log;

#ifdef PHP_WIN32
    zend_bool windows_show_crt_warning;
#endif
};

PHP_MINFO_FUNCTION(php_core) { /* {{{ */
	php_info_print_table_start();
	php_info_print_table_row(2, "PHP Version", PHP_VERSION);
	php_info_print_table_end();
	DISPLAY_INI_ENTRIES();
}

void  zm_info_php_core(zend_module_entry *zend_module)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "PHP Version", PHP_VERSION);
	php_info_print_table_end();
	DISPLAY_INI_ENTRIES();
}



