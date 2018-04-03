"here some basic customizations, please refer to the top of the vimrc file for all possible options
let g:spacevim_default_indent = 4
"let g:spacevim_max_column     = 80
"let g:spacevim_colorscheme    = 'solarized'
"let g:spacevim_colorscheme    = 'desert'
"let g:spacevim_colorscheme    = 'molokai'
"let g:spacevim_plugin_manager = 'dein'  " neobundle or dein or vim-plug

" change the default directory where all miscellaneous persistent files go
"let g:spacevim_cache_dir = "/home/leon/jjc

"let g:spacevim_buffer_index_type = 1
let g:spacevim_enable_debug = 0
let g:spacevim_debug_level = 1
let g:mapleader = ";"
let g:spacevim_checkinstall = 1
let g:spacevim_sidebar_width = 20
"let g:spacevim_enable_neomake = 0
let g:spacevim_enable_cursorline = 1
let g:spacevim_enable_googlesuggest    = 0
let g:spacevim_enable_vimfiler_gitstatus = 0
""let g:spacevim_simple_mode = 1
" by default, language specific plugins are not loaded.  this can be changed
" with the following:
"let g:spacevim_plugin_groups_exclude = ['c','php', 'javascript']

"" if there are groups you want always loaded, you can use this:
"let g:spacevim_plugin_groups_include = ['go']

" alternatively, you can set this variable to load exactly what you want
"let g:spacevim_plugin_groups = ['core', 'lang']
" if there is a particular plugin you don't like, you can define this variable to disable them entirely
 let g:spacevim_disabled_plugins=['phpfold.vim']
" if you want to add some custom plugins, use this options.
"
 let g:spacevim_custom_plugins = [
             \ ['tomphp/vim-phpdoc'],
             \ ['tsukkee/unite-tag'],
             \ ['SpaceVim/unite-ctags'],
             \ ['vim-php/tagbar-phpctags.vim'],
             \ ]
 nnoremap <C-M> <ESC> :call PhpDoc()<CR>i 
 " \ ['plasticboy/vim-markdown', 'on_ft' : 'markdown'],
 " \ ['wsdjeg/GitHub.vim'],

" " anything defined here are simply overrides
 "set wildignore+=\*/node_modules/\*
 "set guifont=Wingdings:h10
" ]
"
let g:VimQQaccount = '764436364'
"let g:spacevim_force_global_config = 1
let g:spacevim_lint_on_save = 1
let g:spacevim_lint_on_the_fly = 1
let g:indentLine_faster = 1
let g:spacevim_github_username = "764436364@qq.com"

let g:deoplete#ignore_sources = {}
let g:deoplete#ignore_sources.php = []
let g:deoplete#enable_profile = 1

call SpaceVim#layers#load('git')
call SpaceVim#layers#load('tags')
call SpaceVim#layers#load('unite')
call SpaceVim#layers#load('denite')
call SpaceVim#layers#load('edit')
" call SpaceVim#layers#load('lang#go')
set mouse=
call SpaceVim#layers#load('lang#c')
call SpaceVim#layers#load('lang#php')
call SpaceVim#layers#load('lang#sh')
