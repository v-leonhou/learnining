set rtp+=/home/leon/.cache/vimfiles/repos/github.com/Shougo/deoplete.nvim
set rtp+=/home/leon/.cache/vimfiles/repos/github.com/lvht/phpcd.vim
let g:deoplete#enable_at_startup = 1
let g:deoplete#ignore_sources = get(g:,'deoplete#ignore_sources',{})
let g:deoplete#ignore_sources.php = ['omni']
